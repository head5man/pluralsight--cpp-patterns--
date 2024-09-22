#pragma once
#include "interfaces/coffee-machine.h"

#include <iostream>
#include <memory>

class CoffeeMachineFactory {
public:
  std::unique_ptr<CoffeeMachine> createMachine(int machine);
};
