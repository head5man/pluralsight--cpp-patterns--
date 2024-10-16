#include "Ticket.h"

#include <iostream>
#include <fmt/core.h>

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

std::string Ticket::ToString(const char* formatSeatsVenueArea)
{
  if (formatSeatsVenueArea == nullptr)
  {
    formatSeatsVenueArea =
      "ticket for {0} seats "
      "at the {1} venue "
      "in the {2} area";
  }

  return fmt::format(
    formatSeatsVenueArea,
    getNumberOfSeats(), to_string(getVenueType()), to_string(getTicketType()));
}
