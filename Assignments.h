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
	void printHomework();
	void setFileName();
private:
	list<Homework> Assigned;
	list<Homework> Completed;
	string fileName;
};

void Assignments::addAssignment(Date dueDate, Date assignedDate, string Description, string Status)
{
	list<Homework>::iterator it;
	Homework tempAssignment(dueDate, assignedDate, Description, Status);
	if (tempAssignment.getStatus() == "assigned")
	{
		Assigned.push_back(tempAssignment);
	}
	else
	{
		Completed.push_back(tempAssignment);
	}
}

Homework Assignments::getHomework(string assignedDate){
	list<Homework>::iterator it;
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
	while (file.good()){
		getline(file, tempData);
		if (tempData == "") continue;
		//still needs to call a sort method for dates, file contains chronological dates only
		tempData.erase(std::remove(tempData.begin(), tempData.end(), ','), tempData.end()); //pops commas
		ss << tempData;
		ss >> assignedDate >> description >> dueDate >> status;		
		addAssignment(dueDate, assignedDate, description, status);
		ss.clear();		
	}
	file.close();
}

void Assignments::printHomework(){ //this is only for testing purposes
	list<Homework>::iterator itAssigned = Assigned.begin(), itCompleted = Completed.begin();
	while (itAssigned != Assigned.end()){
		cout << itAssigned->getDescription() << "-->";
		++itAssigned;
	}
	cout << endl << endl;
	while (itCompleted != Completed.end()){
		cout << itCompleted->getDescription() << "-->";
		++itCompleted;
	}
}

void Assignments::exportHomework(string& fileName){
	ofstream file(fileName);
	list<Homework>::iterator itAssigned = Assigned.begin(), itCompleted = Completed.begin();
	while (itAssigned != Assigned.end()){
		file << itAssigned->getAssignedDate().toString() + ", " + itAssigned->getDescription() + ", "
			 + itAssigned->getDueDate().toString() + ", " + itAssigned->getStatus() << endl;
		++itAssigned;
	}
	cout << endl << endl;
	while (itCompleted != Completed.end()){
		file << itCompleted->getAssignedDate().toString() + ", " + itCompleted->getDescription() + ", "
			+ itCompleted->getDueDate().toString() + ", " + itCompleted->getStatus() << endl;
		++itCompleted;
	}
	file.close();
}

void Assignments::setFileName(){
	fileName = GetFileName(5, 20, EXT);
}


//delete this comment