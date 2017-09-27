//Svetleen Guerrier
//Spring 2017 335
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include "SequenceMap.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns the number of recursion calls in the function. 
     */
    int contains( const Comparable & x ) 
    {
        int counter = 0;
        int result = contains( x, root, counter );
        return result;
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    /*
    * Calls Find function, similar to contains.
    */
    void find(const Comparable & x)
    {
        find( x, root);
    }
    /*
    * Calls the Height function. Returns Height of the tree.
    */
    double getHeight()
    {
        return Height(root);
    }
    /*
    *Calls and returns the Depth of the tree.
    */
    double getDepth()
    {
        return Internal_PathLength(root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    int remove( const Comparable & x )
    {
        int counter = 0;
        int result = remove( x, root, counter );
        return result;
    }
    /*
    *Calls and returns the Number of Nodes in the tree.
    */
    double GetNumberofNodes()
    {
        return NumberOfNodes(root);
    }

  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);  // Duplicate; do nothing
    }
    /*
    * If found cout the enzyme elements in the tree.
    * Compares elements currently in the tree to the comparable element
    * If not found cout not found.
    */
    void find( const Comparable& x, BinaryNode * & t)
    {
        if(t == nullptr)
            cout<<"Not found"<<endl;
        else if(x < t->element)
            find(x, t->left);
        else if(t->element < x)
            find(x, t->right);
        else
            t->element.output_vector(t->element);
    }
    /*
    * returns the depth of the tree 
    */
    double Internal_PathLength(BinaryNode * & t)
    {
        if(t==nullptr)
            return 0;
        else
        {
            return (Internal_PathLength(t->left) + Internal_PathLength(t->right) + NumberOfNodes(t)-1);
        }
    }
    /*
    * returns the height of the tree. 
    */
    double Height(BinaryNode * & t)
    {
        if(t==nullptr)
            return 0;
        else
        {
            return max(Height(t->left),Height(t->right)+1);
        }

    }
    /*
    * Returns the number of nodes in the tree.
    */
    double NumberOfNodes(BinaryNode * & t)
    {
        if(t==nullptr)
            return 0;
        else
        {
            return (NumberOfNodes(t->left)+NumberOfNodes(t->right)+1);
        }
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     *Count is the number of recursion calls return if negative or postive.
     */
    int remove( const Comparable & x, BinaryNode * & t, int count )
    {
        if( t == nullptr )
            return (count*-1);   // Item not found; do nothing
        if( x < t->element )
            return remove( x, t->left, count + 1 );
        else if( t->element < x )
            return remove( x, t->right, count + 1 );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            return remove( t->element, t->right, count + 1 );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            return count;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * count is the number of recursiion calls that the function uses.
     */
    
    int contains( const Comparable & x, BinaryNode *t, int count) 
    {
        if( t == nullptr )
            return (count*-1);
        else if( x < t->element )
            return contains( x, t->left,count+1);
        else if( t->element < x )
            return contains( x, t->right,count+1 );
        else
            return count;    // Match
    }
    
    /*
    bool contains( const Comparable & x, BinaryNode *t, int& count ) const
    {
        while( t != nullptr )
            if( x < t->element )
            {
                t = t->left;
                count = count+1;
            }
            else if( t->element < x )
            {
                t = t->right;
                count = count +1;
            }
            else
                return count;    // Match

        return (count*-1);   // No match
    }
    */
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif
