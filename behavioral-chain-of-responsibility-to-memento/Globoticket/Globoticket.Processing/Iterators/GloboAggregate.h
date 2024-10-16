#pragma once

#include "GloboIterator.h"

#include <vector>
#include <memory>

template <typename Item>
class GloboAggregate
{
  friend class GloboIterator<Item, GloboAggregate>;
private:
  std::vector<Item> _items;
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
};

