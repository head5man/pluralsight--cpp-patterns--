#pragma once
#include <vector>
#include "Venue.h"
#include "../Handlers/PriceHandler.h"
class TicketManager
{
private:
	std::vector<Ticket> _tickets;
	PriceHandler* _priceHandler;
	Venue* _hugeTheatre;
	Venue* _largeTheatre;
	Venue* _smallTheatre;
	void TakeInteger(int& integer);
  Venue* getVenueByVenueType(VenueType venueType);
public:
	TicketManager();
	void BookSeats();
	void HandleTotalPrice();
	void ClearTickets();
};

