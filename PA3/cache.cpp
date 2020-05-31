//include any header files as required
#include <iostream>
#include "cache_linearprobing.h"
#include <fstream>
#include <sstream>

using namespace std;

void search_dic_sample()
{
    /*clock_t time_req;

    time_req = clock();

    ifstream file;
    file.open("secret1.txt");

    while(file>>temp && i<entries)
    {
        int siz = temp.length();
        temp = temp.substr(0,siz-1);
        arr[i] = temp;
        i++;
    }

    int x = 1;

    ifstream filedic;
    filedic.open("dictionary.txt");

    while (filedic >> number >> word && x <= entries)
    {
        for (int i = 0; i<entries; i++)
        {
            if (arr[i] == number)
            {
                cout<<x<<". "<<number<<"  "<<word<<endl;
                x++;
            }
        }
    }
    cout<<x<<endl;
    filedic.close();

    time_req = clock() - time_req;
    cout<<(float)time_req/CLOCKS_PER_SEC<<endl;*/

    /*clock_t time_req;

    time_req = clock();

    int x = 0;

    ifstream file;
    file.open("secret1.txt");

    while (file>>temp && x < 100)
    {
        int siz = temp.length();
        temp = temp.substr(0,siz-1);

        cout<<i<<".  "<<temp<<"  ";

        ifstream filedic;
        filedic.open("dictionary.txt");
        while (filedic>>number>>word)//(!filedic.eof())
        {
            if (number == temp)
            {
                cout<<word<<endl;
                x++;
                i++;
            }
        }
    }

    cout<<x<<endl;
    file.close();

    time_req = clock() - time_req;
    cout<<(float)time_req/CLOCKS_PER_SEC<<endl;*/
}

void search_cache_sample()
{
    /*clock_t time_req;

    time_req = clock();

    HashL* cache = new HashL();

    ifstream file;
    file.open("secret1.txt");

    while(file>>temp >> comma && i<entries)
    {
        arr[i] = temp;
        i++;
    }

    for (int j=0; j<entries; j++)
    {
        cout<<x;
        block* y = cache->lookup(arr[j]);

        if(y != NULL)
        {
            cout<<"  Cache  "<<y->value<<endl;
        }

        else
        {
            ifstream filedic;
            filedic.open("dictionary.txt");

            unsigned long count = -1;

            while (count != arr[j])
            {
                filedic >> number >> word;
                count++;
            }

            if (number == arr[j])
            {
                cache->insert(number, word);
                cout<<"  Dictionary  "<<word<<endl;
            }

            filedic.close();
        }
        x++;
    }

    file.close();

    time_req = clock() - time_req;
    cout<<(float)time_req/CLOCKS_PER_SEC<<endl;*/
}

void search_dic(string file_name)
{
    unsigned long temp;
    string word;
    unsigned long number;
    string comma;

    int waise_hi = 0;

    int i = 0;
    int x = 0;
    int entries = 1500;

    unsigned long arr[entries] = {};

    clock_t time_req;

    time_req = clock();

    ifstream file;
    file.open(file_name);

    while (file>>temp>>comma && x < entries)
    {
        unsigned long count = -1;

        ifstream filedic;
        filedic.open("dictionary.txt");

        while (count != temp)
        {
            filedic >> number >> word;
            count++;
        }

        if (number == temp)
        {
            waise_hi++;
            //cout<<x<<"  Dictionary  "<<word<<endl;
        }

        x++;
    }

    file.close();

    time_req = clock() - time_req;
    cout<<(float)time_req/CLOCKS_PER_SEC<<endl;
}

void search_cache(string file_name)
{
	unsigned long temp;
    string word;
    unsigned long number;
    string comma;

    int i = 0;
    int x = 0;
    int entries = 1500;

  	unsigned long arr[entries] = {};

    clock_t time_req;

    time_req = clock();

    HashL* cache = new HashL();

    ifstream file;
    file.open(file_name);

    while (file>>temp>>comma && x < entries)
    {
        //cout<<x<<endl;
        block* y = cache->lookup(temp);

        if (y != NULL)
        {
            //cout<<"  Cache  "<<y->value<<endl;
        }

        else
        {
            unsigned long count = -1;

            ifstream filedic;
            filedic.open("dictionary.txt");

            while (count != temp)
            {
                filedic >> number >> word;
                count++;
            }

            if (number == temp)
            {
                cache->insert(number, word);
                //cout<<"  Dictionary  "<<word<<endl;
            }
        }
        x++;
    }

    file.close();

    time_req = clock() - time_req;
    cout<<(float)time_req/CLOCKS_PER_SEC<<endl;
}

int main()
{
    string f1 = "secret1.txt";  
    string f2 = "secret2.txt";      
    string f3 = "secret3.txt";  

    cout<<"Decode secret1.txt without cache!!"<<endl;
	cout<<"Time taken: ";
    search_dic(f1);
    cout<<endl;

    cout<<"Decode secret1.txt with cache!!"<<endl;
    cout<<"Time taken: ";
    search_cache(f1);
    cout<<endl;

    cout<<"Decode secret2.txt without cache!!"<<endl;
    cout<<"Time taken: ";
    search_dic(f2);
    cout<<endl<<endl;

    cout<<"Decode secret2.txt with cache!!"<<endl;
    cout<<"Time taken: ";
    search_cache(f2);
    cout<<endl<<endl;

    cout<<"Decode secret3.txt without cache!!"<<endl;
    cout<<"Time taken: ";
    search_dic(f3);
    cout<<endl<<endl;

    cout<<"Decode secret3.txt with cache!!"<<endl;
    cout<<"Time taken: ";
    search_cache(f3);
    cout<<endl<<endl;


    return 0;
}