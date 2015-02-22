#include "Assignments.h"
#include "Helpers.h"
#include <iostream>
#include <istream>
using namespace std;

class UI {
public:
	void displayMenu();
	void getUserFileName();
private:
	Assignments org;
	static string Menu;
};

string UI::Menu("Choose from one of the following:\n\
[A]: Add Assignment\n\
[B]: Edit Assignment\n\
[C]: Complete Assignment\n\
[D]: Display Assignments\n\
[E]: Display Number of Late Assignments\n\
[I]: Import Assignments\n\
[S]: Save\n");

void UI::displayMenu(){
	string choice;
	string dueDate, assignedDate, Description, Status;
	
	cout << Menu << "-->";
	cin >> choice;
	while (!IsInString(choice, "ABCDEISabcdeis") || choice.length() > 1){
		cout << "Invalid menu choice. Try again." << endl << "-->";
		cin >> choice;
	}
	choice = toupper(choice[0]);
	switch (choice[0]){
	case 'A': //Add Assignment
		cout << "Due Date:(YYYY/MM/DD) ";
		cin >> dueDate;
		/*while (!stringIsValidDate(dueDate)){
			cout << "Invalid Date. Retry. Makes sure date is in (YYYY/MM/DD) format " << endl << "-->";
		cin >> dueDate;
		}
		cout << endl << "Assigned Date:(YYYY/MM/DD) ";
		cin >> assignedDate;
		while (!stringIsValidDate(assignedDate)){
			cout << "Invalid Date. Retry. Makes sure date is in (YYYY/MM/DD) format" << endl << "-->";
			cin >> dueDate;
		}*/
		cout << endl << "Description: ";
		getline(cin, Description);
		cout << endl << "Status: ";
		cin >> Status;
		org.addAssignment(dueDate, assignedDate, Description, Status);
		break;
	case 'B': break; //edit assignment
	case 'C': break;//complete assignment
	case 'D': break; //Display Assignment(s)
	case 'E': break; //Display number of late assignments
	case 'I': org.setFileName(); break; //currently imports, and exports for ease of testing break;
	case 'S': break; //save I.E. export

	}
	
}