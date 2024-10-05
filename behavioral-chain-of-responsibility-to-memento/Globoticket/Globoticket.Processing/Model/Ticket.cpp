#include "Ticket.h"
Ticket::Ticket(TicketType ticketType, VenueType venueType, int numberOfSeats)
{
	_ticketType = ticketType;
	_venueType = venueType;
	_numberOfSeats = numberOfSeats;
}
