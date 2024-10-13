#pragma once

#include "../Model/Ticket.h"
#include "Context.h"
#include "BookingExpression.h"

class TicketExpression : public BookingExpression
{
private:
  TicketType _ticketType;
public:
  TicketExpression(std::string name, TicketType ticketType, std::shared_ptr<Ticket> ticket)
    : BookingExpression(name, ticket, ExpressionType::NonTerminal), _ticketType(ticketType)
  {
  }

  virtual std::shared_ptr<Ticket> Interpret(Context<int>& context) override;

  virtual int GetValue() override;
};