#include "Note.h"

Note::Note(std::string n) {
	name = n;
	desc = "";
	hasDate = false;
	isArchived = false;
}

Note::Note(std::string n, std::string d) {
	name = n;
	if (d != "") {
		desc = d + '\n';
		descReadOnly = '\t' + desc;
	}
	hasDate = false;
	isArchived = false;
}

std::string Note::getName() {
	return "\""+ name + "\"";
}

std::string Note::getNameRaw() {
	return name;
}

std::string Note::getDesc() {
	return desc;
}

std::string Note::getDescReadOnly() {
	return descReadOnly;
}

void Note::setName(std::string n) {
	name = n;
}

void Note::setDesc(std::string d) {
	if (d != "") {
		desc = d + '\n';
		descReadOnly = '\t' + desc;
	}
	else {
		desc = d;
		descReadOnly = d;
	}
}

void Note::addDescLine(std::string l) {
	if (l != "") {
		desc += l + '\n';
		descReadOnly += '\t' + l + '\n';
	}
}

int Note::getDay() {
	return day;
}
int Note::getMonth() {
	return month;
}
int Note::getYear() {
	return year;
}
void Note::setDay(int d) {
	day = d;
}
void Note::setMonth(int m) {
	month = m;
}
void Note::setYear(int y) {
	year = y;
}

std::string Note::getFullDate() {	//debug
	if (!hasDate)
		return "no date";
	else
		return this->getDayString() + "." + this->getMonthString() + "." + std::to_string(year);
	
}

std::string Note::getDayString() {
	if (day < 10)
		return "0" + std::to_string(day);
	else return std::to_string(day);
}

std::string Note::getMonthString() {
	if (month < 10)
		return "0" + std::to_string(month);
	else return std::to_string(month);
}

void Note::setDateManually() {
	this->hasDate = true;
	std::string input;
	int num;

	try {
		do {
			std::cout << "the note's year (2020-2120): " << std::endl << "> ";
			std::getline(std::cin, input);
			num = stoi(input);
			if (num < 2020 or num > 2120)
				std::cout << "Error: invalid year" << std::endl;
		} while (num < 2020 or num > 2120);
		this->setYear(num);

		do {
			std::cout << "the note's month (1-12): " << std::endl << "> ";
			std::getline(std::cin, input);
			num = stoi(input);
			if (num < 1 or num>12)
				std::cout << "Error: invalid month" << std::endl;
		} while (num < 1 or num>12);
		this->setMonth(num);

		do {
			std::cout << "the note's day (1-31): " << std::endl << "> ";
			std::getline(std::cin, input);
			num = stoi(input);
			if (num < 1 or num>31)
				std::cout << "Error: invalid day" << std::endl;
		} while (num < 1 or num>31);
		this->setDay(num);
	}
	catch (...) {
		std::cout << "Error: wrong date format" << std::endl;
		this->hasDate = false;
		this->day = 1;
		this->month = 1;
		this->year = 2020;
		system("pause");
		return;
	}
}