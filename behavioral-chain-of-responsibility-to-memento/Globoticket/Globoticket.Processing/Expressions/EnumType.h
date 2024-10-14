#pragma once

#include <fmt/core.h>
#include <string>
#include <stdexcept>

namespace {
  template <typename T>
  const char* _IsValid(std::string str)
  {
    for (auto& c : str)
    {
      c = std::tolower(c);
    }

    for (auto value : T::Values)
    {

      if (strcmp(value, str.c_str()) == 0)
        return value;
    }

    return nullptr;
  }

  template <typename T>
  const char* _IsValid(const char* input)
  {
    std::string str;
    for (int i = 0; i < strlen(input); i++)
    {
      auto c = input[i];
      str += std::tolower(c);
    }

    for (auto value : T::Values)
    {

      if (strcmp(value, str.c_str()) == 0)
        return value;
    }

    return nullptr;
  }

  template <typename T>
  int _Count()
  {
    return sizeof(T::Values) / sizeof(T::Values[0]);
  }

  template <typename T>
  int _IndexOf(const char* item)
  {
    for (int i = 0; i < _Count<T>(); i++)
    {
      T value = T::Values[i];
      if (value == item)
      {
        return i;
      }
    }
    return -1;
  }
}

struct EnumType
{
protected:
  const char* _value;

  template <typename T>
  void Initialize(const char* value)
  {
    _value = _IsValid<T>(value);
    if (_value == nullptr)
    {
      throw std::runtime_error(fmt::format("Invalid type assignment %s", value));
    }
  }
public:
  template <typename T>
  static bool IsValidToken(const char* token)
  {
    const char* p = _IsValid<T>(token);
    return p != nullptr;
  }

  template <typename T>
  static bool IsValidToken(std::string token)
  {
    const char* p = _IsValid<T>(token);
    return p != nullptr;
  }
};