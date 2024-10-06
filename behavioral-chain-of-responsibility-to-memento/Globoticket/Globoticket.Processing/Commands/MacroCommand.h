#pragma once
#include "Command.h"

#include <memory>

#include <list>
class MacroCommand :
    public Command
{
private:
  std::list<std::unique_ptr<Command>> _commands;
  MacroCommand(const MacroCommand&&) = delete;
public:
  MacroCommand() : _commands(std::list<std::unique_ptr<Command>>()) {};

  virtual void Add(std::unique_ptr<Command> command);
  virtual bool Execute() override;
  virtual void Undo() override;
  virtual bool CanExecute() override;
};

