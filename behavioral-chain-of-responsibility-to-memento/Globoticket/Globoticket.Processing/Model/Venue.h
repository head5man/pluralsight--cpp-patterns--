#pragma once
#include "VenueType.h"
#include "Ticket.h"
#include <string>

class Venue
{
private:
	VenueType _venueType;

	int _numberOfPremiumSeats;
	int _numberOfStallsSeats;
	int _numberOfDressCircleSeats;

	int _numberOfBookedPremiumSeats;
	int _numberOfBookedStallsSeats;
	int _numberOfBookedDressCircleSeats;

	std::string NotEnoughSeatsAvailable(TicketType ticketType, int unbookedSeats);

public:
	Venue(VenueType type);

	VenueType getVenueType() { return _venueType; }

  int getNumberOfAvailableSeats(TicketType type);

  void ThrowIfNotEnoughSeatsAvailable(TicketType type, int numberOfSeatsToBook);

	int getNumberOfPremiumSeats() { return _numberOfPremiumSeats; }
	int getNumberOfStallsSeats() { return _numberOfStallsSeats; }
	int getNumberOfDressCircleSeats() { return _numberOfDressCircleSeats; }
	
	/// <summary>
	/// Book a number of seats of the specified type.
	/// </summary>
	/// <param name="numberOfSeatToBook">The number of seats to book.</param>
	/// <param name="ticketType">The type of seats to book.</param>
	/// <returns>The number of seats of the specified type still remaining.</returns>
	int BookSeats(int numberOfSeatToBook, TicketType ticketType);
};

