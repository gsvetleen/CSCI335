/*
Svetleen Guerrier
Class: CSCI335

*/
#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include "QuadraticProbing.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

// Linear probing implementation.
template <typename HashedObj>
class HashTableLinear:public HashTable <HashedObj>
{
protected:
//Finds the right position for table.
 size_t FindPos(const HashedObj & x) const 
  {
    size_t offset = 1;
    size_t current_pos = this->InternalHash(x);
      
    while (this->array_[current_pos].info_ != this->EMPTY &&
     this->array_[current_pos].element_ != x) 
    {
      current_pos += offset;  // Compute ith probe.
      this->collisions++;
      offset++;
      if (current_pos >= this->array_.size())
         current_pos -= this->array_.size();
    }

    this->offsetcopy = std::move(offset);
    offset = 0;
    return current_pos;
  }
};

#endif  // LINEAR_PROBING_H
