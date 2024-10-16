#pragma once
#include "../Model/Ticket.h"
#include "../Handlers/PriceHandler.h"
class Accounting
{
public:
	void NotifyAccoutning(std::vector<Ticket> tickets);
};

