#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.h"
#include "list.cpp"
#include <cstdlib>
#include <ctime>

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
    int siz = nums.size();
    long* arr = new long[siz];

    for (int x = 0; x<siz; x++)
    {
        arr[x] = nums[x];
    }

    int i = 1;
    int j;
    long marker;

    while (i < siz)
    {
        marker = arr[i];
        j = i-1;

        while (j >= 0 && arr[j] > marker)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = marker;
        i++;
    }

    for (int x = 0; x< siz; x++)
    {
        nums[x] = arr[x];
    }

    return nums;
}

//=====================================================================================
ListItem<long>* merge_lists(ListItem<long>* list1, ListItem<long>* list2)
{
    if (list1 == NULL)
    {
        return list2;
    }
    if (list2 == NULL)
    {
        return list1;
    }

    if (list1->value < list2->value)
    {
        list1->next = merge_lists(list1->next, list2);
        list1->next->prev = list1;
        list1->prev = NULL;
        return list1;
    }
    else
    {
        list2->next = merge_lists(list1, list2->next);
        list2->next->prev = list2;
        list2->prev = NULL;
        return list2;
    }
}
x
ListItem<long>* sort_list(ListItem<long>* head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    else
    {
        ListItem<long>* ptr1 = head;
        ListItem<long>* ptr2 = head;

        while (ptr1->next != NULL && ptr1->next->next != NULL)
        {
            ptr1 = ptr1->next->next;
            ptr2 = ptr2->next;
        }

        ListItem<long>* temp = ptr2->next;
        ptr2->next = NULL;
        ListItem<long>* second_list = temp;

        head = sort_list(head);
        second_list = sort_list(second_list);

        return merge_lists(head, second_list);
    }
}

vector<long> MergeSort(vector<long> nums)
{
    List<long> obj;
    int siz = nums.size();

    for (int i = 0; i<siz; i++)
    {
        obj.insertAtHead(nums[i]);
        //cout<<"hey"<<endl;
    }

    ListItem<long>* temp = sort_list(obj.getHead());

    int x = 0;
    while (temp != NULL)
    {
        nums[x] = temp->value;
        temp = temp->next;
        x++;
        //cout<<"in while"<<endl;
    }
    return nums;
}

//=====================================================================================
long* quick_sort_array_last(long arr[], int start_index, int last_index)
{
     //Taking the last element as the pivot
    if (last_index > start_index)
    {
        // here we will find the pivot by making the last element as the pivot and placing
        // all values smaller than it to the left and values greater than it to the right and then we call merge_sort_array
        // on the two parts of the array, left and right to pivot separately to sort them

        int pivot = arr[last_index];
        int curr_index = start_index - 1;

        for (int x = start_index; x<last_index; x++)
        {
            if(pivot >= arr[x])
            {
                curr_index++;
                int temp_value = arr[curr_index];
                arr[curr_index] = arr[x];
                arr[x] = temp_value;
            }
            else{}
        }

        int temp1 = arr[curr_index + 1];
        arr[curr_index + 1] = arr[last_index];
        arr[last_index] = temp1;

        int pivot_index = curr_index + 1;

        quick_sort_array_last(arr, start_index, pivot_index - 1);
        quick_sort_array_last(arr, pivot_index + 1, last_index);
    }

    long* x = arr;
    return x;
}

long* quick_sort_array_first(long arr[], int start_index, int last_index)
{
     //Taking the first element as the pivot
    if (last_index > start_index)
    {
        // here we will find the pivot by making the last element as the pivot and placing
        // all values smaller than it to the left and values greater than it to the right and then we call merge_sort_array
        // on the two parts of the array, left and right to pivot separately to sort them

        int pivot = arr[start_index];
        int curr_index = start_index - 1;

        for (int x = start_index; x<last_index; x++)
        {
            if(pivot >= arr[x])
            {
                curr_index++;
                int temp_value = arr[curr_index];
                arr[curr_index] = arr[x];
                arr[x] = temp_value;
            }
            else{}
        }

        int temp1 = arr[curr_index + 1];
        arr[curr_index + 1] = arr[last_index];
        arr[last_index] = temp1;

        int pivot_index = curr_index + 1;

        quick_sort_array_first(arr, start_index, pivot_index - 1);
        quick_sort_array_first(arr, pivot_index + 1, last_index);
    }

    long* x = arr;
    return x;
}

vector<long> QuickSortArray(vector<long> nums)
{
    int siz = nums.size();
    long* arr = new long[siz];

    for (int i = 0; i<siz; i++)
    {
        arr[i] = nums[i];
    }

    int start_index = 0;
    int last_index = siz - 1;

    long* temp = quick_sort_array_last(arr, start_index, last_index);

    for(int i = 0; i< siz; i++)
    {
        nums[i] = temp[i];
    }

    return nums;
}

//=====================================================================================
void quick_sort_list(ListItem<long>* head, ListItem<long>* tail)
{
    if (tail == NULL || head == tail || head == tail->next)
    {
        return;
    }
    else
    {
        long pivot_value = tail->value;
        ListItem<long>* temp = head->prev;

        ListItem<long>* current = head;

        while (current != tail)
        {
            if (pivot_value >= current->value)
            {
                if (temp != NULL)
                {
                    temp = temp->next;
                }
                else
                {
                    temp = head;
                }
                //cout<<"here"<<endl;
                long temp_value = temp->value;
                temp->value = current->value;
                current->value = temp_value;
            }
            current = current->next;
        }

        if (temp != NULL)
        {
            temp = temp->next;
        }
        else
        {
            temp = head;
        }

        long temp_value = temp->value;
        temp->value = tail->value;
        tail->value = temp_value;

        quick_sort_list(head, temp->prev);
        quick_sort_list(temp->next, tail);
    }
}

vector<long> QuickSortList(vector<long> nums)
{
    List<long> obj;
    int siz = nums.size();

    for (int i = 0; i<siz; i++)
    {
        // insert the elements from nums in the list in the given order
        obj.insertAtHead(nums[i]);
    }

    // select a random index of the vector nums and make it the pivot
    srand(time(NULL));
    int index = rand() % siz;
    cout<<"index == "<<index <<endl;

    long value = nums[index];

    // move this randomly selected pivot to the end of the list and sort it as if the pivot was at the end
    ListItem<long>* curr = obj.searchFor(value);
    ListItem<long>* tail = obj.getTail();
    ListItem<long>* head = obj.getHead();

    // swap values of the pivot selected at random with the last element in the list,(continuation of previous comment)
    long temp1 = curr->value;
    curr->value = tail->value;
    tail->value = temp1;

    /*for (int i = 0; i<siz; i++)
    {
        cout<<head->value<<" ";
        head = head->next;
    }*/

    quick_sort_list(obj.getHead(), obj.getTail());

    ListItem<long>* temp = obj.getHead();

    /*for (int i = 0; i<siz; i++)
    {
        cout<<temp->value<<" "<<endl;
        temp = temp->next;
    }*/


    int x = 0;
    while (temp != NULL)
    {
        nums[x] = temp->value;
        temp = temp->next;
        x++;
    }
    return nums;
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
    MinHeap* obj = new MinHeap(nums.size());
    int siz = nums.size();
    long* arr = new long[siz];

    for (int i=0; i<siz; i++)
    {
        arr[i] = nums[i];
    }

    for (int i = 0; i<siz; i++)
    {
        obj->insertKey(arr[i]);
    }

    for (int i = 0; i<siz; i++)
    {
        int val = obj->extractMin();
        nums[i] = val;
    }
    return nums;
}

//=====================================================================================
vector<long> QueenOfAllSorts(vector<long> nums)
{
    int siz = nums.size();

    long maxi =  nums[0];
    long mini =  nums[0];

    for (int i = 0; i<siz; i++)
    {
        if (nums[i] > maxi)
        {
            maxi = nums[i];
        }
        if (nums[i] < mini)
        {
            mini = nums[i];
        }
    }

    int siz1 = (maxi - mini + 10);
    long *arr = new long[siz1];
    int bias = 0;
    int val = INT_MAX;
    int j = 0;

    for (int i = 0; i<siz1; i++)
    {
        arr[i] = NULL;
    }

    if (mini < 0)
    {
        bias = -1 * mini;
    }

    for (int i = 0; i<siz; i++)
    {
        val = nums[i] + bias;
        long value = arr[val] + 1;
        arr[val] = value;
    }

    for (int i = 0; i<siz1; i++)
    {
        if (arr[i] != NULL)
        {
            if (arr[i] > 0)
            {
                for (int x = 0; x < arr[i]; x++)
                {
                    nums[j] = i - bias;
                    j++;
                }
            }
        }
    }

    return nums;
}
#endif
