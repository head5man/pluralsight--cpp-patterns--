#include "abstract-factory.h"

#include <iostream>

class SimpleCoffee : public Coffee
{
public:
  void stir() override
  {
    std::cout << "Stir simple coffee" << std::endl;
  }
};

class RowbustCoffee : public Coffee
{
public:
  void stir() override
  {
    std::cout << "Stir robust coffee" << std::endl;
  }
};

namespace {
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
}

std::unique_ptr<CoffeeMachine> SimpleCoffeeFactory::createMachine() {
      return std::make_unique<SimpleCoffeeMachine>();
  }
  
std::unique_ptr<Coffee> SimpleCoffeeFactory::createCoffee() {
  return std::make_unique<SimpleCoffee>();
}


std::unique_ptr<CoffeeMachine> RobustCoffeeFactory::createMachine() {
  return std::make_unique<RobustCoffeeMachine>();
}

std::unique_ptr<Coffee> RobustCoffeeFactory::createCoffee() {
  return std::make_unique<RowbustCoffee>();
}

