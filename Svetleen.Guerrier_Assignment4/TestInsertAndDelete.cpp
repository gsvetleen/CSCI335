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
Inserts Element into the Binomial queue Deletes through numbers given
in the file through the queue.

If it is a successful remove return true
If not return false.

Tells user number of Inputs and the Minimum Element.
*/
template <typename BinomialQueueType>
void
TestQueueInsert(BinomialQueueType &BinomialQueue, const string &words_filename, const string &query_filename)
{
  cout << "TestFunctionForQueue..." << endl;
  cout << "Input file: " << words_filename << endl;
  cout << "Test filename: " << query_filename << endl; 
  
  //Opens file to input to Binomial Queue and table.
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
  	if(BinomialQueue.Remove(get_int)==false)
  		cout<<"Problem with Remove for "<<get_int<<endl;
  	else
  		cout<<"Deletion of "<<get_int<<" Successful. New Minimum is: "<<BinomialQueue.findMin()<<endl;
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
