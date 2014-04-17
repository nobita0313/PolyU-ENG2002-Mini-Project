#include <iostream>
#include "Weeks.h"
using namespace std;

Weeks::Weeks(){
	for(int i=0; i<7; i++){
		for(int j=0; j<3; j++){
		daysInWeek[i][j] = 0;
		}
	}
}
void Weeks::setYW(int year, int week){
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
}

void Weeks::getDaysInWeek(int dayInWeek, int *year, int *month, int *day){
	*year = daysInWeek[dayInWeek][0];
	*month = daysInWeek[dayInWeek][1];
	*day = daysInWeek[dayInWeek][2];
}

int main(){
	Weeks thisWeek;
	thisWeek.setYW(2015, 1);
	int year = 0;
	int month = 0; 
	int day = 0;
	for(int i=0; i<7; i++){
		thisWeek.getDaysInWeek(i, &year, &month, &day);
		cout << year << endl;
		cout << month << endl;
		cout << day << endl;
	}
}

