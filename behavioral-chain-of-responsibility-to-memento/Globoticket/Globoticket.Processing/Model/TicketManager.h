#pragma once

#include "Venue.h"
#include "../Handlers/PriceHandler.h"
#include "../Commands/Command.h"

#include <vector>
#include <stack>
#include <memory>

class TicketManager
{
private:
	std::vector<std::shared_ptr<Ticket>> _tickets;
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
};

