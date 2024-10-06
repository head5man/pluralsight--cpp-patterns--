#pragma once
#include "Command.h"
#include "..\Model\Venue.h"

class BookVenueCommand :
    public Command
{
private:
  Venue* _venue;
  int _numberOfSeatsToBook;
  int _numberOfRemainingSeats;
  TicketType _ticketType;
  BookVenueCommand() = delete;
  BookVenueCommand(const BookVenueCommand&&) = delete;
public:
  virtual bool Execute() override;
  virtual bool CanExecute() override;
  BookVenueCommand(Venue* venue, int numberOfSeatsToBook, TicketType ticketType);
  int GetNumberOfRemainingSeats() { return _numberOfRemainingSeats; }
};

