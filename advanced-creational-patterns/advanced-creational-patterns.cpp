// advanced-creational-patterns.cpp : Defines the entry point for the application.
//

#include "advanced-creational-patterns.h"
#include "factory-method.h"
#include "abstract-factory.h"
#include "dep-injection/coffee-machine-base.h"
#include "dep-injection/proper-coffee-service.h"
#include "dep-injection/mock-coffee-service.h"

using namespace std;

int main()
{
  std::cout << "Factory method pattern" << std::endl;
  auto factory = std::make_unique<CoffeeMachineFactory>();
  auto one = factory->createMachine(1);
  auto two = factory->createMachine(2);

  one->brew();
  two->brew();
  std::cout << std::endl;
  std::cout << "Abstract factory pattern" << std::endl;
  auto factoryOne = std::make_unique<SimpleCoffeeFactory>();
  auto machineOne = factoryOne->createMachine();
  auto coffeeOne = factoryOne->createCoffee();


  auto factoryTwo = std::make_unique<RobustCoffeeFactory>();
  auto machineTwo = factoryTwo->createMachine();
  auto coffeeTwo = factoryTwo->createCoffee();

  machineOne->brew();
  coffeeOne->stir();

  machineTwo->brew();
  coffeeTwo->stir();

  std::cout << std::endl;
  std::cout << "Dependency injection pattern" << std::endl;
  CoffeeMachineBase mockServiceMachine(std::make_unique<MockCoffeeService>());
  mockServiceMachine.brew();
  CoffeeMachineBase properServiceMachine(std::make_unique<ProperCoffeeService>());
  properServiceMachine.brew();
}
