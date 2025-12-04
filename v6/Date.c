#include "Date.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

DateCompare(Date d1, Date d2)
{
	int result = d1.YY - d2.YY;

	if (result == 0)
	{
		result = d1.MM - d2.MM;

		if (result == 0)
		{
			result = d1.DD - d2.DD;
		}
	}

	return result;
}