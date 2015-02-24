#include "Assignments.h"
#include "Helpers.h"
#include <iostream>
#include <istream>
using namespace std;

class UI 
{
public:
	void displayMenu();
	void getUserFileName();
private:
	Assignments org;
	static string menuChoices;
	static string Menu;
	Date dDate, aDate;
};

string UI::menuChoices("ABCDEISQabcdeisq");
string UI::Menu("Choose from one of the following:\n\
[A]: Add Assignment\n\
[B]: Edit Assignment\n\
[C]: Complete Assignment\n\
[D]: Display Assignments\n\
[E]: Display Number of Late Assignments\n\
[I]: Import Assignments\n\
[S]: Save\n\
[Q]: Quit\n");

void UI::displayMenu()
{
	bool run = true;
	string choice;
	string dueDate, assignedDate, Description, Status;
	while (run)
	{
		cout << Menu << "-->";
		cin >> choice;
		while (!IsInString(choice, menuChoices) || choice.length() > 1)
		{
			cout << "Invalid menu choice. Try again." << endl << "-->";
			cin >> choice;
		}
		choice = toupper(choice[0]);
		switch (choice[0])
		{
		case 'A': //Add Assignment // THIS NEEDS TO BE A METHOD IN ASSIGNMENT
			cout << "Due Date:(YYYY/MM/DD) ";
			cin >> dueDate;
			dDate = dueDateCheck(dueDate, aDate);
			cout << endl << "Assigned Date:(YYYY/MM/DD) ";
			cin >> assignedDate;
			aDate = assignedDateCheck(assignedDate, dDate);
			cout << endl << "Description: ";
			cin.ignore();
			getline(cin, Description);
			cout << endl << "Status: ";
			cin >> Status;
			statusCheck(Status);
			org.addAssignment(dDate, aDate, Description, Status);
			break;
		case 'B':
			cout << "Enter Assigned Date: ";
			cin >> assignedDate;
			if (makeLowercase(assignedDate) == "exit")
				break;
			if (stringIsValidDate(assignedDate)){
				aDate = aDate.parseDate(assignedDate, Standard);
				org.editAssignment(aDate);
			}
			break; //edit assignment
		case 'C': break;//complete assignment
		case 'D': org.displayAssignments(); break; //Display Assignment(s)
		case 'E': break; //Display number of late assignments
		case 'I': org.setFileName(); org.inputUserFile(); break; //currently imports, and exports for ease of testing break;
		case 'S': org.outputUserFile(); cout << "SAVE COMPLETE\n" << endl; break; //save I.E. export
		case 'Q': run = false;
		default: break;
		}
		cout << endl << endl;
	}
}