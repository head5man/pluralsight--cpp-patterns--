#pragma once

class Command
{
public:
  virtual bool Execute() = 0;
  virtual bool CanExecute() { return true; };
};