#pragma once
#include "PriceReceiver.h"

class PremiumPriceHandler :
    public PriceReceiver
{
public:
  virtual double HandlePrice(const Ticket& ticket) override;
};

