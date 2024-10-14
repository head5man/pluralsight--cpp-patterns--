#pragma once
#include "AbstractExpression.h"
#include "../Model/Ticket.h"

#include <memory>

class ExpressionNames
{
public:
  static constexpr const char* const VenueName = "venue";
};

class BookingExpression : public AbstractExpression<Ticket, int>
{
protected:
  std::shared_ptr<Ticket> _ticket;
public:
  BookingExpression(std::string name, std::shared_ptr<Ticket> ticket, ExpressionType type)
    : AbstractExpression(name, type, ticket)
  {
    _ticket = ticket;
  }

  ~BookingExpression()
  {
    _ticket.reset();
  }
};

