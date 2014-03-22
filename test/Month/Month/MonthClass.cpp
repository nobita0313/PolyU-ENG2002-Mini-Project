#include "Month.h"
Month::Month(int year, int month){
	itsYear = year;
	itsMonth = month;
	itsMaxDay = maxDay(year, month);
}
Month::~Month(){
}
void Month::SetYM(int year, int month){
	itsYear = year;
	itsMonth = month;
	itsMaxDay = maxDay(year, month);
}
int Month::GetYear(){
	return itsYear;
}
int Month::GetMonthNo(){
	return itsMonth;
}
int Month::GetMaxDay(){
	return itsMaxDay;
}