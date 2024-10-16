#pragma once

#include <vector>

template <typename Item, typename Aggregate>
class Iterator
{
  typedef typename std::vector<Item>::iterator iterator_type;
public:
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() = 0;
  virtual iterator_type CurrentItem() = 0;
};

