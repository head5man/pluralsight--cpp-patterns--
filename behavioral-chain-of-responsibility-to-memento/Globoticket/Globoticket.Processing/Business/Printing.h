#pragma once
#include "../Model/Ticket.h"
#include "../Mediators/Notifier.h"
#include "../Iterators/TicketAggregate.h"

#include <vector>

class Printing
  : public Notifier<MediatedType>
{
public:
  Printing(GloboMediator<MediatedType>* mediator)
    : Notifier<MediatedType>(mediator)
  {

  }

  void NotifyPrinting(MediatedType* tickets);

  void Notify(MediatedType* tickets) override;
};