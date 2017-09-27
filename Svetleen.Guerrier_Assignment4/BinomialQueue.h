/**
Svetleen Guerrier
Class: CSCI335
BinomialQueue
*/
#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include "HashTable.h"
#include <cstdlib>
using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue
{
  public:
    BinomialQueue( ) : theTrees( DEFAULT_TREES )
    {
        for( auto & root : theTrees )
            root = nullptr;
        currentSize = 0;
    }
    //Creates new Queue item.
    BinomialQueue( const Comparable & item ) : theTrees( 1 ), currentSize{ 1 }
    {
      theTrees[ 0 ] = new BinomialNode{ item, nullptr, nullptr, nullptr}; 
    }

    BinomialQueue( const BinomialQueue & rhs )
      : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
    { 
        for( int i = 0; i < rhs.theTrees.size( ); ++i )
            theTrees[ i ] = clone( rhs.theTrees[ i ] );
    }

    BinomialQueue( BinomialQueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
    { 
    }

    ~BinomialQueue( )
      { makeEmpty( ); }

    
    /**
     * Deep copy.
     */
    BinomialQueue & operator=( const BinomialQueue & rhs )
    {
        BinomialQueue copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    BinomialQueue & operator=( BinomialQueue && rhs )
    {
        std::swap( currentSize, rhs.currentSize );
        std::swap( theTrees, rhs.theTrees );
        
        return *this;
    }
    
    /**
     * Return true if empty; false otherwise.
     */
    bool isEmpty( ) const
      { return currentSize == 0; }

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
        {
          cout<<"Queue is empty."<<endl; 
          exit(1);
        }

        return theTrees[ findMinIndex( ) ]->element;
    }
    
    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( const Comparable & x )
    { 
      BinomialQueue oneItem{ x };
      BinomialTable.Insert(x, oneItem.theTrees[0]); 
      mergesimple( oneItem ); 
    }
    /*
    Function specifically designed for one element insertion.
    Deletes cases 1, 0, 6, and 7.
    */

    void mergesimple(BinomialQueue &rhs)
    {
      if( this == &rhs )    // Avoid aliasing problems
            return;
      
      currentSize += rhs.currentSize;

      if( currentSize > capacity( ) )
      {
        int oldNumTrees = theTrees.size( );
        int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
        theTrees.resize( newNumTrees );
        for( int i = oldNumTrees; i < newNumTrees; ++i )
            theTrees[ i ] = nullptr;
      }

      BinomialNode *carry = nullptr;
      for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
      {
          BinomialNode *t1 = theTrees[ i ];
          //If the current i is greater than the size of rhs. set rhs to null.
          BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;

          int whichCase = t1 == nullptr ? 0 : 1; //If t1 is not empty then it receieves case 1.
          whichCase += t2 == nullptr ? 0 : 2; //If tree 2 is not empty then it receieves case 2.
          whichCase += carry == nullptr ? 0 : 4; //If carry is not empty then 
          switch( whichCase )
          {
            case 2: /* Only rhs */
              theTrees[ i ] = t2;
              rhs.theTrees[ i ] = nullptr;
              break;
            case 4: /* Only carry */
              theTrees[ i ] = carry;
              carry = nullptr;
              break;
            case 3: /* this and rhs */
              carry = combineTrees( t1, t2 );
              theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
              break;
            case 5: /* this and carry */
              carry = combineTrees( t1, carry );
              theTrees[ i ] = nullptr;
              break;
          }
        
      }    
      for( auto & root : rhs.theTrees )
        root = nullptr;
      rhs.currentSize = 0;
  }

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( Comparable && x )
    { 
      BinomialQueue oneItem{ std::move( x ) }; 
      BinomialTable.Insert(x, oneItem.theTrees[0]);
      mergesimple( oneItem ); 
    }
    
    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {
        Comparable x;
        deleteMin( x );
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem )
    {
        if( isEmpty( ) )
        {
          cout<<"Queue is empty."<<endl; 
          exit(1);
        }

        int minIndex = findMinIndex( );
        minItem = theTrees[ minIndex ]->element;

        BinomialNode *oldRoot = theTrees[ minIndex ];
        BinomialNode *deletedTree = oldRoot->leftChild;
        oldRoot = nullptr;
        delete oldRoot;

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize( minIndex );
        deletedQueue.currentSize = ( 1 << minIndex ) - 1;
        for( int j = minIndex - 1; j >= 0; --j )
        {
            deletedQueue.theTrees[ j ] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[ j ]->nextSibling = nullptr;
        }

        // Construct H'
        theTrees[ minIndex ] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge( deletedQueue );
    }

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & root : theTrees )
            makeEmpty( root );
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
    void merge( BinomialQueue & rhs )
    {
        if( this == &rhs )    // Avoid aliasing problems
            return;

        currentSize += rhs.currentSize;
        if( currentSize > capacity( ) )
        {
            int oldNumTrees = theTrees.size( );
            int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
            theTrees.resize( newNumTrees );
            for( int i = oldNumTrees; i < newNumTrees; ++i )
                theTrees[ i ] = nullptr;
        }

        BinomialNode *carry = nullptr;
        for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
        {
            BinomialNode *t1 = theTrees[ i ];
            //If the current i is greater than the size of rhs. set rhs to null.
            BinomialNode *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;

            int whichCase = t1 == nullptr ? 0 : 1; //If t1 is not empty then it receieves case 1.
            whichCase += t2 == nullptr ? 0 : 2; //If tree 2 is not empty then it receieves case 2.
            whichCase += carry == nullptr ? 0 : 4; //If carry is not empty then 

            switch( whichCase )
            {
              case 0: /* No trees */
              case 1: /* Only this */
                break;
              case 2: /* Only rhs */
                theTrees[ i ] = t2;
                rhs.theTrees[ i ] = nullptr;
                break;
              case 4: /* Only carry */
                theTrees[ i ] = carry;
                carry = nullptr;
                break;
              case 3: /* this and rhs */
                carry = combineTrees( t1, t2 );
                theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
                break;
              case 5: /* this and carry */
                carry = combineTrees( t1, carry );
                theTrees[ i ] = nullptr;
                break;
              case 6: /* rhs and carry */
                carry = combineTrees( t2, carry );
                rhs.theTrees[ i ] = nullptr;
                break;
              case 7: /* All three */
                theTrees[ i ] = carry;
                carry = combineTrees( t1, t2 );
                rhs.theTrees[ i ] = nullptr;
                break;
            }
        }
        for( auto & root : rhs.theTrees )
            root = nullptr;
        rhs.currentSize = 0;
    }    
    //Returns whether the not the elemet is in the queue or not.
    bool Find(const Comparable & x )
    {
      return (BinomialTable.Contains(x));
    }
    //Returns size of the queue.
    size_t size()
    {
       return currentSize;
    }
    
    /*
    Function recieves pointer to the node we want to delete.
    Swap the element from the botttom all the way to the top.
    the elements we passed will be removedfrom hashed table then updated with the element along with the new pointer.
    Set the element when it reaches the root to a low value.
    Delete Min.

    If not found flag not found. 

    */
    bool Remove(Comparable x)
    {
      if(!(BinomialTable.Contains(x)==true))
        return false;
     
      BinomialNode *removecopy = BinomialTable.ReturnP(x);
      while(removecopy->parentnode!=nullptr)
      {
        BinomialTable.Remove(removecopy->parentnode->element);
        swap(removecopy->element,removecopy->parentnode->element);
        BinomialTable.Insert(removecopy->element,removecopy); 
        removecopy = removecopy->parentnode;
      }
      BinomialTable.Remove(removecopy->element);
      if(BinomialTable.Contains(removecopy->element)==true)
        return false;
      
      removecopy->element = -25;
      deleteMin();
      return true;
    }
    //Swap variable.
    void swap(Comparable& a, Comparable& b)
    {
        Comparable Temp;
        Temp = a;
        a = b;
        b = Temp;
    }

  private:
    struct BinomialNode
    {
        Comparable    element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
        BinomialNode *parentnode;

        BinomialNode( const Comparable & e, BinomialNode *lt, BinomialNode *rt, BinomialNode *pt )
          : element{ e }, leftChild{ lt }, nextSibling{ rt }, parentnode { pt } { }
        
        BinomialNode( Comparable && e, BinomialNode *lt, BinomialNode *rt, BinomialNode *pt )
          : element{ std::move( e ) }, leftChild{ lt }, nextSibling{ rt }, parentnode { pt } { }

    };

    const static int DEFAULT_TREES = 1;
    HashTable<Comparable,BinomialNode*>BinomialTable;
    vector<BinomialNode *> theTrees;  // An array of tree roots
    int currentSize;                  // Number of items in the priority queue

    
    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    int findMinIndex( ) const
    {
        int i = 0;
        int minIndex = 0;

        for( i = 0; theTrees[ i ] == nullptr; ++i )
            ;

        for( minIndex = i; i < theTrees.size( ); ++i )
            if( theTrees[ i ] != nullptr &&
                theTrees[ i ]->element < theTrees[ minIndex ]->element )
                minIndex = i;

        return minIndex;
    }

    /**
     * Return the capacity.
     */
    int capacity( ) const
      { return ( 1 << theTrees.size( ) ) - 1; }

    /**
     * Return the result of merging equal-sized t1 and t2.
     * Set parent node.
     */
    BinomialNode * combineTrees( BinomialNode *t1, BinomialNode *t2 )
    {
        if( t2->element < t1->element )
            return combineTrees( t2, t1 );

        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        t2->parentnode = t1;
        return t1;
    }

    /**
     * Make a binomial tree logically empty, and free memory.
     */
    void makeEmpty( BinomialNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->leftChild );
            makeEmpty( t->nextSibling );
            
            delete t;
            t = nullptr;
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinomialNode * clone( BinomialNode * t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinomialNode{ t->element, clone( t->leftChild ), clone( t->nextSibling ) };
    }

};

#endif