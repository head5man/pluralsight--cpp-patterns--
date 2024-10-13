#include "VenueExpression.h"

std::shared_ptr<Ticket> VenueExpression::Interpret(Context<int>& context)
{
  _ticket = BookingExpression::Interpret(context);
  _venue->BookSeats(_ticket->getNumberOfSeats(), _ticket->getTicketType());
  _ticket->setVenueType(context.Lookup(_name));
  return _ticket;
}

int VenueExpression::GetValue()
{
  return (int)_venueType;
}
