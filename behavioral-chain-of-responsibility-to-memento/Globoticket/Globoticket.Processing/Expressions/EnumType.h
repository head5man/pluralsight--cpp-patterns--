#pragma once

#include <string>
#include <stdexcept>

namespace {
  template <typename T>
  const char* IsValid(std::string str)
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
  int Count()
  {
    return sizeof(T::Values) / sizeof(T::Values[0]);
  }

  template <typename T>
  int IndexOf(T item)
  {
    for (int i = 0; i < Count<T>(); i++)
    {
      T value = T::Values[i];
      if (T == item)
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
    std::string str(value);
    _value = IsValid<T>(str);
    if (_value == nullptr)
    {
      throw std::runtime_error(fmt::format("Invalid type assignment %s", type));
    }
  }
};