// Globoticket.Processing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fmt/core.h>
#include "Model\Ticket.h"

#include "Globoticket.Processing.h"
#include "Handlers/PriceHandler.h"

#include "Handlers/PremiumPriceHandler.h"
#include "Handlers/StallsPriceHandler.h"
#include "Handlers/DressCirclePriceHandler.h"

using namespace std;
vector<Ticket> _tickets;

PriceHandler* _priceHandler = new PriceHandler();

int main()
{
  _priceHandler->SetNext(new PremiumPriceHandler())
    ->SetNext(new StallsPriceHandler())
    ->SetNext(new DressCirclePriceHandler());
	SystemMenu();

}

void SystemMenu()
{
	char selection = ' ';
	const char* ticketType_str[] =
	{ "Premium", "Stalls", "Dress Circle" };

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
			int numberOfTickets;
			cout << fmt::format("How many tickets would you like to reserve?\n");

			TakeInteger(numberOfTickets);

			int typeOfTicket;
			typeOfTicket = 0;

			while (typeOfTicket < 1 || typeOfTicket > 3)
			{
				cout << fmt::format("Which type of ticket would you "
					"like to reserve?\n");
				cout << fmt::format("1: Premium\n");
				cout << fmt::format("2: Stalls\n");
				cout << fmt::format("3: Dress Circle\n");

				TakeInteger(typeOfTicket);
			}

			Ticket ticket((TicketType)typeOfTicket, numberOfTickets);

			double ticketPrice = _priceHandler->HandlePrice(ticket);

			_tickets.push_back(ticket);

			cout << fmt::format("You reserved a ticket for {0} seats "
				"in the {1} area which costs {2} dollars. \n",
				ticket.getNumberOfSeats(),
				ticketType_str[ticket.getTicketType() - 1],
				ticketPrice);
			break;
		}
		case '2':
		{
			double totalPrice = _priceHandler->HandleTotalPrice(_tickets);
			int totalNumberOfSeats = 0;
			for (Ticket ticket : _tickets)
			{
				totalNumberOfSeats += ticket.getNumberOfSeats();
			}

			cout << fmt::format("You reserved a total {0} tickets for {1} seats "
				"with a total cost of {2} dollars. \n",
				_tickets.size(),
				totalNumberOfSeats,
				totalPrice);

			break;
		}
		case '3':
		{
			_tickets.clear();
			cout << "All ticket reservations have been cleared.\n";
			break;
		}
		default:
			cout << "Please make a valid selection.\n";
			break;
		}
	}
}

void TakeInteger(int& integer)
{
	while (true)
	{
		cin >> integer;

		// Check that the user entered an integer
		if (!cin)
		{
			cout << "Please enter an integer number " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else break;
	}
}