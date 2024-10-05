#include "PremiumPriceHandler.h"
#include <cstddef>

double PremiumPriceHandler::HandlePrice(Ticket ticket)
{
    if (ticket.getTicketType() == TicketType::premium)
    {
      return (_basePrice * 2.0) * ticket.getNumberOfSeats();
    }

    return NULL;
}
