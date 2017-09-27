// Svetleen Guerrier
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) 
{

  /*Test 1****************************
  -> Opens and Inputs the  file containng the enzyme and recognition sequence using getline
    and sringstream.
  -> Creates a new object based on the two strings.
  -> Inputs object into the tree. 

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
  /*Test 2 and 3***************************
  ->Finds the average depth by taking the number of nodes
  of the tree and the Depth and dividing. Outputs result
  ->Finds and outputs the ratio by dividing average depth by height.
  ->Outputs the number of Nodes.

  */
  double Depth = a_tree.getDepth();
  double NumNodes = a_tree.GetNumberofNodes();
  double Height = a_tree.getHeight();
  double Average_depth = (Depth/NumNodes);
  double Ratio = (Average_depth/Height);


  cout<<"(2) Number of Nodes: "<<NumNodes<<endl;
  cout<<"(3a) Average Depth: "<<Average_depth<<endl;
  cout<<"(3b) Ratio: "<<Ratio<<endl;

  /*Test 4*************************************
  ->Opens sequence file and creates a new object with an empty enzyme.
  ->Calls the public contains function which counts the number of calls and returns 
    whether the item is found or not.
  ->Calculates the total successful queries and total recursion calls.
  ->couts average recursion calls to successful queries.
  ->couts successful queries and average number of recursion calls to successful querries.
  */
  string seq_line="";
  an_enz_acro="";
  ifstream inputfile;
  inputfile.open(seq_filename);
  int total_queries = 0;
  int recursioncalls = 0;
  double Avg_Rec = 0;

  while(!(inputfile.eof()))
  {
    inputfile >> seq_line;
    SequenceMap Check2(seq_line,an_enz_acro);
    recursioncalls = a_tree.contains(Check2);
    if (recursioncalls<0)
    {
      recursioncalls*=-1;
      Avg_Rec+=recursioncalls;
      continue;
    }
    Avg_Rec+=recursioncalls;
    total_queries++;
  }

  cout<<"(4a) Number of successful Matches: "<< total_queries <<endl;
  cout<<"(4b) Average number of Recursion Calls: "<< Avg_Rec/total_queries<<endl;

  //Test 5***************************************
  /*
  ->Goes back to beginning of the file.
  ->Removes every other recognition sequence found in the file in the tree.
  ->Calls remove function which returns the number of recursion counts and the removal 
    success.
  ->couts total successful calls and average number of recursion calls to successful querries.

  */
  inputfile.clear();
  inputfile.seekg (0, ios::beg);
  seq_line ="";
  Avg_Rec = 0;
  total_queries = 0;
  
  while(!(inputfile.eof()))
  {
    inputfile >>seq_line;
    SequenceMap Check3(seq_line,an_enz_acro);
    recursioncalls = a_tree.remove(Check3);
    if (recursioncalls<0)
    {
      recursioncalls*=-1;
      Avg_Rec+=recursioncalls;
    }
    else
    {
      Avg_Rec+= recursioncalls;
      total_queries++;
    }

    inputfile >> seq_line;

  }

  cout<<"(5a) Number of successful removes: "<< total_queries <<endl;
  cout<<"(5b) Average number of Remove Recursion Calls: "<< Avg_Rec/total_queries<<endl;

  /*Test 6*************************************************
  -> Couts the modified number of nodes, Average Depth, and Adjusted Ratio.
  */
  Depth = a_tree.getDepth();
  NumNodes = a_tree.GetNumberofNodes();
  Height = a_tree.getHeight();
  Average_depth = (Depth/NumNodes);
  Ratio = (Average_depth/Height);


  cout<<"(6a) Adjusted Number of Nodes: "<<NumNodes<<endl;
  cout<<"(6b) Adjusted Average Depth: "<<Average_depth<<endl;
  cout<<"(6c) Adjusted Ratio: "<<Ratio<<endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
