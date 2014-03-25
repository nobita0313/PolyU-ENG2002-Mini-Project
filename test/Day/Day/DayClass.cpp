#include <ctime>
class Day{
public:
	Day(int year, int month, int day);
	void SetDay(int day);
	int GetDay();
	void SetWeekNo(int week);
	int GetWeekNo();
	void SetDayOfWeek(int wday);
	int GetDayOfWeek();

private:
	int itsDay;
	int itsWeekNo;
	int itsDayOfWeek;
}

Day::Day(int y, int m, int d){
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    itsDayOfWeek = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;

	int julian, dow, dowJan1;
	julian = getDayOfYear(myDate);  // Jan 1 = 1, Jan 2 = 2, etc...
	dow = itsDayOfWeek;     // Sun = 0, Mon = 1, etc...
	dowJan1 = (y + y/4 - y/100 + y/400 + 1) % 7;   // find out first of year's day
	itsWeekNo = ((julian + 6) / 7);   // probably better.  CHECK THIS LINE. (See comments.)
	if (dow < dowJan1) {                // adjust for being after Saturday of week #1
		++itsWeekNo;
	}

	itsDay = d;
}