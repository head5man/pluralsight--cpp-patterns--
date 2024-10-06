#pragma once
#include "../Model/Ticket.h"

class PriceReceiver
{
protected:
  double _basePrice = 30.0;
public:
  virtual double HandlePrice(const Ticket& ticket) = 0;
};