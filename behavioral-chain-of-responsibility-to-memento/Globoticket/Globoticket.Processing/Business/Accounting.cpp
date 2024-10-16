#include "Accounting.h"

#include <fmt/core.h>
#include <iostream>

 void Accounting::NotifyAccounting(MediatedType* tickets)
{
	std::cout << fmt::format("Thanks for notifying accounting.\n");
	std::cout << fmt::format("The records have been updated with a reservation of {0} "
		"tickets.\n",tickets->size());
}

 void Accounting::Notify(MediatedType* tickets)
 {
   NotifyAccounting(tickets);
 }
