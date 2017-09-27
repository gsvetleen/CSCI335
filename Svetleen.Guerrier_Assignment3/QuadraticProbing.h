/*
Svetleen Guerrier
Class: CSCI335

*/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>


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


// Quadratic probing implementation.
template <typename HashedObj>
class HashTable {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  //Constructor
  explicit HashTable(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }

  //return true is item is in table  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  //Clears Hash table
  void MakeEmpty() {
    current_size_ = 0;
    collisions = 0; 
    offsetcopy = 0;

    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }


  //Inserts item to hash table l-Value
  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    //Inserts item to hash table R-Value
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

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
    return true;
  }

  //Returns Number of elements in Hash table
  size_t NumberofElements()
  {
  
    return current_size_;
  }

  //Returns table size
  size_t SizeofTable()
  {
    return array_.size();
  }

  //Returns lambda value
  double loadfactor()
  {
    return ((double)current_size_/array_.size());
  }

  //Returns Collisions
  size_t TotalNumberofCollisions()
  {
    return collisions;
  }

  //Returns Average number of Collisons
  double AverageNumberofCollisions()
  {
    return ((double)collisions/current_size_);
  }

  size_t Probing()
  {
    return offsetcopy;
  }

protected:   
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
  mutable size_t collisions;
  mutable size_t offsetcopy;

  //Checks wheteher element is active
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }


  //Finds the right position for table.
  virtual size_t FindPos(const HashedObj & x) const {

    int offset = 1;
    size_t current_pos = InternalHash(x);
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) { 
      current_pos += offset;  // Compute ith probe.
      offset +=2;
      collisions++;
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }

    offsetcopy = std::move(offset);
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
	Insert(std::move(entry.element_));
  }
  
  //Finds the key for inputted item.
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // QUADRATIC_PROBING_H
