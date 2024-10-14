#include "Venue.h"
#include <iostream>
#include <fmt/core.h>

std::string Venue::NotEnoughSeatsAvailable(TicketType ticketType, int unbookedSeats)
{
	return fmt::format("The {0} venue does not have enough seats available for this reservation. "
		"Only {1} {2} seats are left.\n ", to_string(_venueType), unbookedSeats, to_string(ticketType));
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
		std::cout << fmt::format(__FUNCTION__ " The {0} venue type is not currently supported.", type);
		_numberOfPremiumSeats = 0;
		_numberOfStallsSeats = 0;
		_numberOfDressCircleSeats = 0;
		break;
	}
}

int Venue::getNumberOfAvailableSeats(TicketType ticketType)
{
  int numberOfUnbookedSeats = 0;

  switch (ticketType)
  {
  case premium:
    numberOfUnbookedSeats = _numberOfPremiumSeats - _numberOfBookedPremiumSeats;
    break;
  case stalls:
    numberOfUnbookedSeats = _numberOfStallsSeats - _numberOfBookedStallsSeats;
    break;
  case dressCircle:
    numberOfUnbookedSeats = _numberOfDressCircleSeats - _numberOfBookedDressCircleSeats;
    break;
  default:
    std::cout << fmt::format(__FUNCTION__ " The {0} ticket type is not currently supported.", ticketType);
    return 0;
  }
  return numberOfUnbookedSeats;
}

int Venue::getNumberOfBookedSeats(TicketType type)
{
  switch (type)
  {
  case premium:
    return _numberOfBookedPremiumSeats;
    break;
  case stalls:
    return _numberOfBookedStallsSeats;
    break;
  case dressCircle:
    return _numberOfBookedDressCircleSeats;
    break;
  default:
    std::cout << fmt::format(__FUNCTION__ " The {0} ticket type is not currently supported.", type);
    return 0;
  }
}

void Venue::ThrowIfNotEnoughSeatsAvailable(TicketType ticketType, int numberOfSeatsToBook)
{
  int numberOfUnbookedSeats = getNumberOfAvailableSeats(ticketType);
  if (numberOfSeatsToBook > numberOfUnbookedSeats)
  {
    std::string error = NotEnoughSeatsAvailable(ticketType, numberOfUnbookedSeats);
    throw std::runtime_error(error);
  }
}

void Venue::ThrowIfNotEnoughSeatsToUnbook(TicketType type, int numberOfSeats)
{

  int bookedSeats = getNumberOfBookedSeats(type);
  if (numberOfSeats > bookedSeats)
  {
    std::string error = NotEnoughSeatsAvailable(type, bookedSeats);
    throw std::runtime_error(error);
  }
}

int Venue::UnbookSeats(int numberOfSeats, TicketType type)
{
  ThrowIfNotEnoughSeatsToUnbook(type, numberOfSeats);
  int* bookedPtr = nullptr;

  switch (type)
  {
  case premium:
    bookedPtr = &_numberOfBookedPremiumSeats;
    break;
  case stalls:
    bookedPtr = &_numberOfBookedStallsSeats;
    break;
  case dressCircle:
    bookedPtr = &_numberOfBookedDressCircleSeats;
    break;
  default:
    std::cout << fmt::format(__FUNCTION__ " The {0} ticket type is not currently supported.", type);
    return 0;
  }

  (*bookedPtr) -= numberOfSeats;

  return getNumberOfAvailableSeats(type);
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
		std::cout << fmt::format(__FUNCTION__ "The {0} ticket type is not currently supported.", ticketType);
		return 0;
	}

  ThrowIfNotEnoughSeatsAvailable(ticketType, numberOfSeatsToBook);

  (*numberOfBookedSeats) += numberOfSeatsToBook;
  return numberOfUnbookedSeats - numberOfSeatsToBook;
}
