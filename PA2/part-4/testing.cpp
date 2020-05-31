#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Dictionary::Dictionary() {
	wordsTree = NULL;
	wordsTree = new BST<string>();
}

Dictionary::~Dictionary(){
    delete wordsTree;
}

void Dictionary::initialize(string wordsFile) {
    ifstream infile;
    infile.open((wordsFile + ".txt").c_str());
    string text;
    int counter = 0;

    if (infile.is_open())
    {
        while (getline(infile, text))
        {
            insertWord(text);
            counter++;
            cout<<"INSERTION NUMBER: "<<counter<<endl;
        }
        infile.close();
        cout<<"INSERTION SUCESSFULL!!"<<endl;
        cout<<"Total Insertions: "<<counter<<endl;
    }
    else
    {
        cout<<"File did not open properly!!"<<endl;
    }
}

bool Dictionary::deleteWord(string word) {
    wordsTree->delete_node(word);
	return false;
}
bool Dictionary::editWord(string oldWord, string newWord) {
    wordsTree->delete_node(oldWord);
    wordsTree->insert(newWord, newWord);
	return false;
}

bool Dictionary::insertWord(string word) {
    wordsTree->insert(word, word);
    //cout<<"ROOT IS: "<<wordsTree->getRoot()->key<<endl;
	return false;
}
node<string>* Dictionary::findWord(string word) {
	clock_t t;
    t = clock();
    cout<<t<<endl;

    node<string>* temp = wordsTree->search(word);
    //cout<<temp->key<<endl;

    if (temp == NULL)
    {
        cout<<"Word Not Found!!"<<endl;
    }
    else
    {
        double x = clock();
        cout<<t<<endl;

        t = (clock() - t);

        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

        double time_in_nano = time_taken * 1000000000;

        cout<<"time taken = "<<time_in_nano<<endl;
        cout << "findWord() took " << time_in_nano << " sec to search for " << word << endl;
        return temp; // TODO
    }
}

void Dictionary::checking(string word)
{
    cout<<"ROOT IS: "<<wordsTree->getRoot()->key<<endl;
    cout<<"ROOT's LEFT CHILD: "<<wordsTree->getRoot()->left->key<<endl;
    cout<<"ROOT's RIGHT IS: "<<wordsTree->getRoot()->right->key<<endl;
    cout<<"ROOT's LEFT CHILD KA LEFT IS: "<<wordsTree->getRoot()->left->left->key<<endl;
    cout<<"ROOT's LEFT CHILD KA LEFT IS: "<<wordsTree->getRoot()->left->right->key<<endl<<endl<<endl;
}

void Dictionary::checking1(string word)
{
    cout<<"ROOT IS: "<<wordsTree->getRoot()->key<<endl;
    cout<<"ROOT's LEFT CHILD: "<<wordsTree->getRoot()->left->key<<endl;
    cout<<"ROOT's RIGHT IS: "<<wordsTree->getRoot()->right->key<<endl;
    cout<<"ROOT's LEFT CHILD KA LEFT IS: "<<wordsTree->getRoot()->left->left->key<<endl;
    cout<<"ROOT's RIGHT CHILD KA RIGHT IS: "<<wordsTree->getRoot()->right->right->key<<endl<<endl<<endl;
}

#endif

int main() {
    Dictionary obj;
    obj.initialize("words");
    //cout<<endl<<"AFTER INSERTION: "<<endl;
    //obj.checking("seventh");
    //cout<<endl<<"AFTER DELETION: "<<endl;
    //obj.deleteWord("fifth");
    //obj.checking1("seventh");
    //cout<<"AFTER EDITING WORDS: "<<endl;
    //obj.editWord("four", "three");
    //obj.checking1("seventh");

    //obj.findWord("four");

	return 0;
}

