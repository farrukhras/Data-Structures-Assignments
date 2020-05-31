#ifndef GRAPH__CPP
#define GRAPH__CPP
#include <fstream>
#include <list>
#include "Graph.h"

Graph::Graph(char* file, bool isUnitLength=false)
{
	string name;
	string name1;
	float index;

	ifstream myfile(file);

	if(myfile.is_open())
	{
		while ((myfile >> name) && (name != "CONNECTIONS"))
   	 	{
			if (name == "PEOPLE")
			{
				continue;
			}

			else
			{
				node* obj = new node;
				obj->name = name;
				obj->visit = 0;
				cities.push_back(obj);
			}
		}

		while(myfile >> name >> name1 >> index)
		{
			if (name == "CONNECTIONS")
			{
				continue;
			}

			else
			{
				node* temp_origin;
				node* temp_Dest;
				int siz = cities.size();

				for (int i = 0; i<siz; i++)
				{
					if (name == cities[i]->name)
					{
						temp_origin = cities[i]; 
					}
				}

				for (int i = 0; i<siz; i++)
				{
					if (name1 == cities[i]->name)
					{
						temp_Dest = cities[i]; 
					}
				}

				edge obj1;
				edge obj2;
				obj1.Origin = temp_origin;
				obj1.Dest = temp_Dest;
				obj2.Origin = temp_Dest;
				obj2.Dest = temp_origin;

				if (isUnitLength == true)
				{
					obj1.weight = 1;
					obj2.weight = 1;
				}
				else
				{
					obj1.weight = index;
					obj2.weight = index;
				}


				arcs.push_back(obj1);
				arcs.push_back(obj2);
				temp_origin->edges.push_back(obj1);
				temp_Dest->edges.push_back(obj2);
			}		
		}
    	myfile.close();
	}

	cout<<"File reading Successful"<<endl;
}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}

bool Graph::Reachable(string start, string dest) // USING DFS
{
	if (start == dest)
	{
		return true;
	}

	node* temp_node = new node; // temp node* which is updated recursively everytime a new starting name is set

	for (int x = 0; x < cities.size(); x++)
	{
		if (cities[x]->name == start)
		{
			cities[x]->visit = 1;
			temp_node = cities[x];
		}
	}

	if (temp_node->visit == 1)
	{
		return true;
	}

	//temp_node->visit = 1;
	int siz = temp_node->edges.size();
	//cout<<siz<<endl;
	int i = 0;

	while (i < siz)
	{
		node* temp1 = temp_node->edges[i].Dest;
		string temp_start = temp1->name;

		if(temp1->visit == 0)
		{
			Reachable(temp_start, dest);
		}

		i++;
	}
}

vector<node*> Graph::Prims()
{

}

vector<node*> Graph::Kruskal()
{
	/*priority_queue<edge, vector<edge>> pq; // initialise the priority queue

	for (int i = 0; i < arcs.size(); i++) // push all the edges in the priority queue
	{
		pq.push(arcs[i]);
	}*/


}

vector<string> Graph::Dijkstra(string start, string dest, float &d)
{
	int cities_size = cities.size();

	// allocate the distance field of allnodes to max value
	for (int i = 0; i < cities_size; i++)
	{
		cities[i]->distance = INT_MAX;
		cities[i]->visit = 0;
	}

	// find the node object of the start, start is a string so we find the corresponding node object for use in the function
	// this can be thougth of using the string start for understanding (the same is done for string dest)
	node* temp_source;
	node* temp_dest;

	for (int i = 0; i< cities_size; i++)
	{
		if (cities[i]->name == start)
		{
			temp_source = cities[i]; 
			break;
		}
	}

	for (int i = 0; i< cities_size; i++)
	{
		if (cities[i]->name == 	dest)
		{
			temp_dest = cities[i]; 
			break;
		}
	}

	temp_source->distance = 0;

	// copy the node objects in cities vector in a temp vector if we want to make changes to it
	vector<node*> temp_v;

	for (int i = 0; i< cities_size; i++)
	{
		//temp_v.push_back(cities[i]);
		if (cities[i]->name == temp_source->name)
		{
			temp_v.push_back(temp_source);
		}

		else
		{
			temp_v.push_back(cities[i]);
		}
	}

	//find the shortest distance
	while (temp_v.size() > 0)
	{
		// find node in the citites vector that has the minimum value for the distance variable
		node* min_node = NULL; // node with theminimum distance
		float min_distance = temp_v[0]->distance;
		int ind = 0; // index of the node with minimum_distance

		for (int i = 1; i < temp_v.size(); i++)
		{
			if(temp_v[i]->distance < min_distance)
			{
				min_distance = temp_v[i]->distance;
				//min_node = temp_v[i];
				ind = i;
			}
		}

		min_node = temp_v[ind];
		min_node->visit = 1; // this node has been visited

		temp_v.erase(temp_v.begin() + ind);  //remove this minimum node from the vector

		for (int i = 0; i < min_node->edges.size(); i++)
		{
			if (min_node->edges[i].Dest->visit == 0)
			{
				// calculate the new distance and update and use the path that has the smallest distance from source node
				float new_distance = min_node->edges[i].weight + min_node->distance;
				//d = min_node->edges[i].weight + min_node->distance;

				if (new_distance < min_node->edges[i].Dest->distance)
				{
					min_node->edges[i].Dest->res = min_node;
					min_node->edges[i].Dest->distance = new_distance;
				}
			}
		}
	}

	vector<node*> result; //vector that stores which name appear in the shortest path
	vector<string> result1; //vector that stores which name appear in the shortest path

	node* temp_ptr = temp_dest;

	while(temp_ptr != temp_source)
	{
		result.push_back(temp_ptr);
		temp_ptr = temp_ptr->res;
	}

	result.push_back(temp_source);
	d = temp_dest->distance;

	int siz = result.size() - 1;

	for (int i = 0; i< result.size(); i++)
	{
		string nam = result[siz]->name;
		result1.push_back(nam);
		siz--; 
	}

	return result1;
}

int main()
{
	cout<<"Initialize your graph in main!"<<endl;
	
	Graph object("friends.txt");

	//Test Part1 
	/*int siz = object.cities.size();
	cout<<"Cities vector size: "<<siz<<endl;

	int siz1 = object.arcs.size();
	cout<<"Arcs vector size: "<< siz1<<endl;
	
	for(int i = 0; i<siz; i++)
	{
		cout<<object.cities[i]->name<<endl;
	}

	for(int i = 0; i<siz1; i++)
	{
		cout<<object.arcs[i].Origin->name<<"		"<<object.arcs[i].Dest->name<<"	"<<object.arcs[i].weight<<endl;
	}*/

	//Test Part 2
	/*bool ans = object.Reachable("Mannan", "Ali");
	//bool ans = object.Reachable("Mannan", "Trump");
	//bool ans = object.Reachable("Ali", "Trump");
	if (ans == true)
	{
		cout<<"Connected"<<endl;
	}
	else
	{
		cout<<"Not Connected"<<endl;
	}*/

	//Test Part 3
	/*float distance = 0;
	
	vector<string> res = object.Dijkstra("Trump", "Ali", distance);

	for (int i = 0; i < res.size(); i++)
	{
		cout<<res[i]<<"		";
	}

	cout<<distance<<endl;*/

	//Test Part 4



	// write code for part 6 here
}

#endif
 /*
	Part 6 
	1)
		i- Mannan and Ali are connected
		ii- Mannan and Trump are connected
		iii- Ali and Trump are connected

		Deduction: Every node is connected to every other node in the graph.
	
	2) Ali is 2 hops away from Trump
	3) Mannan is 3 hops away from Trump



 */