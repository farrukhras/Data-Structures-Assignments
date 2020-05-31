#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
#include <sstream>

// try to make get_node() and get_file() after tree initialization

Tree::Tree(string data)
{
	TreeItem* new_node = new TreeItem();
	new_node->id = 1;
	new_node->latest_data = data;
	VCS_node initial(data , 0);
	new_node->container.push_back(initial);
	root = new_node;
}

void Tree::Delete_helper(TreeItem* temp)
{
    if (temp->child.empty())
    {
        delete temp;
    }
    else
    {
        int child_list_size = temp->child.size();

        for (int j = 0; j < temp->child.size(); j++)
        {
            Delete_helper(temp->child[j]);
        }
        delete temp;
    }
}

Tree::~Tree()
{
    TreeItem* temp = root;

    while (temp != NULL)
    {
        if (temp->child.empty())
        {
            delete temp;
            delete root;
        }
        else
        {
            int child_list_size = temp->child.size();

            for (int i = 0; i< child_list_size; i++)
            {
                Delete_helper(temp->child[i]);
            }
            delete temp;
            delete root;
        }
    }
}

void Tree::branch(int id)
{
	TreeItem* temp = get_node(id); //temp points to the parent jis ko bacha dena hai
    int node_ke_bache = temp->child.size();

	if (temp != NULL)
	{
		if (node_ke_bache < 3)
		{
		    int new_node_ke_bache = node_ke_bache + 1;

            //converting the id of parent and child number of the child to string for example
            //a parent with id 1 has 1 child, then the id of the child will be 11,
            //to get this id we will convert the id of parent and child number to string and concatenate them
            //and finally convert them to int to get the id of child

            //converting parent id to string
            ostringstream id_of_node;
            id_of_node << id;
            string parent_id = id_of_node.str();

            //converting child number to string
            ostringstream child_number_in_string;
            child_number_in_string << new_node_ke_bache;
            string child_number = child_number_in_string.str();

            //concatenate id's
			string chil_id = parent_id + child_number;

            //convert the id from string to int
            stringstream to_convert(chil_id);
            int child_id = 0;
            to_convert >> child_id;

			int id_of_child = child_id;

			TreeItem *child = new TreeItem; //child pointer points to the child of the parent
			child->id = id_of_child;
			child->latest_data = temp->latest_data;

            //put the child onto the list of children for the current parent
			VCS_node temp1(temp->latest_data , 0);
			child->container.push_back(temp1);
			temp->child.push_back(child);
		}
	}
}

void Tree::merge(int src_id,int dst_id)
{
    TreeItem* source_node = get_node(src_id);
    TreeItem* dest_node = get_node(dst_id);

    if ((source_node != NULL) && (dest_node != NULL))
    {
        //save the merge history in the history vector
        merge_state state;
		state.src_id = src_id;
		state.dst_id = dst_id;
		history.push_back(state);

        //append data from latest version of source to the end of data in latest version of destination
        string source_data;
        source_data = source_node->latest_data;
        dest_node->latest_data = dest_node->latest_data + source_data;

        //store the new data, after merging, at the end of the dest container
		dest_node->container[dest_node->container.size()-1].data = dest_node->latest_data;
    }
}

void Tree::commit(int src_id,string new_data)
{
	TreeItem *node = get_node(src_id); // node on whom commit is called

	if(node != NULL)
	{
	    int size_of_current_container = node->container.size();
        string old_data = node->latest_data;
        string newdata = old_data + new_data; // data to be stored on the newer version of the file

        VCS_node vcs; //create a node of type VCS and declare its elements
        vcs.data = newdata;
        vcs.time_stamp = size_of_current_container;

        node->latest_data = newdata;
        node->container.push_back(vcs); //stores the newer version of the file in the vector within our node
	}
}

string Tree::get_file(int id, int t_stamp)
{
    TreeItem* file = get_node(id);
    //int container_size = file->container.size();
    string ret = "";

    if (file != NULL)
    {
        for(int i = 0; i < file->container.size(); i++)
        {
            if (file->container[i].time_stamp == t_stamp)
            {
                return file->container[i].data;
            }
        }
    }
    return ret;
}

TreeItem* Tree::get_node(int id)
{
	if(id == 1)
    {
        return root;
    }

	if(id >= 11 && id <= 13)
	{
		if(!root->child.empty()) // root has at least 1 child
        {
            for(int i = 0; i < root->child.size(); i++)
            {
                if (root->child[i]->id == id)
                {
                    return root->child[i];
                }
            }
            return NULL;
        }

		else{return NULL;}
	}

	else if(id >= 111 && id <= 193)
	{
		if(!root->child.empty()) //root has at least 1 child
		{
			for(int i = 0; i < root->child.size(); i++)
            {
                if (root->child[i]->id == id/10)
                {
                    TreeItem* root_child = root->child[i];

					if(!root_child->child.empty()) // if root's children have at least 1 child
					{
						for(int i = 0; i < root_child->child.size(); i++)
                        {
                            if(root_child->child[i]->id == id)
                            {
                                return root_child->child[i];
                            }
                        }
					}
					else{return NULL;}

                }
            }
			return NULL;
		}

		else{return NULL;}
    }

    else{return NULL;}
}

vector<merge_state> Tree::merge_history()
{
	return history ;
}

void Tree::level_traversal()
{
	if (root == NULL)
    {
        return;
    }

	else
    {
        Queue<TreeItem*> queu;

        while(root != NULL)
        {
            cout<<"ID of Node: "<<root->id<<endl;
            cout<<"Latest Data: "<<root->latest_data<<endl<<endl;

            int child_size = root->child.size();

            for (int i = 0 ; i < child_size; i++)
            {
                queu.enqueue(root->child[i]); // inserts the current root ka child at the end of the queue
            }

            root = queu.dequeue(); // sets root to its next child
        }
    }
}

#endif
