#pragma once
#include <string>
#include "Date.h"

bool dateRangeIsValid(Date assignedDate, Date dueDate)
{
	return assignedDate <= dueDate;
}

