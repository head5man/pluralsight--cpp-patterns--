#pragma once
#include "Iterator.h"

#include <functional>

template <typename Item, typename Aggregate>
class FilterIterator :
    public Iterator<Item, Aggregate>
{
  typedef typename std::vector<Item>::iterator iterator_type;
private:
  Aggregate& _collection;
  iterator_type _iterator;
  std::function<bool(Item)> _predicate;
public:
  FilterIterator(Aggregate& collection, std::function<bool(Item)> predicate)
    : _collection(collection), _predicate(predicate)
  {
    _iterator = _collection._items.begin();
    FindNextPredicateMatch();
  }

  virtual void First() override
  {
    _iterator = _collection._items.begin();
    FindNextPredicateMatch();
  }

  virtual void Next() override
  {
    FindNextPredicateMatch(true);
  }

  virtual bool IsDone() override
  {
    return (_iterator == _collection._items.end());
  }

  virtual iterator_type CurrentItem() override
  {
    return _iterator;
  }

  void FindNextPredicateMatch(bool autoAdvance = false)
  {
    if (_collection.Count() > 0)
    {
      if (autoAdvance)
      {
        ++_iterator;
      }

      while (_iterator != _collection._items.end() && _predicate(*CurrentItem()) == false)
      {
        ++_iterator;
      }
    }
  }
};

