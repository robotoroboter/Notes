#pragma once
#include <iostream>
#include <string>
class Note
{
public:
	Note(std::string n);
	Note(std::string n, std::string d);
	std::string getName();
	std::string getNameRaw();		//name without quote tags
	std::string getDesc();			//raw description: for exporting to file
	std::string getDescReadOnly();	//desc with paragraphs: for aesthetics
	void setName(std::string n);
	void setDesc(std::string d);
	void addDescLine(std::string l);
	int getDay();
	int getMonth();
	int getYear();
	void setDay(int d);
	void setMonth(int m);
	void setYear(int y);
	bool hasDate;
	std::string getFullDate();		//only for debugging
	std::string getDayString();		//with '0' at the beginning
	std::string getMonthString();	//with '0' at the beginning
	void setDateManually();			//interactive
	bool isArchived;
private:
	std::string name;
	std::string desc;
	std::string descReadOnly;
	int day;
	int month;
	int year;
};

