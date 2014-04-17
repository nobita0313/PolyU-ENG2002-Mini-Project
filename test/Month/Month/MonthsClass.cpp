#include "Months.h"
#include "CalendarCore.h"

Months::Months(){
}
Months::~Months(){
}
void Months::SetYM(int year, int month){
	itsYear = year;
	itsMonth = month;
	itsMaxDay = getDaysInMonth(year, month);
}
int Months::GetYear(){
	return itsYear;
}
int Months::GetMonthNo(){
	return itsMonth;
}
int Months::GetMaxDay(){
	return itsMaxDay;
}