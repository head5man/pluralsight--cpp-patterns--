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
  Venue* _venue;
public:
  VenueExpression(std::string name, VenueType venueType, Venue* venue, std::shared_ptr<Ticket> ticket)
    : BookingExpression(name, ticket, ExpressionType::NonTerminal), _venueType(venueType), _venue(venue)
  {

  }

  virtual std::shared_ptr<Ticket> Interpret(Context<int>& context) override;
  virtual int GetValue() override;
};