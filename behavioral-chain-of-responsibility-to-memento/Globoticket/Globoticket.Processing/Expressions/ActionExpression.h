#pragma once
#include "BookingExpression.h"
#include "AbstractExpression.h"
#include "ActionType.h"

typedef Venue* (*fVenueGetter)(VenueType);

class ActionExpression :
    public BookingExpression
{
private:
  ActionType _actionType;
  fVenueGetter _getVenueByType;
public:
  ActionExpression(std::string name, std::shared_ptr<Ticket> ticket, fVenueGetter getVenueByType)
    : BookingExpression(name, ticket, ExpressionType::NonTerminal), _actionType(name.c_str()), _getVenueByType(getVenueByType)
  { }

  virtual int GetValue() const override;

  virtual std::shared_ptr<Ticket> Interpret(Context<int>& context) override;

  static bool IsValidToken(std::string token)
  {
    return EnumType::IsValidToken<ActionType>(token);
  }
};

