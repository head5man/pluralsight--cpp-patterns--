#pragma once

#include "EnumType.h"

#include <string>
#include <stdexcept>
#include <algorithm>
#include <fmt/core.h>

struct ExpressionType
{
  const char* _value = nullptr;
  inline ExpressionType(const char* type)
  {
    std::string str(type);
    _value = IsValid<ExpressionType>(str);
    if (_value == nullptr)
    {
      throw std::runtime_error(fmt::format("Invalid type assignment %s", type));
    }
  }

public:
  static constexpr const char* const Terminal = "terminal";
  static constexpr const char* const NonTerminal = "nonterminal";
  static constexpr const char* const Values[] = { Terminal, NonTerminal };

  inline ExpressionType operator=(const char* type)
  {
    return ExpressionType(type);
  }

  inline operator const char* () { return _value; }

  inline operator int()
  {
    return IndexOf<ExpressionType>(_value);
  }

  inline ExpressionType operator=(int value)
  {
    auto count = Count<ExpressionType>();
    if (value >= 0 && value < count)
    {
      return ExpressionType(Values[value]);
    }

    std::runtime_error(fmt::format("Given index(%d) is out of the bounds of array(%d)", value, count));
  }
};

