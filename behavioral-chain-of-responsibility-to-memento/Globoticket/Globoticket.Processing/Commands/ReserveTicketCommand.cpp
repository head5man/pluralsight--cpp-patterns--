#include "ReserveTicketCommand.h"
#include "..\Model\Venue.h"

#include <iostream>
#include <fmt/core.h>

bool ReserveTicketCommand::Execute()
{
  bool canExecute = CanExecute();
  if (canExecute)
  {
    Ticket ticket(_ticketType, _venueType, _numberOfSeatsToBook);

    double ticketPrice = _priceHandler->HandlePrice(ticket);

    _tickets->push_back(ticket);

    std::cout << fmt::format("You reserved a ticket for {0} seats "
      "at the {1} venue in the {2} area which costs {3} dollars. \n",
      ticket.getNumberOfSeats(), to_string(ticket.getVenueType()), to_string(ticket.getTicketType()),
      ticketPrice);
  }
  return canExecute;
}

ReserveTicketCommand::ReserveTicketCommand(std::vector<Ticket>* tickets, PriceHandler* priceHandler, TicketType ticketType, VenueType venueType, int numberOfSeatsToBook)
  : Command(),
  _tickets(tickets),
  _priceHandler(priceHandler),
  _ticketType(ticketType),
  _venueType(venueType), _numberOfSeatsToBook(numberOfSeatsToBook)
{

}
