#pragma once
#include <iostream>

class Command
{
public:
  virtual ~Command() { std::cout << "~Command" << std::endl; };
  virtual bool Execute() = 0;
  virtual void Undo() { std::cout << "Nothing to undo\n"; }
  virtual bool CanExecute() { return true; };
};