#pragma once

#include <string>
#include <ostream>
#include <sstream>

enum VenueType { huge = 1, large, small };

inline std::ostream& operator<<(std::ostream& os, VenueType type)
{
  const char* names[] = { "Huge", "Large", "Small" };
  switch (type)
  {
  case huge:
  case large:
  case small:
    return os << names[type - 1];
    break;
  // omitting default to trigger compiler warning for missing cases
  }

  return os << type;
}

inline std::string to_string(VenueType type)
{
  std::stringstream ss;
  ss << type;
  return ss.str();
}

class VenueTypeConverter
{
public:
  static bool IsValidToken(std::string token)
  {
    bool ret = false;
    if (token == "small" || token == "large" || token == "huge")
    {
      ret = true;
    }

    return ret;
  }

  static VenueType FromToken(std::string token)
  {
    if (token == "huge")
    {
      return VenueType::huge;
    }

    if (token == "large")
    {
      return VenueType::large;
    }

    if (token == "small")
    {
      return VenueType::small;
    }

    throw std::runtime_error("Not a valid token(" + token + ")");
  }
};