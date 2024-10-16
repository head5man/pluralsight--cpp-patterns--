#pragma once
#include "GloboMediator.h"
#include "NotificationType.h"
#include "../Business/Accounting.h"
#include "../Business/Printing.h"
#include "../Iterators/TicketAggregate.h"
#include <map>

class NotificationMediator :
  public GloboMediator<MediatedType>
{
private:
  std::map<NotificationType, std::shared_ptr<Notifier<MediatedType>>> _notifiers;
  MediatedType* _tickets;
public:
  virtual void CallNotifier(NotificationType notifier) override;
  virtual void CreateNotifiers(MediatedType& tickets) override;
};

