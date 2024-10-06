#include "MacroCommand.h"
#include <stdexcept>
#include <iostream>

void MacroCommand::Add(std::unique_ptr<Command> command)
{
  _commands.push_back(std::move(command));
}

bool MacroCommand::Execute()
{
  bool canExecute = CanExecute();
  if (canExecute)
  {
    for (std::unique_ptr<Command>& command : _commands)
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

void MacroCommand::Undo()
{
  for (std::unique_ptr<Command>& command : _commands)
  {
    try
    {
      command->Undo();
    }
    catch (std::runtime_error& e)
    {
      std::cout << "Macro execution failed.\n";
      throw;
    }
  }
}

bool MacroCommand::CanExecute()
{
  bool canExecute = true;
  for (std::unique_ptr<Command>& command : _commands)
  {
    canExecute &= command->CanExecute();
  }
  return canExecute;
}
