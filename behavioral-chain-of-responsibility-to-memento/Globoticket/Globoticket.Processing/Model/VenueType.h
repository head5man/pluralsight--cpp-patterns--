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
  // omitting default trigger compiler warning for missing
  }
  return os << type;
}

inline std::string to_string(VenueType type)
{
  std::stringstream ss;
  ss << type;
  return ss.str();
}
