//Jack Brockett and Sean Gordon 3-16-17

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "word.h"
#include "wordsearch.h"

using namespace std;

// Given a directory, return all the files in that directory
// if the directory does not exist -- report error.
int getdir (string dir, vector<string> &files)
{
  	DIR *dp;
  	struct dirent *dirp;
  	if((dp  = opendir(dir.c_str())) == NULL) {
    		cout << "Error(" << errno << ") opening " << dir << endl;
    		return errno;
  	}

  	while ((dirp = readdir(dp)) != NULL) {
    		files.push_back(string(dirp->d_name));
  	}
  	closedir(dp);
  	return 0;
}



int main(int argc, char* argv[])
{
        wordsearch wsearch;
  	string dir; 
  	vector<string> files = vector<string>();

  	if (argc < 2){
		cout << "No Directory specified; Exiting ..." << endl;
		return(-1);
    	}
  	dir = string(argv[1]);
  	if (getdir(dir,files)!=0){
		cout << "Error opening " << dir << "; Exiting ..." << endl;
		return(-2);
    	}
  
  	// THIS PART OF THE CODE SETS UP THE INVERTED INDEX 
  	string slash("/");
 	for (unsigned int i = 0; i < files.size(); i++) {
   	if(files[i][0]=='.') continue; //skip hidden files
    	ifstream fin((string(argv[1])+slash+files[i]).c_str()); //open using absolute path
    	string word;
    	while(true){
      		fin>>word;
      		if(fin.eof()) {break;}
      		wsearch.organize(word, files[i]);
    		}
    	fin.close();
	}
	
  	//ask user the word and repeat process until "exit" is typed
	cout << "Mode1:" << endl;
  	string keyword = "";
  	cout << "Input word (or enter \"exit\" to quit):";
  	cin >> keyword;

  	while (keyword != "exit"){
		cout << "\nOutput:\n" << endl;
		Word* cursor = wsearch.getWordIndex();
	        wsearch.search(keyword, cursor);
      		cout << "\nEnter Word (or enter \"exit\" to quit):" << endl;
      		cin >> keyword;
  	}



	//ask the user how many words to call in order from the binary tree
	cout << "\nMode2:" << endl;
	cout << "How many words? " << endl;
	int count = 0;
	cin >> count;
	cout << endl;

	Word* cursor = wsearch.getWordIndex();
	wsearch.inOrder(cursor);
	wsearch.print(count);

  	return 0;
}






//constructor for wordsearch
wordsearch::wordsearch(){
  	wordIndex = NULL;
}

//returns the head of the binary tree
Word* wordsearch::getWordIndex(){
	return wordIndex;
}





//the word will be placed in the wordIndex list and duplicate entries will be added to the doc list
void wordsearch::organize(string word, string file){

	if (!wordChange(word))
		return;	

	if (wordIndex == NULL){
		wordIndex = new Word();
		wordIndex->insert(word, file);
	}


	//check if word is already in the list
	//if it is then check if the file is already in the document list
	bool foundWord = false;
	bool foundFile = false;
	Word* cursor = wordIndex;
	Word* prev = NULL;
	while (!foundWord && cursor != NULL){

		if (stringCom(cursor->getWord(), word) == 0){
			foundWord = true;
			foundFile = foundFile = cursor->foundFile(file);
	        	break;
		}
		else if (stringCom(cursor->getWord(), word) < 0){
			prev = cursor;
			cursor = cursor->getRight();
		}
		else if (stringCom(cursor->getWord(), word) > 0){
			prev = cursor;
			cursor = cursor->getLeft();
		}
	}  
	


	//if word and file are both found, add to the file count
	if (foundWord && foundFile){
		cursor->addFileCount(file);
	}
			
	//if word is found but not the file in the list
	if (foundWord && !foundFile){
  		cursor->insertFile(file);
	}

	//if word is nowhere to be found so far then make the cursor the new word
	if (!foundWord && !foundFile){
  		Word* newWord = new Word();
  		newWord->insert(word, file);
  		cursor = newWord;
		if (stringCom(prev->getWord(), word) > 0)
			prev->setLeft(newWord);
		else 
			prev->setRight(newWord);
  	}
}


//search the binary tree wordIndex
void wordsearch::search(string keyword, Word* cursor){

	if (cursor == NULL){
		cout << "The word you entered is not found.\n" << endl;
		return;
	}

	if (stringCom(cursor->getWord(), keyword) == 0){
		cursor->print();
		return;
	}
	else if (stringCom(cursor->getWord(), keyword) > 0)
		return search(keyword, cursor->getLeft());
	else
		return search(keyword, cursor->getRight());
}


//prints the words in order lexicographically
void wordsearch::inOrder(Word* cursor){

	if(cursor == NULL){
		
		return;
	}
	
	inOrder(cursor->getLeft());
	words += cursor->getWord() + " ";
	inOrder(cursor->getRight());
	
	return;
}


//prints the number of words lexicographically
void wordsearch::print(int count){

	string numWords[count];
	int num = 0;
	for (int i = 0; i < words.length(); i++){
		if (num < count){
			if (words[i] != ' ')
				numWords[num] += words[i];
			else
				num++;
		}
	}

	if (count > num){
		cout << "The number you entered is greater than the number of words in the files." << endl;
		cout << "So here is a list of all the words stored in the index.\n" << endl;
	}

	for (int i = 0; i < num; i++)
		cout << numWords[i] << endl;
}


//checks if the strings are equal
int wordsearch::stringCom(string string1, string string2){

	if (string1.compare(string2) > 0)
		return 1;
	else if (string1.compare(string2) < 0)
		return -1;
	else
		return 0;

}


//changes the word before being entered into the binary tree
//returns false if the word has a digit
//returns true if there are just letters
bool wordsearch::wordChange(string& s){

	string change = "";
	for (int i = 0; i < s.length(); i++){

		if (isdigit(s[i]) != 0)
			return false;

		if (ispunct(s[i]) != 0)
			change += "";

		if (isalpha(s[i]) != 0)
			change += tolower(s[i]);	
	}
	
	//rids of possession
	if (ispunct(s[s.length() - 2]) != 0 && s[s.length() - 1] == 's'){
		change = change.substr(0, change.length() - 1);
	}

	if (change == "")
		return false;	

	s = change;
	return true;
}


