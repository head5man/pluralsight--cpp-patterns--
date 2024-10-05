#pragma once
#include "TicketType.h"
#include "Venue.h"
#include "VenueType.h"
class Ticket
{
private:
	TicketType _ticketType;
	VenueType _venueType;
	int _numberOfSeats;

public:
	Ticket(TicketType type, VenueType venueType, int numberOfSeats);

	TicketType getTicketType() { return _ticketType; }
	VenueType getVenueType() { return _venueType; }
	int getNumberOfSeats() { return _numberOfSeats; }
};

