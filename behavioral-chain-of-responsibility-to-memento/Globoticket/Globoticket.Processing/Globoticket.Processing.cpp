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

	while (selection != 'q' && selection != 'Q')
	{
		cout << fmt::format("Welcome to the Globoticket system\n");
		cout << fmt::format("Please make a selection\n");
		cout << fmt::format("1: Make ticket reservation\n");
		cout << fmt::format("2: Calculate total price of current tickets\n");
		cout << fmt::format("3: Clear ticket list\n");
		cout << fmt::format("Q: Quit\n");
		cin >> selection;

		switch (selection)
		{
		case '1':
		{
			_ticketManager->BookSeats();
			break;
		}
		case '2':
		{
			_ticketManager->HandleTotalPrice();
			break;
		}
		case '3':
		{
			_ticketManager->ClearTickets();
			break;
		}
		default:
			cout << "Please make a valid selection.\n";
			break;
		}
	}
}