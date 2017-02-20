//Jack Brockett and Sean Gordon 2-14-17
//project takes awhile to initialize for large text files
//takes about 15min to initialize the 8 text files from Gauchospace


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
  	string keyword = "";
  	cout << "Input word (or enter \"exit\" to quit):";
  	cin >> keyword;
  	while (keyword != "exit"){
		cout << "\nOutput:\n" << endl;
	        wsearch.search(keyword);
      		cout << "\nEnter Word (or enter \"exit\" to quit):" << endl;
      		cin >> keyword;
  	}
  	return 0;
}






//constructor for wordsearch
wordsearch::wordsearch(){
  	wordIndex = NULL;
}

//the word will be placed in the wordIndex list and duplicate entries will be added to the doc list
void wordsearch::organize(string word, string file){

	if (wordIndex == NULL){
		wordIndex = new Word();
		wordIndex->insert(word, file);
	}


	//check if word is already in the list
	//if it is then check if the file is already in the document list
	bool foundWord = false;
	bool foundFile = false;
	Word* cursor = wordIndex;
	while (!foundWord && cursor != NULL){
	        if (stringEqual(cursor->getWord(), word)){      
	        	foundWord = true;
			foundFile = cursor->foundFile(file);
	        	break;
	    	}
	    	else
	      		cursor = cursor->getNext();
	}  
	


	//if word and file are both found, add to the file count
	if (foundWord && foundFile){
		cursor->addFileCount(file);
	}
			
	//if word is found but not the file in the list
	if (foundWord && !foundFile){
  		cursor->insertFile(file);
	}

	//if word is nowhere to be found so far then add to the front of the index
	if (!foundWord && !foundFile){
  		Word* newWord = new Word();
  		newWord->insert(word, file);
  		newWord->setNext(wordIndex);
  		wordIndex = newWord;
  	}
}

//search for the keyword in the lists and print the data
void wordsearch::search(string keyword){

	bool foundWord = false;
	Word* cursor = wordIndex;
	while (!foundWord && cursor != NULL){
		if (stringEqual(cursor->getWord(), keyword)){
			foundWord = true;
			cursor->print();
			break;
		}
		else 
			cursor = cursor->getNext();
	}
	
	if (!foundWord)
		cout << "The word you entered is not found.\n" << endl;
}

//checks if the strings are equal
bool wordsearch::stringEqual(string string1, string string2){
	
	if (string1.length() != string2.length())
		return false;
	
	for (int i = 0; i < string1.length(); i++){
		if (toupper(string1[i]) != toupper(string2[i]))
			return false; 
	}
		
	return true;
}

