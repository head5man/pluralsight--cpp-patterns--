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
protected:
  static int count;
public:
  ~Ticket();
	Ticket(TicketType type, VenueType venueType, int numberOfSeats);

	TicketType getTicketType() const { return _ticketType; }
	VenueType getVenueType() const { return _venueType; }
	int getNumberOfSeats() const { return _numberOfSeats; }
};

