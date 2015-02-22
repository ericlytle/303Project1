#pragma once

#include <string>
#include "Date.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <math.h>
#include <algorithm>

using namespace std;

const unsigned int MAX_STRING = 50; // max length of user input string
const string EXT = ".txt"; // valid file extention

bool IsInString(string s1, string s2);
string NumberToStringBuilder(double number);
string GetFileName(int minLength, int maxLength, string validExtension);
string GetUserString(int minLength, int maxLength, string validInput);
bool IsAlphaNumeric(string c);
bool dateRangeIsValid(Date assignedDate, Date dueDate);
bool stringIsValidDate(string d);
bool stringIsValidAssignmentStatus(string status);

bool dateRangeIsValid(Date assignedDate, Date dueDate)
{
	return assignedDate <= dueDate;
}

// test this
bool stringIsValidDate(string date)
{
	// check for 0000-00-00 string before entering try block
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
{
	// convert status to lowercase before return
	return status == "assigned" || status == "late" || status == "completed";
}

bool IsInString(string s1, string s2)
// Returns True of string s1 in in string s2.
// Otherwise, returns False.
{
	if (s2.find(s1) != string::npos) return true;
	else return false;
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
		cout << "Enter Your File Name - Text Files only\n->";
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
// Gets an alpha-numeric string from user within a length range.
// Checks user input against a validInput string that's passed into the function.
// If you don't want to check input against validInput string, pass an empty string "" into
// the function.
// Returns the valid string.
{
	string userString = "";
	while (true)
	{
		
		cin >> userString;
		if (validInput != "" && userString.find(validInput) == string::npos) cout << "Invalid input. " << endl;
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

string NumberToStringBuilder(double number)
// Takes double and returns a string representation.
// Example input: 5.0, output: "5.0"
{
	string numberAsString;
	ostringstream conversionStream;
	conversionStream << number;
	return numberAsString = conversionStream.str();
}