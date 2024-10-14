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
}

void TicketManager::BookSeats()
{
	int numberOfSeatsToBook;
	std::cout << fmt::format("How many seats would you like to reserve?\n");

	TakeInteger(numberOfSeatsToBook);

	int typeOfTicketInt = 0;

	while (typeOfTicketInt < 1 || typeOfTicketInt > 3)
	{
		std::cout << fmt::format("Which type of ticket would you "
			"like to reserve?\n");
		std::cout << fmt::format("1: Premium\n");
		std::cout << fmt::format("2: Stalls\n");
		std::cout << fmt::format("3: Dress Circle\n");

		TakeInteger(typeOfTicketInt);
	}

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
	double totalPrice = _priceHandler->HandleTotalPrice(_tickets);
	int totalNumberOfSeats = 0;
	for (auto const& ticket : _tickets)
	{
		totalNumberOfSeats += ticket->getNumberOfSeats();
	}

	std::cout << fmt::format("You reserved a total {0} tickets for {1} seats "
		"with a total cost of {2} dollars. \n",
		_tickets.size(),
		totalNumberOfSeats,
		totalPrice);
}

void TicketManager::HandleFreeText()
{
  std::cout << "Enter expression - {action} {number} {venue} {ticket type}\n";
  std::string expression;
  TakeExpression(expression);
  std::cout << "<- " << expression << std::endl;
}

void TicketManager::ClearTickets()
{
	_tickets.clear();
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

void TicketManager::TakeInteger(int& integer)
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
		else break;
	}
}

void TicketManager::TakeExpression(std::string& expression)
{
  std::getline(std::cin, expression);
}
