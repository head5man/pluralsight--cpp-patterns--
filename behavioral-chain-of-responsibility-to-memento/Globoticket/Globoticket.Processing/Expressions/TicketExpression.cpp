#include "TicketExpression.h"

std::shared_ptr<Ticket> TicketExpression::Interpret(Context<int>& context)
{
  _ticket = BookingExpression::Interpret(context);
  _ticket->setTicketType((TicketType)context.Lookup(_name));
  return _ticket;
}

int TicketExpression::GetValue() const
{
  return (int)_ticketType;
}
