//Jack Brockett and Sean Gordon 2-14-17

#ifndef LIST_H
#define LIST_H
#include <string>
#include <iostream>
#include "itemtype.h"

using namespace std;

class list{
	public:
		list();
		
		void insertBack(string doc);
		void print();
		void addFileListCount(string doc);
		
		bool findFile(string doc);
		
	private:
		File* doclist;
};
#endif
