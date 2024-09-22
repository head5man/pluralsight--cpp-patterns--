#pragma once

/// <summary>
/// Interface defining the CoffeeService type
/// </summary>
struct iCoffeeService {
  virtual void sendMetrics() = 0;
  virtual ~iCoffeeService() = default;
};