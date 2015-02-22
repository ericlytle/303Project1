#pragma once

#include <string>
#pragma once
#include "Date.h"

bool dateRangeIsValid(Date assignedDate, Date dueDate)
{
	return assignedDate <= dueDate;
}

bool stringIsValidDate(string d)
{
	try
	{
		Date date;
		date.parseDate(d, DateFormat::Standard);
		return true;
	}
	catch (exception)
	{
		return false;
	}
}

bool stringIsValidAssignmentStatus(string status)
{
	return status == "assigned" || status == "late" || status == "completed";
}
