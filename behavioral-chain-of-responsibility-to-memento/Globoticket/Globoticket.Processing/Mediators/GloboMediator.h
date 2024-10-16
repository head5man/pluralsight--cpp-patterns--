#pragma once

#include "NotificationType.h"
#include "../Model/Ticket.h"

#include <vector>
#include <memory>

template <typename T>
class GloboMediator
{
protected:
  virtual void CreateNotifiers(T&) = 0;
public:
  virtual void CallNotifier(NotificationType notificationType) = 0;
};

