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
	void displayAssignments();
private:
	list<Homework> Assigned;
	list<Homework> Completed;
	list<Homework>::iterator it;
	string fileName;
	bool assignmentExists(Homework HW);
	//returns true if the assignment exists. 
};

void Assignments::addAssignment(Date dueDate, Date assignedDate, string Description, string Status)
{
	Homework tempAssignment(dueDate, assignedDate, Description, Status);
	if (!assignmentExists(tempAssignment)){ //quick addition to show the use of new private method
		if (tempAssignment.getStatus() == "assigned")
		{
			Assigned.push_back(tempAssignment);
		}
		else
		{
			Completed.push_back(tempAssignment);
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

void Assignments::displayAssignments(){
	cout << "--------Assigned---------" << endl;
	it = Assigned.begin();
	if (it == Assigned.end()){
		cout << "0 'Assigned' assignments" << endl << endl;
	}
	else{
		while (it != Assigned.end()){
			cout << "Description:   " << it->getDescription() << endl;
			cout << "Assigned Date: " << it->getAssignedDate().toString() << endl;
			cout << "Due Date:      " << it->getDueDate().toString() << endl;
			cout << "Status:        " << it->getStatus() << endl << endl;
			++it;
		}
	}

	it = Completed.end();
	cout << "--------Complete---------" << endl;
	if (it == Completed.end()){
		cout << "0 'Completed' assignments" << endl << endl;
	}
	else{
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