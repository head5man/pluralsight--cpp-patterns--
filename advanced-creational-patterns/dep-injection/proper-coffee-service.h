#pragma once
#include "icoffee-service.h"

#include <iostream>

class ProperCoffeeService : public iCoffeeService {
  void sendMetrics() override {
    std::cout << "Sending proper metrics!" << std::endl;
  }
};