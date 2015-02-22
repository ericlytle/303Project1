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
	void addAssignment(string dueDate, string assignedDate, string Description, string Status);
	Homework getHomework(string date);
	void importHomework(ifstream& file);
	void exportHomework(ofstream& file);
	void printHomework();
	void editAssignment(string assignedDate);
private:
	list<Homework> Assigned;
	list<Homework> Completed;
};

void Assignments::addAssignment(string dueDate, string assignedDate, string Description, string Status)
{
	list<Homework>::iterator it;
	Homework tempAssignment(dueDate, assignedDate, Description, Status);
	Date due(dueDate,  DateFormat::US);
	if (tempAssignment.getStatus() == "assigned")
	{
		//Assigned.push_back(tempAssignment);
		if (Assigned.empty())
			Assigned.push_back(tempAssignment);
		else
		{
			it = Assigned.begin();
			while (it != Assigned.end())
			{
				Date tempDue(it->getDueDate(), DateFormat::US);
				if (tempDue >= due)
				{
					Assigned.insert(it, tempAssignment);
				}
				++it;
			}
		}
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

void Assignments::importHomework(ifstream& file){
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

void Assignments::exportHomework(ofstream& file){
	list<Homework>::iterator itAssigned = Assigned.begin(), itCompleted = Completed.begin();
	while (itAssigned != Assigned.end()){
		file << itAssigned->getAssignedDate() + ", " + itAssigned->getDescription() + ", "
			 + itAssigned->getDueDate() + ", " + itAssigned->getStatus() << endl;
		++itAssigned;
	}
	cout << endl << endl;
	while (itCompleted != Completed.end()){
		file << itCompleted->getAssignedDate() + ", " + itCompleted->getDescription() + ", "
			+ itCompleted->getDueDate() + ", " + itCompleted->getStatus() << endl;
		++itCompleted;
	}
}