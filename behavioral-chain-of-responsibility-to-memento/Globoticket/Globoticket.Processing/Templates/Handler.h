#pragma once
#include <stdexcept>

template<typename T, typename R>
class Handler
{
private:
  Handler<T, R>* _nextHandler;
protected:
  virtual R HandleItem(T item);
public:
  Handler() : _nextHandler(nullptr) {}
  virtual Handler<T, R>* SetNext(Handler<T,R>* handler);
};

template<typename T, typename R>
inline R Handler<T, R>::HandleItem(T item)
{
  if (_nextHandler)
  {
    return _nextHandler->HandleItem(item);
  }
  
  throw std::runtime_error("No handler found for this item");
}

template<typename T, typename R>
inline Handler<T, R>* Handler<T, R>::SetNext(Handler<T, R>* handler)
{
  if (_nextHandler == nullptr)
  {
    _nextHandler = handler;
    return handler;
  }

  return _nextHandler->SetNext(handler);
}
