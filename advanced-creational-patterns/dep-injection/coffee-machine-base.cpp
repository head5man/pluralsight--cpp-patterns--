#include "coffee-machine-base.h"

#include <iostream>

void CoffeeMachineBase::brew()
{
  std::cout << "Brewing coffee!" << std::endl;
  _coffeeService->sendMetrics();
}
