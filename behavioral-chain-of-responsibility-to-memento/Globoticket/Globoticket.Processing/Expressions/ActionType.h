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
  static constexpr const char* const Reserve = "reserve";
  static constexpr const char* Values[] = { Reserve };

  inline ActionType operator=(const char* type)
  {
    return ActionType(type);
  }

  inline operator const char* () { return _value; }

  inline operator int()
  {
    return IndexOf<ActionType>(_value);
  }

  inline ActionType operator=(int value)
  {
    auto count = Count<ActionType>();
    if (value >= 0 && value < count)
    {
      return ActionType(Values[value]);
    }

    std::runtime_error(fmt::format("Given index(%d) is out of the bounds of array(%d)", value, count));
  }
};