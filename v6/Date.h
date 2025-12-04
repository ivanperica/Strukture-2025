#pragma once

#define YEAR_LENGTH (4)
#define MONTH_LENGTH (2)
#define DAY_LENGTH (2)
#define DASH_LENGTH (1)
#define NULL_LENGTH (1)
#define MAX_DATE_LENGTH (YEAR_LENGTH + DASH_LENGTH + MONTH_LENGTH + DASH_LENGTH + DAY_LENGTH + NULL_LENGTH)

typedef struct _date* DatePosition;
typedef struct _date {
	int YY;
	int MM;
	int DD;
	char datestring[MAX_DATE_LENGTH];
}Date;

DateCompare(Date d1, Date d2);