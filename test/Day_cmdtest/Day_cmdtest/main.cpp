#include <iostream>
using namespace std;
class Days{
public:
	Days(int year=0, int month=0, int day=0, int fday =0);
	~Days();
	void SetYMD(int year, int month, int day);
	void SetStartDay(int fday);
	int GetDay();
	int GetWeekNo();
	int GetDayOfWeek();
	int GetXY(char type);

private:
	int itsDay;
	int itsWeekNo;
	int itsDayOfWeek;
	int firstDayOfWeek;
	int itsX;
	int itsY;
};

bool isLeapYear(int year){
	if((year-2000)%4==0){
		return true;
	} else {
		return false;
	}
}

int maxDay(int year, int month){
	int maxDay;
	if (month%2 == 0){
		if (month == 2){
			if(isLeapYear(year)){
				maxDay = 29;
			} else {
				maxDay = 28;
			}
		} else {
			maxDay = 30;
		}
	} else {
		maxDay = 31;
	}
	return maxDay;
}

int dayOfWeek(int y, int m, int d){
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    int dayOfWeek = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
	return dayOfWeek;
}

Days::Days(int y, int m, int d, int fday){
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
	int col = itsDayOfWeek - fday;
	int day1 = firstDayOfWeek - fday;
	int day = itsDay;
	if (col < 0){
		col += 7;
	} 
	if (day1 < 0){
		day1 += 7;
	} 
	while(day > (7 - day1)){
		day -= 7;
		row++;
	}
	itsX = col;
	itsY = row;
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
	while(day > (7 - day1)){
		day -= 7;
		row++;
	}
	itsX = col;
	itsY = row;
		cout << firstDayOfWeek;
}

void Days::SetStartDay(int fday){
	int row = 1;
	int col = itsDayOfWeek - fday;
	int day1 = firstDayOfWeek - fday;
	int day = itsDay;
	if (col < 0){
		col += 7;
	} 
	if (day1 < 0){
		day1 += 7;
	} 
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

int main(){
	Days * date = new Days[31];
	for(int i=1; i<32; i++){
		date[i-1].SetYMD(2014, 3, i);
		cout << "Day: " << date[i-1].GetDay() << endl;
		cout << "DayOfWeek: " << date[i-1].GetDayOfWeek() << endl;
		cout << "WeekNo: " << date[i-1].GetWeekNo() << endl;
		cout << "Y: " << date[i-1].GetXY('y') <<  endl;
		cout << "X: " << date[i-1].GetXY('x') <<  endl;
	}
}