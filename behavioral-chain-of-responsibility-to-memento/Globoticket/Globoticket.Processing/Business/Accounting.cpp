#include "Accounting.h"

 void Accounting::NotifyAccoutning(std::vector<Ticket> tickets)
{
	std::cout << fmt::format("Thanks for notifying accounting.\n");
	std::cout << fmt::format("The records have been updated with a reservation of {0} "
		"tickets with a value of {1}.\n",tickets.size());
}
