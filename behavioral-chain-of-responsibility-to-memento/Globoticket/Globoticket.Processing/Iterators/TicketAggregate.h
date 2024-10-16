#pragma once

#include "../Model/Ticket.h"
#include "GloboAggregate.h"

#include <memory>

typedef GloboAggregate<std::shared_ptr<Ticket>> TicketAggregate;

typedef Iterator<std::shared_ptr<Ticket>, TicketAggregate> TicketIterator;