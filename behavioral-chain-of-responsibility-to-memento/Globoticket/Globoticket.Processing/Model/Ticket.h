#pragma once
#include "TicketType.h"
class Ticket
{
private:
	TicketType _ticketType;
	int _numberOfSeats;

public:
	Ticket(TicketType type, int numberOfSeats);

	TicketType getTicketType() { return _ticketType; }
	int getNumberOfSeats() { return _numberOfSeats; }
};

