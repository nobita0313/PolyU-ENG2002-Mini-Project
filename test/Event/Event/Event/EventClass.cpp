#include "Event.h"
void even::setname(char*n)
{
	name=n;
}
void even::settime(char*t)
{
	duration=t;
}


	void even::setcat(int c)
	{
	category=c;
	}

	void even::setdate(char*d)
	{
	date=d;
	}
	void even::setloe(int l)
	{
	color=l;
	}
	char* even::getname()
	{
	return name;
	}
	char* even::getdate()
	{
	return date;
	}
	char* even::gettime()
	{
	return duration;
	}
	int even::getcat()
	{
	return category;
	}
	int even::getloe()
	{
	return color;
	}