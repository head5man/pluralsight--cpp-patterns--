#pragma once

#include "coffee.h"
#include "coffee-machine.h"

#include <memory>

class CoffeeFactory {
public:
  virtual std::unique_ptr<CoffeeMachine> createMachine() = 0;
  virtual std::unique_ptr<Coffee> createCoffee() = 0;
};