class Months{
	public:
		Months();
		~Months();
		void SetYM(int year, int month);
		int GetYear();
		int GetMonthNo();
		int GetMaxDay();
	private:
		int itsYear;
		int itsMonth;
		int itsMaxDay;
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