#pragma once

#include "EnumType.h"

#include <string>
#include <stdexcept>
#include <algorithm>
#include <fmt/core.h>

struct ExpressionType;

struct ExpressionType : public EnumType
{
  inline ExpressionType(const char* type)
  {
    EnumType::Initialize<ExpressionType>(type);
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

  inline operator int() const
  {
    return _IndexOf<ExpressionType>(_value);
  }

  inline ExpressionType operator=(int value)
  {
    auto count = _Count<ExpressionType>();
    if (value >= 0 && value < count)
    {
      return ExpressionType(Values[value]);
    }

    throw std::runtime_error(fmt::format("Given index(%d) is out of the bounds of array(%d)", value, count));
  }
};
