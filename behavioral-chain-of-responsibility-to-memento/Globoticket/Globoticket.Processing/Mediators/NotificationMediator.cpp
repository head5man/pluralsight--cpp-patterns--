
#include "NotificationMediator.h"

void NotificationMediator::CallNotifier(NotificationType type)
{
  auto it = _notifiers.find(type);
  if (it == _notifiers.end())
    return;

  auto& notifier = it->second;
  notifier->Notify(_tickets);
}

void NotificationMediator::CreateNotifiers(MediatedType& tickets)
{
  _tickets = &tickets;
  _notifiers[NotificationType::accounting] = std::make_shared<Accounting>(this);
  _notifiers[NotificationType::printing] = std::shared_ptr<Printing>(new Printing(this));
}
