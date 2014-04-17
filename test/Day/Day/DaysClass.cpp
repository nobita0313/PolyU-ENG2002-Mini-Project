#include "Days.h"
#include "CalendarCore.h"

Days::Days(){
}

Days::~Days(){
}

void Days::SetYMD(int y, int m, int d){
    itsDayOfWeek = getDayOfTheWeek(y, m, d);
	firstDayOfWeek = getDayOfTheWeek(y, m, 1);

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