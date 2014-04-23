class even
{
public:
	char*getdate();
		char*getname();
	void settime(char*t);
	char*gettime();
	int getloe();
	int getcat();
	void setcat(int c);
	void setloe(int l);
	void setdate(char*d);
	void setname(char*n);

private:
	char* date;
	char *name;
	int category;
	char *duration;
	int color;
};