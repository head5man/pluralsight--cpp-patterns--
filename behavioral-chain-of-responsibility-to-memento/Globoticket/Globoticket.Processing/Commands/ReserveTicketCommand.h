#pragma once
#include "Command.h"
#include "../Model/VenueType.h"
#include "../Model/TicketType.h"
#include "../Handlers/PriceHandler.h"

#include <vector>
#include <memory>

class ReserveTicketCommand :
    public Command
{
private:
  std::vector<std::shared_ptr<Ticket>>& _tickets;
  PriceHandler* _priceHandler;
  TicketType _ticketType;
  VenueType _venueType;
  std::shared_ptr<Ticket> _ticket = nullptr;
  int _numberOfSeatsToBook;
public:
  ~ReserveTicketCommand();
  ReserveTicketCommand(std::vector<std::shared_ptr<Ticket>>& tickets, PriceHandler* priceHandler, TicketType ticketType, VenueType venueType, int numberOfSeatsToBook);
  virtual bool Execute() override;
  virtual void Undo() override;
};

