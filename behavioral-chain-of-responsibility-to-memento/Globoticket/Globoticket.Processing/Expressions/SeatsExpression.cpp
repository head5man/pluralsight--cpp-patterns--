#include "SeatsExpression.h"

std::shared_ptr<Ticket> SeatsExpression::Interpret(Context<int>& context)
{
  _ticket = BookingExpression::Interpret(context);
  _ticket->setNumberOfSeats(context.Lookup(_name));
  return _ticket;
}

int SeatsExpression::GetValue()
{
  return _numberOfSeats;
}
