#pragma once

#include "EnumType.h"
#include "BookingExpression.h"

#include "../Model/Ticket.h"
#include "../Model/VenueType.h"
#include "../Model/Venue.h"

class VenueExpression : public BookingExpression
{
private:
  VenueType _venueType;
public:
  VenueExpression(std::string name, std::shared_ptr<Ticket> ticket)
    : BookingExpression(ExpressionNames::VenueName, ticket, ExpressionType::NonTerminal), _venueType(VenueTypeConverter::FromToken(name))
  {

  }

  virtual std::shared_ptr<Ticket> Interpret(Context<int>& context) override;

  virtual int GetValue() const override;

  static bool IsValidToken(std::string token)
  {
    return VenueTypeConverter::IsValidToken(token);
  }
};