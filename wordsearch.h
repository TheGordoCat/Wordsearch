//Jack Brockett and Sean Gordon 2-14-17

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
		void search(string keyword);

		bool stringEqual(string string1, string string2);

	private:
		Word* wordIndex;
};
#endif
