#pragma once
#include <stdexcept>
#include <ostream>
#include <sstream>

enum TicketType { premium = 1, stalls, dressCircle };

inline std::ostream& operator<<(std::ostream& os, TicketType type)
{
  const char* names[] = { "Premium", "Stalls", "Dress Circle" };
  switch (type)
  {
  case premium:
  case stalls:
  case dressCircle:
    return os << names[type - 1];
    break;
    // omitting default to trigger compiler warning for missing cases
  }
  return os << type;
}

inline std::string to_string(TicketType type)
{
  std::stringstream ss;
  ss << type;
  return ss.str();
}

class TicketTypeConverter
{
public:
  static bool IsValidToken(std::string token)
  {
    bool ret = false;
    if (token == "premium" || token == "dress" || token == "dresscircle" || token == "stalls")
    {
      ret = true;
    }

    return ret;
  }

  static TicketType FromToken(std::string token)
  {
    if (token == "premium")
    {
      return TicketType::premium;
    }

    if (token == "dress" || token == "dresscircle")
    {
      return TicketType::dressCircle;
    }

    if (token == "stalls")
    {
      return TicketType::stalls;
    }

    throw std::runtime_error("Not a valid token(" + token + ")");
  }
};
