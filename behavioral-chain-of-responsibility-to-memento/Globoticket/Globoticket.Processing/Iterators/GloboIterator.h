#pragma once

#include "Iterator.h"

template <typename Item, typename Aggregate>
class GloboIterator :
    public Iterator<Item, Aggregate>
{
  typedef typename std::vector<Item>::iterator iterator_type;
private:
  Aggregate& _collection;
  iterator_type _iterator;
public:
  GloboIterator(Aggregate& collection)
    : _collection(collection) 
  {
    _iterator = _collection._items.begin();
  }
  
  virtual void First() override
  {
    _iterator = _collection._items.begin();
  }

  virtual void Next() override
  {
    _iterator++;
  }

  virtual bool IsDone() override
  {
    return (_iterator == _collection._items.end());
  }

  virtual iterator_type CurrentItem()
  {
    return _iterator;
  }
};

