#include<iostream>
#include<cstdlib>
#include<stdexcept>
#include<fstream>
#include<string>
#include<exception>
#include<sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <functional>
#include <stdio.h>

#include "CCourse.h"

using namespace std;

class Students;

//====================================
class StudentNode
{
	private:
		//data elements
		string studentID;
		string firstName;
		string lastName;
		string username;
		string password;

		Courses<Students> course_list;


		StudentNode* next; //Link (pointer) to the next Node

	public:
		StudentNode(string studentID, string firstName, string lastName, string username, string password) :
		studentID(studentID) , firstName(firstName) , lastName(lastName) , username(username) , password(password)
		{}

		friend class Students ;


};
//=====================================
class Students
{
	private:
		StudentNode* head; // pointer to the head of list
	public:
		Students (); // empty list constructor
		~Students (); // destructor to clean up all nodes

		bool empty() const; // is list empty?
		void addFront(const string& studentID, const string& firstName, const string& lastName, const string& username, const string& password); // add a new Node at the front of the list
		void removeFront(); // remove front Node from the list
		void display() const;
		void loadData(string); //read a file and load it into the linked list
		void dumpData(string) const; //write the linked list to a file
		bool checkUsername(string)const;
		bool checkPassword(string,string)const;

		bool checkExistance(string id) const;
		void studentCommands();
		void registering(string, string) const;
		void withdraw();
};

//====================================
// constructor
Students::Students ()
{
	this->head = NULL;
}
//====================================
// destructor to clean up all nodes
Students::~Students ()
{
	while (!empty())
	{
		removeFront();
	}
	this->head = NULL;
}
//====================================
// Check if the list is empty or not
bool Students::empty() const
{
	return (this->head == NULL);
}
//====================================
// add a node at the front of list
void Students::addFront(const string& studentID, const string& firstName, const string& lastName, const string& username, const string& password )
{
	StudentNode* front = new StudentNode(studentID, firstName, lastName, username,password);
	front->next = this->head;
	this->head = front;
}
//====================================
// remove the first node from the list
void Students::removeFront()
{
	if (empty())
	{
		throw out_of_range("This list is empty.");
	}
	else
	{
		StudentNode* old = this->head;
		this->head = old->next;
		delete old;
	}

}
//====================================
// display all nodes of the linked list
void Students::display() const
{
	StudentNode* currentNode = this->head;
	cout<<endl;
	while (currentNode != NULL)
	{
		cout<<" Student ID: "<<currentNode->studentID<<endl<<" First Name: "<<currentNode->firstName<<endl<<" Last Name: "<<currentNode->lastName<<endl<<" Username: "<<currentNode->username<<endl<<" Password: "<<currentNode->password;
		cout<<endl<<endl;
		currentNode = currentNode->next;
	}
}

//==============================================
//Load data from a file and add it to the Linked List
void Students::loadData(string path)
{

	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		cout<<"Error opening file."<<endl;
	}
	else
	{
		string line, word;
		string id, first, last, user, pass;
		getline(fin,line);

		while(getline(fin,line))
		{
			line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
			stringstream word(line);

			getline(word,id,',');
			getline(word,first,',');
			getline(word,last,',');
			getline(word,user,',');
			getline(word,pass,',');

			addFront(id, first, last, user, pass);
		}
	}
	fin.close();
}

//=================================================
//checking if username entered is correct
bool Students::checkUsername(string username) const{

	StudentNode* currentStudent = this->head;
	bool valid = false;
	while (currentStudent!=NULL){
		if (currentStudent->username == username){
			valid = true;
			break;
		}
		currentStudent = currentStudent->next;
	}
	return valid;

}
//=================================================
//checking if password entered matches username
bool Students::checkPassword(string username, string password)const{
	StudentNode* currentStudent = this->head;
	bool valid = false;
	while (currentStudent!=NULL){
		if ( currentStudent->username == username  && currentStudent->password == password){
			cout<<currentStudent->password<<" hello "<<endl;

			valid = true;
			break;

		}
		currentStudent = currentStudent->next;
	}
	return valid;
}

//====================================
void Students::studentCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"view_courses       : View list of all your courses"<<endl
		<<"view_available     : View list of all available courses"<<endl
		<<"register           : Register in a course"<<endl
		<<"withdraw           : Withdraw from a course if possible"<<endl
		<<"help               : Display the list of commands again"<<endl
		<<"exit               : Exit the Program"<<endl;
}

//=========================================
bool Students::checkExistance(string id) const{
	bool exist = false;
	StudentNode* currentStudent = this->head;
	while (currentStudent!=NULL){
		if (currentStudent->studentID == id){
			exist = true;
			break;
		}
		currentStudent = currentStudent->next;
	}
	return exist;


}
//===================================================
void Students::registering(string courseID, string courseSection) const {
// 	CourseNode* ptr = this->head;
// 	while (ptr !=NULL){
// 		if (ptr->courseID == courseID && ptr->courseSection == courseSection){
// 			if (ptr->currentNumber < ptr->maxCapacity){
// 				ptr->currentNumber++;
// 				break;
// 			}
// 		}
// 		ptr = ptr->next;
// 	}



}
//==================================================
void Students::withdraw() {

}

//=================================================
//writing/dumping the contents of the list into a file

void Students::dumpData(string path) const
{
	//opening the old file
	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		cout<<"Error opening file."<<endl;
	}

	//writing data into new file.
	StudentNode* temp = this->head;
	ofstream fout;
	fout.open("newfile.csv");
	if (!fout.is_open())
	{
		cout<<"Error opening file."<<endl;
	}
	else
	{	
		fout<<"Student_ID,First_name,Last_name,username,password"<<endl;
		while(temp->next != NULL) //until the element before last
		{
			fout<<temp->studentID<<","<<temp->firstName<<","<<temp->lastName<<","<<temp->username<<","<<temp->password<<endl;
			temp = temp->next;
			
		}
	}

	//deleting the old file and renaming the updated one (with the name of the old file)
	int result1,result2,result3;
	char name[] = "newfile.csv";
	char newname[] = "MyUniversityStudents.csv";
	result1 = rename (path.c_str(), "older.csv");

	result2 = rename(name,newname);
	result3 = remove("older.csv");

	if(result1 == 0 && result2 == 0 && result3 == 0 ){cout<<"Student file updated successfully."<<endl;}
	else if (result1 != 0 && result2 != 0 && result3 != 0){cout<<"Error updating file."<<endl;}



	//closing both files
	fin.close();
	fout.close();


}
















