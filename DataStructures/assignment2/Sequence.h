#ifndef SEQUENCE_H
#define SEQUENCE_H


#include <iostream>
#include<cstdlib>
#include<stdexcept>
#include<fstream>
#include<string>
#include<exception>
#include<sstream>
#include<iomanip>
#include <algorithm>

using namespace std;


typedef string Elem;

//exception class inspired from lab6 by Khalid
//=========================================================================================================
class SequenceEmpty: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Sequence is Empty."; 
	}
};

class InvalidPosition: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Position is Invalid."; 
	}
};

class IndexOutOfBounds: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Index is out of Boundary."; 
	}
};

//=========================================================================================================

class Sequence {

friend class TextEditor;

protected:
	struct Node
	{
	private:
		Elem elem; //data element (type string in this case)
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node

	friend class Sequence;
	friend class TextEditor;
	};

public:

	class Iterator {
	protected:
		Node *v;
		Iterator(Node *u);

	friend class Sequence;
	friend class TextEditor;
	
	public:
		// ~Iterator();
		Iterator();
		Elem& operator*();
		bool operator==(const Iterator& p)const;
		bool operator!=(const Iterator& p)const;
		Iterator& operator++();
		Iterator& operator--();	
	};

public:
	Sequence();
	~Sequence();
	int size();
	bool isEmpty();
	void insertBefore(const Sequence::Iterator& p, const Elem& e);
	void insertAfter(const Sequence::Iterator& p, const Elem& e);
	void eraseAtPosition(const Sequence::Iterator& p);
	Sequence::Iterator& before(const Sequence::Iterator& p);
	Sequence::Iterator& after(const Sequence::Iterator& p);
	int IndexOf(const Sequence::Iterator& p);
	Sequence::Iterator& begin();			// throws an error if the container is empty
	Sequence::Iterator& end();			// throws an error if the container is empty
	Sequence::Iterator& atIndex(int index);
	void insertAtIndex(int index, const Elem& e);
	void eraseAtIndex(int index);
	Sequence::Iterator& insertFront(const Elem& e);
	Sequence::Iterator& insertBack(const Elem& e);
	void eraseFront();			// throws an error if the container is empty
	void eraseBack();			// throws an error if the container is empty
	Elem& frontElement();		// throws an error if the container is empty
	Elem& backElement();		// throws an error if the container is empty

protected:
	Node* header; // pointer to the header of List
	Node* trailer; // pointer to the trailer of List
	int n;		//number of nodes

};

#endif