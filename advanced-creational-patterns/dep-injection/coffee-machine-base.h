#pragma once

#include "icoffee-service.h"
#include "../interfaces/coffee-machine.h"

#include <memory>

class CoffeeMachineBase : public CoffeeMachine {
public:
  CoffeeMachineBase(std::unique_ptr<iCoffeeService>&& coffeeService) : _coffeeService(std::move(coffeeService))
  {}

  void brew() override;
private:
  std::unique_ptr<iCoffeeService> _coffeeService;
};