#pragma once
#include "..\Mementos\UserSettingsMemento.h"
#include <memory>

class UserSettings
{
private:
	int _colorSetting = 7;
public:
	void SetColorSetting(int setting) { _colorSetting = setting; }
	int GetColorSetting() { return _colorSetting; }
	
  void SetMemento(std::shared_ptr<UserSettingsMemento> memento);
  std::shared_ptr<UserSettingsMemento> CreateMemento();
};

