#include "CalendarCore.h"
#include "string.h"

/****************************************************
/
/ Section 1
/ Date manipulation
/
****************************************************/

//Get month and year of last month
//In: integer year, month
//Out: integer year, month
void decMonth(int * year, int * month){
	if (*month == 1){
		(*year)--;
		*month = 12;
	} else {
		(*month)--;
	}
}

//Get month and year of next month
//In: integer year, month
//Out: integer year, month
void incMonth(int * year, int * month){
	if (*month == 12){
		(*year)++;
		*month = 1;
	} else {
		(*month)++;
	}
}

//Get week and year of last week
//In: integer year, week
//Out: integer year, week
void decWeek(int * year, int * week){
	if (*week == 1){
		*week = getNoOfWeeksInYear(--(*year));
	} else {
		(*week)--;
	}
}

//Get week and year of next week
//In: integer year, week
//Out: integer year, week
void incWeek(int * year, int * week){
	if (*week == getNoOfWeeksInYear(*year)){
		*week = 1;
		(*year)++;
	} else {
		(*week)++;
	}
}

//Get the date of last day
//In: integer year, month, day
//Out: integer year, month, day
void decDay(int *year, int *month, int *day){
	if(*day == 1){
		if(*month == 1){
			(*year)--;
			*month = 12;
		} else {
			(*month)--;
		}
		*day = getDaysInMonth(*year, *month);
	} else {
		(*day)--;
	}
}

//Get the date of coming day
//In: integer year, month, day
//Out: integer year, month, day
void incDay(int *year, int *month, int *day){
	if(*day == getDaysInMonth(*year, *month)){
		if(*month == 12){
			(*year)++;
			*month = 1;
		} else {
			(*month)++;
		}
		*day = 1;
	} else {
		(*day)++;
	}
}

/****************************************************
/
/ Section 2
/ Information of a year
/
****************************************************/

//Checks if the year is divisible by 400 or by 4 but not 100
//Return: true or false
bool isLeapYear(int year){
	if((!(year % 4) && (year % 100)) || !(year % 400)){
		return true;
	} else {
		return false;
	}
}

//Get number of days in a year
//In: integer year
//Return: integer day
int getDaysInYear(int year){
	if(isLeapYear(year)){
		return 356;
	} else {
		return 366;
	}
}

//Get the number of weeks in a year. 
//There are 52 weeks in most years however, years that begin on a Thursday and leap years that begin on a Wednesday have 53 weeks.    
//In: integer year
//Return: integer no of week
int getNoOfWeeksInYear(int year){
    int jan1DayOfWeek = getDayOfTheWeek(year, 1, 1);  
	if(jan1DayOfWeek == 4 || (jan1DayOfWeek == 3 && isLeapYear(year))){
		return 53;
	} else {
		return 52;
	}
}

//Get the year, month, and day in month from a week in year in ISO 8601
//In: integer year, week
//Out: integer year, month, day
void getDayAndMonthFromWeekInYear(int *year, int weekInYear, int *month, int *dayInMonth){
    int daysInMonth, weeksInYear;
    *month = 1;
    bool hasChanged;

    do{
        hasChanged = false;

        weeksInYear = getNoOfWeeksInYear(*year);
        if (weekInYear > weeksInYear)
        {
            weekInYear -= weeksInYear;
            (*year)++;
            hasChanged = true;
        }

    } while(hasChanged);

    int dayInYear = (weekInYear - 1)  * 7 + 1;

    // Since the first day of week 1 in a year in the Gregorian calendar is not usually January 1st we need to handle the offset
    static int t[] = {0, 0, -1, -2, -3, 3, 2, 1};
    int jan1DayOfWeek = getDayOfTheWeek(*year, 1, 1); 
    dayInYear += t[jan1DayOfWeek];

    if (dayInYear <= 0){
        // dayInYear is in the previous year
        (*year)--;
        dayInYear += getDaysInYear(*year);
    } else {
        int daysInYear = getDaysInYear(*year);
        if (dayInYear > daysInYear)
        {
            // dayInYear is in the next year
            (*year)++;
            dayInYear -= daysInYear;
        }
    }

    getDayAndMonthFromDayInYear(*year, dayInYear, month, dayInMonth);
}


/****************************************************
/
/ Section 3
/ Information of a month
/
****************************************************/

//Get number of days in a month
//In: integer year, month
//Return: integer no of day
int getDaysInMonth(int year, int month){
	int maxDay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(isLeapYear(year)){
		maxDay[1] = 29;
	} 
	return maxDay[month-1];
}

/****************************************************
/
/ Section 4
/ Information of a day
/
****************************************************/

//Get the day of week in a Gregorian calendar
//Uses the Claus Tøndering algorithm
//In: integer year, month, day
//Return: integer day of week
int getDayOfTheWeek(int year, int month, int day){
   static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
   year -= month < 3;
   return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}

//Get week in year from date
//In: integer year, month, day
//Return: integer week number
int getWeekInYearFromDate(int year, int month, int day){
	int firstDay = 0;
	int firstMonth = 0; 
	int firstYear = year;
	getDayAndMonthFromWeekInYear(&firstYear, 1, &firstMonth, &firstDay);
	int firstDayInYear = getDayInYearFromDayAndMonth(firstYear, firstMonth, firstDay);
	int dayInYear = getDayInYearFromDayAndMonth(year, month, day);
	if(firstDayInYear > 30){
		dayInYear += getDaysInYear(firstYear) - firstDayInYear;
	} else {
		dayInYear -= firstDayInYear;
	}
	int weekInYear = 1 + dayInYear/7;
	if (weekInYear>getNoOfWeeksInYear(year)){
		weekInYear = 1;
	}
	return weekInYear;
}

//Gets day in year from month and day in month
//In: integer year, month, day
//Return: integer day in year
int getDayInYearFromDayAndMonth(int year, int month, int day){
	int dayInYear = 0;
	for(int i=1; i<month; i++){
		dayInYear += getDaysInMonth(year, i);
	}
	dayInYear += day;
	return dayInYear;
}

//Gets the month and day in month from a day in year
//In: integer year, day in year
//Out: integer month, day in month
void getDayAndMonthFromDayInYear(int year, int dayInYear, int *month, int *dayInMonth){
    int daysInMonth;
    *month = 1;

    for (int i = 1; i <= 12 ; i++)
    {
        daysInMonth = getDaysInMonth(year, i);

        if (dayInYear <= daysInMonth) break;

        (*month)++;
        dayInYear -= daysInMonth;
    }

    *dayInMonth = (int)dayInYear;
}

/****************************************************
/
/ Section 5
/ Others
/
****************************************************/

//Correct offset of day of week due to start day change
//In: integer day of week
//Return: integer day of week(Sun=0 Sat=6)
int fDayCorrection(int x){
	if (x < 0){
		x += 7;
	} 
	if (x > 6){
		x -= 7;
	} 	
	return x;
}

//Check if a char array contain integer only
//In: char
//Return: true or false
bool isInteger(char * c){
	bool result;
	for(int i = 0; i < strlen(c); i++){
		if(! (c[i] >= '0' && c[i] <= '9' || c[i] == ' ') ){
			result = false;
			break;
		} else {
			result =  true;
		}
	}
	return result;
}