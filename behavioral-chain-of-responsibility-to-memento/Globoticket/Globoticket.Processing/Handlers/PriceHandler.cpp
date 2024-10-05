#include "PriceHandler.h"
#include <iostream>

PriceHandler* PriceHandler::SetNext(PriceReceiver* receiver)
{
  _receivers.push_back(receiver);
  return this;
}

double PriceHandler::HandlePrice(Ticket ticket)
{
  for (auto receiver : _receivers)
  {
    auto price = receiver->HandlePrice(ticket);
    if (price != NULL)
      return price;
  }
  std::cout << "No price handler found for this ticket\n";
  return NULL;
}

double PriceHandler::HandleTotalPrice(std::vector<Ticket> tickets)
{
  double totalPrice = 0;

  for (Ticket ticket : tickets)
  {
    totalPrice += HandlePrice(ticket);
  }
  return totalPrice;
}
