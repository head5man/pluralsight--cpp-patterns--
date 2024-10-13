#pragma once
#include "TicketType.h"
#include "Venue.h"
#include "VenueType.h"
class Ticket
{
private:
  TicketType _ticketType;
  VenueType _venueType;
  int _numberOfSeats;
protected:
  static int count;
public:
  ~Ticket();
  Ticket(TicketType type, VenueType venueType, int numberOfSeats);
  Ticket() = default;

  TicketType getTicketType() const { return _ticketType; }
  VenueType getVenueType() const { return _venueType; }
  int getNumberOfSeats() const { return _numberOfSeats; }
  int setNumberOfSeats(int seats) { _numberOfSeats = seats; }
  int setVenueType(int venueType) { _venueType = (VenueType)venueType; }
  int setTicketType(int ticketType) { _ticketType = (TicketType)ticketType; }
};

