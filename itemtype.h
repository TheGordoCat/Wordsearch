//Jack Brockett and Sean Gordon 2-14-17

#ifndef ITEMTYPE_H
#define ITEMTYPE_H
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class File{
	public:
		File();
		File(string doc);

		void setDocument(string doc);
		void setNext(File* n);
		void addCount();

		string getDocument();
		int getCount(); 
		File* getNext(); 

		bool hasNext(); 
	private:
		string document;
		int count;
		File* next;
};
#endif
