#include <iostream>
using namespace std;

int main()
{
    string s[5] = {"seventh", "three", "fifth", "sixeth", "eigth88"};
    string temp;

    cout<<"Before: "<<endl;
    for(int i = 0; i < 5; i++)
    {
        cout<<s[i]<<endl;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = i+1; j<5; j++)
        {
            if (s[i] > s[j])
            {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    cout<<"In Lexicographical Order: "<<endl;

    for(int i = 0; i < 5; i++)
    {
        cout<<s[i]<<endl;
    }

    return 0;
}
