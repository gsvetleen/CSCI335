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
Function used for the Dijkstra Algorithm
inputs graph inputs outs shortest paths.
*/
void
TestDijkstra(const string &words_filename, int& v)
{
  cout << "TestFunctionForQueue..." << endl;
  cout << "Input file: " << words_filename << endl;
  
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

  Test.Dijkstra(v);
} 






int main(int argc, char **argv) 
{
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <InputFile> <startvertex>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  int vertex_given = atoi(argv[2]);
  TestDijkstra(words_filename, vertex_given);    

  return 0;
}