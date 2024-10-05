#pragma once
#include "PriceReceiver.h"

class DressCirclePriceHandler :
    public PriceReceiver
{
public:
  virtual double HandlePrice(Ticket ticket) override;
};

