#pragma once
#include <map>
#include <string>
#include <memory>

template <typename T>
class Context
{
public:
  std::unique_ptr<std::map<std::string, T>> Values;
  Context();
  void Assign(std::string name, T value);
  T Lookup(std::string name);
};

template <typename T>
inline Context<T>::Context()
{
  Values = std::unique_ptr<std::map<std::string, T>>();
}

template <typename T>
inline void Context<T>::Assign(std::string name, T value)
{
  Values->insert(std::make_pair(name, value));
}

template <typename T>
inline T Context<T>::Lookup(std::string name)
{
  return (*Values)[name];
}
