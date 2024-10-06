#include "BookVenueCommand.h"

void BookVenueCommand::Execute()
{
  _numberOfRemainingSeats = _venue->BookSeats(_numberOfSeatsToBook, _ticketType);
}

bool BookVenueCommand::CanExecute()
{
  auto numberOfRemainingSeats = _venue->getNumberOfAvailableSeats(_ticketType);
  return (_numberOfRemainingSeats > 0 && numberOfRemainingSeats >= _numberOfSeatsToBook);
}

BookVenueCommand::BookVenueCommand(Venue* venue, int numberOfSeatsToBook, TicketType ticketType)
  : _venue(venue), _numberOfSeatsToBook(numberOfSeatsToBook), _ticketType(ticketType)
{
}
