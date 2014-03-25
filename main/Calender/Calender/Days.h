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