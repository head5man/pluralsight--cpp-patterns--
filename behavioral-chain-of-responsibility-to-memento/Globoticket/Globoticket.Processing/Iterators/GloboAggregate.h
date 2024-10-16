#pragma once

#include "GloboIterator.h"
#include "FilterIterator.h"

#include <vector>
#include <memory>

template <typename Item>
class GloboAggregate
{
  friend class GloboIterator<Item, GloboAggregate>;
  friend class FilterIterator<Item, GloboAggregate>;
public:
  typedef std::vector<Item> ItemContainer;
private:
  ItemContainer _items;
public:
  void Push(Item item)
  {
    _items.push_back(item);
  }

  Item Pop()
  {
    Item item = _items.back();
    _items.pop_back();
    return item;
  }

  void Clear()
  {
    _items.clear();
  }

  size_t Count()
  {
    return _items.size();
  }

  bool IsEmpty()
  {
    _items.empty();
  }

  std::shared_ptr<Iterator<Item, GloboAggregate<Item>>> CreateIterator()
  {
    return std::make_shared<GloboIterator<Item, GloboAggregate<Item>>>(*this);
  }

  std::shared_ptr<Iterator<Item, GloboAggregate<Item>>> CreateFilterIterator(std::function<bool(Item)> predicate)
  {
    return std::make_shared<FilterIterator<Item, GloboAggregate<Item>>>(*this, predicate);
  }

  operator ItemContainer&() { return _items; }
};

