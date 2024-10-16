#pragma once
#include "GloboMediator.h"

#include <memory>

template <typename T>
class Notifier
{
private:
  GloboMediator<T>* _mediator;
public:
  Notifier(GloboMediator<T>* mediator)
    : _mediator(mediator)
  {
  }

  virtual void Notify(T*) = 0;
};

