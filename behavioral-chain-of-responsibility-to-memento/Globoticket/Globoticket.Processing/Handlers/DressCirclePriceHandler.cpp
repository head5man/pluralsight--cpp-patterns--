#include "DressCirclePriceHandler.h"
#include <cstddef>

double DressCirclePriceHandler::HandlePrice(const Ticket& ticket)
{
    if (ticket.getTicketType() == TicketType::dressCircle)
    {
      return _basePrice * ticket.getNumberOfSeats();
    }

    return NULL;
}
