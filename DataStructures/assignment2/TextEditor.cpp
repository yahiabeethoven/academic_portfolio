
#include<fstream>
#include "TextEditor.h"

TextEditor::TextEditor() {
	cursor.v = S.header;
}

TextEditor::~TextEditor(){}

void TextEditor::loadData(string path) {
	ifstream fin;
	fin.open(path);

	if (!fin.is_open()) {
		cerr<<"Error opening file."<<endl;				//if file was not foun/ could not be created return error
	}

	else {
		string temp, line;

		while (getline(fin, line)) {

			while (line.length() > 1) {									//make sure there is only sentence per line
				temp = line.substr(0, line.find('.') + 1);
				if (temp.substr(0,1) == " ") {							//if the first character in the sentence is a space, skip it
					temp = temp.substr(1);
				}
				S.insertBack(temp);
				line = line.erase(0, line.find('.') + 1);
			}
			// temp = line+period;
			

		// line.erase(remove(line.begin(), line.end(), '\r'), line.end() );
		}
		fin.close();
		cursor = S.begin();							//set cursor to first line
		maintainSentencePerLine();
		cout<<"----------------------------------"<<endl;
		cout<<endl<<"The content of "<< path << " file:"<<endl<<endl;
		cout<<"----------------------------------"<<endl;
		printAll();
	}
	
	cout<<endl;
	
}

bool TextEditor::isEmpty(){							//is file empty
	if ((S.isEmpty()) && (cursor.v == S.header)) {
		return true;
	}

	else {
		return false;
	}
}			/* Return true if and only if the text is completely empty (and cursor
is at line -1 (imaginary line, only in case the text is completely
empty ). */

int TextEditor::size(){							//number of lines in file
	return S.size();
}		// Return the current number of lines (i.e. sentences) of text.

bool TextEditor::isCursorAtLastLine(){				
	if ((cursor.v == S.trailer->prev) || (isEmpty())) {
		return true;
	}
	else {
		return false;
	}
	
}		/* Return true if and only if the cursor is at the last line in the
text or the text is empty. */

void TextEditor::cursorDown(){
	try {
		if (isCursorAtLastLine()) {
			throw InvalidLine();
		}

		else {

			++cursor;
		}
	}
	catch (InvalidLine& e) {
		cout<< e.what() <<endl;
	}
}			/* Set the cursor to be in the line after its current position. (Error
if there is no line after) */

void TextEditor::cursorUp(){
	try {
		if (S.before(cursor).v == S.header) {
			throw InvalidLine();
		}

		else {
			--cursor;
		}
	}
	catch (InvalidLine& e) {
		cout<< e.what() <<endl;
	}
}		/* Set the cursor to be in the line before its current position. (Error
if there is no line before) */

void TextEditor::moveCursorToLine(int i){
	try {
		if (i > (size() - 1) || i < 0) {
			throw InvalidLine();
		}

		else {

			cursor = S.atIndex(i);
		}
	}
	catch (InvalidLine& e) {
		cout<< e.what() <<endl;
	}
}			/* Set the cursor to be the line indexed i (the first line is line 0).
(Error if i is out of boundary) */

int TextEditor::cursorLineNum(){
	if (cursor.v == S.header) {
		return -1;
	}
	else {
		return S.IndexOf(cursor);
	}
	
}		// Return the line number (i.e. index) of where the cursor is.

void TextEditor::insertLineAfterCursor(string sentence){
	S.insertAfter(cursor, sentence);
	cursorDown();
	maintainSentencePerLine();
}			/* Insert a new line (containing the new sentence) after the line the
current cursor is at, moving the cursor to the new line inserted. */

void TextEditor::insertLineBeforeCursor(string sentence){
	S.insertBefore(cursor, sentence);
	cursorUp();
	maintainSentencePerLine();
}			/* Insert a new line (containing the new sentence) before the line the
current cursor is at, moving the cursor to the new line inserted. */

void TextEditor::replaceAtCursor(string sentence){
	int index = cursorLineNum();
	S.insertAtIndex(index, sentence);
	maintainSentencePerLine();
}		/* Replace the sentence at the current cursor with the sentence given
as an argument, keeping the cursor at this line. */

void TextEditor::removeAtCursor(){
	string content = *cursor;
	try {
		if (content == "") {
			throw EmptyLine();
		}

		else {
			S.eraseAtPosition(cursor);

			if (!isCursorAtLastLine()) {
				cursorDown();
			}
			else {
				cursor.v = S.header;
			}
			
		}

	}
	catch (EmptyLine& e) {
		cout<< e.what()<<endl;
	}
}			/* Remove the line at the current cursor; setting the cursor to now be
the position of the next line, unless the cursor was the last line, in
which case the cursor should move to line -1. (Error if the text is
empty) */

void TextEditor::maintainSentencePerLine(){
int index = cursorLineNum();

	for (Sequence::Iterator current = S.begin(); current != S.end(); ++current) {
		string checkLine, temp;
		checkLine = *current;
		cursor = current;

		if ((checkLine.find(".") != -1) && (checkLine.length() - 1 != checkLine.find("."))) {
			vector <string> x = split(checkLine, '.');
			for (unsigned i = 0; i < x.size(); i++) {
				if (x.at(i).substr(0,1) == " ") {
					x.at(i) = x.at(i).substr(1);
					// x.at(i).substr(1);
				}
			}
			replaceAtCursor(x.at(0) + '.');
			for (unsigned i=1; i<x.size(); i++) {
				insertLineAfterCursor(x.at(i)+ '.');
			}
		}
	}
// cursor = S.begin();
moveCursorToLine(index);
}				/* Make sure that each line in the entire text contains one sentence
only. For example, if a line contains two sentences, keep the first
sentence in the same line and move the second to a new line next to the
current line. */

void TextEditor::printAtCursor(){
	cout<< *cursor <<endl;
}				// Print the line, where the cursor is, to the terminal.

void TextEditor::printAll(){
	for (Sequence::Iterator current = S.begin(); current != S.end(); ++current) {
		cout<< *current <<endl;
	}
}		// Print the entire text (i.e. all sentences) to the terminal.

void TextEditor::dumpData(string path, string fileName) {

	//opening the old file
	maintainSentencePerLine();
	ifstream fin;
	fin.open(path);
	if (!fin)
	{
		cerr<<"Error loading original file."<<endl;
		return;
	}
	fin.close();

	//writing data into new file.
	cursor = S.begin();
	ofstream fout;
	
	if (fileName.substr(fileName.length() - 4) != ".txt") {				//if the given input was not in format xxx.txt, make it so
		fileName += ".txt";
	}

	fout.open(fileName);

	if (!fout)
	{
		cerr<<"Error opening file."<<endl;
		return;
	}
	else
	{	
		while(cursor != S.end()) //until the element before last
		{
			fout<<*cursor<<endl;
			++cursor;
		}
	fout.close();
	}
}


// supporting function inspired from https://stackoverflow.com/questions/890164/how-can-i-split-a-string-by-a-delimiter-into-an-array
vector<string> TextEditor::split(const string& line, const char& period) {
    string following;
    vector<string> temp;

    // iterate through characters
    for (string::const_iterator current = line.begin(); current != line.end(); current++) {

        if (*current == period) {
            // If there are strings after the period
            if (!following.empty()) {
                // add them to temp
                temp.push_back(following);
                following.clear();
            }
        } else {
            // keep adding the corresponding characters
            following += *current;
        }
    }
    if (!following.empty())
         temp.push_back(following);
    return temp;
}	



