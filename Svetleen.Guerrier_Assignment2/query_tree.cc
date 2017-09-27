// Svetleen Guerrier
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

namespace 
{

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) 
{
  /* Test 1***********************************************
  Opens database file and inputs in to the tree after creating a new object
  called SequenceMap with the given enzymes and recognition sequence from the file.

  */
  string db_line;
  ifstream infile; 
  infile.open(db_filename);
  string an_enz_acro="";
  string a_reco_seq="";
  while(!(infile.eof()))
  {
    infile >> db_line;
    db_line = db_line.substr(0,(db_line.size()-2));
    stringstream strStream(db_line);
    getline(strStream,an_enz_acro,'/');
    while(getline(strStream,a_reco_seq,'/'))
    {
      SequenceMap new_sequence_map(a_reco_seq,an_enz_acro);
      a_tree.insert(new_sequence_map);
      a_reco_seq = "";
    }

  }
  /*
  Opens the input file 2a and searches the tree for the recognition sequences 
  If found cout the enzymes corresponding to the recognition sequence.
  */
  an_enz_acro="";
  string string1="";
  for(int i=0;i<3;i++)
  {
    cin>>string1;
    SequenceMap Check1(string1,an_enz_acro);
    a_tree.find(Check1);
    string1="";
  }

}

} // namespace

int
main(int argc, char **argv) 
{
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
