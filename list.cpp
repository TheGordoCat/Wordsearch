//Sean Gordon 2-14-17

#include "list.h"
#include "itemtype.h"
#include <iostream>
#include <string>

list::list(){
	doclist = NULL;
}

void list::insertBack(string doc){
	File* newFile = new File();
	newFile->setDocument(doc);
	if(doclist == NULL)
		doclist = newFile;
	else{
		File* temp_file;
		temp_file = doclist;
		while (temp_file->hasNext())
			temp_file = temp_file->getNext();
		temp_file->setNext(newFile);
	}
}

void list::print(){
	File* cursor;
	for (cursor = doclist; cursor != NULL; cursor = cursor->getNext()){
		cout << cursor->getDocument() << "           (" << cursor->getCount() << ") " << endl;
	}
	cout << endl;
}

//instantiate
void list::addFileListCount(string doc){
	
	bool found = false;
	File* cursor = doclist;

	while (!found && cursor != NULL){
		if (cursor->getDocument() == doc){
			found = true;
			cursor->addCount();
			break;
		}	
		else
			cursor = cursor->getNext();
	}
}

bool list::findFile(string doc){
	
	bool found = false;
	File* cursor = doclist;

	while (!found && cursor != NULL){
		if (cursor->getDocument() == doc)
			found = true;
		else
			cursor = cursor->getNext();
	}

	return found;
}


