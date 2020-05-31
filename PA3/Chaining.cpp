#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
	tableSize = size;
	hashTable = new LinkedList<string>[tableSize];

}
HashC::~HashC(){
	delete hashTable;
}

unsigned long HashC :: hash(string input){
	unsigned long x = bitHash(input);
	return divCompression(x, tableSize);
 
}

void HashC::insert(string word){
	unsigned long index = hash(word);
	hashTable[index].insertAtTail(word);

} 

ListItem<string>* HashC :: lookup(string word){
	unsigned long x = hash(word);
	return hashTable[x].searchFor(word);
}

void HashC :: deleteWord(string word){
	unsigned long index = hash(word);
	hashTable[index].deleteElement(word);
}


#endif