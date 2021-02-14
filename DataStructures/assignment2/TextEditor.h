#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


#include <iostream>
#include<cstdlib>
#include<stdexcept>
#include<fstream>
#include<string>
#include<exception>
#include<sstream>
#include <cctype>
#include <algorithm>
#include <vector>

#include "Sequence.h"

using namespace std;

//=========================================================================================================

class InvalidLine: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Cannot move the cursor to this line.."; 
	}
};

class EmptyLine: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Line is Empty."; 
	}
};

//=========================================================================================================

class TextEditor {

public:
	Sequence S;
	Sequence::Iterator cursor;

	TextEditor();
	~TextEditor();
	void loadData(string);
	bool isEmpty();
	int size();
	bool isCursorAtLastLine();
	void cursorDown();
	void cursorUp();
	void moveCursorToLine(int i);
	int cursorLineNum();
	void insertLineAfterCursor(string sentence);
	void insertLineBeforeCursor(string sentence);
	void replaceAtCursor(string sentence);
	void removeAtCursor();
	void maintainSentencePerLine();
	void printAtCursor();
	void printAll();
	void dumpData(string path, string fileName);
	vector<string> split(const string& line, const char& period);


friend class Sequence;

};

#endif