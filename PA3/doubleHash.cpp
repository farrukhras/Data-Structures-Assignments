#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"

HashD::HashD(){
    tableSize = 10000; // you cant change this
    count = 0;
    hashTable = new block*[tableSize];

    for (int i =0; i<tableSize; i++)
    {
    	hashTable[i] = NULL;
    }
}

HashD::~HashD(){
    for (int i = 0; i<tableSize; i++)
    {
        delete hashTable[i];
    }
}

unsigned long HashD :: hash1(string value){
	unsigned long x = bitHash(value);
	return madCompression(x, tableSize);
}

unsigned long HashD :: hash2(string value){
	unsigned long x = bitHash(value);
	return divCompression(x, tableSize);
}

void HashD::resizeTable(){
	int old_tablesize = tableSize;
	tableSize = tableSize*2;

	block** oldhashtable = new block*[tableSize];

	for (int i=0; i<tableSize; i++)
	{
		oldhashtable[i] = NULL;
	};

	for (int i = 0; i<old_tablesize; i++)
	{
		if (hashTable[i] != NULL)
		{
			unsigned long index = (hash1(hashTable[i]->value));
			int x = 1;
			unsigned long index_hash = index;

			while(oldhashtable[index] != NULL)
			{
				index = ((index_hash) + (x*(hash2(hashTable[i]->value)))) % tableSize;
				x++;
			}

			oldhashtable[index] = new block(index, hashTable[i]->value);
		}
		else
		{

		}
	}
	for (int i =0; i< old_tablesize; i++)
	{
		delete hashTable[i];
	}
	delete hashTable;
	hashTable = oldhashtable;
	oldhashtable = NULL;
}

void HashD::insert(string value){
	double load_factor = (count*1.0)/tableSize;

	if (load_factor > 0.15)
	{
		resizeTable();
	}

	unsigned long index = hash1(value);
	int i = 1;
	unsigned long index_hash1 = index;

	while (hashTable[index] != NULL && hashTable[index]->key != -1)
	{
		index = ((index_hash1) + (i*(hash2(value)))) % tableSize;
		i++;
	}
	//cout<<"inserting"<<c<<endl;
	//c++;
	hashTable[index] = new block(index, value);
	count++;
}

void HashD::deleteWord(string value){
	//unsigned long index = hash1(value);

	block* temp = lookup(value);

	if (temp != NULL)
	{
		temp->key = -1;
		temp->value = "-1";
	}
}

block* HashD::lookup(string value){
	unsigned long index = hash1(value);
	unsigned long index_hash1 = index;
	int i = 1;

	while (hashTable[index] != NULL)
	{
		if (index >= tableSize)
		{
			index = 0;
		}

		if (hashTable[index]->value == value)
		{
			//cout<<"lookup: "<<hashTable[index]->value<<endl;
			return hashTable[index];
		}

		else
		{
			index = (index_hash1 + (i*hash2(value))) % tableSize;
			i++;
		}
	}

	return NULL;
}

#endif
