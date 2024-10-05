#include "Venue.h"
#include <iostream>
#include <fmt/core.h>

std::string Venue::NotEnoughSeatsAvailable(TicketType ticketType, int unbookedSeats)
{
	const char* ticketType_str[] =
	{ "Premium", "Stalls", "Dress Circle" };
	const char* venueType_str[] =
	{ "Huge", "Large", "Small" };

	return fmt::format("The {0} venue does not have enough seats available for this reservation. "
		"Only {1} {2} seats are left.\n ", venueType_str[_venueType - 1], unbookedSeats, ticketType_str[ticketType-1]);
}

Venue::Venue(VenueType type)
{
	_venueType = type;
	_numberOfBookedPremiumSeats = 0;
	_numberOfBookedStallsSeats = 0;
	_numberOfBookedDressCircleSeats = 0;

	switch (_venueType)
	{
	case huge:
		_numberOfPremiumSeats = 200;
		_numberOfStallsSeats = 600;
		_numberOfDressCircleSeats = 1200;
		break;
	case large:
		_numberOfPremiumSeats = 80;
		_numberOfStallsSeats = 120;
		_numberOfDressCircleSeats = 300;
		break;
	case small:
		_numberOfPremiumSeats = 10;
		_numberOfStallsSeats = 25;
		_numberOfDressCircleSeats = 65;
		break;
	default:
		std::cout << fmt::format("The {0} venue type is not currently supported.", type);
		_numberOfPremiumSeats = 0;
		_numberOfStallsSeats = 0;
		_numberOfDressCircleSeats = 0;
		break;
	}
}

int Venue::BookSeats(int numberOfSeatsToBook, TicketType ticketType)
{
	int numberOfUnbookedSeats = 0;
	int* numberOfBookedSeats = 0;

	switch (ticketType)
	{
	case premium:
		numberOfUnbookedSeats = _numberOfPremiumSeats - _numberOfBookedPremiumSeats;
		numberOfBookedSeats = &_numberOfBookedPremiumSeats;
		break;
	case stalls:
		numberOfUnbookedSeats = _numberOfStallsSeats - _numberOfBookedStallsSeats;
		numberOfBookedSeats = &_numberOfBookedStallsSeats;
		break;
	case dressCircle:
		numberOfUnbookedSeats = _numberOfDressCircleSeats - _numberOfBookedDressCircleSeats;
		numberOfBookedSeats = &_numberOfBookedDressCircleSeats;
		break;
	default:
		std::cout << fmt::format("The {0} ticket type is not currently supported.", ticketType);
		return 0;
	}

	int seatsLeftAfterBooking = numberOfUnbookedSeats - numberOfSeatsToBook;

	if (seatsLeftAfterBooking >= 0)
	{
		(*numberOfBookedSeats) += numberOfSeatsToBook;
		return seatsLeftAfterBooking;
	}

	std::cout << NotEnoughSeatsAvailable(ticketType, numberOfUnbookedSeats);
	return -1;
}
