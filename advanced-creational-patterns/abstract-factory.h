#pragma once
#include "interfaces/coffee-factory.h"

class SimpleCoffeeFactory : public CoffeeFactory {
public:
  std::unique_ptr<CoffeeMachine> createMachine() override;
  std::unique_ptr<Coffee> createCoffee() override;
};


class RobustCoffeeFactory : public CoffeeFactory {
public:
  std::unique_ptr<CoffeeMachine> createMachine() override;
  std::unique_ptr<Coffee> createCoffee() override;
};
