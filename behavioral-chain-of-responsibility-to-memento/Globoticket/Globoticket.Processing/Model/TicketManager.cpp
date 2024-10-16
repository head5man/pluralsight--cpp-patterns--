#include "TicketManager.h"
#include "../Handlers/PriceHandler.h"
#include "../Handlers/PremiumPriceHandler.h"
#include "../Handlers/DressCirclePriceHandler.h"
#include "../Handlers/StallsPriceHandler.h"
#include "../Commands/BookVenueCommand.h"
#include "../Commands/ReserveTicketCommand.h"
#include "../Commands/MacroCommand.h"
#include "../Expressions/BookingExpressions.h"
#include "../lambda/CPP20LambdaCapture.h"
#include <iostream>
#include <fmt/core.h>

namespace {
  void ShowTickets(std::shared_ptr<TicketIterator> it, PriceHandler* priceHandler)
  {
    std::cout << "Venue\tType of seats\tNumber of seats\tPrice\n";
    std::cout << "------\t------\t\t------\t\t------\n";
    for (it->First(); it->IsDone() == false; it->Next())
    {
      auto ticket = *(it->CurrentItem());
      double price = priceHandler->HandlePrice(*ticket);
      auto str = ticket->ToString("{1:8}{2:16}{0:<16}");
      std::cout << fmt::format("{0}{1}\n",
        str,
        price);
    }
  }

  void TakeInteger(int& integer, int maxNumber = 0)
  {
    while (true)
    {
      std::cin >> integer;

      // Check that the user entered an integer
      if (!std::cin)
      {
        std::cout << "Please enter an integer number " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      else if (maxNumber > 0 && integer > maxNumber)
      {
        std::cout << "Please enter an integer number that is no higher than " << maxNumber << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      else break;
    }
  }

  int TakeTicketType(const char* postfix = "reserve?", bool exitZero = false, const char* querybody =
    "Which type of ticket would you like to"
    )
  {
    int typeOfTicketInt = -1;

    while (typeOfTicketInt < (exitZero ? 0 : 1) || typeOfTicketInt > 3)
    {
      std::cout << fmt::format("{0} {1}\n", querybody, postfix);
      std::cout << (exitZero ? "0: Exit\n" : "");
      std::cout << fmt::format("1: Premium\n");
      std::cout << fmt::format("2: Stalls\n");
      std::cout << fmt::format("3: Dress Circle\n");

      TakeInteger(typeOfTicketInt);
    }

    return typeOfTicketInt;
  }

}

TicketManager::TicketManager()
{
  // Setup venues
  _hugeTheatre = new Venue(huge);
  _largeTheatre = new Venue(large);
  _smallTheatre = new Venue(small);

  // Setup price handling chain
  _priceHandler = new PriceHandler;
  DressCirclePriceHandler* dcPriceHandler = new DressCirclePriceHandler;
  StallsPriceHandler* sPriceHandler = new StallsPriceHandler;
  PremiumPriceHandler* pPriceHandler = new PremiumPriceHandler;

  _priceHandler
    ->SetNext(dcPriceHandler)
    ->SetNext(sPriceHandler)
    ->SetNext(pPriceHandler);

  _notificationMediator = std::make_unique<NotificationMediator>();
  _notificationMediator->CreateNotifiers(_tickets);
}

void TicketManager::BookSeats()
{
  int numberOfSeatsToBook;
  std::cout << fmt::format("How many seats would you like to reserve?\n");

  TakeInteger(numberOfSeatsToBook);

  int typeOfTicketInt = TakeTicketType();

  int typeOfVenueInt = 0;

  while (typeOfVenueInt < 1 || typeOfVenueInt > 3)
  {
    std::cout << fmt::format("At what type of venue would you "
      "like to reserve?\n");
    std::cout << fmt::format("1: Huge\n");
    std::cout << fmt::format("2: Large\n");
    std::cout << fmt::format("3: Small\n");

    TakeInteger(typeOfVenueInt);
  }

  TicketType ticketType = (TicketType)typeOfTicketInt;
  VenueType venueType = (VenueType)typeOfVenueInt;
  int numberOfRemainingSeats = 0;

  try
  {
    auto command = std::make_unique<MacroCommand>();
    Venue* venue = getVenueByVenueType(venueType);
    auto book = std::make_unique<BookVenueCommand>(venue, numberOfSeatsToBook, ticketType);
    auto reserve = std::make_unique<ReserveTicketCommand>(_tickets, _priceHandler, ticketType, venueType, numberOfSeatsToBook);
    command->Add(std::move(book));
    command->Add(std::move(reserve));

    if (command->Execute() == false)
    {
      std::cout << "No tickets booked\n";
      return;
    }
    _commands.push(std::move(command));
  }
  catch (std::runtime_error& e)
  {
    std::cout << e.what() << "No tickets booked\n";
  }
}

Venue* TicketManager::getVenueByVenueType(VenueType venueType)
{
  switch (venueType)
  {
  case small:
    return _smallTheatre;
  case large:
    return _largeTheatre;
  case huge:
    return _hugeTheatre;
  }
  throw std::runtime_error("Selected venue not currently available");
}

void TicketManager::HandleTotalPrice()
{
  auto it = _tickets.CreateIterator();
  double totalPrice = _priceHandler->HandleTotalPrice(*it);
  int totalNumberOfSeats = 0;
  for (it->First(); it->IsDone() == false; it->Next())
  {
    auto ticket = *it->CurrentItem();
    totalNumberOfSeats += ticket->getNumberOfSeats();
  }

  std::cout << fmt::format("You reserved a total {0} tickets for {1} seats "
    "with a total cost of {2} dollars. \n",
    _tickets.Count(),
    totalNumberOfSeats,
    totalPrice);
}

void TicketManager::HandleFreeText()
{
  try
  {
    while (true)
    {
      std::cout << "Enter expression - {action} {number} {venue} {ticket type}\n";
      std::string expression;
      TakeExpression(expression);
      std::cout << "<- " << expression << std::endl;
      auto expressionTree = Lex(expression, std::make_shared<Ticket>());
      if (expressionTree.empty())
        return;
      Context<int> context;
      Parse(expressionTree, context);

      auto action = expressionTree.front();
      auto ticket = action->Interpret(context);
      ActionType actionType = action->GetValue();

      if (actionType == ActionType::Reserve)
      {
        _tickets.Push(ticket);
        DisplayTicketInformation(ticket);
      }
    }
  }
  catch (std::runtime_error& e)
  {
    std::cout << e.what() << "\n";
  }
}

void TicketManager::ClearTickets()
{
  _tickets.Clear();
  while (_commands.size() > 0)
  {
    auto cmd = std::move(_commands.top());
    _commands.pop();
  }
  std:: cout << "All ticket reservations have been cleared.\n";
}

void TicketManager::UndoReservation()
{
  if (_commands.empty())
  {
    std::cout << "No reservation(s) to undo.\n";
    return;
  }

  auto command = std::move(_commands.top());
  _commands.pop();
  command->Undo();
}

void TicketManager::ListAllTickets()
{
  auto it = _tickets.CreateIterator();
  ShowTickets(it, _priceHandler);
}

void TicketManager::ListAllTicketsBySeatType()
{
  while (int selection = TakeTicketType("list tickets for?", true))
  {
    if (selection <= 0)
      break;
    auto it = _tickets.CreateFilterIterator([selection](std::shared_ptr<Ticket> ticket) { return ticket->getTicketType() == selection; });
    ShowTickets(it, _priceHandler);
  }
}

void TicketManager::NotifyPrinting()
{
  _notificationMediator->CallNotifier(NotificationType::printing);
}

void TicketManager::NotifyAccounting()
{
  _notificationMediator->CallNotifier(NotificationType::accounting);
}


std::vector<std::shared_ptr<BookingExpression>> TicketManager::Lex(const std::string input, std::shared_ptr<Ticket> ticket)
{
  const char* delim = " ";
  std::vector<std::shared_ptr<BookingExpression>> expressionTree;
  std::locale loc;
  std::string lowerCaseInput = "";
  for (auto c : input)
    lowerCaseInput += std::tolower(c);
  
  char* nextToken = &lowerCaseInput[0];

  char* token = strtok_s(nextToken, delim, &nextToken);
  bool startsWithAction = false;
  try
  {
    while (token != nullptr)
    {
      if (!startsWithAction)
      {
        if (ActionExpression::IsValidToken(token) == false)
        {
          throw std::runtime_error("Invalid statement. Statement must start with an action.");
        }

        startsWithAction = true;
        auto func = lambda_to_pointer([this](VenueType v) -> Venue* { return getVenueByVenueType(v); });
        auto expression = std::make_shared<ActionExpression>(std::string(token), ticket, func);
        expressionTree.push_back(expression);
      }
      else
      {
        std::string tokenString(token);

        if (TicketExpression::IsValidToken(tokenString))
        {
          auto expression = std::make_shared<TicketExpression>(tokenString, ticket);
          expressionTree.push_back(expression);
        }
        else if (VenueExpression::IsValidToken(tokenString))
        {
          auto expression = std::make_shared<VenueExpression>(tokenString, ticket);
          expressionTree.push_back(expression);
        }
        else
        {
          bool isNumerical = (tokenString.find_first_not_of("01234567890") == std::string::npos);
          if (isNumerical)
          {
            int tokenInt = std::stoi(tokenString);
            auto expression = std::make_shared<SeatsExpression>(tokenString, tokenInt, ticket);
            expressionTree.push_back(expression);
          }
          else
          {
            throw std::runtime_error("Unrecognized token");
          }
        }
      }

      token = strtok_s(NULL, delim, &nextToken);
    }

    return expressionTree;
  }
  catch (std::runtime_error&)
  {
    throw;
  }
}

void TicketManager::Parse(const std::vector<std::shared_ptr<BookingExpression>>& tree, Context<int>& context)
{
  std::shared_ptr<BookingExpression> prev = nullptr;
  bool firstRun = true;

  for (const auto& next : tree)
  {
    std::string name = next->GetName();
    int value = next->GetValue();

    context.Assign(name, value);

    if (!firstRun && prev->GetExpressionType() == ExpressionType::NonTerminal)
    {
      prev->AddChild(next);
    }

    firstRun = false;

    if (next->GetExpressionType() == ExpressionType::NonTerminal)
    {
      prev = next;
    }
  }
}

void TicketManager::TakeExpression(std::string& expression)
{
  std::getline(std::cin, expression);
}

void TicketManager::DisplayTicketInformation(std::shared_ptr<Ticket> ticket)
{
  double ticketPrice = _priceHandler->HandlePrice(*ticket);
  std::cout << fmt::format("You reserved a {0} which costs {1} dollars.\n",
    ticket->ToString(),
    ticketPrice);
}
