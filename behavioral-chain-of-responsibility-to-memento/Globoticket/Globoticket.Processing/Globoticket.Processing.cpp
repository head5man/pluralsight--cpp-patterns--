// Globoticket.Processing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fmt/core.h>
#include "Model\Ticket.h"
#include "Model\Venue.h"
#include "Model\VenueType.h"
#include "Globoticket.Processing.h"
#include "Model\TicketManager.h"

using namespace std;
TicketManager* _ticketManager;
int main()
{
  _ticketManager = new TicketManager;
  SystemMenu();
}

void SystemMenu()
{
  char selection = ' ';

  do
  {
    switch (selection)
    {
    case '1':
    {
      _ticketManager->BookSeats();
      break;
    }
    case '5':
      _ticketManager->HandleFreeText();
      break;
    case 't':
    {
      _ticketManager->HandleTotalPrice();
      break;
    }
    case 'c':
    {
      _ticketManager->ClearTickets();
      break;
    }
    case 'u':
    {
      _ticketManager->UndoReservation();
      break;
    }
    case 'l':
    {
      _ticketManager->ListAllTickets();
      break;
    }
    case 'f':
    {
      _ticketManager->ListAllTicketsBySeatType();
      break;
    }
    case -1:
    case ' ':
      cout << fmt::format("Welcome to the Globoticket system\n");
      cout << fmt::format("Please make a selection\n");
      cout << fmt::format("1: Make ticket reservation\n");
      cout << fmt::format("5: Reserve ticket expression\n");
      cout << "L: List all tickets\n";
      cout << "F: List tickets by seat type\n";
      cout << fmt::format("T: Calculate total price of current tickets\n");
      cout << fmt::format("C: Clear ticket list\n");
      cout << fmt::format("U: Undo last reservation\n");
      cout << fmt::format("Q: Quit\n");
      break;
    case 'q':
      break;
    default:
      cout << "Please make a valid selection.\n";
      break;
    }
  } while (GetSelection(selection) && selection != 'q');
}

char GetSelection(char& c)
{
  c = 0;
  std::string selection;
  if (std::getline(cin, selection))
  {
    c = selection.c_str()[0];
    c = std::iscntrl(c) ? -1 : std::tolower(c);
  }
  return c;
}