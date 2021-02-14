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
#include <ctime>

#include "shared.cpp"
#include "CStudent.h"
#include "CAdmin.h"

using namespace std;

//==============
bool is_num(string);
//
int main(){

	Admin adminArray[3];
	Students student;
	Courses<Students> course;
	//loading all data
	loadAdmin(adminArray);
	student.loadData("MyUniversityStudents.csv");
	course.loadData("MyUniversityCourses.csv");

	// display(adminArray);
	// course.display();
	// student.display();


	cout<<"+--------------------------------------------+"<<endl;
	cout<<"|   Welcome to: Course Registration System   |"<<endl;
	cout<<"+--------------------------------------------+"<<endl<<endl;

	string userType, type;
	cout<<"Are you an administrative staff or a student?"<<endl;
	cout<<"Type staff or student to choose: ";
	getline(cin,userType);
	type = userType.substr(0,userType.find(" "));
	string username, password;
	bool valid1,valid2;

	if (type == "student"){
		cout<<"Welcome, student. Please enter your username: ";
		cin>>username;

		valid1 = student.checkUsername(username);
		if (valid1){
			cout<<"Great. Now enter your password: ";
			cin>>password;
			valid2 = student.checkPassword(username,password);

			if (valid2){
				cout<<"You are in. Choose a command."<<endl;
				student.studentCommands();
				string userChoice,command,parameter;
				cin.ignore();
				do
				{
					cout<<">";
					getline(cin,userChoice);
					command = userChoice.substr(0,userChoice.find(" "));
					parameter = userChoice.substr(userChoice.find(" ")+1);



					if(command=="view_courses")	        course.display();
					else if(command=="view_available")  course.display_available();
					// else if(command=="register")		student.registering(string, string);
					else if(command == "withdraw")		student.withdraw();
					else if(command == "help")			student.studentCommands();
					else if(command == "exit")			{cout<<"Goodbye."<<endl;
														break;}
					else 								cout<<"Invalid Command."<<endl;

				}while (command!= "exit");
			}
			else{
				cout<<"Password is incorrect."<<endl;
			}
		}
		else{
			cout<<"Invalid entry. Cannot find this username."<<endl;
		}
	}
	else if (type == "staff"){
		cout<<"Welcome, staff member. Please enter your username: ";
		cin>>username;

		valid1 = checkUsername(username,adminArray);
		if (valid1){
			cout<<"Great. Now enter your password: ";
			cin>>password;
			valid2 = checkPassword(username,password,adminArray);
			if (valid2){
				cout<<"You are in. Choose a command."<<endl;
				adminCommands();
				string userChoice,command,parameter;
				cin.ignore();
				do
				{
					cout<<">";
					getline(cin,userChoice);
					command = userChoice.substr(0,userChoice.find(" "));

					if (command == "add_course")
					{
						string id,name,capacity,current,instructor,section,location;
						cout<<"Enter the new course's ID: ";
						getline(cin,id); trim(id);
						cout<<"Now, the name: ";
						getline(cin,name); trim(name);
						cout<<"Now, the student capacity: ";
						getline(cin,capacity); trim(capacity);
						if (!is_num(capacity)) {cout<<"Your input is invalid. It is not a number."<<endl; break;}
						cout<<"Now, the current number of student enrolled in it (Should be 0): ";
						getline(cin,current); trim(current);
						if (!is_num(current)) {cout<<"Your input is invalid. It is not a number."<<endl; break;}
						cout<<"Now, the instructor name: ";
						getline(cin,instructor); trim(instructor);
						cout<<"Now, the section number: ";
						getline(cin,section); trim(section);
						if (!is_num(section)) {cout<<"Your input is invalid. It is not a number."<<endl; break;}
						cout<<"And finally, the location of the course: ";
						getline(cin,location); trim(location);
						course.addFront(id,name,stoi(capacity),stoi(current),instructor,section,location);
						cout<<"The course has been added."<<endl;
					}
					else if (command == "delete_course"){
						string id;
						cout<<"Enter the ID of the course you want to delete: ";
						getline(cin,id); trim(id);
						course.removeAt(id);
						
					}
					else if (command == "change_instructor"){
						string id, newInstructor;
						cout<<"Enter the ID of the course for which you want to change the instructor: ";
						getline(cin,id); trim(id);
						cout<<"Enter the name of the new instructor: ";
						getline(cin,newInstructor); trim(newInstructor);
						course.changeInstructor(id,newInstructor);

					}
					else if(command=="view_details"){
						string id;
						cout<<"Enter the ID of the course for which you want to see all details (except student list): ";
						getline(cin,id); trim(id);
						course.view_details(id);
					}
					else if (command == "add_student"){
						string first, last,id,username,password;
						cout<<"Enter the first name of the student you want to register: ";
						getline(cin,first); trim(first);
						cout<<"Now, enter their last name: ";
						getline(cin,last); trim(last);
						srand((unsigned)time(0));
						do{
							int x= rand() % 9999 + 1000;
							id = to_string(x);
						}while(student.checkExistance(id));
						//make a lower case string of first
						string lower_first = first;
						for (int i=0; lower_first[i]; i++) lower_first[i] = tolower(lower_first[i]);
						username = lower_first +id;
						int y = rand() % 9999 + 1000;
						//make a lower case string of last
						string lower_last = last;
						for (int i=0; lower_last[i]; i++) lower_last[i] = tolower(lower_last[i]);
						password = lower_last + to_string(y);
						student.addFront(id,first,last,username,password);
						cout<<"The student has been added."<<endl;



					}
					else if (command == "students_in_course") {
						string id;
						cout<<"Enter the ID of the course for which you want to see the enrolled students: ";
						getline(cin,id); trim(id);
						// Students enrolled_students = course.students_in_course(id);
						// enrolled_students.display();

					}
					else if(command=="view_courses")	course.display();
					else if(command=="view_available")  course.display_available();
					else if(command == "exit"){
						cout<<"Goodbye."<<endl;
						course.dumpData("MyUniversityCourses.csv");
						student.dumpData("MyUniversityStudents.csv");
					    break;
					}
					else cout<<"Invalid Command."<<endl;

				}while(command!= "exit");
			}
			else{
				cout<<"Password is incorrect."<<endl;
			}
		}
		else{
			cout<<"Invalid Entry. Cannot find this username."<<endl;
		}


	}

	else{
		cout<<"Invalid user type."<<endl;
	}

	return EXIT_SUCCESS;
}

















