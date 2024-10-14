#pragma once
#include "BookingExpression.h"
#include "AbstractExpression.h"
#include "ActionType.h"

class ActionExpression :
    public BookingExpression
{
private:
  ActionType _actionType;
public:
  ActionExpression(std::string name, ActionType type, std::shared_ptr<Ticket> ticket)
    : BookingExpression(name, ticket, ExpressionType::NonTerminal), _actionType(type)
  { }

  virtual int GetValue() const override;

};

