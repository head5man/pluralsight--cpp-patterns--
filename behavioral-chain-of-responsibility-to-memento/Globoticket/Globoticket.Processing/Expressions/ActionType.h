#pragma once

#include "EnumType.h"

#include <fmt/core.h>

struct ActionType : public EnumType
{
  inline ActionType(const char* type)
  {
    Initialize<ActionType>(type);
  }

public:
  ActionType(int value)
  {
    this->operator=(value);
  }

  static constexpr const char* const Reserve = "reserve";
  static constexpr const char* Values[] = { Reserve };

  ActionType() = default;
  
  inline ActionType operator=(const char* type)
  {
    return ActionType(type);
  }

  inline operator const char* () { return _value; }

  inline operator int() const;

  inline ActionType& operator=(int value);
};

inline ActionType::operator int() const
{
  return _IndexOf<ActionType>(_value);
}

inline ActionType& ActionType::operator=(int value)
{
  auto count = _Count<ActionType>();
  if (value >= 0 && value < count)
  {
    _value = Values[value];
    return *this;
  }

  throw std::runtime_error(fmt::format("Given index(%d) is out of the bounds of array(%d)", value, count));
}