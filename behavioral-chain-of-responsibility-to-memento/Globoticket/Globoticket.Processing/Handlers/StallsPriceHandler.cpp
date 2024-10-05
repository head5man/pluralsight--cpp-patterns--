#include "StallsPriceHandler.h"
#include <cstddef>

double StallsPriceHandler::HandlePrice(Ticket ticket)
{
    if (ticket.getTicketType() == TicketType::stalls)
    {
      return _basePrice * ticket.getNumberOfSeats() * 1.5;
    }

    return NULL;
}
