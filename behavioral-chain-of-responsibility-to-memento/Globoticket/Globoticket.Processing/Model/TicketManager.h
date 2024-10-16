#pragma once

#include "Venue.h"
#include "../Handlers/PriceHandler.h"
#include "../Commands/Command.h"
#include "../Expressions/BookingExpression.h"
#include "../Iterators/TicketAggregate.h"

#include <vector>
#include <stack>
#include <memory>

class TicketManager
{
private:
  TicketAggregate _tickets;
  std::stack<std::unique_ptr<Command>> _commands;
  PriceHandler* _priceHandler;
  Venue* _hugeTheatre;
  Venue* _largeTheatre;
  Venue* _smallTheatre;
  void TakeInteger(int& integer);
  void TakeExpression(std::string& expression);
  Venue* getVenueByVenueType(VenueType venueType);

public:
  TicketManager();
  void BookSeats();
  void HandleTotalPrice();
  void HandleFreeText();
  void ClearTickets();
  void UndoReservation();
  void ListAllTickets();

  // will tokenize the input and lex the tokens into expression syntax tree
  std::vector<std::shared_ptr<BookingExpression>> Lex(const std::string input, std::shared_ptr<Ticket> ticket);

  // will parse the context from the expression syntax tree
  void Parse(const std::vector<std::shared_ptr<BookingExpression>>& tree, Context<int>& context);

  void DisplayTicketInformation(std::shared_ptr<Ticket> ticket);
};

