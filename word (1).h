//Jack Brockett and Sean Gordon 3-16-17

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
		Word(string words, Word* left, Word* right);

		void setWord(string word);
		void setLeft(Word* left);
		void setRight(Word* right);

		void insert(string word, string doc);
		void insertFile(string doc);
		void print();
		void addFileCount(string doc);
		void Average();

		string getWord();
		Word* getLeft();
		Word* getRight();
    
		bool hasLeft();
		bool hasRight();
		bool foundFile(string doc);
	private:
		string words;
		int wordTotal;
		int fileTotal;
		double average;

		Word* left;
		Word* right;
		list dlist;
};
#endif
