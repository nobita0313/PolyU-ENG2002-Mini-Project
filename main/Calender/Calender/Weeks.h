class Weeks{
public:
	Weeks();
	void SetYW(int year, int week);
	void GetDaysInWeek(int dayInWeek, int *year, int *month, int *day);
	int GetYear();
	int GetMonthNo();
	int GetWeek();
private:
	int daysInWeek[7][3];
	int itsYear;
	int itsMonth;
	int itsWeek;
};