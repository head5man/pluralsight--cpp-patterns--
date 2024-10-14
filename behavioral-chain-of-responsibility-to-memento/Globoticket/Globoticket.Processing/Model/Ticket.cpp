#include "Ticket.h"

#include <iostream>

int Ticket::count = 0;

Ticket::~Ticket()
{
  std::cout << "~Ticket #" << std::to_string(--count) << std::endl;
}

Ticket::Ticket(TicketType ticketType, VenueType venueType, int numberOfSeats)
{
  count++;
	_ticketType = ticketType;
	_venueType = venueType;
	_numberOfSeats = numberOfSeats;
}

Ticket::Ticket()
{
  count++;
}

