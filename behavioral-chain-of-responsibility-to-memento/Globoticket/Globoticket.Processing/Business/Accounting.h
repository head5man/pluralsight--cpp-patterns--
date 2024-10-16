#pragma once
#include "../Model/Ticket.h"
#include "../Handlers/PriceHandler.h"
#include "../Mediators/Notifier.h"

#include "../Iterators/TicketAggregate.h"

class Accounting
  : public Notifier<MediatedType>
{
public:
  Accounting(GloboMediator<MediatedType>* mediator)
    : Notifier<MediatedType>(mediator)
  {

  }

	void NotifyAccounting(MediatedType* tickets);

  void Notify(MediatedType* tickets) override;
};

