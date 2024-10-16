#pragma once

#include "../Model/Ticket.h"
#include "GloboAggregate.h"

#include <memory>

typedef std::shared_ptr<Ticket> ItemType;

typedef GloboAggregate<ItemType> TicketAggregate;

typedef Iterator<ItemType, TicketAggregate> TicketIterator;

typedef TicketAggregate::ItemContainer MediatedType;