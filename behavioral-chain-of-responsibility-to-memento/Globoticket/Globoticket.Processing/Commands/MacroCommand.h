#pragma once
#include "Command.h"

#include <memory>

#include <list>
class MacroCommand :
    public Command
{
private:
  std::unique_ptr<std::list<Command*>> _commands;
  MacroCommand(const MacroCommand&&) = delete;
public:
  MacroCommand() : _commands(std::make_unique<std::list<Command*>>()) {};

  virtual void Add(Command* command);
  virtual void Remove(Command* command);

  virtual bool Execute() override;
  virtual bool CanExecute() override;
};

