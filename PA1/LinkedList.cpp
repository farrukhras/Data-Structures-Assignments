#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include <iostream>
#include "LinkedList.h"
using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    if (otherLinkedList.head == NULL)
        {
            return;
        }

    head = NULL;
    T temp = otherLinkedList.head->value;
    head->value = temp;
    head->next = NULL;

    ListItem<T> *temp_ptr = otherLinkedList.head->next;
   
    while (temp_ptr != NULL)
    {
        cout<<"hey"<<endl;
        insertAtTail(temp_ptr->value);
        temp_ptr = temp_ptr->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    ListItem<T> *temp = head;

    if (head != NULL)
    {
        temp = temp->next;
        head->next = NULL;
        head->prev = NULL;
        delete head;

        while (temp != NULL)
        {
            head = temp;
            temp = temp->next;
            head->next = NULL;
            head->prev = NULL;
            delete head;
        }
        head = NULL;
    }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	if (head == NULL)
	{
		ListItem <T> *newnode = new ListItem<T> (item);
		newnode->next = NULL;
		newnode->prev = NULL;
		head = newnode;
		//newnode->value = item;
	}

	else
	{
		ListItem <T> *newnode = new ListItem<T> (item);
		//newnode->value = item;
		newnode->next = head;
		newnode->prev = NULL;
		head = newnode ;

		//if (head != NULL)
		//{
			//head->prev = newnode;
		//}

		//head = newnode;
	}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	if (head == NULL) //if list is empty then make newnode the head node
	{
		//insertAtHead(item);
		ListItem <T> *newnode = new ListItem<T> (item);
		newnode->next = NULL;
		newnode->prev = NULL;
		head = newnode;
	}

	else
	{
	    ListItem <T> *newnode = new ListItem<T> (item);
	    ListItem <T> *newnode2 = head ;
	    while(newnode2->next != NULL)
        {

            //else
            //{
                newnode2 = newnode2 -> next ;
                if (newnode2 -> next == NULL)
                    goto jump ;
            //}
        }
      //  if (newnode2 -> next == NULL)
        //    {
                //newnode2 = newnode;
                jump: newnode2 -> next = newnode ;
                newnode -> prev = newnode2 ;
                newnode -> next = NULL ;

          //  }

        //newnode->next = NULL;

		//ListItem<T> *temp_ptr = head; //temp_ptr to traverse through thr list to the end of the list

		//while (temp_ptr->next != NULL)
		//{
			//temp_ptr = temp_ptr->next;
		//}

		//temp_ptr->next = newnode;
		//newnode->prev = temp_ptr;
		//newnode -> next = NULL;

		//return;
	}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    ListItem<T> *temp1 = searchFor(afterWhat);

	if (head != NULL)
	{
        if (temp1 == NULL)
        {
            return;
        }

        ListItem<T> *newnode = new ListItem<T>(toInsert);
        newnode->next = temp1->next;
        newnode->prev = temp1;
        temp1->next = newnode;

        if (newnode->next != NULL)
        {
            newnode->next->prev = newnode;
        }
    }
}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
	ListItem<T> *temp = head;
	while (temp != NULL)
    {
        temp = temp->next;
    }
    return temp;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
    ListItem<T> *temp = head;

    while (temp != NULL)
    {
        if (temp->value == item)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    ListItem<T> *temp = head;
    if (head != NULL)
    {
        deleteHead();
    }
    else
    {
        while ((temp != NULL) && (temp->value != item))
        {
            temp = temp->next;
        }

        if (temp->value == item)
        {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete temp;
        }
    }
}

template <class T>
void LinkedList<T>::deleteHead()
{
    ListItem<T> *temp = head;

    if (temp == NULL)
    {
        delete head;
    }
    else
    {
        head = head->next;
        head->prev = NULL;
        delete temp;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    ListItem<T> *temp = head;
    if (head != NULL)
    {
        while (temp != NULL)
        {
            temp = temp->next;
        }
        delete temp;
    }
}

template <class T>
int LinkedList<T>::length()
{
    ListItem<T> *temp = head;

    if (head != NULL)
    {
        int counter = 0;
        while (temp != NULL)
        {
            temp = temp->next;
            counter++;
        }
        return counter;
    }
    else
    {
        return 0;
    }
}

#endif
