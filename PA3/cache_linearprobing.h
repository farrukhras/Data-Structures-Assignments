#include "cache_linearprobing.cpp"
#ifndef CACHE_LINEARPROBING_H
#define CACHE_LINEARPROBING_H

#include <string>
#include <iostream>

using namespace std;
class block{
    public:
        unsigned long key;
        string value;
        int frequency ;
        block(unsigned long _key,string _value){
            this->key = _key;
            this->value = _value;
            this->frequency = 0 ;
        }
};


class HashL{
    private:
        block** hashTable;
        long tableSize;
        unsigned long hash(string value); // return the corresponding key of the value
        long count; // keeps a count of the number of entries in the table.
    public:
        HashL();
        ~HashL();
        void insert(unsigned long key, string value);
		block* lookup(unsigned long key);
};

#endif
