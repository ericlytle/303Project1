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
		Date date(d);
		return true;
	}
	catch (exception)
	{
		return false;
	}
}

