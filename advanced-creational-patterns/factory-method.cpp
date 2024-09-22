#include "factory-method.h"

class SimpleCoffeeMachine : public CoffeeMachine {
public:
  void brew() override {
    std::cout << "Brewing simple coffee" << std::endl;
  }
};

class RobustCoffeeMachine : public CoffeeMachine {
public:
  void brew() override {
    std::cout << "Brewing robust coffee" << std::endl;
  }
};


std::unique_ptr<CoffeeMachine> CoffeeMachineFactory::createMachine(int machine)
{
  switch (machine)
  {
  default:
  case 1:
    return std::make_unique<SimpleCoffeeMachine>();
  case 2:
    return std::make_unique<RobustCoffeeMachine>();
  }
}
