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

template <typename T>
class CourseNode
{
	private:
		 //data elements
		string courseID;
		string courseName;
		int maxCapacity;
		int currentNumber;
		string instructorName;
		string courseSection;
		string courseLocation;

		T student_list;

	 CourseNode<T>* next; //Link (pointer) to the next CourseNode

	public:
	 CourseNode(string courseID, string courseName, int maxCapacity, int currentNumber, string instructorName, string courseSection, string courseLocation) :
		courseID(courseID) , courseName(courseName) , maxCapacity(maxCapacity) , currentNumber(currentNumber) , instructorName(instructorName) , courseSection(courseSection), courseLocation(courseLocation)
		{}
		template <typename R>
		friend class Courses;

};

template<typename T>
class Courses
{
	private:
		CourseNode<T>* head;

	public:
		Courses (); // empty list constructor
		~Courses (); // destructor to clean up all CourseNodes
		bool empty() const; // is list empty?
		void addFront(const string& courseID, const string& courseName, const int& maxCapacity, const int& currentNumber, const string& instructorName, const string& courseSection, const string& courseLocation); // add a new CourseNode at the front of the list
		void removeFront(); // remove front CourseNode from the list
		void removeAt(string);
		void display() const;
		void display_available() const;
		void view_details(string) const;
		void changeInstructor(string,string);
		T students_in_course(string id) const;
		void loadData(string); //read a file and load it into the linked list
		void dumpData(string) const; //write the linked list to a file
};


//====================================
// constructor
template <typename T>
Courses<T>::Courses ()
{
	this->head = NULL;
}
//====================================
// destructor to clean up all CourseNodes
template <typename T>
Courses<T>::~Courses ()
{
	while (!empty()) {
		removeFront();
	}
	this->head = NULL;
}
//====================================

// Check if the list is empty or not
template <typename T>
bool Courses<T>::empty() const
{
	return this->head == NULL;
}

//====================================
// add a CourseNode at the front of list
template <typename T>
void Courses<T>::addFront( const string& courseID, const string& courseName, const int& maxCapacity, const int& currentNumber, const string& instructorName, const string& courseSection, const string& courseLocation)
{
	CourseNode<T>* u = new CourseNode<T>(courseID, courseName, maxCapacity, currentNumber, instructorName, courseSection, courseLocation);
	u->next = this->head;
	this->head = u;
}

//====================================
// remove the first CourseNode from the list
template <typename T>
void Courses<T>::removeFront()
{
	if (empty())
	{
		throw out_of_range("This list is empty.");
	}
	else
	{
		CourseNode<T>* old = this->head;
		this->head = old->next;
		delete old;
	}

}

//====================================
// display all CourseNodes of the linked list

template <typename T>
void Courses<T>::display() const
{
 CourseNode<T>* ptr = this->head;
	cout<<endl;
	while(ptr != NULL) {

		cout<<" Course ID: "<<ptr->courseID<<endl<<" Course Name: "<<ptr->courseName<<endl<<" Maximum No. Students: "<<ptr->maxCapacity<<endl<<" Current No. Students: "<<ptr->currentNumber<<endl<<" Instructor: "
		<< ptr->instructorName <<endl<<" Section Number: "<<ptr->courseSection <<endl<<" Course Location: "<<ptr-> courseLocation<<endl<<endl;
		ptr = ptr->next;
	}
}

//====================================
// display all availble Courses
template <typename T>
void Courses<T>::display_available() const
{
 CourseNode<T>* ptr = this->head;
	cout<<endl;
	while(ptr != NULL) {
		if (ptr->currentNumber < ptr->maxCapacity ){
			cout<<" Course ID: "<<ptr->courseID<<endl<<" Course Name: "<<ptr->courseName<<endl<<" Maximum No. Students: "<<ptr->maxCapacity<<endl<<" Current No. Students: "<<ptr->currentNumber<<endl<<" Instructor: "
		<< ptr->instructorName <<endl<<" Section Number: "<<ptr->courseSection <<endl<<" Course Location: "<<ptr-> courseLocation<<endl<<endl;
			ptr = ptr->next;
		}
	}
}


//===========================================
//Load data from a file and add it to the Linked List
template <typename T>
void Courses<T>::loadData(string path)
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
		string id, name, max, current, instructor, section, location;
		getline(fin,line);

		while(getline(fin,line))
		{
			line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() );
			stringstream word(line);

			getline(word, name, ',');
			getline(word, id, ',');
			getline(word, max, ',');
			getline(word, current, ',');
			getline(word, instructor, ',');
			getline(word, section, ',');
			getline(word, location, ',');

			addFront(id, name, stoi(max), stoi(current), instructor, section, location);
		}
	}
	fin.close();
}
//=================================================
//writing/dumping the contents of the list into a file
template<typename T>
void Courses<T>::dumpData(string path) const
{
	//opening the old file
	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		cout<<"Error opening file."<<endl;
	}

	//writing data into new file.
	CourseNode<T>* temp = this->head;
	ofstream fout;
	fout.open("newFile.csv");
	if (!fout.is_open())
	{
		cout<<"Error opening file."<<endl;
	}
	else
	{	
		fout<<"Course_Name,Course_Id,Maximum_Students,Current_Students,Course_Instructor,Course_Section_Number,Course_Location"<<endl;
		while(temp->next != NULL) //until the element before last
		{
			fout<<temp->courseID<<","<<temp->courseName<<","<<temp->maxCapacity<<","<<temp->currentNumber<<","<<temp->instructorName<<","<<temp->courseSection<<","<<temp->courseLocation<<","<<endl;
			temp = temp->next;
			
		}
	}

	//deleting the old file and renaming the updated one (with the name of the old file)
	int result1,result2,result3;
	char name[] = "newFile.csv";
	char newname[] = "MyUniversityCourses.csv";
	result1 = rename (path.c_str(), "old.csv");

	result2 = rename(name,newname);
	result3 = remove("old.csv");

	if(result1 == 0 && result2 == 0 && result3 == 0 ){cout<<"Course file updated successfully."<<endl;}
	else if (result1 != 0 && result2 != 0 && result3 != 0){cout<<"Error updating file."<<endl;}



	//closing both files
	fin.close();
	fout.close();


}

// ====================================
// removes a CourseNode at a specific location.
template <typename T>
void Courses<T>::removeAt(string id)
{
	if (empty())
	{
		throw out_of_range("This list is empty.");
	}
	else
	{	
		bool exists = false;
		if (this->head->courseID == id)
		{
			removeFront();
			cout<<"The course has been deleted."<<endl;

		}
		else{
			CourseNode<T>* temp = this->head;
			while(temp != NULL){
				if(temp->next->courseID == id){
					exists = true;
					break;
				}
				temp= temp->next;
			}
			if(exists){	
				CourseNode<T>* toDelete = temp->next;
				temp->next = toDelete->next;
				delete toDelete;
				cout<<"The course has been deleted."<<endl;
			}
			else {cout<<"This courseID doesn't exist."<<endl;}
		}
		
	}

}
//==============================================
//function to change the instructor of a course:
template <typename T>
void Courses<T>::changeInstructor(string id,string newInstructor){
	if (empty())
	{
		throw out_of_range("This list is empty.");
	}
	else{
		bool exists = false;
		CourseNode<T>* temp = this->head;
		while(temp != NULL){
			if(temp->courseID == id){
				temp->instructorName = newInstructor;
				exists = true;
				break;
			}
			temp= temp->next;
		}
		if (exists){cout<<"Instructor for this course changed successfully."<<endl;}
		else{cout<<"CourseID doesn't exist"<<endl;}
	}

}
//====================================
// display all CourseNodes of the linked list

template<typename T>
void Courses<T>::view_details(string id) const{
	if (empty())
	{
		throw out_of_range("This list is empty.");
	}
	else{
		bool exists = false;
		CourseNode<T>* ptr = this->head;
		while(ptr != NULL){
			if(ptr->courseID == id){
				cout<<" Course ID: "<<ptr->courseID<<endl<<" Course Name: "<<ptr->courseName<<endl<<" Maximum No. Students: "<<ptr->maxCapacity<<endl<<" Current No. Students: "<<ptr->currentNumber<<endl<<" Instructor: "
				<< ptr->instructorName <<endl<<" Section Number: "<<ptr->courseSection <<endl<<" Course Location: "<<ptr-> courseLocation<<endl<<endl;
		
				exists = true;
				break;
			}
		ptr= ptr->next;
		}
		if (!exists){cout<<"CourseID doesn't exist"<<endl;}
	}


}
//====================================
// return the student list of a specific course
template<typename T>
T Courses<T>::students_in_course(string id) const{
	// if (empty())
	// {
	// 	cout<<"This list is empty."<<endl;
	// }
	// else{
	// 	bool exists = false;
	// 	CourseNode<T>* ptr = this->head;
	// 	while(ptr != NULL){
	// 		if(ptr->courseID == id){
	// 			exists = true;
	// 			break;
	// 		}
	// 	ptr= ptr->next;	
	// 	}
	// 	if (exists) {return ptr->courseList;}
	// 	else{cout<<"CourseID doesn't exist."<<endl;}	

	// }

}











