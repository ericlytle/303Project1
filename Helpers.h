#include <string>
#include "Date.h"

bool dateRangeIsValid(Date assignedDate, Date dueDate)
{
	return assignedDate <= dueDate;
}

bool dateIsValid(string d)
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

