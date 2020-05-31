#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std::chrono;

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
        while (!infile.eof()) //&& counter < 10000)
       {
            infile >> text;
            insertWord(text);
            counter++;
            //cout<<"INSERTION NUMBER: "<<counter<<endl;
        }
        infile.close();
        //cout<<"INSERTION SUCESSFULL!!"<<endl;
        //cout<<"Total Insertions: "<<counter<<endl;
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
    if (wordsTree == NULL)
    {
        return true;
    }
    else
    {
        node<string>* temp1 = wordsTree->search(oldWord);
        if (temp1 == NULL)
        {
            cout<<"Word to replace the new word with NOT found in the Dictionary"<<endl;
            return true;
        }
        else
        {
            bool res = deleteWord(oldWord);
            if (res == false)
            {
                wordsTree->insert(newWord, newWord);
                return false;
            }
            else {return true;}
        }
    }
}
bool Dictionary::insertWord(string word) {
    wordsTree->insert(word, word);
    //cout<<"ROOT IS: "<<wordsTree->getRoot()->key<<endl;
	return false;
}
node<string>* Dictionary::findWord(string word) {
	//clock_t t;
    //t = clock();

    auto start = high_resolution_clock::now();
    node<string>* temp = wordsTree->search(word);

    if (temp == NULL)
    {
        cout<<"word not found!"<<endl;
        return temp;
    }

    auto stop = high_resolution_clock::now();

    //t = clock() - t;
    

    //double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    auto duration = duration_cast<nanoseconds>(stop - start);

    //double time_in_nano = time_taken * 1000000000;
    //cout<<"time taken = "<<time_in_nano<<endl;

    cout << "findWord() took " << duration.count() << " nanosec to search for " << word << endl;
    return temp; // TODO
}

#endif

int main() {
    Dictionary obj;
    int choice = -1;

    cout<<"Initializing the Tree, Kindly show Patience!!"<<endl;
    obj.initialize("words");

    while (choice != 0)
    {
        cout<<"Choose which operation to perform"<<endl;
        cout<<"1. Insert a word"<<endl;
        cout<<"2. Delete a word"<<endl;
        cout<<"3. Search a word"<<endl;
        cout<<"4. Edit a word"<<endl<<endl;
        cout<<"Press 0 to quit"<<endl<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cout<<endl;
        string word;

        if(choice == 1){
            cout<<"Enter the word to insert in the Dictionary: ";
            cin>>word;
            cout<<endl;
            bool res = obj.insertWord(word);
            if (res == false){cout<<"Word Insertion successful!!"<<endl;}
            else{cout<<"Word Insertion successful!!"<<endl;}
        }
        else if (choice == 2){
            cout<<"Enter the word to delete from the Dictionary: ";
            cin>>word;
            cout<<endl;
            bool res = obj.deleteWord(word);
            if (res == false){cout<<"Word Deletion successful!!"<<endl;}
            else{cout<<"Word Deletion successful!!"<<endl;}
        }
        else if (choice == 3){
            cout<<"Enter the word to find in the Dictionary: ";
            cin>>word;
            cout<<endl;
            obj.findWord(word);
        }
        else if (choice == 4){
            string word2;
            cout<<"Enter the words to edit in the Dictionary"<<endl;
            cout<<"Old Word: ";
            cin>>word;
            cout<<"New Word: ";
            cin>>word2;
            cout<<endl;
            bool res = obj.editWord(word, word2);
            if (res == false){cout<<"Word Edition successful!!"<<endl;}
            else{cout<<"Word Edition unsuccessful!!"<<endl;}
        }
        else{
            return 0;
        }
    }

	return 0;
}
