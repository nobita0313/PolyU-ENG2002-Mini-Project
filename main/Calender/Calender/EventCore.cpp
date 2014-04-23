#include "EventCore.h"
#include <string.h>
#include <fstream>
#include <stdlib.h>
using namespace std;
bool loadevent(char *** buff, char *filename){
	int a=0;
	ifstream fin(filename);
	int i=0;
	int j=0;
	if(!fin)
	{
		return false;
	}
	else
	{
		while (fin.getline(buff[i][j],30))
		{
			if (j<4)
				j++;
			else
			{
				j=0;
				i++;
			}
		}
		a=i;
		return true;
	}

	fin.close(); 

}


int evefind(int myYear, int myMonth, int myDay, char ** name, int * loe, int *shour, int *smin, int *ehour, int *emin, char *** buff)

{   char numref[5];
int a=0;
char* show = new char;

int num=0;
int y=myYear, m=myMonth,d=myDay;
char date[9];
char mbuff[3];
char dbuff[3];
itoa(y,date,10);
itoa(m,mbuff,10);
itoa(d,dbuff,10);
if(m<10)
{
	if(d<10)
	{
		strcat(date,"0");
		strcat(date,mbuff);
		strcat(date,"0");
		strcat(date,dbuff);
	}

	else
	{
		strcat(date,"0");
		strcat(date,mbuff);
		strcat(date,dbuff);
	}
}
else
{
	if(d<10)
	{

		strcat(date,mbuff);
		strcat(date,"0");
		strcat(date,dbuff);
	}
	else
	{
		strcat(date,mbuff);
		strcat(date,dbuff);
	}

}
int i=0;
int	j=0;
while(i<1000)
{
	if(strcmp(buff[i][0],date)==0)
	{
		numref[num]=i;
		name[num]=buff[numref[num]][1];
		char*load=buff[numref[num]][4] ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
		load1[0]=load[0];
		load1[1]=load[1];
		load2[0]=load[2];
		load2[1]=load[3];
		load3[0]=load[5];
		load3[1]=load[6];
		load4[0]=load[7];
		load4[1]=load[8];
		shour[num]=atoi(load1);
		smin[num]=atoi(load2);
		ehour[num]=atoi(load3);
		emin[num]=atoi(load4);
		loe[num]=atoi(buff[numref[num]][2]);
		num++;
	}
	i++;
}
return num;
}
