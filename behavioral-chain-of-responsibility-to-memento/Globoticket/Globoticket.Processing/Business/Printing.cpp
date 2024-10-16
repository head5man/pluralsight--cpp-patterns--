#include "Printing.h"

#include <fmt/core.h>
#include <iostream>

void Printing::NotifyPrinting(MediatedType* tickets)
{
  std::cout << fmt::format("Thanks for notifying printing.\n");
  std::cout << fmt::format("We have prepared the printing of {0} "
    "tickets.\n", tickets->size());
}

void Printing::Notify(MediatedType* tickets)
{
  NotifyPrinting(tickets);
}