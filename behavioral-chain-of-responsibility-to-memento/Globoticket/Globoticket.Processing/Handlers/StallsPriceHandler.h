#pragma once
#include "PriceReceiver.h"

class StallsPriceHandler :
    public PriceReceiver
{
public:
  virtual double HandlePrice(const Ticket& ticket) override;
};

