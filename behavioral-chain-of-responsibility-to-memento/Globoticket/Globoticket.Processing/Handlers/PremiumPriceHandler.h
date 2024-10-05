#pragma once
#include "PriceReceiver.h"

class PremiumPriceHandler :
    public PriceReceiver
{
public:
  virtual double HandlePrice(Ticket ticket) override;
};

