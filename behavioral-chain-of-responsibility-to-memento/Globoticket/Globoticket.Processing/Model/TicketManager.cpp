#include "TicketManager.h"
#include "../Handlers/PriceHandler.h"
#include "../Handlers/PremiumPriceHandler.h"
#include "../Handlers/DressCirclePriceHandler.h"
#include "../Handlers/StallsPriceHandler.h"
#include <iostream>
#include <fmt/core.h>

TicketManager::TicketManager()
{
	// Setup venues
	_hugeTheatre = new Venue(huge);
	_largeTheatre = new Venue(large);
	_smallTheatre = new Venue(small);

	// Setup price handling chain
	_priceHandler = new PriceHandler;
	DressCirclePriceHandler* dcPriceHandler = new DressCirclePriceHandler;
	StallsPriceHandler* sPriceHandler = new StallsPriceHandler;
	PremiumPriceHandler* pPriceHandler = new PremiumPriceHandler;

	_priceHandler
		->SetNext(dcPriceHandler)
		->SetNext(sPriceHandler)
		->SetNext(pPriceHandler);
}

void TicketManager::BookSeats()
{
	const char* ticketType_str[] =
	{ "Premium", "Stalls", "Dress Circle" };
	const char* venueType_str[] =
	{ "Huge", "Large", "Small" };

	int numberOfSeatsToBook;
	std::cout << fmt::format("How many seats would you like to reserve?\n");

	TakeInteger(numberOfSeatsToBook);

	int typeOfTicketInt = 0;

	while (typeOfTicketInt < 1 || typeOfTicketInt > 3)
	{
		std::cout << fmt::format("Which type of ticket would you "
			"like to reserve?\n");
		std::cout << fmt::format("1: Premium\n");
		std::cout << fmt::format("2: Stalls\n");
		std::cout << fmt::format("3: Dress Circle\n");

		TakeInteger(typeOfTicketInt);
	}

	int typeOfVenueInt = 0;

	while (typeOfVenueInt < 1 || typeOfVenueInt > 3)
	{
		std::cout << fmt::format("At what type of venue would you "
			"like to reserve?\n");
		std::cout << fmt::format("1: Huge\n");
		std::cout << fmt::format("2: Large\n");
		std::cout << fmt::format("3: Small\n");

		TakeInteger(typeOfVenueInt);
	}

	TicketType ticketType = (TicketType)typeOfTicketInt;
	VenueType venueType = (VenueType)typeOfVenueInt;

	int numberOfRemainingSeats = 0;

	switch (venueType)
	{
	case huge:
		numberOfRemainingSeats = _hugeTheatre->BookSeats(numberOfSeatsToBook, ticketType);
		break;
	case large:
		numberOfRemainingSeats = _largeTheatre->BookSeats(numberOfSeatsToBook, ticketType);
		break;
	case small:
		numberOfRemainingSeats = _smallTheatre->BookSeats(numberOfSeatsToBook, ticketType);
		break;
	default:
		break;
	}

	if (numberOfRemainingSeats >= 0)
	{
		Ticket ticket(ticketType, venueType, numberOfSeatsToBook);

		double ticketPrice = _priceHandler->HandlePrice(ticket);

		_tickets.push_back(ticket);

		std::cout << fmt::format("You reserved a ticket for {0} seats "
			"at the {1} venue in the {2} area which costs {3} dollars. \n",
			ticket.getNumberOfSeats(),
			venueType_str[ticket.getVenueType() - 1],
			ticketType_str[ticket.getTicketType() - 1],
			ticketPrice);
	}
	else
	{
		std::cout << "No seats reserved.\n ";
	}
}

void TicketManager::HandleTotalPrice()
{
	double totalPrice = _priceHandler->HandleTotalPrice(_tickets);
	int totalNumberOfSeats = 0;
	for (Ticket ticket : _tickets)
	{
		totalNumberOfSeats += ticket.getNumberOfSeats();
	}

	std::cout << fmt::format("You reserved a total {0} tickets for {1} seats "
		"with a total cost of {2} dollars. \n",
		_tickets.size(),
		totalNumberOfSeats,
		totalPrice);
}

void TicketManager::ClearTickets()
{
	_tickets.clear();
	std:: cout << "All ticket reservations have been cleared.\n";
}

void TicketManager::TakeInteger(int& integer)
{
	while (true)
	{
		std::cin >> integer;

		// Check that the user entered an integer
		if (!std::cin)
		{
			std::cout << "Please enter an integer number " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else break;
	}
}
