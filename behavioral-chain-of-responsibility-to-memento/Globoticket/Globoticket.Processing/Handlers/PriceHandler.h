#pragma once
#include "../Model/Ticket.h"
#include "PriceReceiver.h"

#include <vector>

class PriceHandler
{
private:
  std::vector<PriceReceiver*> _receivers;
public:
  virtual PriceHandler* SetNext(PriceReceiver* receiver);

  double HandlePrice(const Ticket& ticket);
  double HandleTotalPrice(const std::vector<std::shared_ptr<Ticket>>& tickets);
};

