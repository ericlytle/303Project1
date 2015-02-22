#include "Assignments.h"
#include <iostream>
using namespace std;

class UI {
public:
	void displayMenu();
private:
	Assignments org;
	static string Menu;
};

string UI::Menu("Choose from one of the following:\n[A]: Add Assignment\n[B]: Edit Assignment\n[I]Import Assignments\n");
void UI::displayMenu(){
	char choice;
	string dueDate, assignedDate, Description, Status;
	
	cout << Menu << "-->";
	cin >> choice;
	switch (choice){
	case 'A':
		cout << "Due Date: ";
		cin >> dueDate;
		cout << endl << "Assigned Date: ";
		cin >> assignedDate;
		cout << endl << "Description: ";
		cin >> Description;
		cout << endl << "Status: ";
		cin >> Status;
		org.addAssignment(dueDate, assignedDate, Description, Status);
		break;
	case 'B': break;
	case 'I':
		fstream fin("input.txt"); //still need to get file from user, put in assignments header
		org.importHomework(fin);
		org.printHomework();
		break;

	}
	
}