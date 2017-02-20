//Sean Gordon 2-14-17

#include "itemtype.h"
#include <string>

File::File(){
	document = "";
	count = 1;
	next = NULL;
}

File::File(string doc){
	document = doc;
	count = 1;
	next = NULL;
}

void File::setDocument(string doc) {
	document = doc;
}

void File::setNext(File* n) {
	next = n;
}

void File::addCount(){
	count++;
}

string File::getDocument() {
	return document;
}

int File::getCount() {
	return count;
}

File* File::getNext() {
	return next;
}

bool File::hasNext() {
	return (getNext() != NULL);
}
