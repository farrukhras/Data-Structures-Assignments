#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
}

template <class T>
Stack<T>::Stack(const Stack<T>& otherStack): list(otherStack.list)
{

}

template <class T>
Stack<T>::~Stack()
{
}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
    if (list.getHead() == NULL)
    {
       return list.getHead()->value;
    }
    else
    {
        T a = list.getHead()->value;
        return a;
    }
}

template <class T>
T Stack<T>::pop()
{
    if(list.getHead()->next == NULL)
    {
        return list.getHead()->value;
    }
    else
    {
        T a = list.getHead()->value;
        list.deleteHead();
        return a;
    }
}

template <class T>
int Stack<T>::length()
{
    int a = list.length();
    return a;
}

template <class T>
bool Stack<T>::isEmpty()
{
    if (list.getHead() == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif
