#pragma once
#include "BookingExpression.h"

#include <memory>

class SeatsExpression : public BookingExpression
{
  int _numberOfSeats;
public:
  SeatsExpression(std::string name, int numberOfSeats, std::shared_ptr<Ticket> ticket)
    : BookingExpression(name, ticket, ExpressionType::Terminal), _numberOfSeats(numberOfSeats)
  {
  }

  virtual std::shared_ptr<Ticket> Interpret(Context<int>& context) override;

  virtual int GetValue() override;

};