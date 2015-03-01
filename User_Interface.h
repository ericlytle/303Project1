#include "Assignments.h"
#include "Helpers.h"
#include <iostream>
#include <istream>
using namespace std;

class UI 
{
public:
	void displayMenu();
private:
	Assignments org;
	static string menuChoices;
	static string Menu;
	Date dDate, aDate;
};

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
	while (run)
	{
		// Initialize local strings
		string Description, Status;

		// Diplay Menu, get user choice
		cout << Menu << ARROW;
		char choice = GetUserMenuChoice(MAIN_MENU_CHOICES);

		switch (choice)
		{
		case 'A': //Add Assignment

			// due date
			cout << "Due Date:" << DATE_FORMAT << " ";
			dDate = GetUserDate();
			
			// assigned date
			cout << endl << "Assigned Date:" << DATE_FORMAT << " ";
			while (true)
			{
				aDate = GetUserDate();
				if (dateRangeIsValid(aDate, dDate))
				{
					break;
				}
				cout << INVALID_DATE_RANGE_TEXT << endl << ARROW;
			}
			
			// description
			cout << endl << "Description: ";
			Description = GetUserLine();
			
			// status
			cout << endl << "Status: ";
			Status = GetUserStatus();

			// create assignment and break
			org.addAssignment(dDate, aDate, Description, Status);
			break;

		case 'B': // Edit Assignment

			// assigned date
			cout << endl << "Assigned Date:(YYYY/MM/DD) ";
			while (true)
			{
				aDate = GetUserDate();
				unsigned int attempts = 0;
				if (org.assignmentExists(aDate) || attempts > 3)
				{
					break;
				}
				assignmentDoesNotExistMessage(aDate);
				++attempts;
			}

			// perform edit and break
			org.editAssignment(aDate);
			break;

		case 'C': // Complete Assignment
			break;

		case 'D': // Display Assignment(s)
			org.displayAssignments();
			break;

		case 'E': // Display Number of Late Assignments
			break;

		case 'I': //currently imports, and exports for ease of testing break;
			org.setFileName();
			org.inputUserFile();
			break; 

		case 'S': // Save I.E. Export
			org.outputUserFile();
			cout << "SAVE COMPLETE\n" << endl;
			break;

		case 'Q': // Quit Program
			run = false;
			break;

		default: // Default
			break;
		}
		cout << endl << endl;
	}
}