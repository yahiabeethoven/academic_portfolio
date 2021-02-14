//Yahia Beethoven Tayel
//Assignment3 - 3rd of December, 2020
//summation hash function used


#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<list>
#include<algorithm>
#include<string>
#include <cctype>
#include <iomanip>


using namespace std;
class HashNode
{
	private:
		string key;
		int frequency;
	public:
		HashNode(string key, int frequency)
		{
			this->key = key;
			this->frequency = frequency;
		}
		friend class HashTable;

};

class HashTable
{
	private:
		list<HashNode> *buckets;		// Array of lists of type Hash Nodes
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;					//total collisions in text
		int wordRepeated;				//number of repeated words in text
		int totalWords;					//total number of words in text
	public:
		HashTable(int capacity);
		unsigned long hashCode(const string key);
		void insert(const string key);
		int find_freq(const string _key);
		int getSize();
		int count_collision();
		int count_unique_words();
		int count_words();
		float unique_words_percent();
		~HashTable();

};
HashTable::HashTable(int capacity)
{
	buckets = new list<HashNode>[capacity];			//Create an array of size capacity. Each locaiton of Array is a list/chain
	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
	this->wordRepeated = 0;
	this->totalWords = 0;
}

unsigned long HashTable::hashCode(const string key)	//summation hashfunction
{
	int length = key.length();

		if (length == 0) {										//if string is empty then return 0
			return 0;
		}

		unsigned long code = 0;									//initialize hash code to 1

		for (int i = 0; i < length; i++) {						//iterate over characters of key
			code += (unsigned long)(key[i]);				
		}

	return code;	
}
//================================================
void HashTable::insert(const string key)
{
	unsigned long index = hashCode(key) % this->capacity;								//acquiring index from hash function

	list<HashNode>::iterator p;															//iterator to traverse list at index
	for (p = buckets[index].begin(); p != buckets[index].end(); ++p) {
		
		if (p->key == key) {															//if key already exists
			p->frequency++;											//increment the word's frequency
			this->wordRepeated++;
			this->totalWords++;	
			return;																	//break loop and leave function
		}
		
	}
	
	if (buckets[index].size() > 0) {			//if the for loop was not exited just because the list is actually empty, then a collision happened
		this->collisions++;
	}

	buckets[index].push_back(HashNode(key, 1));										//if after loop it was not found, then add it at the end of the list as a new node		
	this->totalWords++;																		//update size used accordingly
}
//===================================================
int HashTable::find_freq(const string _key)
{
	
	char x;	
	string key;							//acquiring index from hash function											//initializing comparisons made before finding to 0
	for (int i = 0; i < _key.length(); ++i) {
		if (isalpha(_key[i])) {					//if character is alphabetical, then deal with it, otherwise just ignore it
			x = tolower(_key[i]);				//make sure to make all letters lower case
			key += x;
		}
		
	}
	if (key.length() == 0) {					//if after the changes made above the string was empty, then the input was just special character(s)
		return 0;
	}
	unsigned long index = hashCode(key) % this->capacity;
	list<HashNode>::iterator p;											//iterator to traverse list at index
	for (p = buckets[index].begin(); p != buckets[index].end(); ++p) {													//keep increasing comparisons with every iteration until loop is broken
		if (p->key == key) {											//if key is found
			return p->frequency;										//return key's valye concatenated with number of comparisons to get to it
		}
	}
	return 0;											//if still running till here then key doesn't exist
}
//====================================================
int HashTable::count_collision() {
	return this->collisions;
}
//====================================================
int HashTable::count_unique_words(){
	return this->totalWords - this->wordRepeated;				//unique words are just the difference between the total words and the repated ones
}
//====================================================
int HashTable::count_words() {
	return this->totalWords;
}
//====================================================
float HashTable::unique_words_percent() {
	float unique = (float)count_unique_words();
	float total = (float)count_words();
	float percentage = (unique / total) * 100;
	return percentage;
}
//=====================================================

//===================================================
int HashTable::getSize()
{
	return this->size;
}

HashTable::~HashTable()
{
	for(int i=0; i<capacity; i++)
		buckets[i].clear();
	
	delete[] this->buckets;
}

//======================================================

void listCommands()
{
	cout<<endl<<"----------------------------------"<<endl;
	cout<<"Commands available:"<<endl<<endl;
	cout<<"find <word>      				: Search for word and return its frequency."<<endl
		<<"unique     				     	: Print the number of unique words in the text."<<endl
		<<"total     				        : Print the total number of words."<<endl
		<<"percent     				        : Print the percentage of unique words from the total."<<endl
		<<"collisions                       		: Print the total number of collisions."<<endl
		<<"help      					: Display the available commands."<<endl
		<<"exit      					: Exit the program."<<endl;
	cout<<"----------------------------------"<<endl;
}


int main(void)
{
	bool fileExist = false;

	cout<<"+--------------------------------------+"<<endl;
	cout<<"|   Welcome to: Text Analyzer System   |"<<endl;
	cout<<"+--------------------------------------+"<<endl<<endl;
	
	string userPath, path;
	while (!fileExist) {									//keep asking the user to type again as long as input is an invalid file

		cout<< "Please enter the full directory path of the file: "<<endl;
		getline(cin,userPath);
		path = userPath.substr(0,userPath.find(" "));
		
		ifstream temp;
		temp.open(path);
		if (temp.is_open())			//if path provided is valid then break the loop
		{
			fileExist = true;
		}
		else if (path == "exit") {								//if they type exit then just exit program
			exit(-1);
		}
		else {
			cout<<endl<<"Can not open the file, the input is incorrect...!"<<endl<<endl;
		}
	}

	HashTable myHashTable(52121);				// Prime number bigger than > 39083*1.333;
	ifstream fin;
	fin.open(path);
	string line;				
	cout<<endl<<"----------------------------------"<<endl;
	while(!fin.eof())
	{
		string word;
		string temp;
		char x;
		getline(fin,word,' ');
		cout<<word<<" ";
		// string special = "-\'.,!?;";
		for (int i = 0; i < word.length(); ++i) {
			if (isalpha(word[i])) {										//if character is alphabetical
				if (isupper(word[i]) && i != 0 && islower(word[i-1])) {		//if char is uppercase and not the first letter and the previous letter was small case, accounting for typos
					myHashTable.insert(temp);							//insert the previous letters as a word
					temp = "";											//reset temp to an empty string
					x = tolower(word[i]);								//make the letter small
					temp += x;											//add it to temp
				}
				else {
					x = tolower(word[i]);								//make letter lower case and accumulate it to temp
					temp += x;
				}
			}
			else if (word[i] == ',') {									//accounting for typos, if char is a comma within a word									//store the previous letters
				if (temp != "") {										//if previous letters were not an empty string (they are actually a word)
					myHashTable.insert(temp);							//insert that word
				}	
				temp = "";												//reset temp to an empty string
			}
		}
		if (temp != "") {												//make sure whatever was left from the above filtering is not an empty string, otherwise, do nothing
			myHashTable.insert(temp);
		}
	}
	fin.close();
	
	listCommands();

	while(fileExist)
	{
		string user_input;
		cout<<endl<<">";
		getline(cin,user_input);

		string command = user_input.substr(0,user_input.find(" "));
		string argument = user_input.substr(user_input.find(" ")+1);

		if(command == "find") 
			{
				int freq = myHashTable.find_freq(argument);
				if (freq == 0) {
					cout<<"Frequency of '"<<argument<<"' is: 0. This word does not exist in the file."<<endl;
				}
				else {
					cout<<"Frequency of '"<<argument<<"' is: "<<freq<<"."<<endl;
				}
			}		else if(command == "unique") {cout<< "The number of unique words is: " << myHashTable.count_unique_words()<<"."<<endl;}
		else if(command == "total") {cout<< "The total number of words is: " <<myHashTable.count_words()<< "."<<endl ;}
		else if(command == "percent")	  {cout<< "The percentage of unique words from the total is: "<< setprecision(3)<<myHashTable.unique_words_percent()<< "%."<<endl;}
		else if(command == "collisions")	  {cout<< "The number of collisions is: " <<myHashTable.count_collision()<<"."<<endl;}
		else if(command == "help")	  {listCommands();}
		else if(command == "exit")	  {break;}
		else {cout<<"Invalid command !!!"<<endl<<endl;}
	}
	return 0;
}





