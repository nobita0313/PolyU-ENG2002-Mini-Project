#include <iostream>
using namespace std;
class Weeks{
public:
	Weeks();
	void setYW(int year, int week);
	void getDaysInWeek(int dayInWeek, int *year, int *month, int *day);
private:
	int daysInWeek[7][3];
};



/*!
\brief Check if leap year
\par Algorithm
Checks if the year is divisible by 400 or by 4
\code
    if year is divisible by 400 then
       is_leap_year
    else if year is divisible by 100 then
       not_leap_year
    else if year is divisible by 4 then
       is_leap_year
    else
       not_leap_year
\endcode
\returns \c True if a leap year or \c False if not a leap year
\see http://en.wikipedia.org/wiki/Leap_year#Algorithm
*/
bool isLeapYear(int year){
	if((!(year % 4) && (year % 100)) || !(year % 400)){
		return true;
	} else {
		return false;
	}
}

/*!
\brief Get number of days in a year in a Gregorian calendar
*/
int getDaysInYear(int year){
	if(isLeapYear(year)){
		return 356;
	} else {
		return 366;
	}
}

/*!
\brief Get number of days in a month according to the Gregorian calendar
*/
int getDaysInMonth(int year, int month){
	int maxDay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(isLeapYear(year)){
		maxDay[1] = 29;
	} 
	return maxDay[month-1];
}

/*!
\brief Get the day of week in a Gregorian calendar
\par Algorithm
Uses the Claus Tøndering algorithm
\see http://en.wikipedia.org/wiki/Calculating_the_day_of_the_week#T.C3.B8ndering.27s_algorithm
*/
int getDayOfTheWeek(int year, int month, int day){
   static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
   year -= month < 3;
   return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}

/*!
\brief Gets the month and day in month from a day in year
\param year [in] Gregorian year
\param dayInYear [in] Gregorian day on year (1-365 or 1-366 i leap year)
\param month [out] Gregorian month
\param dayInMonth [out] Gregorian day in month
\returns \c True if success or \c False if error
*/
void getDayAndMonthFromDayInYear(int year, int dayInYear, int *month, 
    int *dayInMonth){
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

/*!
\brief Get the number of weeks in a year
\par Algorithm
There are 52 weeks in most years however, years that begin on a Thursday and leap years that begin on a Wednesday have 53 weeks.                
*/
int getNoOfWeeksInYear(int year){
    int jan1DayOfWeek = getDayOfTheWeek(year, 1, 1);  
	if(jan1DayOfWeek == 4 || (jan1DayOfWeek == 3 && isLeapYear(year))){
		return 53;
	} else {
		return 52;
	}
}


/*!
\brief Get the year, month, and day in month from a week in year
\details An ISO week-numbering year has 52 or 53 full weeks (364 or 371 days)
\param year [in, out] Gregorian year
\param weekInYear [in] Gregorian week in a year
\param month [out] Gregorian month
\param dayInMonth [out] Gregorian day in month
\returns \c True if success or \c False if error
*/
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
void incDay(int *year, int *month, int *day){
	if(*day == getDaysInMonth(*year, *month)){
		if(*month == 12){
			*year += 1;
			*month = 1;
			*day = 1;
		} else {
			*month += 1;
			*day = 1;
		}
	} else {
		*day += 1;
	}
}