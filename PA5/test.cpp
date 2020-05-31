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

		while(!myfile.eof())
		{
			myfile >> name >> name1 >> index;

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
				//arcs.push_back(obj2);
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

	node *temp = new node;

	for (int x = 0; x < cities.size(); x++)
	{
		if (start == cities[x]->name)
		{
			cities[x]->visit = 1;
			temp = cities[x];
		}
	}

	if (temp->visit == 1)
	{
		return true;
	}

	for (int x = 0; x < temp->edges.size(); x++){

		node *checker = temp->edges[x].Dest;

		if (checker->visit == 0){
			Reachable(checker->name, dest);
		}

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

/*vector<string> Graph::Dijkstra(string start, string dest, float &d)
{
	for (int i = 0; i< cities.size(); i++)
	{
		cities[i]->distance = INT_MAX;
		cities[i]->visit = 0;
	}

	node* starting_node;
	node* destination_node;
	for (int i = 0; i< cities.size(); i++)
	{
		if (start == cities[i]->name)
		{
			starting_node = cities[i]; //start node is saved	 
			break;
		}
	}
		
	for (int i = 0; i< cities.size(); i++)
	{
		if (dest == cities[i]->name)
		{
			destination_node = cities[i]; //start node is saved	 
			break;
		}
	}
	
	starting_node->distance = 0;
	vector<node*> path_names;
		
	for (int i = 0; i< cities.size();i++)
	{
		path_names.push_back(cities[i]);
	}
		
	int vector_size = path_names.size();
	cout<<"hey"<<endl;	
	while (path_names.size() > 0)
	{
		float min_distance = path_names[0]->distance;

		int fazul = 0;
		node * minNode = NULL; //stores the node having the minimun distance
		for (int i = 1; i < path_names.size(); i++)
		{
			if (path_names[i]->distance < min_distance)
			{
				min_distance = path_names[i]->distance;
				//minNode = path_names[i]; // maybe change this
				fazul = i;
			}
		}

		minNode = path_names[fazul];
		minNode->visit = 1;

		path_names.erase(path_names.begin() + fazul);

		for (int i = 0; i<minNode->edges.size(); i++)
		{
			if (minNode->edges[i].Dest->visit == 0) //update distances
			{
				float dis = minNode->distance + minNode->edges[i].weight;
				if(dis < minNode->edges[i].Dest->distance)
				{
					minNode->edges[i].Dest->distance = dis;
					minNode->edges[i].Dest->res = minNode;
				}
			}
			//var++;
		}
	}

	//cout<<"hey"<<endl;	
	vector<string> result; //vector that stores which name appear in the shortest path

	node* temp_ptr = destination_node;

	while(temp_ptr != starting_node)
	{
		result.push_back(temp_ptr->name);
		temp_ptr = temp_ptr->res;
	}

	result.push_back(starting_node->name);
	d = destination_node->distance;

	return result;
}*/

int main()
{
	cout<<"Initialize your graph in main!"<<endl;
	
	Graph object("friends.txt");

	//bool ans = object.Reachable("Mannan", "Ali");
	//bool ans = object.Reachable("Mannan", "Trump");
	//bool ans = object.Reachable("Ali", "Trump");

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
	/*string n1 = "Michael";
	string n2 = "Amanda";

	bool truth = object.Reachable(n1, n2);
	cout<<truth<<endl;
	
	if (truth == true)
	{
		cout<<n1<<"  is connected to  "<<n2<<endl;		
	}
	
	else
	{
		cout<<n1<<"  is not connected to  "<<n2<<endl;
	}*/

	//Test Part 3
	float distance;
	
	vector<string> res = object.Dijkstra("Trump", "Ali", distance);

	for (int i = 0; i < res.size(); i++)
	{
		cout<<res[i]<<"		";
	}

	cout<<distance<<endl;

	//Test Part 4



	// write code for part 6 here
}

#endif
