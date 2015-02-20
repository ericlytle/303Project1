#include <string>
#include <list>
#include "StringTokenizer.h"
#include "Date.h"
#include "Homework.h"
#include <iostream>
using namespace std;
class Assignments {
public:
	void addAssignment(string dueDate, string assignedDate, string Description, string Status);
	Homework getHomework(string date);
private:
	list<Homework> Assigned;
	list<Homework> Completed;
};

void Assignments::addAssignment(string dueDate, string assignedDate, string Description, string Status){
	Homework tempAssignment(dueDate, assignedDate, Description, Status);
	Assigned.push_back(tempAssignment);
}

Homework Assignments::getHomework(string assignedDate){
	list<Homework>::iterator it;
	for (it = Assigned.begin(); it != Assigned.end(); ++it){
		if (it->getAssignedDate() == assignedDate){
			return *it;
		}
		else
			throw::exception("NO SOUP FOR YOU");
	}
}