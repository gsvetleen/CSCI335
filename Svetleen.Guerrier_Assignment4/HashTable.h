/**
Svetleen Guerrier
Class: CSCI335
BinomialQueue
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include "BinomialQueue.h"


namespace {

// Internal method to test if a positive number is prime.
bool IsPrime(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrime(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrime(n)) n += 2;  
  return n;
}

}  // namespace


// Double probing implementation.
template <typename HashedObj,typename StructObj>
class HashTable {
public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  //Constructor
  explicit HashTable(size_t size = 101) : array_(NextPrime(size))
  { 
    MakeEmpty();
  }

  //return true is item is in table  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));

  }
  
  //Clears Hash table
  void MakeEmpty() {
    current_size_ = 0;

    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  //Return the pointer provided for the given key.
  StructObj& ReturnP(HashedObj &x)
  {
    size_t current_pos = FindPos(x);
    if(Contains(x)==true)
    {
      return array_[current_pos].pointer;
    }
    array_[current_pos].pointer=nullptr;
    return (array_[current_pos].pointer);
  }
  //Inserts item to hash table l-Value as well as the pointer.
  bool Insert(const HashedObj & x, StructObj& p) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    array_[current_pos].pointer = p;
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    //Inserts item to hash table R-Value
  bool Insert(HashedObj && x, StructObj& p)
  {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;
    array_[current_pos].pointer = p;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  //Deletes item form Hash Table
  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    array_[current_pos].pointer = nullptr;
    return true;
  }
private:   
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    StructObj pointer;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY, const StructObj& p = StructObj{} )
    :element_{e}, info_{i}, pointer{p} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY,const StructObj& p = StructObj{})
    :element_{std::move(e)}, info_{ i }, pointer{p} {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;

  //Checks wheteher element is active
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }


  //Finds the right position for table using double hashing.
  size_t FindPos(const HashedObj & x) const 
  {
    static std::hash<HashedObj> hf;
    size_t counter=1;
    size_t offset = counter*(55-(hf(x)%55));
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
     array_[current_pos].element_ != x) 
    {
      current_pos += offset;  // Compute ith probe.
      counter++;
      if (current_pos >= array_.size())
         current_pos -= array_.size();
    }

    offset = 0;
    return current_pos;
  }

  //Expands table size.
  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_),entry.pointer);
  }
  
  //Finds the key for inputted item.
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // Hash_Table
