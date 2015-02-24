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
	Homework getHomework(string date);
	void importHomework(string& fileName);
	void exportHomework(string& fileName);
	void setFileName();
	void displayAssignments();
	void inputUserFile();
	void outputUserFile();
private:
	list<Homework> Assigned;
	list<Homework> Completed;
	list<Homework>::iterator it;
	string fileName;
	bool assignmentExists(Homework HW);
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

Homework Assignments::getHomework(string assignedDate){
	for (it = Assigned.begin(); it != Assigned.end(); ++it){
		if (it->getAssignedDate() == assignedDate){
			return *it;
		}
		else
			throw::exception("ASSIGNMENT NOT FOUND");
	}
}

void Assignments::importHomework(string& fileName){
	ifstream file(fileName);
	string tempData, dueDate, assignedDate, description, status;
	stringstream ss;
	Date tempDate;
	while (file.good()){
		getline(file, tempData);
		if (tempData == "") continue;
		//still needs to call a sort method for dates, file contains chronological dates only
		tempData.erase(std::remove(tempData.begin(), tempData.end(), ','), tempData.end()); //pops commas
		ss << tempData;
		ss >> assignedDate >> description >> dueDate >> status;		
		addAssignment(tempDate.parseDate(dueDate,US), tempDate.parseDate(assignedDate,US), description, status);
		ss.clear();		
	}
	file.close();
}

void Assignments::exportHomework(string& fileName){
	//iterates through both lists and writes them to textfile, overwrites input textfile
	ofstream file("output.txt"); //"output.txt for testing purpose eventually change to fileName
	static string comSpace = ", ";
	list<Homework>::iterator itAssigned = Assigned.begin(), itCompleted = Completed.begin();
	while (itAssigned != Assigned.end()){
		file << itAssigned->getAssignedDate().toString() + comSpace + itAssigned->getDescription() + comSpace
			+ itAssigned->getDueDate().toString() + comSpace + itAssigned->getStatus() << endl;
		++itAssigned;
	}
	while (itCompleted != Completed.end()){
		file << itCompleted->getAssignedDate().toString() + comSpace + itCompleted->getDescription() + comSpace
			+ itCompleted->getDueDate().toString() + comSpace + itCompleted->getStatus() << endl;
		++itCompleted;
	}
	file.close();
}

void Assignments::setFileName(){
	fileName = GetFileName(5, 20, EXT);
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
			cout << "Description:   " << it->getDescription() << endl;
			cout << "Assigned Date: " << it->getAssignedDate().toString() << endl;
			cout << "Due Date:      " << it->getDueDate().toString() << endl;
			cout << "Status:        " << it->getStatus() << endl << endl;
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

bool Assignments::assignmentExists(Homework HW){
	//returns true if the assignment already exists and false otherwise. 
	it = Assigned.begin();
	while (it != Assigned.end()){
		if (*it == HW)
			return true;
		++it;
	}
	return false;
}


//delete this now