#pragma once

#include <stdio.h>
#include <string>
#include "Date.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <math.h>
#include <algorithm>
#include <ctype.h>

using namespace std;

#pragma region Prototypes

Date GetUserDate();
bool IsInString(string s1, string s2);
string GetFileName(int minLength, int maxLength, string validExtension);
string GetUserString(int minLength, int maxLength, string validInput);
bool dateRangeIsValid(Date assignedDate, Date dueDate);
bool stringIsValidDate(string d);
bool stringIsValidAssignmentStatus(string status);
bool IsNumeric(char c);
void invalidDateMessage();
void displayEditAssignmentMenu();
char GetUserMenuChoice(string validInput);
void assignmentDoesNotExistMessage(Date date);

#pragma endregion

#pragma region Definitions

bool dateRangeIsValid(Date assignedDate, Date dueDate)
// returns True is the assignedDate is less than or
// equal to the dueDate, otherwise returns False
{
	return assignedDate <= dueDate;
}

bool stringIsValidDate(string date)
// returns True if string "date" represents a valid format
// for dates passed into the Date.h object, otherwise false
{
	// check length
	if (date.length() != 10)
	{
		return false;
	}
	// check for 0000-00-00 string before entering try block
	for (unsigned int i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
		{
			// if is digit, invalid
			if (IsNumeric(date[i]))
			{
				return false;
			}
		}
		else
		{
			// if not digit, invalid
			if (!IsNumeric(date[i]))
			{
				return false;
			}
		}

	}
	try
	{
		Date date(date);
		return true;
	}
	catch (exception)
	{
		return false;
	}
}

bool stringIsValidAssignmentStatus(string status)
// returns True if string status matches one of the three
// valid assignment status types, otherwise returns false
{
	return (IsInString(status, ASSIGNED) && status.length() == 8)
		|| (IsInString(status, LATE) && status.length() == 4)
		|| (IsInString(status, COMPLETED) && status.length() == 9);
}

bool IsInString(string s1, string s2)
// Returns True of string s1 is in string s2.
// Otherwise, returns False.
{
	return s2.find(s1) != string::npos;
}

string GetFileName(int minLength, int maxLength, string validExtension)
// Gets a filename from user.
// Checks for length within bounds, alpha-numeric characters,
// dashes, underscores, and valid file extension.
{
	while (true)
	{
		unsigned int index = 0;
		string fileName = "";
		string fileExtension = "";
		cout << "Please Enter Your Filename with " << EXT << " Extension " << ARROW;
		fileName = GetUserString(minLength, maxLength, "");
		while (fileName[index] != '.' && index < fileName.length())
		{
			index++;
		}
		while (index < fileName.length())
		{
			fileExtension += fileName[index];
			index++;
		}
		if (fileExtension != validExtension) cout << "Invalid file. " << endl;
		else if (fileExtension == validExtension)
		{
			ifstream fin;
			fin.open(fileName);
			if (fin.good())
			{
				fin.close();
				return fileName;
			}
			else
			{
				cout << "Could not open file. Please try again. " << endl;
				fin.close();
			}
		}
	}
}

char GetUserMenuChoice(string validInput)
// gets a single CHAR from user for menu options
{
	string userString = GetUserString(1, 1, validInput);
	userString = toupper(userString[0]);
	return userString[0];
}

string GetUserStatus()
// Gets a status from user
{
	while (true)
	{
		string userString = GetUserString(4, MAX_STRING, "");
		if (stringIsValidAssignmentStatus(userString))
		{
			return userString;
		}
		cout << "Invalid Status. Retry.\nValid statuses include:\n1. assigned\n2. late\n3. completed\n-->";
	}
}

string GetUserLine()
// Gets a line from the user
{
	string desc;
	cin.ignore();
	getline(cin, desc);
	return desc;
}

Date GetUserDate()
// Gets valid Date from user
{
	while (true)
	{
		string userString = GetUserString(4, 10, "");
		if (stringIsValidDate(userString))
		{
			Date userDate(userString);
			return userDate;
		}
		invalidDateMessage();
	}
}

string GetUserString(int minLength, int maxLength, string validInput)
// Checks user input against a validInput string that's passed into the function.
// If you don't want to check input against validInput string, pass an empty string "" into
// the function.
// Returns the valid string.
{
	string userString = "";
	while (true)
	{
		cin >> userString;
		if (validInput != "" && !IsInString(userString, validInput)) cout << "Invalid input. " << endl;
		else if (static_cast<int>(userString.length()) < minLength) cout << "Too short. " << endl;
		else if (static_cast<int>(userString.length()) > maxLength) cout << "Too long. " << endl;
		else return userString;
	}
}

bool IsNumeric(char c)
// True if char c is numeric, otherwise false
{
	return c >= 48 && c <= 57;
}

void invalidDateMessage()
// Message to user if date format is invalid
{
	cout << INVALID_DATE_TEXT << endl << ARROW;
}

void invalidDateRangeMessage()
// Message to user if invalid date range
{
	cout << INVALID_DATE_RANGE_TEXT << endl << ARROW;
}

void displayEditAssignmentMenu()
{
	cout << "Choose from the following:\n"
		<< "[A]: Edit Due Date\n"
		<< "[B]: Edit Description\n"
		<< "[Q]: Quit\n"
		<< ARROW;
}

void assignmentDoesNotExistMessage(Date date)
{
	cout << "ERROR. NO ASSIGNMENT WITH " << date.toString() << " DATE" << endl << "Try again" << ARROW;
}

#pragma endregion
