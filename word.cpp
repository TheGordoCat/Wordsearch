//Sean Gordon 3-16-17

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "word.h"

Word::Word(){
	words = "";
	wordTotal = 1;
	fileTotal = 1;
	average = 0;

	left = NULL;
	right = NULL;
}

Word::Word(string words, Word* left, Word* right){
	this->words = words;
	this->left = left;
	this->right = right;
}

void Word::setWord (string word){
	this->words = word;
}

void Word::setLeft(Word* left){
	this->left = left;
}

void Word::setRight(Word* right){
	this->right = right;
}


void Word::insert(string word, string doc){
       
        setWord(word);
	dlist.insertBack(doc);
}

void Word::insertFile(string doc){
  	dlist.insertBack(doc);
	wordTotal++;	
	fileTotal++;
}

void Word::print(){
        cout << "File name" << "      " << "Count"  << endl;
	dlist.print();
	cout << "WordTotal" << "        " << wordTotal << endl;
	cout << "FileTotal" << "        " << fileTotal << endl;
	Average();
	cout << "Average" << "          " << setprecision(3) << average << endl;
}

void Word::addFileCount(string doc){
	dlist.addFileListCount(doc);
	wordTotal++;
}

void Word::Average(){
	average = ((double) wordTotal) / fileTotal;
}

string Word::getWord(){
	return words;
}

Word* Word::getLeft(){
	return left;
}

Word* Word::getRight(){
	return right;
}

bool Word::hasLeft() {
	return (getLeft() != NULL);
}

bool Word::hasRight() {
	return (getRight() != NULL);
}

bool Word::foundFile(string doc){
	return dlist.findFile(doc);
}
