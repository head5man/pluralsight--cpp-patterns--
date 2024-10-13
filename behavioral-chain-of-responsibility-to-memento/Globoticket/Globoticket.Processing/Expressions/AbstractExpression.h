#pragma once
#include "ExpressionType.h"
#include "Context.h"

#include <string>

#include <stdexcept>
#include <stack>

template <typename T, typename TVal>
class AbstractExpression
{
protected:
  std::string _name;
  ExpressionType _type;
  std::shared_ptr<T> _item;
  std::stack<std::shared_ptr<AbstractExpression<T, TVal>>> _children;

  AbstractExpression(std::string name, ExpressionType type, std::shared_ptr<T> item)
    : _name(name), _type(type), _children(), _item(item)
  { }
  
public:
  virtual TVal GetValue() = 0;

  virtual std::shared_ptr<T> Interpret(Context<TVal>& context)
  {
    if (GetExpressionType() == ExpressionType::NonTerminal)
    {
      std::shared_ptr<AbstractExpression<T, TVal>> next = GetNext();
      while (next != nullptr)
      {
        _item = next->Interpret(context);
        next = GetNext();
      }
    }

    return _item;
  }

  virtual ExpressionType GetExpressionType() 
  { 
    return _type;
  }

  virtual std::string GetName() 
  {
    return _name;
  }

  virtual void AddChild(std::shared_ptr<AbstractExpression<T, TVal>> child) 
  {
    _children.push(child);
  }

  virtual std::shared_ptr<AbstractExpression<T, TVal>> GetNext()
  {
    if (_children.empty())
    {
      return nullptr;
    }

    auto child = _children.top();
    _children.pop();
    return child;
  }
};


