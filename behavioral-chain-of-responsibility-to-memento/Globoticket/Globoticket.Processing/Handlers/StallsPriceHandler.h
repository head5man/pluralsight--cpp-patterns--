#pragma once
#include "PriceReceiver.h"

class StallsPriceHandler :
    public PriceReceiver
{
public:
  virtual double HandlePrice(Ticket ticket) override;
};

