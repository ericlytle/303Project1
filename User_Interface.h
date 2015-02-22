#include "Assignments.h"
#include "Helpers.h"
#include <iostream>
using namespace std;

class UI {
public:
	void displayMenu();
	void getUserFileName();
private:
	Assignments org;
	static string Menu;
	string fileName;
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
		fileName = GetFileName(5, 20, EXT);
		ifstream fin(fileName); 
		ofstream fout("output.txt");
		org.importHomework(fin);
		org.printHomework();
		org.exportHomework(fout);
		fin.close();
		fout.close();
		break;
	}	
}