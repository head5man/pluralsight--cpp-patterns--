#pragma once

#include "icoffee-service.h"

#include <iostream>

class MockCoffeeService : public iCoffeeService {
  void sendMetrics() override {
    std::cout << "Sending mock metrics!" << std::endl;
  }
};