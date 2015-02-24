#pragma once

#include <stdio.h>
#include <string>
#include "Date.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <math.h>
#include <algorithm>
#include <ctype.h>

using namespace std;

#pragma region Constants
const unsigned int MAX_STRING = 50; // max length of user input string
const string EXT = ".txt"; // valid file extension
#pragma endregion

#pragma region Prototypes
bool IsInString(string s1, string s2);
string NumberToStringBuilder(double number);
string GetFileName(int minLength, int maxLength, string validExtension);
string GetUserString(int minLength, int maxLength, string validInput);
bool IsAlphaNumeric(string c);
bool dateRangeIsValid(Date assignedDate, Date dueDate);
bool stringIsValidDate(string d);
bool stringIsValidAssignmentStatus(string status);
bool IsNumeric(char c);
string makeLowercase(string s);
Date dueDateCheck(string stringDueDate, Date aDate);
Date assignedDateCheck(string stringAssignedDate, Date dDate);
void statusCheck(string& status);
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
	string s = makeLowercase(status);
	return s == "assigned" || s == "late" || s == "completed";
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
// dashes, underscores, and valid file extensions.
{
	while (true)
	{
		unsigned int index = 0;
		string fileName = "";
		string fileExtension = "";
		cout << "Please Enter Your Filename with .txt Extension -->";
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

string GetUserString(int minLength, int maxLength, string validInput)
// Gets an alpha-numeric string from user within a length range. <-- commented out AlphaNumeric check below
// Checks user input against a validInput string that's passed into the function.
// If you don't want to check input against validInput string, pass an empty string "" into
// the function.
// Returns the valid string.
{
	string userString = "";
	while (true)
	{
		cin >> userString;
		//if (!IsAlphaNumeric(userString)) cout << "Invalid input: Must be alpha-numeric, period, dash, or underscore. " << endl;
		/*else*/ if (validInput != "" && userString.find(validInput) == string::npos) cout << "Invalid input. " << endl;
		else if (static_cast<int>(userString.length()) < minLength) cout << "Too short. " << endl;
		else if (static_cast<int>(userString.length()) > maxLength) cout << "Too long. " << endl;
		else return userString;
	}
}

bool IsAlphaNumeric(string c)
// Returns True if all characters in a string are
// alpha-numeric, period, dash, or underscore.
// Otherwise, returns False.
{
	for (unsigned int i = 0; i < c.length(); i++)
	{
		if (!(c[i] == 45
			|| c[i] == 46
			|| (c[i] >= 48 && c[i] <= 57)
			|| (c[i] >= 65 && c[i] <= 90)
			|| c[i] == 95
			|| (c[i] >= 97 && c[i] <= 122))) return false;
	}
	return true;
}

bool IsNumeric(char c)
// True if char c is numeric, otherwise false
{
	return c >= 48 && c <= 57;
}

string NumberToStringBuilder(double number)
// Takes double and returns a string representation.
// Example input: 5.0, output: "5.0"
{
	string numberAsString;
	ostringstream conversionStream;
	conversionStream << number;
	return numberAsString = conversionStream.str();
}

string makeLowercase(string s)
// Takes a string, converts to lowercase (if possible),
// returns lowercase string
{
	char c;
	char* str = new char[s.length()];
	string lower = "";
	// convert string s into str[]
	for (unsigned int i = 0; i < s.length(); i++)
	{
		str[i] = s[i];
	}
	unsigned int i = 0;
	for (unsigned int j = 0; j < s.length(); j++)
	{
		c = str[j];
		lower += tolower(c);
	}
	delete[] str;
	return lower;
}
Date dueDateCheck(string stringDueDate, Date aDate){
	Date parser;
	parser = parser.parseDate(stringDueDate, Standard);
	while (!stringIsValidDate(stringDueDate) || !dateRangeIsValid(aDate,parser)){
		cout << "Invalid Date. Retry. Makes sure date is in (YYYY/MM/DD) format" << endl << "-->";
		cin >> stringDueDate;
		parser.parseDate(stringDueDate, Standard);
	}
	return parser;
}

Date assignedDateCheck(string stringAssignedDate, Date dDate){
	Date parser;
	parser = parser.parseDate(stringAssignedDate, Standard);
	while (!stringIsValidDate(stringAssignedDate) || !dateRangeIsValid(parser, dDate)){
		cout << "Invalid Date. Retry." << endl << "-->";
		cin >> stringAssignedDate;
		parser = parser.parseDate(stringAssignedDate, Standard);
	}
	return parser;
}

void statusCheck(string& status){
	while (!stringIsValidAssignmentStatus(status)){
		cout << "Invalid Status. Retry." << endl << "-->";
		cin >> status;
	}
}
#pragma endregion