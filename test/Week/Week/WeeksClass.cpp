#include "Weeks.h"
#include "CalendarCore.h"

Weeks::Weeks(){
	for(int i=0; i<7; i++){
		for(int j=0; j<3; j++){
		daysInWeek[i][j] = 0;
		}
	}
}
void Weeks::SetYW(int year, int week){
	int yearOfDay = year;
	int monthOfDay = 0;
	int day = 0;
	getDayAndMonthFromWeekInYear(&yearOfDay, week, &monthOfDay, &day);
	for(int i=0; i<7; i++){
		daysInWeek[i][0] = yearOfDay;
		daysInWeek[i][1] = monthOfDay;
		daysInWeek[i][2] = day;

		incDay(&yearOfDay, &monthOfDay, &day);
	}
	itsYear = daysInWeek[3][0];
	itsMonth = daysInWeek[3][1];
	itsWeek = week;
}

void Weeks::GetDaysInWeek(int dayInWeek, int *year, int *month, int *day){
	*year = daysInWeek[dayInWeek][0];
	*month = daysInWeek[dayInWeek][1];
	*day = daysInWeek[dayInWeek][2];
}

int Weeks::GetYear(){
	return itsYear;
}

int Weeks::GetMonthNo(){
	return itsMonth;
}

int Weeks::GetWeek(){
	return itsWeek;
}