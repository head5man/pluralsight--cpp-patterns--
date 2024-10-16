#include "ColorChanger.h"
#include <windows.h> 
void ColorChanger::ChangeConsoleColor(int colorSetting)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorSetting);
}
