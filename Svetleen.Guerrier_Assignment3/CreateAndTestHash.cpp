/*
Svetleen Guerrier
Class: CSCI335

*/
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleProbing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



template <typename HashTableType>
void
TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();  
  
  //Opens file to input tohash table.
  ifstream infile; 
  infile.open(words_filename);
  string get_line="";
  while(!(infile.eof()))
  {
    infile>>get_line;
    hash_table.Insert(get_line);
  }

  //Outputs Collisions, Number of Elements, Size of Table, Load factor, and Average Number of Collisions.
  cout << "Collisions: " << hash_table.TotalNumberofCollisions() << endl;
  cout << "Number of items: " << hash_table.NumberofElements() << endl;
  cout << "Size of hash table: " << hash_table.SizeofTable() << endl;
  cout << "Load factor: " << hash_table.loadfactor() << endl;
  cout << "Avg. number of collisions: " << hash_table.AverageNumberofCollisions() << endl;

  //Opens file to compare use with HashTable
  get_line = "";
  ifstream nextfile;
  nextfile.open(query_filename);
  
  cout<<endl;

  //Compares inputed to whats in the HashTable. outputs found if found. else otherwise.
  while(!(nextfile.eof()))
  {
    nextfile>>get_line;
    if(hash_table.Contains(get_line)==true)
      cout<<get_line<<"->Found. Number of Probes: " << hash_table.Probing() << endl;
    else
      cout<<get_line<<"->Not Found. Number of Probes: " <<hash_table.Probing() << endl;
  }
}

// Sample main for program CreateAndTestHash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
