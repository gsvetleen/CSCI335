//Svetleen Guerrier
//The chain has two private data memebers array and size, pointer and size_t respectively
//what they are members along with the public member functions that create and modify chains
//of any type.

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <cstddef>
#include <sstream>

namespace teaching_project {
// Chain class to create and modify chains.
template<typename Object>
class Chain 
{
 public:

  // Zero-parameter constructor.
  Chain()
  {
    array_ = nullptr;
    size_ = 0;
  }

  // Copy-constructor.
  Chain(const Chain &rhs)
  {
    //create new object equal to parameter size
    array_ = new Object[rhs.size_];
    for(size_t i = 0; i < rhs.size_;i++)
    {
        //set values
        array_[i] = rhs.array_[i];
    }
    //set parameter size.
    size_ = rhs.size_;
  }

  Chain& operator=(const Chain &rhs)
  {
    
    //create new chain equal to parameter
    Chain copy = rhs; 
    //make a new synonym 
    std::swap(*this, copy);
    return *this;
  
  }

  // Move-constructor. 
  Chain(Chain &&rhs)
  {
    //move value types then set paramet values to zero.
    array_ = rhs.array_;
    size_ = rhs.size_;
    rhs.array_ = nullptr;
    rhs.size_ = 0;
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Chain& operator=(Chain &&rhs)
  {
    //swap paramtr values
    std::swap(size_,rhs.size_);
    std::swap(array_,rhs.array_);
    return *this;
  }

  ~Chain() 
  {
    //destroy pointer and set size to zero.
    size_ =0;
    array_=nullptr;
    delete array_;
  }

  // End of big-five.

  // One parameter constructor.
  Chain(const Object& item) 
  {
    //create new object equal to 1 and set value
    array_ = new Object[1];
    array_[0] = item;
    size_ = 1;
  }

  // Read a chain from standard input.
  void ReadChain() 
  {
    //read input
    std::string chain;
    std::getline(std::cin,chain);
    chain = chain.substr(1,(chain.size()-2));
    std::stringstream strStream(chain);
    std::string getsize;

    //seperate non int or string values
    std::getline(strStream,getsize,':');
    size_t getreal;

    std::stringstream sizeconverter(getsize);
    sizeconverter >> getreal;
    size_ = getreal;

    //set size based on first integer
    array_ = new Object[size_];
    //set values
    for(size_t i = 0; i < size_;i++)
    {
      strStream >> array_[i];
    }

  }

  //return size of object
  size_t size() const 
  { 
    return size_;
  }

  // @location: an index to a location in the chain.
  // @returns the Object at @location.
  // const version.
  // abort() if out-of-range.
  const Object& operator[](size_t location) const 
  { 
    if((location >=0) && (location<size_))
      return array_[location];
    else
      abort();
  }

 // @location: an index to a location in the range.
 // @returns the Object at @location.
 // non-const version.
 // abort() if out-of-range.
 Object& operator[](size_t location) 
 { 
   if((location >=0) && (location<size_))
      return array_[location];
    else
      abort();
 }

 //  @c1: A chain.
 //  @c2: A second chain.
 //  @return the concatenation of the two chains.
 friend Chain operator+(const Chain &c1, const Chain &c2) 
 {
   //create new object
   Chain c3;
   int counter = 0;
   //set size equal to both parameter size member
   size_t total = c1.size_ + c2.size_;
   //allocate new chain array based on new size.
   c3.array_ = new Object[total];

   //copy values from first chain
   for(size_t i = 0; i < c1.size_; i++)
   {
      c3.array_[i] = c1.array_[i];
   }
   //copy values from second chain.
   for(size_t i = c1.size_; i < total; i++)
   {
      c3.array_[i] = c2.array_[counter];
      counter++;
   }
   //set size parameter
   c3.size_= total;

   return c3;
 }

 friend Chain operator+(const Chain &c1, const Object &s3)
 {
    //create new object
    Chain c4;
    //set size equal to one plus the parameter chain size.
    size_t total = c1.size_ + 1;

    //allocate new size
    c4.array_ = new Object[total];
    //copy array values
    for(size_t i = 0; i < c1.size_; i++)
    {
      c4.array_[i] = c1.array_[i];
    }
    //copy object
    c4.array_[c1.size_] = s3;
    //set size
    c4.size_ = total;

    return c4;

 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain)
 {
    //output data that is in array.
    out<<"[ ";
    for(int i = 0; i < a_chain.size_;i++)
    {
      out<<a_chain.array_[i]<<" ";
    }

    out<<"]"<<std::endl;
   return out;
 }
 
 private:
  size_t size_;
  Object *array_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_
