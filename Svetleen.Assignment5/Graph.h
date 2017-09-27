/*
Svetleen Guerrier
Ioannis Stamos
CSCI335
Spring 2017
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <Queue>
#include <list>
using namespace std;

class Graph
{
public:
	/*
	Sets the Vectors to number Vertexes
	Intializes Vertex object for each vertex.
	*/
	Graph(int& numberofvectors)
	{
		numvectors = numberofvectors;
		list_Vertex.resize(numvectors);
		indegrees.resize(numvectors);

		for(auto& i : list_Vertex)
		{
			i = new Vertex;
		}

		for(int i = 0; i<numvectors; i++)
		{
			list_Vertex[i]->Vertexnumber = i+1;
		}

	}
	/*
	inputs adjacent edge to the adjacency list and sets indegress for each 
	adjacent vertex.
	*/
	void AddEdge(int& vertex1, int& vertex2, double& weight)
	{	
		Vertex::Adjacency a;
		a.AdjacencyNumber = vertex2;
		a.weight = weight;
	
		list_Vertex[vertex1-1]->Aj.push_back(a);

		indegrees[vertex2-1]+=1;

	}
	/*
	Sorting algorithm requiring the use of the adjacency list,and 
	already setted indegrees.
	*/
	void TopologicalSort()
	{
		queue<Vertex*> q;
		
		for(int i = 0;i<numvectors;i++)
		{
			if(indegrees[i]==0)
				q.push(list_Vertex[i]);
				
		}
		int counter = 0;
		vector<Vertex*> top_order;
		top_order.reserve(numvectors);

		while(!q.empty() )
		{
			Vertex* V = q.front();
			q.pop();
			top_order.push_back(V);

			const auto& startlist = V->Aj;
			for(auto i= startlist.begin(); i!=startlist.end();i++)
			{
				if(--indegrees[(i->AdjacencyNumber)-1]==0)
					q.push(list_Vertex[(i->AdjacencyNumber)-1]);
				
			}

			counter++;
		}
		
		if(counter!=numvectors)
		{
			cout<<"There is a cycle"<<endl;
			return;
		}
		
		for(int i = 0;i < numvectors;i++)
		{
			cout<<top_order[i]->Vertexnumber<<" ";
		}

		
		cout<<endl;

	}
	/*
	Dijkstra Algorithm takes the input for the starting vertex
	and sets the cost and number of paths for each adjacent vertex.
	*/
	void Dijkstra(const int& first)
	{
		priority_queue<Vertex*,vector<Vertex*>, compare> pq;

		for(auto& j: list_Vertex)
		{
			j->visited = false;
			j->distance = 10000;
		}

		Vertex* start = list_Vertex[first-1];
		start->distance = 0;

		pq.push(start);
		while(!pq.empty())
		{
			Vertex* temp = pq.top();
			pq.pop();
			temp->visited = true;

			const auto& startlist = temp->Aj;
			for(auto i = startlist.begin(); i!=startlist.end();i++)
			{
				Vertex* hold = list_Vertex[(i->AdjacencyNumber)-1];
				if(hold->visited == false)
				{
					if(temp->distance + i->weight < hold->distance)
					{
						hold->distance = temp->distance + i->weight;
						hold->path = temp;
						pq.push(hold);
					}
				}

			}
			
		
		}

		PrintPath(first);


	}
	/*
	Prints out the path for the DijkStra Algorithm 
	as well as the total cost for each vertex.
	*/
	void PrintPath(int first)
	{
		vector<int>path;
		for(int i = 0; i < list_Vertex.size();i++)
		{
			cout<<i+1<<": ";
			Vertex* hold = list_Vertex[i];
			int cost = hold->distance;
			while(hold!=nullptr)
			{
				if(hold->Vertexnumber==0)
					hold->Vertexnumber = i+1;
				path.push_back(hold->Vertexnumber);
				hold = hold->path;
			}
			
			reverse(path.begin(),path.end());
			for(int i= 0; i<path.size();i++)
			{
				cout<<path[i]<<" ";
			}
			path.clear();

			cout<<"(Cost: "<<cost<<")"<<endl;
		}
	}
	/*
	Returns the weight of Vertex if it is connected.
	If not connected -1 will indicate that its not.
	*/
	double CheckConnection(int vertex1, int vertex2)
	{
		Vertex* check = list_Vertex[vertex1-1];

		const auto& checklist = check->Aj;
		for(auto i = checklist.begin(); i!= checklist.end();i++)
		{
			if(i->AdjacencyNumber == vertex2)
			{
				return i->weight/1.0;
			}
		}

		return -1;
	}

private:
	struct Vertex
	{
		//Adjacency vertex to see the neighboring vertexes.
		struct Adjacency
		{

			int AdjacencyNumber;
			double weight;
			Adjacency() : AdjacencyNumber{}, weight{} {}
		};

		list<Adjacency> Aj;
		int Vertexnumber;
		bool visited;
		int distance;
		Vertex* path;
		
		Vertex() : Aj{}, Vertexnumber {}, visited {}, distance {}, path{nullptr} {}

	};
	//Compares distaces of Vertexes.
	struct compare{

		bool operator()(const Vertex* l1, Vertex* l2)
		{
			return l1->distance > l2->distance;
		}
	};


	int numvectors;
	vector<int> indegrees;
	vector<Vertex*> list_Vertex;

	
};

#endif