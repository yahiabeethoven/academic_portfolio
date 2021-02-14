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

using namespace std;

class Admin
{
	private:
		string staffID;
		string firstName;
		string lastName;
		string username;
		string password;

		friend void loadAdmin(Admin[]);
		friend void display(Admin[]);
	public:
		//setter methods
		void setID(string);
		void setFirst(string);
		void setLast(string);
		void setUsername(string);
		void setPassword(string);
		//getter methods
		string getID() const;
		string getFirst()const;
		string getLast()const;
		string getUsername()const;
		string getPassword()const;
		//other methods
		friend bool checkUsername(string,Admin[]);
		friend bool checkPassword(string,string,Admin[]);


};

void loadAdmin(Admin adminArray[]){
	
	//open admin file
	ifstream admins;
	admins.open("MyUniversityAdmin.csv");

	if (!admins.is_open())
	{
		cout<<"Error opening file. File was not found."<<endl;
	}

	else
	{

		//skip first line
		string line, word;
		getline(admins,line);


		//traverse the rest .csv file
		int i=0;
		while(getline(admins,line)){ //going through the lines
			line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
			stringstream s(line); //dividing the line into words
			int counter = 0;
			while (getline(s,word,',')){ //going through the words
				
				
				switch (counter)
				{
					case 0 :adminArray[i].setID(word);
							// cout<<adminArray[i].getID()<<endl;
							break;
					case 1 :adminArray[i].setFirst(word);
							break;
					case 2 :adminArray[i].setLast(word);
							break;
					case 3 :adminArray[i].setUsername(word);
							break;
					case 4 :adminArray[i].setPassword(word);
							break;
				}
				counter++;
			}
			i++;
		}
	}
	admins.close();
}


void display(Admin adminArray[]){
	for (int i=0; i<3; i++){
		cout<<adminArray[i].getID()<<" "<<adminArray[i].getFirst()<<" "<<adminArray[i].getLast()<<" "<<adminArray[i].getUsername()<<" "<<adminArray[i].getPassword()<<endl;
	}
}

void Admin::setID(string id){
	staffID = id;
}
void Admin::setFirst(string first){
	firstName = first;
}
void Admin::setLast(string last){
	lastName = last;
}
void Admin::setUsername(string user){
	username = user;
}
void Admin::setPassword(string pass){
	password = pass;
}
string Admin::getID()const{
	return staffID;
}
string Admin::getFirst()const{
	return firstName;
}
string Admin::getLast()const{
	return lastName;
}
string Admin::getUsername()const{
	return username;
}
string Admin::getPassword()const{
	return password;
}



bool checkUsername(string user,  Admin adminArray[]){
	bool valid=false;
	for (int i=0; i<3; i++){
		if (adminArray[i].getUsername() == user){
			valid = true;
			break;
		}
	}
	return valid;
}

bool checkPassword(string user, string pass, Admin adminArray[]){
	bool valid=false;
	for (int i=0; i<3; i++){
		if (adminArray[i].getUsername() == user && adminArray[i].getPassword() == pass){
			valid = true;
			break;
		}
	}
	return valid;
}


//====================================
void adminCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"add_course           : Add a new course"<<endl
		<<"delete_course        : Delete a course"<<endl
		<<"change_instructor    : Change a course's instructor"<<endl
		<<"view_details         : View a course's details(without the list of students)"<<endl
		<<"students_in_course   : View list of students enrolled in a course"<<endl
		<<"add_student          : Register a new student"<<endl
		<<"courses_in_student   : View list of courses a student is enrolled in"<<endl
		<<"view_courses         : View list of all courses"<<endl
		<<"view_available       : View list of all available courses"<<endl
		<<"help                 : Display the list of commands again"<<endl
		<<"exit                 : Exit the Program"<<endl;
}

//====================================













