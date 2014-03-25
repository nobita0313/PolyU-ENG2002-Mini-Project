class Days{
public:
	Days();
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

int fDayCorrection(int x){
	if (x < 0){
		x += 7;
	} 
	return x;
}