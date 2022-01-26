#include <iostream>
#include <fstream>
#include <string>
#include "Note.h"
#include <vector>

std::vector <Note> notes;
void loadDatabase();
void showNotes();
void showOptions();
void executeCommand();
void saveDatabase();
void showNotesOld();											//unused
bool archiveModeCheck();
void showCredits();

bool running = true;
bool archiveMode = false;
bool descriptions = true;

std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int main() {
	loadDatabase();
	while (running) {
		system("cls");
		showNotes();
		showOptions();
		executeCommand();
	}
}

void loadDatabase() {
	std::ifstream file;
	std::string line;
	std::string date;
	file.open("database.dtb");
	while (getline(file, line)) {
		if (line[0] == '#' || line[0] == '@') {					//new note symbols
			date = line;
			getline(file, line);								//note name
			notes.push_back(Note(line));
			if (date[0] == '@')									//new archived note symbol
				notes[notes.size() - 1].isArchived = true;
			if (date.length() > 1) {
				notes[notes.size() - 1].hasDate = true;
				notes[notes.size() - 1].setDay( stoi( date.substr(1,2) ) );
				notes[notes.size() - 1].setMonth( stoi(date.substr(4,2)) );
				notes[notes.size() - 1].setYear( stoi(date.substr(7,4)) );
			}
		}
		else {
			notes[notes.size() - 1].addDescLine(line);			//note description
		}
	}
	file.close();
}

void showNotes() {
	if (archiveMode)
		std::cout << "__________________________________ARCHIVE MODE__________________________________" << std::endl;
	else
		std::cout << "________________________________________________________________________________" << std::endl;
	bool empty = true;											//date-less notes: for the first note of this kind,
	for (int i = 0; i < notes.size(); i++) {					//there will be a "no date" heading
		if (notes[i].isArchived == archiveMode) {
			if (!notes[i].hasDate) {
				if (empty) {
					std::cout << "----------------No  date----------------" << std::endl;
					empty = false;
				}
				std::cout << "   " << notes[i].getName() << " [" << i + 1 << "]" << std::endl;
				if (descriptions)
					std::cout << notes[i].getDescReadOnly() << std::endl;
			}
		}
	}
	for (int y = 2020; y <= 2120; y++) {						//for each year...
		bool emptyYear = true;									//same as for date-less notes previously
		for (int m = 1; m <= 12; m++) {							//for each month...
			for (int d = 1; d <= 31; d++) {						//for each day...
				bool emptyDay = true;							//same as for date-less notes
				for (int i = 0; i < notes.size(); i++) {		//for each note, if it matches witch the proper year and day and month
					if (notes[i].isArchived == archiveMode) {
						if (notes[i].hasDate) {					//it will be printed in this part
							if (notes[i].getYear() == y) {
								if (emptyYear) {
									std::cout << "------------------" << y << "------------------" << std::endl;
									emptyYear = false;
								}
								if (notes[i].getMonth() == m and notes[i].getDay() == d) {
									if (emptyDay) {
										std::cout << notes[i].getDayString() << " " << months[notes[i].getMonth() - 1] << ":" << std::endl;
										emptyDay = false;
									}
									std::cout << "   " << notes[i].getName() << " [" << i + 1 << "]" << std::endl;
									if (descriptions)
										std::cout << notes[i].getDescReadOnly() << std::endl;
								}
							}
						}
					}
				}
			}
		}
	}
}

void showOptions() {
	if (archiveMode)
		std::cout << "__________________________________ARCHIVE MODE__________________________________" << std::endl;
	else
		std::cout << "________________________________________________________________________________" << std::endl;
	std::cout << "Avaible commands:" << std::endl;
	if (!archiveMode) {
		std::cout << "create - creates a new note" << std::endl
			<< "update [number] - adds a new text line to the note description" << std::endl
			<< "changename [number] - replaces the note's name with a new one" << std::endl
			<< "changedesc [number] - replaces the note's description with a new one" << std::endl
			<< "changedate [number] - replaces the note's date with a new one" << std::endl
			<< "remove [number] - removes the note completely" << std::endl;
	}
	std::cout << "archive [number] - switch the note's archived status" << std::endl
		<< "archivemode - switch the program's archive mode" << std::endl
		<< "short - switch the program's short mode" << std::endl
		<< "save - saves the changes" << std::endl
		<< "exit - exits the program" << std::endl
		<< "about - shows the program's description" << std::endl;
}

void executeCommand() {
	std::string cmd;											//full line
	std::string keyword;										//only the first part, before the space
	int number = 0;
	std::cout << std::endl << "Enter the command:" << std::endl << "> ";
	std::getline(std::cin, cmd);
	for (int i = 0; cmd[i] != ' ' and i < cmd.length() ; i++) {	//extract keyword from cmd
		keyword += cmd[i];
	}
	
	//if command type requires a number
	if (keyword.length() != cmd.length() && (keyword == "update" || keyword == "changename" || keyword == "changedesc" || keyword == "remove" || keyword == "changedate" || keyword == "archive") ) {
		try {
			number = stoi(cmd.substr(keyword.length(), cmd.length()));	//extract the number from cmd
		}
		catch (...) {											//for example when number is a string
			std::cout << "Error: wrong number format" << std::endl;
			system("pause");
			return;
		}
		if (number > notes.size() || number == 0) {
			std::cout << "Error: there is no note of the number " << number << std::endl;
			std::cout << "the last number is " << notes.size() << std::endl;
			system("pause");
			return;
		}
		std::cout << "selected note: " << notes[number - 1].getName() << std::endl;

		if (keyword == "archive") {
			notes[number - 1].isArchived = !notes[number - 1].isArchived;
			return;
		}
		if (archiveModeCheck())
			return;
		if (keyword == "changedate")
			notes[number - 1].setDateManually();
		else if (keyword == "remove") {
			std::cout << "Are you sure to remove the note?" << std::endl;
			std::cout << "type 'y' to continue: " << std::endl << "> ";
			std::string confirm;
			std::getline(std::cin, confirm);
			if (confirm[0] == 'y') {
				notes.erase(notes.begin() + number - 1);
			}
			else {
				std::cout << "Operation aborted" << std::endl;
				system("pause");
			}
		}												
		else {													//for update, changename or changedesc
			std::string text;
			std::cout << "Type the text: " << std::endl << "> ";
			std::getline(std::cin, text);
			if (keyword == "update")
				notes[number - 1].addDescLine(text);
			else if (keyword == "changename")
				notes[number - 1].setName(text);
			else if (keyword == "changedesc")
				notes[number - 1].setDesc(text);
		}
		return;
	}
	else {														//for save, exit, archivemode, descriptions, about, create
		if (keyword == "save") {
			saveDatabase();
		}
		else if (keyword == "exit") {
			running = false;
		}
		else if (keyword == "archivemode") {
			archiveMode = !archiveMode;
		}
		else if (keyword == "short") {
			descriptions = !descriptions;
		}
		else if (keyword == "about") {
			showCredits();
		}
		else if (keyword == "create") {
			if (archiveModeCheck())
				return;
			std::string name;
			std::string desc;
			do {
				std::cout << "Type the note name: " << std::endl << "> ";
				std::getline(std::cin, name);
				if (name == "")
					std::cout << "Error: the name cannot be empty" << std::endl;
			} while (name == "");
			std::cout << "Type the note description: " << std::endl << "> ";
			std::getline(std::cin, desc);
			notes.push_back(Note(name, desc));
			std::cout << "Do you want to add the note's date?" << std::endl;
			std::cout << "type 'y' if so: " << std::endl << "> ";
			std::string confirm;
			std::getline(std::cin, confirm);
			if (confirm[0] == 'y') {
				notes[notes.size() - 1].hasDate = true;
				notes[notes.size() - 1].setDateManually();
			}
		}
		else {
			std::cout << "Error: unkown command or missing note number" << std::endl;
			system("pause");
		}
		return;
	}
}

void saveDatabase() {
	try {
		std::ofstream file;
		file.open("database.dtb");
		for (Note note : notes) {
			if (note.isArchived)
				file << "@";									//new archived note symbol
			else
				file << "#";									//new note symbol
			if (note.hasDate)
				file << note.getDayString() << "-" << note.getMonthString() << "-" << note.getYear();
			file << std::endl << note.getNameRaw() << std::endl << note.getDesc();
		}
		file.close();
	}
	catch (...) {
		std::cout << "Error: could not save the changes" << std::endl;
		system("pause");
		return;
	}
	std::cout << "Changes saved!" << std::endl;
	system("pause");
	return;
}

void showNotesOld() {											//unused
	for (int i = 0; i < notes.size(); i++) {
		std::cout << notes[i].getName() << " [" << i + 1 << "]" << std::endl;
		std::cout << notes[i].getFullDate() << std::endl;
		std::cout << notes[i].getDesc() << std::endl;
	}
}

bool archiveModeCheck() {
	if (archiveMode) {
		std::cout << "Error: this command is not avaible in archive mode" << std::endl;
		system("pause");
		return true;
	}
	return false;
}

void showCredits() {

	system("cls");
	std::cout << std::endl << std::endl << std::endl << std::endl;
	std::cout << "\t\t @-------------------------------------------------------------------------@" << std::endl;
	std::cout << "\t\t | . . . . \"NOTES\" - a program to create and manage simple notes . . . . . |" << std::endl
			  << "\t\t | . . . . author: czarek szymanski (roboto roboter) . . . . . . . . . . . |" << std::endl
			  << "\t\t | . . . . verson: 1.2 . . . . . . . . . . . . . . . . . . . . . . . . . . |" << std::endl
			  << "\t\t | . . . . language: c++ . . . . . . . . . . . . . . . . . . . . . . . . . |" << std::endl
			  << "\t\t | . . . . created: 09.08.2021 . . . . . . . . . . . . . . . . . . . . . . |" << std::endl
			  << "\t\t | . . . . latest update: 20.08.2021 . . . . . . . . . . . . . . . . . . . |" << std::endl
			  << "\t\t | . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . |" << std::endl
			  << "\t\t | . . . . I wish you a nice day:))))) . . . . . . . . . . . . . . . . . . |" << std::endl
			  << "\t\t @-------------------------------------------------------------------------@" << std::endl
			  << std::endl << "\t\t\t\t\t ";
	system("pause");

	/*
	system("cls");
	std::cout << "--------------------------------------------------------------------------" << std::endl;
	std::cout << "| \t \"NOTES\" - a program to create and manage simple notes \t\t |" << std::endl
		<< "| \t author: czarek szymanski (roboto roboter) \t\t\t |" << std::endl
		<< "| \t verson: 1.1 \t\t\t\t\t\t\t |" << std::endl
		<< "| \t language: c++ \t\t\t\t\t\t\t |" << std::endl
		<< "| \t created: 09.08.2021 \t\t\t\t\t\t |" << std::endl
		<< "| \t latest update: 19.08.2021 \t\t\t\t\t |" << std::endl
		<< "| \t \t\t\t\t\t\t\t\t |" << std::endl
		<< "| \t i wish you a nice day:))))) \t\t\t\t\t |" << std::endl;
	std::cout << "--------------------------------------------------------------------------" << std::endl << std::endl <<"\t\t";
	system("pause");
	*/
}