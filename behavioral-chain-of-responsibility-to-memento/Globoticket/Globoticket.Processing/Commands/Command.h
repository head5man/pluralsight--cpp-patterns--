#pragma once

class Command
{
public:
  virtual void Execute() = 0;
  virtual bool CanExecute() { return true; };
};