//Jack Brockett and Sean Gordon 2-14-17

#include <iostream>
#include <cstdlib>
#include <string>
#include "word.h"

Word::Word(){
	words = "";
	next = NULL;
}

Word::Word(string words, Word* next){
	this->words = words;
	this->next = next;
}

void Word::setWord (string word){
	this->words = word;
}

void Word::setNext(Word* next){
	this->next = next;
}


void Word::insert(string word, string doc){
       
        setWord(word);
	dlist.insertBack(doc);
}

void Word::insertFile(string doc){
  dlist.insertBack(doc);
}

void Word::print(){
        cout << "File name" << "      " << "Count"  << endl;
	dlist.print();
}

void Word::addFileCount(string doc){
	dlist.addFileListCount(doc);
}

string Word::getWord(){
	return words;
}

Word* Word::getNext(){
	return next;
}


bool Word::hasNext() {
	return (getNext() != NULL);
}

bool Word::foundFile(string doc){
	return dlist.findFile(doc);
}
