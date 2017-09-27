/*
Svetleen Guerrier
Class: CSCI335
BinomialQueue search.
*/
#include "BinomialQueue.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
Inserts Element into the Binomial queue Searches through the queue.
If found function in .h returns true.
If not found function in .h returns false.
Flag is outputted to the user.

Tells user number of Inputs and the Minimum Element.
*/
template <typename BinomialQueueType>
void
TestQueueInsert(BinomialQueueType &BinomialQueue, const string &words_filename, const string &query_filename)
{
  cout << "TestFunctionForQueue..." << endl;
  cout << "Input file: " << words_filename << endl;
  cout << "Test filename: " << query_filename << endl; 
  
  //Opens file to input to Binomial Queue and hash table.
  ifstream infile; 
  infile.open(words_filename);
  int get_int=0;
  while(!(infile.eof()))
  {
    infile>>get_int;
    BinomialQueue.insert(get_int);
  }

  cout<<"Success Inserting "<<BinomialQueue.size()<<" into the Queue."<<endl;
  cout<<"Minimum Element is: "<<BinomialQueue.findMin()<<endl;


  get_int = 0;
  ifstream checkfile; 
  checkfile.open(query_filename);
  while(!(checkfile.eof()))
  {
  	checkfile>>get_int;
  	if(BinomialQueue.Find(get_int)==true)
  		cout<<get_int<<"-> Found."<<endl;
  	else
  		cout<<get_int<<"-> Not Found."<<endl;
  }
} 
int main(int argc, char **argv) 
{
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <InputFile> <SearchFile>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);

  BinomialQueue<int>B_Queue;
  TestQueueInsert(B_Queue, words_filename, query_filename);    

  return 0;
}
