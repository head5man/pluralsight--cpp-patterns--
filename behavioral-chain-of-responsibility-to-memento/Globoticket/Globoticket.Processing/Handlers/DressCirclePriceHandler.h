#pragma once
#include "PriceReceiver.h"

class DressCirclePriceHandler :
    public PriceReceiver
{
public:
  virtual double HandlePrice(const Ticket& ticket) override;
};

