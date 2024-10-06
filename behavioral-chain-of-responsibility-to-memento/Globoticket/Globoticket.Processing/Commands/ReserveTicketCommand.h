#pragma once
#include "Command.h"
#include "../Model/VenueType.h"
#include "../Model/TicketType.h"
#include "../Handlers/PriceHandler.h"

#include <vector>

class ReserveTicketCommand :
    public Command
{
private:
  std::vector<Ticket>* _tickets;
  PriceHandler* _priceHandler;
  TicketType _ticketType;
  VenueType _venueType;
  int _numberOfSeatsToBook;
public:
  ReserveTicketCommand(std::vector<Ticket>* tickets, PriceHandler* priceHandler, TicketType ticketType, VenueType venueType, int numberOfSeatsToBook);
  virtual bool Execute() override;
};

