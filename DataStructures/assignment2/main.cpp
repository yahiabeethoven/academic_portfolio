#include <iostream>
#include<cstdlib>
#include<stdexcept>
#include<fstream>
#include<string>
#include<exception>
#include<sstream>
#include <algorithm>

#include "TextEditor.h"

using namespace std;

void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"nextLine      					: Set the cursor to be in the line after its current position."<<endl
		<<"prevLine      					: Set the cursor to be in the line before its current position."<<endl
		<<"goToLine <key>      				: Set the cursor to be the line indexed (the first line is line 0)."<<endl
		<<"currentLine      				: Return the line number (i.e. index) of where the cursor is."<<endl
		<<"insertLineAfterCursor <key>      : Insert a new line (containing the new sentence) after the current cursor, moving the cursor to the new line inserted."<<endl
		<<"insertLineBeforeCursor <key>     : Insert a new line (containing the new sentence) before the current cursor, moving the cursor to the new line inserted."<<endl
		<<"replaceLine <key>      			: Replace the sentence at the current cursor with the sentence given as an argument, keeping the cursor at this line."<<endl
		<<"removeLine      					: Remove the line at the current cursor."<<endl
		<<"maintainSentencePerLine          : Make sure that each line in the entire text contains one sentence only."<<endl
		<<"printLine      					: Print the line, where the cursor is, to the terminal."<<endl
		<<"printAll      					: Print the entire text (i.e. all sentences) to the terminal."<<endl
		<<"help      						: Display the available commands."<<endl
		<<"exit      						: Exit the program (save or not save)."<<endl;
}

int main() {

	TextEditor texteditor;

	cout<<"+------------------------------------+"<<endl;
	cout<<"|   Welcome to: Text Editor System   |"<<endl;
	cout<<"+------------------------------------+"<<endl<<endl;

	string userPath, path;
	cout<< "Please enter the full directory path of the file: "<<endl;
	getline(cin,userPath);
	path = userPath.substr(0,userPath.find(" "));

	texteditor.loadData(path);
	bool fileExist;

	ifstream temp;
	temp.open(path);
	if (!temp.is_open())			//if path provided doesn't exist or cannot open a file
	{
		fileExist = false;
	}
	else {
		fileExist = true;
	}


	if (fileExist) {
		listCommands();
		cout<<"----------------------------------"<<endl;
		cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
	}
	
	//commands function and setup inspired from Professor Khalid's labs format

	string user_input;
	string command;
	string key;

	while (fileExist) {
		cout<<endl<<">";
		getline(cin,user_input);

		command = user_input.substr(0,user_input.find(" "));
		key = user_input.substr(user_input.find(" ")+1);

		cout<<"----------------------------------"<<endl;
		if( command =="nextLine")	//move cursor down
			{
				texteditor.cursorDown();
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="prevLine")	//move cursor up
			{
				texteditor.cursorUp();
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			} 
		else if( command =="goToLine")	//go to line indexed
			{
				texteditor.moveCursorToLine(stoi(key));
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="currentLine")	//return current line
			{
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="insertLineAfterCursor")		//insert line after current using given
			{
				texteditor.insertLineAfterCursor(key);
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="insertLineBeforeCursor")		//insert line before current using given
			{
				texteditor.insertLineBeforeCursor(key);
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="replaceLine")		//replace current line using given
			{
				texteditor.replaceAtCursor(key);
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="removeLine")	//delete current line and update list accordingly
			{
				texteditor.removeAtCursor();
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="maintainSentencePerLine")	//maintain one sentence per one line
			{
				texteditor.maintainSentencePerLine();
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="printLine")			//print content of line of cursor
			{
				texteditor.printAtCursor();
				cout<< "The cursor is at line: "<<texteditor.cursorLineNum()<<"."<<endl;
			}
		else if( command =="printAll")				//print all the lines
			{
				texteditor.printAll();
			}
		
		else if( command =="exit") 		{
			cout<< "Would you like to save the changes you made to this file? (yes or no)"<<endl;		//ask user if they want to save
			cout<<endl<<">";
			string userQuit, save, quit, fileName;
			getline(cin,userQuit);

			quit = userQuit.substr(0,userQuit.find(" "));


			if (quit == "yes") {
				cout<<"----------------------------------"<<endl;
				cout<<"Please specify the full name of the updated text file to be created (including '.txt'):"<<endl;
				cout<<endl<<">";
				getline(cin, save);
				fileName = save.substr(0,save.find(" "));
				texteditor.dumpData(path, fileName);						//create new file with updates
				cout<<endl;
				break;
			}
			else {
				break;									//quit program permanently and delete changes
			}
		}

		else if( command == "help") 	{listCommands();}
		else cout<<endl<<"Invalid command!"<<endl;
	}

	return 0;

}