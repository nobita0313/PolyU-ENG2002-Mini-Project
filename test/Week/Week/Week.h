class Week {
public: 
	Week(int month, int order);
	void SetWeekNo(int month, int order);
	int GetWeekNo();
	void SetPosition(int x, int y);
	int GetX();
	int GetY();
private:
	int itsWeekNo;
	int itsPositionX;
	int itsPositionY;
};

Week::Week(int month, int order){
	itsWeekNo = (month - 1)*4 + order;

};