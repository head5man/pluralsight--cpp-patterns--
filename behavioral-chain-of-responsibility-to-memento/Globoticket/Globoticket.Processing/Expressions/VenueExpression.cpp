#include "VenueExpression.h"

std::shared_ptr<Ticket> VenueExpression::Interpret(Context<int>& context)
{
  _ticket = BookingExpression::Interpret(context);
  _ticket->setVenueType(context.Lookup(_name));
  return _ticket;
}

int VenueExpression::GetValue() const
{
  return (int)_venueType;
}
