#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"

void swap (int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

MinHeap::MinHeap(int cap)
{
    harr = new int[cap];
    capacity = cap;
    heap_size = 0;
}

void MinHeap::MinHeapify(int i)
{
    //we set the last element in the harr as the root node and now recusively make the new arr follow both BST and HEAP properties
    int left_node = left(i);
    int right_node = right(i);
    int temp;

    if (right_node >= heap_size)
    {
        if (left_node >= heap_size) {return;}
        else {temp = left_node;}
    }
    else
    {
        if (harr[left_node] <= harr[right_node]) {temp = left_node;}
        else {temp = right_node;}
    }

    if (harr[i] > harr[temp])
    {
        swap(&harr[temp], &harr[i]);
        MinHeapify(temp);
    }

    /*if (left_node < heap_size && harr[left_node] < harr[i])
    {
        temp = left_node;
    }
    if (right_node < heap_size && harr[right_node] < harr[temp])
    {
        temp = right_node;
    }

    if (temp != i)
    {
        //cout<<"Before swap:   "<<harr[i]<<"   "<<harr[temp]<<endl;
        swap(&harr[i], &harr[temp]);
        //cout<<"After swap:   "<<harr[i]<<"   "<<harr[temp]<<endl;
        MinHeapify(temp);
    }*/
}

int MinHeap::parent(int i)
{
    return (i-1)/2;
}

int MinHeap::left(int i)
{
    return (2*i + 1);
}

int MinHeap::right(int i)
{
    return (2*i + 2);
}

int MinHeap::extractMin()
{
    if (heap_size <= 0)
    {
        return INT_MAX;
    }
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    int minimun = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    MinHeapify(0);

    return minimun;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

int MinHeap::getMin()
{
    return harr[0];
}

void MinHeap::deleteKey(int i)
{
    if (i >= heap_size)
    {
        return;
    }

    decreaseKey(i, INT_MIN);
    extractMin();
}

void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        cout<<"Heap is full"<<endl;
    }

    heap_size++;
    int index = heap_size - 1;
    harr[index] = k;
    shiftup(index);
}

void MinHeap::shiftup(int i)
{
    int pi;
    if (i != 0)
    {
        pi = parent(i);
        if (harr[pi] > harr[i])
        {
            swap(&harr[pi], &harr[i]);
            shiftup(pi);
        }
    }
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif
