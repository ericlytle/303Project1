#include <string>
#include <list>
#include "StringTokenizer.h"
#include "Date.h"
#include "Helpers.h"
#include "Homework.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;
class Assignments {
public:
	void addAssignment(Date dueDate, Date assignedDate, string Description, string Status);
	Homework getHomework(Date assignedDate);
	void importHomework(string& fileName);
	void exportHomework(string& fileName);
	void setFileName();
	void displayAssignments();
	void inputUserFile();
	void outputUserFile();
	void editAssignment(Date date);
	bool assignmentExists(Homework HW);
	bool assignmentExists(Date date);
private:
	list<Homework> Assigned;
	list<Homework> Completed;
	list<Homework>::iterator it;
	string fileName;
	Homework tempHomework;
	//returns true if the assignment exists. 
};

void Assignments::addAssignment(Date dueDate, Date assignedDate, string Description, string Status){
	Homework tempHmwrk(dueDate, assignedDate, Description, Status);
	if (tempHmwrk.getStatus() == "assigned")
	{
		if (Assigned.empty())
			Assigned.push_back(tempHmwrk);
		else
		{
			if (tempHmwrk.getDueDate() <= Assigned.front().getDueDate())
				Assigned.push_front(tempHmwrk);
			else if (tempHmwrk.getDueDate() >= Assigned.back().getDueDate())
				Assigned.push_back(tempHmwrk);
			else
			{
				it = Assigned.begin();
				while (tempHmwrk.getDueDate() > it->getDueDate())
					++it;
				Assigned.insert(it, tempHmwrk);
			}
		}
	}
	else
	{
		if (Completed.empty())
			Completed.push_back(tempHmwrk);
		else
		{
			if (tempHmwrk.getDueDate() <= Completed.front().getDueDate())
				Completed.push_front(tempHmwrk);
			else if (tempHmwrk.getDueDate() >= Completed.back().getDueDate())
				Completed.push_back(tempHmwrk);
			else{
				it = Completed.begin();
				while (tempHmwrk.getDueDate() > it->getDueDate())
					++it;
				Completed.insert(it, tempHmwrk);
			}
		}
	}
}

Homework Assignments::getHomework(Date assignedDate){
	for (it = Assigned.begin(); it != Assigned.end(); ++it){
		if (it->getAssignedDate() == assignedDate){
			return *it;
		}
	}
	throw::exception("ASSIGNMENT NOT FOUND");
}

void Assignments::importHomework(string& fileName){
	ifstream file(fileName);
	string tempData, dueDate, assignedDate, description, status;
	while (file.good()){
		getline(file, tempData);
		if (tempData == "") continue;
		
		int count = 0;
		stringstream ss(tempData);
		
		while (getline(ss, tempData, ',')) //split string by comma
		{
			size_t first = tempData.find_first_not_of(' '); //remove spaces front and back
			size_t last = tempData.find_last_not_of(' ');
			tempData = tempData.substr(first, last + 1);

			switch (count)
			{
			case 0: assignedDate = tempData; ++count; break;
			case 1: description = tempData; ++count; break;
			case 2: dueDate = tempData; ++count; break;
			case 3: status = tempData; ++count; break;
			}
		}

		Date tempDueDate(dueDate,US), tempAssnDate(assignedDate,US); //convert 
		Date tempDueDateStd(tempDueDate.getYear(), tempDueDate.getMonth(), tempDueDate.getDay(), Standard);
		Date tempAssnDateStd(tempAssnDate.getYear(), tempAssnDate.getMonth(), tempAssnDate.getDay(), Standard);
		
		addAssignment(tempDueDateStd, tempAssnDateStd, description, status);
		ss.clear();		
	}
	file.close();
}

void Assignments::exportHomework(string& fileName){
	//iterates through both lists and writes them to textfile, overwrites input textfile
	ofstream file("output.txt"); //"output.txt for testing purpose eventually change to fileName
	static string comSpace = ", ";
	it = Assigned.begin();
	while (it != Assigned.end()){
		
		Date tempDueDate((it->getDueDate()).getYear(), (it->getDueDate()).getMonth(), (it->getDueDate()).getDay(), US);
		it->setDueDate(tempDueDate);
		Date tempAssnDate((it->getAssignedDate()).getYear(), (it->getAssignedDate()).getMonth(), (it->getAssignedDate()).getDay(), US);
		it->setAssignedDate(tempAssnDate);
		
		file << it->getAssignedDate().toString() + comSpace + it->getDescription() + comSpace
			+ it->getDueDate().toString() + comSpace + it->getStatus() << endl;
		++it;
	}
	it = Completed.begin();
	while (it != Completed.end()){
		
		Date tempDueDate((it->getDueDate()).getYear(), (it->getDueDate()).getMonth(), (it->getDueDate()).getDay(), US);
		it->setDueDate(tempDueDate);
		Date tempAssnDate((it->getAssignedDate()).getYear(), (it->getAssignedDate()).getMonth(), (it->getAssignedDate()).getDay(), US);
		it->setAssignedDate(tempAssnDate);

		file << it->getAssignedDate().toString() + comSpace + it->getDescription() + comSpace
			+ it->getDueDate().toString() + comSpace + it->getStatus() << endl;
		++it;
	}
	file.close();
}

void Assignments::setFileName(){
	fileName = GetFileName(5, MAX_STRING, EXT);
}

void Assignments::inputUserFile(){
	importHomework(fileName);
}

void Assignments::outputUserFile(){
	exportHomework(fileName);
}

void Assignments::displayAssignments(){
	cout << "--------Assigned---------" << endl;
	it = Assigned.begin();
	if (it == Assigned.end()){
		cout << "0 'Assigned' assignments" << endl << endl;
	}
	else{
		cout << "--------" << Assigned.size() << "-Total----------" << endl;
		while (it != Assigned.end()){
			cout << "Description:    " << it->getDescription() << endl;
			cout << "Assigned Date:  " << it->getAssignedDate().toString() << endl;
			cout << "Due Date:       " << it->getDueDate().toString() << endl;
			cout << "Completed Date: " << it->getCompletedDate().toString() << endl;
			cout << "Status:         " << it->getStatus() << endl << endl;
			++it;
		}
	}

	it = Completed.begin();
	cout << "--------Complete---------" << endl;
	if (it == Completed.end()){
		cout << "0 'Completed' assignments" << endl << endl;
	}
	else{
		cout << "--------" << Completed.size() << "-Total----------" << endl;
		while(it != Completed.end()){
			cout << "Description:   " << it->getDescription() << endl;
			cout << "Assigned Date: " << it->getAssignedDate().toString() << endl;
			cout << "Due Date:      " << it->getDueDate().toString() << endl;
			cout << "Status:        " << it->getStatus() << endl << endl;
			++it;
		}
	}
}

bool Assignments::assignmentExists(Homework HW)
{
	//returns true if the assignment already exists and false otherwise. 
	it = Assigned.begin();
	while (it != Assigned.end()){
		if (*it == HW)
			return true;
		++it;
	}
	return false;
}

bool Assignments::assignmentExists(Date date)
{
	//returns true if the assignment already exists and false otherwise. 
	it = Assigned.begin();
	while (it != Assigned.end()){
		if (it->getAssignedDate() == date)
			return true;
		++it;
	}
	return false;
}

void Assignments::editAssignment(Date date)
// Edit the due date or description of an existing
// homework assignment. Tries to identify the homework
// assignment by assigned date (Date passed into method)
{
	// Try to get homework based on date passed in
	getHomework(date);

	// Initialize locals
	string newDescription;
	Date newDueDate;

	// Diplay menu, get user choice
	displayEditAssignmentMenu();
	char choice = GetUserMenuChoice("ABQabq");

	switch (choice)
	{
	case 'A': // New Due Date

		// get the new due date from user
		cout << "New Due Date:" << endl << ARROW;
		newDueDate = GetUserDate();
		while (true)
		{
			newDueDate = GetUserDate();
			if (dateRangeIsValid(it->getAssignedDate(), newDueDate))
			{
				break;
			}
			cout << INVALID_DATE_RANGE_TEXT << endl << ARROW;
		}
		// set new due date and break
		it->setDueDate(newDueDate);
		break;

	case 'B': // New Description

		// get the new description from user
		cout << "New Description:" << endl << ARROW;
		newDescription = GetUserLine();

		// set new description and break
		it->setDescription(newDescription);
		break;

	case 'Q': // Quit the Edit Assignments Menu
		break;
	}
}
