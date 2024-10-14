#include "ActionExpression.h"

int ActionExpression::GetValue() const
{
  return _actionType;
}

std::shared_ptr<Ticket> ActionExpression::Interpret(Context<int>& context)
{
  VenueType venueType = (VenueType)context.Lookup(ExpressionNames::VenueName);
  Venue* venue = _getVenueByType(venueType);
  auto ticket = BookingExpression::Interpret(context);
  venue->BookSeats(ticket->getNumberOfSeats(), ticket->getTicketType());
  return ticket;
}
