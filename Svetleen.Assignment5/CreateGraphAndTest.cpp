/*
Svetleen Guerrier
Ioannis Stamos
CSCI335
Spring 2017
*/
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

/*
Function used to see if the graph inputs are connected or not
inputs graph data
outputs connection and weight.
*/
void
TestGraphInsert(const string &words_filename, const string &query_filename)
{
  cout << "TestFunctionForQueue..." << endl;
  cout << "Input file: " << words_filename << endl;
  cout << "Test filename: " << query_filename << endl; 
  
  //Opens file to input to Binomial Queue and hash table.
  
  ifstream infile; 
  string line;
  infile.open(words_filename);
  int get_numberofvertices = 0;
  
  infile>>get_numberofvertices;

  Graph Test(get_numberofvertices);
  while(getline(infile,line))
  { 

  	int iteration = 1;
  	int vertex = 0;
    int connectedVertex = 0;
    double weight = 0;
    stringstream strStream(line);
    while(strStream)
    {
    	if(iteration ==1)
    		strStream>>vertex;
    	strStream>>connectedVertex;
    	strStream>>weight;
    	if(strStream)
    		Test.AddEdge(vertex,connectedVertex,weight);
    	iteration++;
    }


  }
  
  cout<<"Successful input."<<endl;

  int vertex1 =0;
  int vertex2 =0;
  ifstream checkfile; 
  checkfile.open(query_filename);
  while(!(checkfile.eof()))
  {
  	checkfile>>vertex1;
  	checkfile>>vertex2;
  	double weight = Test.CheckConnection(vertex1,vertex2);
  	if(weight>0)
  	{
  		cout<< vertex1<<" "<<vertex2<<": Connected, weight of edge is "<<(weight/1.0)<<endl;
  	}

  	else
  		cout<< vertex1<<" "<<vertex2<<": Not Connected "<<endl;

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
  TestGraphInsert(words_filename, query_filename);    

  return 0;
}
