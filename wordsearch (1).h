//Jack Brockett and Sean Gordon 3-16-17

#ifndef WORDSEARCH_H
#define WORDSEARCH_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "word.h"

using namespace std;

class wordsearch{

	public:
		wordsearch();
		void organize(string word, string file);
		void search(string keyword, Word* cursor);
		void inOrder(Word* cursor);
		void print(int count);

		Word* getWordIndex();		

		int stringCom(string string1, string string2);
		bool wordChange(string& s);

	private:
		Word* wordIndex;
		string words;
};
#endif
