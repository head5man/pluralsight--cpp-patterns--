#include "UserSettings.h"

std::shared_ptr<UserSettingsMemento> UserSettings::CreateMemento()
{
	auto memento = std::make_shared<UserSettingsMemento>();
	memento->_colorSetting = _colorSetting;
	return memento;
}

void UserSettings::SetMemento(std::shared_ptr<UserSettingsMemento> memento)
{
	_colorSetting = memento->_colorSetting;
}
