#include "MacroCommand.h"
#include <stdexcept>
#include <iostream>

void MacroCommand::Add(Command* command)
{
  _commands->push_back(command);
}

void MacroCommand::Remove(Command* command)
{
  _commands->remove(command);
}

bool MacroCommand::Execute()
{
  bool canExecute = CanExecute();
  if (canExecute)
  {
    for (auto command : *_commands)
    {
      try
      {
        command->Execute();
      }
      catch (std::runtime_error& e)
      {
        std::cout << "Macro execution failed.\n";
        throw;
      }
    }
  }
  else
  {
    std::cout << "(false)@CanExecute()\n";
  }
  return canExecute;
}

bool MacroCommand::CanExecute()
{
  bool canExecute = true;
  for (auto command : *_commands)
  {
    canExecute &= command->CanExecute();
  }
  return canExecute;
}
