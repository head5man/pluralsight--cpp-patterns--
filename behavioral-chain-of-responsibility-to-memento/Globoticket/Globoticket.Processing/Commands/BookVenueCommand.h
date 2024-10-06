#pragma once
#include "Command.h"
#include "..\Model\Venue.h"

class BookVenueCommand :
    public Command
{
private:
  Venue* _venue;
  int _numberOfSeatsToBook, _numberOfRemainingSeats;
  TicketType _ticketType;
public:
  virtual void Execute() override;
  virtual bool CanExecute() override;
  BookVenueCommand(Venue* venue, int numberOfSeatsToBook, TicketType ticketType);
  int GetNumberOfRemainingSeats() { return _numberOfRemainingSeats; }
};

