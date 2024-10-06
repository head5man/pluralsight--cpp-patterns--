#include "BookVenueCommand.h"
#include <iostream>

bool BookVenueCommand::Execute()
{
  bool canExecute = CanExecute();
  if (canExecute)
    _numberOfRemainingSeats = _venue->BookSeats(_numberOfSeatsToBook, _ticketType);
  return canExecute;
}

bool BookVenueCommand::CanExecute()
{
  auto numberOfRemainingSeats = _venue->getNumberOfAvailableSeats(_ticketType);
  return (_numberOfRemainingSeats > 0 && numberOfRemainingSeats >= _numberOfSeatsToBook);
}

BookVenueCommand::BookVenueCommand(Venue* venue, int numberOfSeatsToBook, TicketType ticketType)
{
  try
  {
    //venue->ThrowIfNotEnoughSeatsAvailable(ticketType, numberOfSeatsToBook);
    _venue = venue;
    _numberOfSeatsToBook = numberOfSeatsToBook;
    _ticketType = ticketType;
    _numberOfRemainingSeats = _venue->getNumberOfAvailableSeats(_ticketType);
  }
  catch (std::runtime_error& e)
  {
    std::cout << "Constructing BookVenueCommand failed\n";
    throw;
  }
}
