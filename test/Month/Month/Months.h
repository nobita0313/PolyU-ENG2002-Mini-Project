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