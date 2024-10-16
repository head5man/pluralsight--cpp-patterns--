#pragma once

#include "Venue.h"
#include "../Handlers/PriceHandler.h"
#include "../Commands/Command.h"
#include "../Expressions/BookingExpression.h"
#include "../Iterators/TicketAggregate.h"
#include "../Mediators/NotificationMediator.h"
#include "../Business/UserSettings.h"
#include "../Business/ColorChanger.h"
#include <vector>
#include <stack>
#include <memory>

class TicketManager
{
private:
  TicketAggregate _tickets;
  std::stack<std::unique_ptr<Command>> _commands;
  std::stack<std::shared_ptr<UserSettingsMemento>> _undoStack;
  std::stack<std::shared_ptr<UserSettingsMemento>> _redoStack;
  std::unique_ptr<NotificationMediator> _notificationMediator;
  UserSettings _userSettings;
  PriceHandler* _priceHandler;
  ColorChanger _colorChanger;
  Venue* _hugeTheatre;
  Venue* _largeTheatre;
  Venue* _smallTheatre;
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
  void ListAllTicketsBySeatType();

  void NotifyPrinting();
  void NotifyAccounting();

  void SetColor();
  void UndoColor(bool redo = false);

  // will tokenize the input and lex the tokens into expression syntax tree
  std::vector<std::shared_ptr<BookingExpression>> Lex(const std::string input, std::shared_ptr<Ticket> ticket);

  // will parse the context from the expression syntax tree
  void Parse(const std::vector<std::shared_ptr<BookingExpression>>& tree, Context<int>& context);

  void DisplayTicketInformation(std::shared_ptr<Ticket> ticket);
};

