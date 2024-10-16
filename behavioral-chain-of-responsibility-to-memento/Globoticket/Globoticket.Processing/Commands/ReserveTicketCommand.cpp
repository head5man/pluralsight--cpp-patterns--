#include "ReserveTicketCommand.h"
#include "..\Model\Venue.h"

#include <iostream>
#include <fmt/core.h>

bool ReserveTicketCommand::Execute()
{
  bool canExecute = CanExecute();
  if (canExecute)
  {
    _ticket = std::make_shared<Ticket>(_ticketType, _venueType, _numberOfSeatsToBook);
    
    double ticketPrice = _priceHandler->HandlePrice(*_ticket);

    std::cout << fmt::format("You reserved a ticket for {0} seats "
      "at the {1} venue in the {2} area which costs {3} dollars. \n",
      _ticket->getNumberOfSeats(), to_string(_ticket->getVenueType()), to_string(_ticket->getTicketType()),
      ticketPrice);
    _tickets.Push(_ticket);
  }
  return canExecute;
}

void ReserveTicketCommand::Undo()
{
  if (_ticket == nullptr)
  {
    Command::Undo();
    return;
  }
  
  double ticketPrice = _priceHandler->HandlePrice(*_ticket);

  // delete last ticket
  _tickets.Pop();

  std::cout << fmt::format("You undid reserved a ticket for {0} seats "
    "at the {1} venue in the {2} area which costs {3} dollars. \n",
    _ticket->getNumberOfSeats(), to_string(_ticket->getVenueType()), to_string(_ticket->getTicketType()),
    ticketPrice);
  _ticket.reset();
}

ReserveTicketCommand::~ReserveTicketCommand()
{
  if (_ticket)
    _ticket.reset();
}

ReserveTicketCommand::ReserveTicketCommand(TicketAggregate& tickets, PriceHandler* priceHandler, TicketType ticketType, VenueType venueType, int numberOfSeatsToBook)
  : Command(),
  _tickets(tickets),
  _priceHandler(priceHandler),
  _ticketType(ticketType),
  _venueType(venueType), _numberOfSeatsToBook(numberOfSeatsToBook)
{

}
