#include "Days.h"
Days::Days(){
}

Days::~Days(){
}

void Days::SetYMD(int y, int m, int d){
    itsDayOfWeek = dayOfWeek(y, m, d);
	firstDayOfWeek = dayOfWeek(y, m, 1);

	int dow, dowJan1;
	int julian = 0;
	for(int i=1; i<m; i++){
		julian += maxDay(y, i);
	}
	julian += d;  // Jan 1 = 1, Jan 2 = 2, etc...
	dow = itsDayOfWeek;     // Sun = 0, Mon = 1, etc...
	dowJan1 = dayOfWeek(y, 1 ,1);   // find out first of year's day
	itsWeekNo = ((julian + 6) / 7);   // probably better.  CHECK THIS LINE. (See comments.)
	if (dow < dowJan1) {                // adjust for being after Saturday of week #1
		++itsWeekNo;
	}

	itsDay = d;

	int row = 1;
	int col = itsDayOfWeek;
	int day1 = firstDayOfWeek;
	int day = itsDay;
	while(day >  (7 -day1)){
		day -= 7;
		row++;
	}
	itsX = col;
	itsY = row;
}

void Days::SetStartDay(int fday){
	int row = 1;
	int col = fDayCorrection(itsDayOfWeek - fday);
	int day1 = fDayCorrection(firstDayOfWeek - fday);
	int day = itsDay;

	while(day > (7 - day1)){
		day -= 7;
		row++;
	}
	itsX = col;
	itsY = row;
}

int Days::GetDay(){
	return itsDay;
}

int Days::GetWeekNo(){
	return itsWeekNo;
}

int Days::GetDayOfWeek(){
	return itsDayOfWeek;
}

int Days::GetXY(char type){
	switch(type){
	case 'x': return itsX; break;
	case 'y': return itsY; break;
	default: return 0; break;
	}
}