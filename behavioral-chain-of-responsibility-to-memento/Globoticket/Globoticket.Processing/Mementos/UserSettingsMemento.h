#pragma once
#include <iostream>
class UserSettingsMemento
{
  friend class UserSettings;
private:
  int _colorSetting = 1;
public:
  ~UserSettingsMemento()
  {
    std::cout << __FUNCTION__ << std::endl;
  }
};

