#ifndef VCS_CPP
#define VCS_CPP
#include "VCS.h"
#include <string>
#include <sstream>

//base constructor, init
VCS::VCS(string fname)
{
	curr_size = 0;
    filename = fname;
}

//destructor
VCS::~VCS()
{

}

string VCS::convert_to_string(int a)
{
    ostringstream str1;
    str1<<a;
    string str = str1.str();
    return str;
}


//time to commit
void VCS::commit(string msg)
{
    VCS_node* newnode = new VCS_node;
    newnode->time_stamp = curr_size;
    newnode->message = msg;
    curr_size++;

    string f_name = filename + convert_to_string(newnode->time_stamp) + ".txt";

    string read;
    ifstream file_read;
    file_read.open((filename + ".txt").c_str());

    ofstream file_write;
    file_write.open(f_name.c_str());

    while (getline(file_read, read))
    {
        file_write<<read;
    }
    file_read.close();
    file_write.close();

    while (!container2.isEmpty())
    {
        container1.push(container2.pop());
    }
    container1.push(*newnode);
    if (curr_size == 200)
    {
        curr_size = 199;
    }
}

//print status of every version
void VCS::status()
{

}

//goes one step back
string VCS::undo()
{
    VCS_node temp = container1.top();

    int temp_time_stamp = temp.time_stamp;

    container2.push(container1.pop());

    temp_time_stamp--;
    string read1;
    ifstream file_read;
    file_read.open((filename + convert_to_string(temp_time_stamp) + ".txt").c_str());

    ofstream file_write;
    file_write.open((filename + ".txt").c_str());

    while (getline(file_read, read1))
    {
        file_write<<read1;
    }
    file_read.close();
    file_write.close();

    return read1;
}

//one step ahead
string VCS::redo()
{
    VCS_node temp = container1.top();

    int temp_time_stamp = temp.time_stamp;

    container1.push(container2.pop());

    temp_time_stamp++;

    string read1;
    ifstream file_read;
    file_read.open((filename + convert_to_string(temp_time_stamp) + ".txt").c_str());

    ofstream file_write;
    file_write.open((filename + ".txt").c_str());

    while (getline(file_read, read1))
    {
        file_write<<read1;
    }
    file_read.close();
    file_write.close();

    return read1;
}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
    VCS_node temp = container1.top();
    string x;
    if (t_stamp < temp.time_stamp)
    {
        while (temp.time_stamp != t_stamp)
        {
            x = undo();
            temp.time_stamp--;
        }
    }
    else if (t_stamp > temp.time_stamp)
    {
        while (temp.time_stamp != t_stamp)
        {
            x = redo();
            temp.time_stamp++;
        }
    }

    return x;
}

#endif
