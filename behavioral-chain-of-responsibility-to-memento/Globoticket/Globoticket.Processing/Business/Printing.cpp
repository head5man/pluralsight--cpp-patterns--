#include "Printing.h"

void Printing::NotifyPrinting(std::vector<Ticket> tickets)
{
	std::cout << fmt::format("Thanks for notifying printing.\n");
	std::cout << fmt::format("We have prepared the printing of {0} "
		"tickets}.\n", tickets.size());
}