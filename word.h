//Sean Gordon 2-14-17

#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "list.h"

using namespace std;

class Word{
	public:
		Word();
		Word(string words, Word* next);

		void setWord(string word);
		void setNext(Word* next);

		void insert(string word, string doc);
		void insertFile(string doc);
		void print();
		void addFileCount(string doc);

		string getWord();
		Word* getNext();
    
		bool hasNext();
		bool foundFile(string doc);
	private:
		string words;
		Word* next;
		list dlist;
};
#endif
