#pragma once
#include "login_form.h"
#include "event_form.h"
#include "stat_form.h"
#include "Months.h"
#include "Weeks.h"
#include "Days.h"
#include "CalendarCore.h"
#include "EventCore.h"

namespace Calendar {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			//Deflickering in TableLayouPanel
			this->SetStyle(static_cast<ControlStyles>(
				ControlStyles::AllPaintingInWmPaint |
				ControlStyles::DoubleBuffer |
				ControlStyles::UserPaint), true); 
			this->UpdateStyles();

			setDoubleBuffer(monthly_cal);
			setDoubleBuffer(weekly_cal);
			setDoubleBuffer(daily_cal);
			setDoubleBuffer(daily_monthly_cal);

			startday = WEEKDAY::Sunday;
			displayType = TYPE::Monthly;
			LabelArr = gcnew array<System::Windows::Forms::Label^, 3>(6, 7, 5); 
			PanelArr = gcnew array<System::Windows::Forms::Panel^, 2>(7, 5); 

			events = new char**[1000];
			for(int i=0; i<1000; i++){
				events[i] = new char*[5];
				for(int j=0; j<5; j++){
					events[i][j] = new char[30];
				}
			}

			thisMonth = new Months;
			lastMonth = new Months; 
			nextMonth = new Months;
			thisWeek = new Weeks;
			thisMonthDate = new Days[31];
			lastMonthDate = new Days[31];
			nextMonthDate = new Days[31];

			setActiveDate(getTime('y'), getTime('m'), getTime('d'), getTime('w'));
			setMonths(activeYear, activeMonth);
			setStartDay(startday);
			drawCal(TYPE::Monthly);

		}
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		//Some variables
		static enum class MONTH {January = 1, February, March, April, May, June, July, August, September, October, November, December};
		static enum class WEEKDAY {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
		static enum class TYPE {Monthly, Weekly, Daily};
		WEEKDAY startday;
		TYPE displayType;
		int activeDay, activeMonth, activeYear, activeWeek, activeHr, activeMin;
		char *** events;
		char * fileName;

		//Colours in argb
		static const Int32 tNormal = 0xFF000000;
		static const Int32 bgNormal = 0xFFFFFFFF;
		static const Int32 tToday = 0xFFD26B69;
		static const Int32 bgToday = 0xFFFDEFF0;
		static const Int32 tPast = 0xFFAAAAAA;
		static const Int32 cBorder = 0xFFA0A0A0;
		static const Int32 bgTrans = 0x00FFFFFF;
		static const Int32 bgTodayTrans = 0x7FFCE3E5;
		static const Int32 bgEvent_Nor = 0xFF6E9EEC;
		static const Int32 bgEvent_Mid = 0xFFAC87E4;
		static const Int32 bgEvent_High = 0xFFD07872;

		//Object required
		Months * thisMonth;
		Months * lastMonth;
		Months * nextMonth;
		Weeks * thisWeek;
		Days * thisMonthDate;
		Days * lastMonthDate;
		Days * nextMonthDate;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			delete thisMonth;
			delete lastMonth;
			delete nextMonth;
			delete thisWeek;
			delete [] thisMonthDate;
			delete [] lastMonthDate;
			delete [] nextMonthDate;
			if (components)
			{
				delete components;
			}
		}

	private: 
		/****************************************************
		/
		/ Section 1 of custom function
		/ Basic functions
		/
		****************************************************/

		//Check if the date is today
		//Return: true or false
		bool isToday(int y, int m, int d){
			if( y == getTime('y') && m == getTime('m') && d == getTime('d')){
				return true;
			} else {
				return false;
			}
		}

		//Get the current date from system
		//Return: integer year, month, day or week
		int getTime(char type){
			System::DateTime now = System::DateTime::Now;

			switch (type){
			case 'd': return now.Day;
				break;
			case 'm': return now.Month;
				break;
			case 'y': return now.Year;
				break;		
			case 'w': return getWeekInYearFromDate(now.Year, now.Month, now.Day);
				break;
			default:	return 0;
				break;
			}
		}

		//Get duration between time
		//In: Start Hr(sHr), Start Min(sMin), End Hr(eHr), End Min(eMin)
		//Out: Duration Hr(dHr), Duration Min(dMin)
		void getDuration(int sHr, int sMin, int eHr, int eMin, int * dHr, int * dMin){
			*dHr = eHr - sHr;
			*dMin = eMin - sMin;
			if (dMin < 0){
				*dMin += 60;
				(*dHr)--;
			}
		}

		//Convert integer to double digi in String
		//Return: String NN
		String^ getDoubleDigi(int num){
			String^ cNum;
			if(num<10){
				cNum = "0" + num;
			} else {
				cNum = "" + num;
			}
			return cNum;
		}

		/****************************************************
		/
		/ Section 2 of custom function
		/ GUI element functions
		/
		****************************************************/

		//Set specified textbox text
		//Usage: Target textbox(tBox), Content(msg)
		void setTextbox(TextBox ^ tBox, String ^ msg){
			tBox->Width = (int)CreateGraphics()->MeasureString(msg, tBox->Font).Width - 5; //For better align in GUI
			tBox->Text = msg;
		}

		//Set specified label text
		//Usage: Target label(lab), Content(msg)
		void setLabel(Label ^ lab, String ^ msg){
			lab->Text = msg;
		}

		//Set data of the date block in specified row and column
		//Usage: Taget tabel(parent), Row(r), Column(c), Target label name(name), Additional date(tag), Background color(bgColor), Text color()textColor
		void setDayInfo(TableLayoutPanel^ parent, int r, int c, String^ name, String^ msg, String^ tag, Int32 bgColor, Int32 textColor){
			Control ^panel = parent->GetControlFromPosition(c, r);
			panel->Tag = tag;
			panel->BackColor = System::Drawing::Color::FromArgb(bgColor);

			for each ( Control ^ctl in panel->Controls ){
				if(!String::IsNullOrEmpty(name)){
					if(ctl->Name->Contains(name)){
						ctl->Text = msg;
						ctl->Tag = tag;
						ctl->ForeColor = System::Drawing::Color::FromArgb(textColor);
					}
				}
			}
		}

		//Calculate the time clicked based on the Y location of the cursor
		//In: Year(y)
		//Out: Hour(hr), Min(min)
		void getTimeFromPos(int y, int * hr, int * min){
			int weeklyCalCHeight = weekly_cal->RowStyles[0]->Height;
			int time = y / (weeklyCalCHeight + 1); // + 1 for boarder height
			*hr = time / 2;
			*min = (time % 2) * 30;
		}

		//Calculate the Y location based on the hour and min input
		//In: Hour(hr), Min(min)
		//Out: Year(y)
		void getPosFromTime(float * y, int hr, int min){
			float weeklyCalCHeight = weekly_cal->RowStyles[0]->Height + 1;
			*y = weeklyCalCHeight * (((float)hr * 2 + (float)min * 2 / 60) ) - 1;
		}

		//Set DoubleBuffer to deflicker
		void setDoubleBuffer(Control ^ ctl){
			ctl->GetType()->GetProperty(
				"DoubleBuffered", 
				System::Reflection::BindingFlags::NonPublic | 
				System::Reflection::BindingFlags::Instance)
				->SetValue(ctl, true, nullptr);
		}

		//Get the ARGB code from level of emegency
		//Return: Int32 argb code
		Int32 getColorFromLOE(int choice){
			switch(choice){
			case 0: return bgEvent_Nor; break;
			case 1: return bgEvent_Mid; break;
			case 2: return bgEvent_High; break;
			case 3: return bgEvent_Nor; break;
			case 4: return tPast; break;
			default: return 0; break;
			}
		}
		/****************************************************
		/
		/ Section 3 of custom function
		/ Calender configuration
		/
		****************************************************/

		//Set activeDate in form of int of string
		void setActiveDate(int y, int m, int d, int w){
			activeDay = d;
			activeMonth = m;
			activeYear = y;
			activeWeek = w;
		}
		void setActiveDate(int y, int m, int d, int w, int hr, int min){
			setActiveDate(y, m, d, w);
			activeHr = hr;
			activeMin = min;
		}
		void setActiveDate(String ^ string){
			array<String^>^ date = string->Split('/');
			activeYear = int::Parse(date[0]);
			activeMonth = int::Parse(date[1]);
			activeDay = int::Parse(date[2]);
			activeWeek = int::Parse(date[3]);
		}

		//Start the starting day of week
		void setStartDay(WEEKDAY fDay){
			fDay++; //skip the first combobox
			for(int i=0; i<6; i++){
				if (fDay > WEEKDAY::Saturday){
					fDay = WEEKDAY::Sunday;
				}

				String^ wDay = Enum::GetName(WEEKDAY::typeid, fDay++);
				setDayInfo(monthly_cal, 0, i+1, "WDay", wDay, "0", bgNormal ,tNormal);

				//Update the x, y position of a date in class
				for(int i=0; i<lastMonth->GetMaxDay(); i++){
					lastMonthDate[i].SetStartDay((int)fDay);
				}				
				for(int i=0; i<thisMonth->GetMaxDay(); i++){
					thisMonthDate[i].SetStartDay((int)fDay);
				}	
				for(int i=0; i<nextMonth->GetMaxDay(); i++){
					nextMonthDate[i].SetStartDay((int)fDay);
				}	
			}
		}

		//Set data of month class objects(three object: lastMonth, thisMonth, nextMonth)
		void setMonths(int year, int month){
			int lastMonthY = year;
			int lastMonthM = month;
			int nextMonthY = year;
			int nextMonthM = month;

			decMonth(&lastMonthY, &lastMonthM);
			incMonth(&nextMonthY, &nextMonthM);
			thisMonth->SetYM(year, month);
			lastMonth->SetYM(lastMonthY, lastMonthM);
			nextMonth->SetYM(nextMonthY, nextMonthM);

			setActiveDate(year, month, activeDay, getWeekInYearFromDate(year, month, activeDay));

			for(int i=0; i<lastMonth->GetMaxDay(); i++){
				lastMonthDate[i].SetYMD(lastMonth->GetYear(), lastMonth->GetMonthNo(), i+1);
			}				
			for(int i=0; i<thisMonth->GetMaxDay(); i++){
				thisMonthDate[i].SetYMD(thisMonth->GetYear(), thisMonth->GetMonthNo(), i+1);
			}	
			for(int i=0; i<nextMonth->GetMaxDay(); i++){
				nextMonthDate[i].SetYMD(nextMonth->GetYear(), nextMonth->GetMonthNo(), i+1);
			}	
		}

		//Set data of week class object(thisWeek)
		void setWeeks(int year, int week){
			int month, day, dow;
			//Get day of week of the activeDay(Mon = 0, Sun = 6) !!!different from WEEKDAY enum!!!
			dow = fDayCorrection(getDayOfTheWeek(activeYear, activeMonth, activeDay) - 1);
			thisWeek->SetYW(year, week);
			thisWeek->GetDaysInWeek(dow, &year, &month, &day);
			setActiveDate(year, month, day, week);
		}

		//Set data of activeDate and update the month object
		void setDays(int year, int month, int day){
			int week = getWeekInYearFromDate(year, month, day);
			setActiveDate(year, month, day, week);
			setMonths(year, month); //Used by the display of mini maothly cal
		}

		/****************************************************
		/
		/ Section 3 of custom function
		/ Calender display
		/
		****************************************************/

		//Switching between different calendar type
		void showEvents(TableLayoutPanel^ table, int r, int c, int y, int m, int d){
			if(!String::IsNullOrEmpty(userName)){
				char ** eName = new char*[5];
				for(int i=0; i<5; i++){
					eName[i] = new char[30];
				}
				int *loe = new int[5];	
				int *sHr = new int[5];
				int *sMin = new int[5];
				int *eHr = new int[5];
				int *eMin = new int[5];
				int eventNum = evefind(y, m, d, eName, loe, sHr, sMin, eHr, eMin, events); //Number of event on that day **EDIT HERE***
				float y = 0;

				if(table->Name->StartsWith("monthly_cal")){
					Control ^ parent = table->GetControlFromPosition(c, r--);	
					for(int i=0; i<eventNum; i++){
						Int32 eventColor = getColorFromLOE(loe[i]);
						String^ cSHr = getDoubleDigi(sHr[i]);
						String^ cSMin = getDoubleDigi(sMin[i]);

						//Eventdata start **EDIT HERE***
						String^ name = Marshal::PtrToStringAnsi((IntPtr)eName[i]); //Start time + Name of event[i]
						String^ text = cSHr + ":" + cSMin + " " + name;
						Int32 color = eventColor; //Color in ARGB for priority
						//Eventdata end

						y += 15;
						LabelArr[r,c,i]=(gcnew System::Windows::Forms::Label());		
						parent->Controls->Add(LabelArr[r,c,i]);

						int width = LabelArr[r,c,i]->Parent->Width;
						LabelArr[r,c,i]->Location = System::Drawing::Point(0, y); 
						LabelArr[r,c,i]->Name = "event_" + r + "_" + c + "_" + i; 
						LabelArr[r,c,i]->Size = System::Drawing::Size(width, 15); 
						LabelArr[r,c,i]->ForeColor = System::Drawing::Color::FromArgb(color);
						LabelArr[r,c,i]->TabIndex = 0; 
						LabelArr[r,c,i]->Text = text; 	
						LabelArr[r,c,i]->TextAlign = System::Drawing::ContentAlignment::TopLeft;
						LabelArr[r,c,i]->Tag = LabelArr[r,c,i]->Parent->Tag;
						LabelArr[r,c,i]->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
						LabelArr[r,c,i]->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
						setDoubleBuffer(LabelArr[r,c,i]);
					}
				}

				if(table->Name->StartsWith("weekly_cal") || table->Name->StartsWith("daily_cal")){
					Control ^ parent = table->GetControlFromPosition(c--, r);	
					for(int i=0; i<eventNum; i++){
						float height;
						int dHr, dMin;
						getDuration(sHr[i], sMin[i], eHr[i], eMin[i], &dHr, &dMin);
						String^ cSHr = getDoubleDigi(sHr[i]);
						String^ cSMin = getDoubleDigi(sMin[i]);
						String^ cEHr = getDoubleDigi(eHr[i]);
						String^ cEMin = getDoubleDigi(eMin[i]);
						Int32 eventColor = getColorFromLOE(loe[i]);

						//Eventdata start **EDIT HERE***
						String^ name = Marshal::PtrToStringAnsi((IntPtr)eName[i]); //Start time + Name of event[i]
						String^ text = cSHr + ":" + cSMin + " - " + cEHr + ":" + cEMin + "\n" + name;
						Int32 color = eventColor; //Color in ARGB for priority
						getPosFromTime(&y, sHr[i], sMin[i]); //get start position, input start hr, min
						getPosFromTime(&height, dHr, dMin); //get height , input duration hr, min
						//Eventdata end
						
						PanelArr[c,i]=(gcnew System::Windows::Forms::Panel());		
						parent->Controls->Add(PanelArr[c,i]);

						int width = PanelArr[c,i]->Parent->Width;
						PanelArr[c,i]->Padding = System::Windows::Forms::Padding(3);
						PanelArr[c,i]->Location = System::Drawing::Point(0, y); 
						PanelArr[c,i]->Name = "eventPanel_" + c + "_" + 1; 
						PanelArr[c,i]->Size = System::Drawing::Size(width, height); 
						PanelArr[c,i]->BackColor = System::Drawing::Color::FromArgb(color);
						PanelArr[c,i]->TabIndex = 0; 	
						PanelArr[c,i]->Tag = PanelArr[c,i]->Parent->Tag;
						PanelArr[c,i]->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
						PanelArr[c,i]->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);

						LabelArr[r,c,i]=(gcnew System::Windows::Forms::Label());		
						PanelArr[c,i]->Controls->Add(LabelArr[r,c,i]);
						
						LabelArr[r,c,i]->Location = System::Drawing::Point(5, 5); 
						LabelArr[r,c,i]->Name = "event_" + r + "_" + c + "_" + i; 
						LabelArr[r,c,i]->Size = System::Drawing::Size(width, height); 
						LabelArr[r,c,i]->ForeColor = System::Drawing::Color::FromArgb(tNormal);
						LabelArr[r,c,i]->TabIndex = 0; 
						LabelArr[r,c,i]->Text = text; 	
						LabelArr[r,c,i]->TextAlign = System::Drawing::ContentAlignment::TopLeft;
						LabelArr[r,c,i]->Tag = LabelArr[r,c,i]->Parent->Tag;
						LabelArr[r,c,i]->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
						LabelArr[r,c,i]->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
						setDoubleBuffer(PanelArr[c,i]);
						setDoubleBuffer(LabelArr[r,c,i]);
					}
				}
			}
		}

		//Clear all the displayed event on screen
		void clearEvent(){
			for(int r=0; r<6; r++){
				for(int c=0; c<7; c++){
					for(int i=0; i<5; i++){
						delete LabelArr[r,c,i];
						delete PanelArr[c,i];
					}
				}
			}
		} 

		//Switching between different calendar type
		void drawCal(TYPE type){
			displayType = type;
			switch(type){
			case 0: 
				drawMonthlyCal(monthly_cal); 
				mPanel->Show();
				wPanel->Hide();
				dPanel->Hide();
				display_week->Hide(); 
				display_day->Hide(); 
				break;
			case 1: 
				drawWeeklyCal(); 
				mPanel->Hide();
				wPanel->Show();
				dPanel->Hide();
				display_week->Show(); 
				display_day->Hide(); 
				break;
			case 2: 
				drawDailyCal(); 
				mPanel->Hide();
				wPanel->Hide();
				dPanel->Show();
				display_week->Hide(); 
				display_day->Show(); 
				break;			
			default: break;
			}
		}

		//Draw the monthly cal in specified table
		void drawMonthlyCal(TableLayoutPanel^ table){
			this->SuspendLayout();

			clearEvent();

			int dayToShow = 0;
			int rowCorrection = 0;

			setTextbox(display_year, thisMonth->GetYear().ToString());
			setTextbox(display_month, Enum::GetName(MONTH::typeid, thisMonth->GetMonthNo()));

			//If first day of thisMonth is at the left top corner, switch it to the second row
			if(thisMonthDate[0].GetXY('x') == 0){
				rowCorrection = 1;
			}

			//Drawing lastMonth
			for(int i=(lastMonth->GetMaxDay() - thisMonthDate[0].GetXY('x') - rowCorrection * 7); i<lastMonth->GetMaxDay(); i++){
				int y = lastMonth->GetYear();
				int m = lastMonth->GetMonthNo();
				int d = lastMonthDate[i].GetDay();
				String ^ tag = y + "/" + m + "/" + d + "/" + getWeekInYearFromDate(y, m, d);
				setDayInfo(table, 1, lastMonthDate[i].GetXY('x'), "Day",  d.ToString(), tag, bgNormal, tPast);
				showEvents(table, 1, lastMonthDate[i].GetXY('x'), y, m, d);
			}

			//Drawing thisMonth
			for(int i=0; i<thisMonth->GetMaxDay(); i++){
				int y = thisMonth->GetYear();
				int m = thisMonth->GetMonthNo();
				int d = thisMonthDate[i].GetDay();

				Int32 textColor = tNormal;
				Int32 bgColor = bgNormal;
				if(isToday(y, m, d)){
					textColor = tToday;
					bgColor = bgToday;
				}

				String ^ tag = y + "/" + m + "/" + d + "/" + getWeekInYearFromDate(y, m, d);
				setDayInfo(table, thisMonthDate[i].GetXY('y') + rowCorrection, thisMonthDate[i].GetXY('x'), "Day",  d.ToString(), tag, bgColor, textColor);
				showEvents(table, thisMonthDate[i].GetXY('y') + rowCorrection, thisMonthDate[i].GetXY('x'), y, m, d);
			}	

			//Drawing nextMonth
			dayToShow = 6 - thisMonthDate[thisMonth->GetMaxDay()-1].GetXY('x');
			rowCorrection += thisMonthDate[thisMonth->GetMaxDay()-1].GetXY('y');
			if(rowCorrection < 6 ){ //6 rows
				dayToShow += 7;
			}
			if(thisMonthDate[thisMonth->GetMaxDay()-1].GetXY('x') == 6){//If lastday of this month is on the last column, jump to next row
				rowCorrection += 1;
			}
			for(int i=0; i<dayToShow; i++){
				int y = nextMonth->GetYear();
				int m = nextMonth->GetMonthNo();
				int d = nextMonthDate[i].GetDay();
				String ^ tag = y + "/" + m + "/" + d + "/" + getWeekInYearFromDate(y, m, d);
				setDayInfo(table, nextMonthDate[i].GetXY('y') - 1 + rowCorrection, nextMonthDate[i].GetXY('x'), "Day",  d.ToString(), tag, bgNormal, tPast);
				showEvents(table, nextMonthDate[i].GetXY('y') - 1 + rowCorrection, nextMonthDate[i].GetXY('x'), y, m, d);
			}
			this->ResumeLayout();
		}

		//Draw the weekly cal
		void drawWeeklyCal(){
			this->SuspendLayout();

			clearEvent();

			//Draw two line for divider
			Point pt = wPanel_body->Location;
			this->wTopLine->Location = pt;
			this->wTopLine->Size = System::Drawing::Size(weekly_cal->Width, 1);
			this->wTopLine->BackColor = System::Drawing::Color::FromArgb(cBorder);
			pt.Y += wPanel_body->Height - 1;
			this->wBtmLine->Location = pt;
			this->wBtmLine->Size = System::Drawing::Size(weekly_cal->Width, 1);
			this->wBtmLine->BackColor = System::Drawing::Color::FromArgb(cBorder);

			setTextbox(display_year, thisWeek->GetYear().ToString());
			setTextbox(display_month, Enum::GetName(MONTH::typeid, thisWeek->GetMonthNo()));
			setTextbox(display_week, "Week " + thisWeek->GetWeek());

			for(int i=0; i<7; i++){
				int y, m, d;
				int w = thisWeek->GetWeek();
				thisWeek->GetDaysInWeek(i, &y, &m, &d);

				Int32 textColor = tNormal;
				Int32 titleBgColor = bgNormal;
				Int32 bodyBgColor = bgTrans;
				if(isToday(y, m, d)){
					textColor = tToday;
					titleBgColor = bgToday;
					bodyBgColor = bgTodayTrans;
				}

				String ^ wDay = Enum::GetName(WEEKDAY::typeid, fDayCorrection(i+1))->Substring(0, 3);
				String ^ text = wDay + " " + d + "/" + m;
				String ^ tag = y + "/" + m + "/" + d + "/" + w;
				setDayInfo(weekly_cal_title, 0, i, "WDay",  text, "0", titleBgColor, textColor);
				setDayInfo(weekly_cal, 0, i+1, "",  "", tag, bodyBgColor, textColor);
				showEvents(weekly_cal, 0, i+1, y, m, d);
			}
			this->ResumeLayout();
		}

		//Draw the daily cal
		void drawDailyCal(){
			this->SuspendLayout();

			clearEvent();

			//Draw two line for divider
			Point pt = dPanel_body->Location;
			this->dTopLine->Location = pt;
			this->dTopLine->Size = System::Drawing::Size(daily_cal->Width, 1);
			this->dTopLine->BackColor = System::Drawing::Color::FromArgb(cBorder);
			pt.Y += dPanel_body->Height - 1;
			this->dBtmLine->Location = pt;
			this->dBtmLine->Size = System::Drawing::Size(daily_cal->Width, 1);
			this->dBtmLine->BackColor = System::Drawing::Color::FromArgb(cBorder);

			setTextbox(display_day, activeDay.ToString());
			setLabel(dDay, activeDay + ",");
			setLabel(dWDay, Enum::GetName(WEEKDAY::typeid, getDayOfTheWeek(activeYear, activeMonth, activeDay)));

			//Fix dWDay location offset
			Point dWDay_pt = dWDay->Location;
			Point dDay_pt = dDay->Location;
			dWDay_pt.X = (dDay_pt.X + dDay->Width)*0.8;
			dWDay->Location = dWDay_pt;

			Int32 bodyBgColor = bgTrans;
			if(isToday(activeYear, activeMonth, activeDay)){
				bodyBgColor = bgTodayTrans;
			}
			String ^ tag = activeYear + "/" + activeMonth + "/" + activeDay + "/" + activeWeek;
			setDayInfo(daily_cal, 0, 1, "",  "", tag, bodyBgColor, 0);
			showEvents(daily_cal, 0, 1, activeYear, activeMonth, activeDay);

			//Draw the mini monthly cal
			drawMonthlyCal(daily_monthly_cal);

			showEvents(daily_cal, 0, 1, activeYear, activeMonth, activeDay);

			this->ResumeLayout();
		}	

	private: String ^ userName;
	private: System::Windows::Forms::Button^  stat_btn;
	private: array<System::Windows::Forms::Label^, 3>  ^LabelArr;
	private: array<System::Windows::Forms::Panel^, 2>  ^PanelArr;
	private: System::Windows::Forms::TableLayoutPanel^  select_day_layout;
	private: System::Windows::Forms::TableLayoutPanel^  type_layout;
	private: System::Windows::Forms::TableLayoutPanel^  monthly_cal;
	private: System::Windows::Forms::Label^  mWDay_1;
	private: System::Windows::Forms::Label^  mWDay_2;
	private: System::Windows::Forms::Label^  mWDay_3;
	private: System::Windows::Forms::Label^  mWDay_4;
	private: System::Windows::Forms::Label^  mWDay_5;
	private: System::Windows::Forms::Label^  mWDay_6;
	private: System::Windows::Forms::Label^  mDay_6_0;
	private: System::Windows::Forms::Label^  mDay_6_1;
	private: System::Windows::Forms::Label^  mDay_6_2;
	private: System::Windows::Forms::Label^  mDay_6_3;
	private: System::Windows::Forms::Label^  mDay_6_4;
	private: System::Windows::Forms::Label^  mDay_6_5;
	private: System::Windows::Forms::Label^  mDay_6_6;
	private: System::Windows::Forms::Label^  mDay_5_0;
	private: System::Windows::Forms::Label^  mDay_5_1;
	private: System::Windows::Forms::Label^  mDay_5_2;
	private: System::Windows::Forms::Label^  mDay_5_3;
	private: System::Windows::Forms::Label^  mDay_5_4;
	private: System::Windows::Forms::Label^  mDay_5_5;
	private: System::Windows::Forms::Label^  mDay_5_6;
	private: System::Windows::Forms::Label^  mDay_4_0;
	private: System::Windows::Forms::Label^  mDay_4_1;
	private: System::Windows::Forms::Label^  mDay_4_2;
	private: System::Windows::Forms::Label^  mDay_4_3;
	private: System::Windows::Forms::Label^  mDay_4_4;
	private: System::Windows::Forms::Label^  mDay_4_5;
	private: System::Windows::Forms::Label^  mDay_4_6;
	private: System::Windows::Forms::Label^  mDay_3_0;
	private: System::Windows::Forms::Label^  mDay_3_1;
	private: System::Windows::Forms::Label^  mDay_3_2;
	private: System::Windows::Forms::Label^  mDay_3_3;
	private: System::Windows::Forms::Label^  mDay_3_4;
	private: System::Windows::Forms::Label^  mDay_3_5;
	private: System::Windows::Forms::Label^  mDay_3_6;
	private: System::Windows::Forms::Label^  mDay_2_0;
	private: System::Windows::Forms::Label^  mDay_2_1;
	private: System::Windows::Forms::Label^  mDay_2_2;
	private: System::Windows::Forms::Label^  mDay_2_3;
	private: System::Windows::Forms::Label^  mDay_2_4;
	private: System::Windows::Forms::Label^  mDay_2_5;
	private: System::Windows::Forms::Label^  mDay_2_6;
	private: System::Windows::Forms::Label^  mDay_1_0;
	private: System::Windows::Forms::Label^  mDay_1_1;
	private: System::Windows::Forms::Label^  mDay_1_2;
	private: System::Windows::Forms::Label^  mDay_1_3;
	private: System::Windows::Forms::Label^  mDay_1_4;
	private: System::Windows::Forms::Label^  mDay_1_5;
	private: System::Windows::Forms::Label^  mDay_1_6;
	private: System::Windows::Forms::TextBox^  display_year;
	private: System::Windows::Forms::TextBox^  display_month;
	private: System::Windows::Forms::Button^  prev_btn;
	private: System::Windows::Forms::Button^  next_btn;
	private: System::Windows::Forms::Button^  monthly_type;
	private: System::Windows::Forms::Button^  weekly_type;
	private: System::Windows::Forms::Button^  daily_type;
	private: System::Windows::Forms::ComboBox^  mWDay_0;
	private: System::Windows::Forms::Button^  now_btn;
	private: System::Windows::Forms::Panel^  mPanel_6_6;
	private: System::Windows::Forms::Panel^  mPanel_6_5;
	private: System::Windows::Forms::Panel^  mPanel_6_4;
	private: System::Windows::Forms::Panel^  mPanel_6_3;
	private: System::Windows::Forms::Panel^  mPanel_6_2;
	private: System::Windows::Forms::Panel^  mPanel_6_1;
	private: System::Windows::Forms::Panel^  mPanel_6_0;
	private: System::Windows::Forms::Panel^  mPanel_5_6;
	private: System::Windows::Forms::Panel^  mPanel_5_5;
	private: System::Windows::Forms::Panel^  mPanel_5_4;
	private: System::Windows::Forms::Panel^  mPanel_5_3;
	private: System::Windows::Forms::Panel^  mPanel_5_2;
	private: System::Windows::Forms::Panel^  mPanel_5_1;
	private: System::Windows::Forms::Panel^  mPanel_5_0;
	private: System::Windows::Forms::Panel^  mPanel_4_6;
	private: System::Windows::Forms::Panel^  mPanel_4_5;
	private: System::Windows::Forms::Panel^  mPanel_4_4;
	private: System::Windows::Forms::Panel^  mPanel_4_3;
	private: System::Windows::Forms::Panel^  mPanel_4_2;
	private: System::Windows::Forms::Panel^  mPanel_4_1;
	private: System::Windows::Forms::Panel^  mPanel_4_0;
	private: System::Windows::Forms::Panel^  mPanel_3_6;
	private: System::Windows::Forms::Panel^  mPanel_3_5;
	private: System::Windows::Forms::Panel^  mPanel_3_4;
	private: System::Windows::Forms::Panel^  mPanel_3_3;
	private: System::Windows::Forms::Panel^  mPanel_3_2;
	private: System::Windows::Forms::Panel^  mPanel_3_1;
	private: System::Windows::Forms::Panel^  mPanel_2_6;
	private: System::Windows::Forms::Panel^  mPanel_2_5;
	private: System::Windows::Forms::Panel^  mPanel_2_4;
	private: System::Windows::Forms::Panel^  mPanel_2_3;
	private: System::Windows::Forms::Panel^  mPanel_2_2;
	private: System::Windows::Forms::Panel^  mPanel_2_1;
	private: System::Windows::Forms::Panel^  mPanel_1_6;
	private: System::Windows::Forms::Panel^  mPanel_1_5;
	private: System::Windows::Forms::Panel^  mPanel_1_4;
	private: System::Windows::Forms::Panel^  mPanel_1_3;
	private: System::Windows::Forms::Panel^  mPanel_1_2;
	private: System::Windows::Forms::Panel^  mPanel_1_1;
	private: System::Windows::Forms::Panel^  mPanel_0_6;
	private: System::Windows::Forms::Panel^  mPanel_0_5;
	private: System::Windows::Forms::Panel^  mPanel_0_4;
	private: System::Windows::Forms::Panel^  mPanel_0_3;
	private: System::Windows::Forms::Panel^  mPanel_0_2;
	private: System::Windows::Forms::Panel^  mPanel_0_1;
	private: System::Windows::Forms::Panel^  mPanel_0_0;
	private: System::Windows::Forms::Panel^  mPanel_1_0;
	private: System::Windows::Forms::Panel^  mPanel_2_0;
	private: System::Windows::Forms::Panel^  mPanel_3_0;
	private: System::Windows::Forms::Panel^  mPanel;
	private: System::Windows::Forms::Panel^  wPanel;
	private: System::Windows::Forms::Panel^  wPanel_0_6;
	private: System::Windows::Forms::Label^  wWDay_0_6;
	private: System::Windows::Forms::Panel^  wPanel_0_5;
	private: System::Windows::Forms::Label^  wWDay_0_5;
	private: System::Windows::Forms::Panel^  wPanel_0_3;
	private: System::Windows::Forms::Label^  wWDay_0_3;
	private: System::Windows::Forms::Panel^  wPanel_0_2;
	private: System::Windows::Forms::Label^  wWDay_0_2;
	private: System::Windows::Forms::Panel^  wPanel_0_1;
	private: System::Windows::Forms::Panel^  wPanel_0_4;
	private: System::Windows::Forms::Label^  wWDay_0_4;
	private: System::Windows::Forms::Label^  wWDay_0_1;
	private: System::Windows::Forms::Panel^  wPanel_body;
	private: System::Windows::Forms::TableLayoutPanel^  weekly_cal_title;
	private: System::Windows::Forms::Panel^  wPanel_head;
	private: System::Windows::Forms::TableLayoutPanel^  weekly_cal;
	private: System::Windows::Forms::Panel^  wPanel_18_0;
	private: System::Windows::Forms::Label^  wHr_18_0;
	private: System::Windows::Forms::Panel^  wPanel_17_0;
	private: System::Windows::Forms::Label^  wHr_17_0;
	private: System::Windows::Forms::Panel^  wPanel_16_0;
	private: System::Windows::Forms::Label^  wHr_16_0;
	private: System::Windows::Forms::Panel^  wPanel_15_0;
	private: System::Windows::Forms::Label^  wHr_15_0;
	private: System::Windows::Forms::Panel^  wPanel_14_0;
	private: System::Windows::Forms::Label^  wHr_14_0;
	private: System::Windows::Forms::Panel^  wPanel_13_0;
	private: System::Windows::Forms::Label^  wHr_13_0;
	private: System::Windows::Forms::Panel^  wPanel_12_0;
	private: System::Windows::Forms::Label^  wHr_12_0;
	private: System::Windows::Forms::Panel^  wPanel_11_0;
	private: System::Windows::Forms::Label^  wHr_11_0;
	private: System::Windows::Forms::Panel^  wPanel_10_0;
	private: System::Windows::Forms::Label^  wHr_10_0;
	private: System::Windows::Forms::Panel^  wPanel_9_0;
	private: System::Windows::Forms::Label^  wHr_9_0;
	private: System::Windows::Forms::Panel^  wPanel_8_0;
	private: System::Windows::Forms::Label^  wHr_8_0;
	private: System::Windows::Forms::Panel^  wPanel_7_0;
	private: System::Windows::Forms::Label^  wHr_7_0;
	private: System::Windows::Forms::Panel^  wPanel_6_0;
	private: System::Windows::Forms::Label^  wHr_6_0;
	private: System::Windows::Forms::Panel^  wPanel_4_0;
	private: System::Windows::Forms::Label^  wHr_4_0;
	private: System::Windows::Forms::Panel^  wPanel_2_0;
	private: System::Windows::Forms::Label^  wHr_2_0;
	private: System::Windows::Forms::Panel^  wPanel_3_0;
	private: System::Windows::Forms::Label^  wHr_3_0;
	private: System::Windows::Forms::Panel^  wPanel_5_0;
	private: System::Windows::Forms::Label^  wHr_5_0;
	private: System::Windows::Forms::Panel^  wPanel_24_0;
	private: System::Windows::Forms::Label^  wHr_24_0;
	private: System::Windows::Forms::Panel^  wPanel_23_0;
	private: System::Windows::Forms::Label^  wHr_23_0;
	private: System::Windows::Forms::Panel^  wPanel_22_0;
	private: System::Windows::Forms::Label^  wHr_22_0;
	private: System::Windows::Forms::Panel^  wPanel_21_0;
	private: System::Windows::Forms::Label^  wHr_21_0;
	private: System::Windows::Forms::Panel^  wPanel_20_0;
	private: System::Windows::Forms::Label^  wHr_20_0;
	private: System::Windows::Forms::Panel^  wPanel_19_0;
	private: System::Windows::Forms::Label^  wHr_19_0;
	private: System::Windows::Forms::Panel^  wPanel_1_0;
	private: System::Windows::Forms::Label^  wHr_1_0;
	private: System::Windows::Forms::Panel^  wBtmLine;
	private: System::Windows::Forms::Panel^  wTopLine;
	private: System::Windows::Forms::TextBox^  display_week;
	private: System::Windows::Forms::TableLayoutPanel^  info_layout;
	private: System::Windows::Forms::Panel^  wPanel_1_7;
	private: System::Windows::Forms::Panel^  wPanel_1_6;
	private: System::Windows::Forms::Panel^  wPanel_1_5;
	private: System::Windows::Forms::Panel^  wPanel_1_4;
	private: System::Windows::Forms::Panel^  wPanel_1_3;
	private: System::Windows::Forms::Panel^  wPanel_1_2;
	private: System::Windows::Forms::Panel^  wPanel_1_1;
	private: System::Windows::Forms::Panel^  dPanel;
	private: System::Windows::Forms::TableLayoutPanel^  daily_monthly_cal;
	private: System::Windows::Forms::Label^  dWDay;
	private: System::Windows::Forms::Label^  dDay;
	private: System::Windows::Forms::Panel^  dPanel_body;
	private: System::Windows::Forms::TableLayoutPanel^  daily_cal;
	private: System::Windows::Forms::Panel^  dPanel_17_0;
	private: System::Windows::Forms::Label^  dHr_17_0;
	private: System::Windows::Forms::Panel^  dPanel_16_0;
	private: System::Windows::Forms::Label^  dHr_16_0;
	private: System::Windows::Forms::Panel^  dPanel_15_0;
	private: System::Windows::Forms::Label^  dHr_15_0;
	private: System::Windows::Forms::Panel^  dPanel_14_0;
	private: System::Windows::Forms::Label^  dHr_14_0;
	private: System::Windows::Forms::Panel^  dPanel_13_0;
	private: System::Windows::Forms::Label^  dHr_13_0;
	private: System::Windows::Forms::Panel^  dPanel_12_0;
	private: System::Windows::Forms::Label^  dHr_12_0;
	private: System::Windows::Forms::Panel^  dPanel_11_0;
	private: System::Windows::Forms::Label^  dHr_11_0;
	private: System::Windows::Forms::Panel^  dPanel_10_0;
	private: System::Windows::Forms::Label^  dHr_10_0;
	private: System::Windows::Forms::Panel^  dPanel_9_0;
	private: System::Windows::Forms::Label^  dHr_9_0;
	private: System::Windows::Forms::Panel^  dPanel_8_0;
	private: System::Windows::Forms::Label^  dHr_8_0;
	private: System::Windows::Forms::Panel^  dPanel_7_0;
	private: System::Windows::Forms::Label^  dHr_7_0;
	private: System::Windows::Forms::Panel^  dPanel_6_0;
	private: System::Windows::Forms::Label^  dHr_6_0;
	private: System::Windows::Forms::Panel^  dPanel_5_0;
	private: System::Windows::Forms::Label^  dHr_5_0;
	private: System::Windows::Forms::Panel^  dPanel_3_0;
	private: System::Windows::Forms::Label^  dHr_3_0;
	private: System::Windows::Forms::Panel^  dPanel_1_0;
	private: System::Windows::Forms::Label^  dHr_1_0;
	private: System::Windows::Forms::Panel^  dPanel_2_0;
	private: System::Windows::Forms::Label^  dHr_2_0;
	private: System::Windows::Forms::Panel^  dPanel_4_0;
	private: System::Windows::Forms::Label^  dHr_4_0;
	private: System::Windows::Forms::Panel^  dPanel_23_0;
	private: System::Windows::Forms::Label^  dHr_23_0;
	private: System::Windows::Forms::Panel^  dPanel_22_0;
	private: System::Windows::Forms::Label^  dHr_22_0;
	private: System::Windows::Forms::Panel^  dPanel_21_0;
	private: System::Windows::Forms::Label^  dHr_21_0;
	private: System::Windows::Forms::Panel^  dPanel_20_0;
	private: System::Windows::Forms::Label^  dHr_20_0;
	private: System::Windows::Forms::Panel^  dPanel_19_0;
	private: System::Windows::Forms::Label^  dHr_19_0;
	private: System::Windows::Forms::Panel^  dPanel_18_0;
	private: System::Windows::Forms::Label^  dHr_18_0;
	private: System::Windows::Forms::Panel^  dPanel_0_0;
	private: System::Windows::Forms::Label^  dHr_0_0;
	private: System::Windows::Forms::Panel^  dPanel_0_1;
	private: System::Windows::Forms::Panel^  wPanel_0_7;
	private: System::Windows::Forms::Label^  wWDay_0_7;
	private: System::Windows::Forms::Panel^  dBtmLine;
	private: System::Windows::Forms::Panel^  dTopLine;
	private: System::Windows::Forms::Panel^  dMPanel_5_6;
	private: System::Windows::Forms::Panel^  dMPanel_5_5;
	private: System::Windows::Forms::Panel^  dMPanel_5_4;
	private: System::Windows::Forms::Panel^  dMPanel_5_3;
	private: System::Windows::Forms::Panel^  dMPanel_5_2;
	private: System::Windows::Forms::Panel^  dMPanel_5_1;
	private: System::Windows::Forms::Panel^  dMPanel_5_0;
	private: System::Windows::Forms::Panel^  dMPanel_4_6;
	private: System::Windows::Forms::Panel^  dMPanel_4_5;
	private: System::Windows::Forms::Panel^  dMPanel_4_4;
	private: System::Windows::Forms::Panel^  dMPanel_4_3;
	private: System::Windows::Forms::Panel^  dMPanel_4_2;
	private: System::Windows::Forms::Panel^  dMPanel_4_1;
	private: System::Windows::Forms::Panel^  dMPanel_4_0;
	private: System::Windows::Forms::Panel^  dMPanel_3_6;
	private: System::Windows::Forms::Panel^  dMPanel_3_5;
	private: System::Windows::Forms::Panel^  dMPanel_3_4;
	private: System::Windows::Forms::Panel^  dMPanel_3_3;
	private: System::Windows::Forms::Panel^  dMPanel_3_2;
	private: System::Windows::Forms::Panel^  dMPanel_3_1;
	private: System::Windows::Forms::Panel^  dMPanel_3_0;
	private: System::Windows::Forms::Panel^  dMPanel_2_6;
	private: System::Windows::Forms::Label^  dDay_2_6;
	private: System::Windows::Forms::Panel^  dMPanel_2_5;
	private: System::Windows::Forms::Label^  dDay_2_5;
	private: System::Windows::Forms::Panel^  dMPanel_2_4;
	private: System::Windows::Forms::Label^  dDay_2_4;
	private: System::Windows::Forms::Panel^  dMPanel_2_3;
	private: System::Windows::Forms::Label^  dDay_2_3;
	private: System::Windows::Forms::Panel^  dMPanel_2_2;
	private: System::Windows::Forms::Label^  dDay_2_2;
	private: System::Windows::Forms::Panel^  dMPanel_2_1;
	private: System::Windows::Forms::Label^  dDay_2_1;
	private: System::Windows::Forms::Panel^  dMPanel_2_0;
	private: System::Windows::Forms::Label^  dDay_2_0;
	private: System::Windows::Forms::Panel^  dMPanel_1_6;
	private: System::Windows::Forms::Label^  dDay_1_6;
	private: System::Windows::Forms::Panel^  dMPanel_1_5;
	private: System::Windows::Forms::Label^  dDay_1_5;
	private: System::Windows::Forms::Panel^  dMPanel_1_4;
	private: System::Windows::Forms::Label^  dDay_1_4;
	private: System::Windows::Forms::Panel^  dMPanel_1_3;
	private: System::Windows::Forms::Label^  dDay_1_3;
	private: System::Windows::Forms::Panel^  dMPanel_1_2;
	private: System::Windows::Forms::Label^  dDay_1_2;
	private: System::Windows::Forms::Panel^  dMPanel_1_1;
	private: System::Windows::Forms::Label^  dDay_1_1;
	private: System::Windows::Forms::Panel^  dMPanel_1_0;
	private: System::Windows::Forms::Label^  dDay_1_0;
	private: System::Windows::Forms::Panel^  dMPanel_0_6;
	private: System::Windows::Forms::Label^  dWDay_6;
	private: System::Windows::Forms::Panel^  dMPanel_0_5;
	private: System::Windows::Forms::Label^  dWDay_5;
	private: System::Windows::Forms::Panel^  dMPanel_0_4;
	private: System::Windows::Forms::Label^  dWDay_4;
	private: System::Windows::Forms::Panel^  dMPanel_0_3;
	private: System::Windows::Forms::Label^  dWDay_3;
	private: System::Windows::Forms::Panel^  dMPanel_0_2;
	private: System::Windows::Forms::Label^  dWDay_2;
	private: System::Windows::Forms::Panel^  dMPanel_0_1;
	private: System::Windows::Forms::Label^  dWDay_1;
	private: System::Windows::Forms::Panel^  dMPanel_0_0;
	private: System::Windows::Forms::Label^  dWDay_0;
	private: System::Windows::Forms::Label^  dDay_5_6;
	private: System::Windows::Forms::Label^  dDay_5_5;
	private: System::Windows::Forms::Label^  dDay_5_4;
	private: System::Windows::Forms::Label^  dDay_5_3;
	private: System::Windows::Forms::Label^  dDay_5_2;
	private: System::Windows::Forms::Label^  dDay_5_1;
	private: System::Windows::Forms::Label^  dDay_5_0;
	private: System::Windows::Forms::Label^  dDay_4_6;
	private: System::Windows::Forms::Label^  dDay_4_5;
	private: System::Windows::Forms::Label^  dDay_4_4;
	private: System::Windows::Forms::Label^  dDay_4_3;
	private: System::Windows::Forms::Label^  dDay_4_2;
	private: System::Windows::Forms::Label^  dDay_4_1;
	private: System::Windows::Forms::Label^  dDay_4_0;
	private: System::Windows::Forms::Label^  dDay_3_6;
	private: System::Windows::Forms::Label^  dDay_3_5;
	private: System::Windows::Forms::Label^  dDay_3_4;
	private: System::Windows::Forms::Label^  dDay_3_3;
	private: System::Windows::Forms::Label^  dDay_3_2;
	private: System::Windows::Forms::Label^  dDay_3_1;
	private: System::Windows::Forms::Label^  dDay_3_0;
	private: System::Windows::Forms::Panel^  dMPanel_6_2;
	private: System::Windows::Forms::Label^  dDay_6_2;
	private: System::Windows::Forms::Panel^  dMPanel_6_1;
	private: System::Windows::Forms::Label^  dDay_6_1;
	private: System::Windows::Forms::Panel^  dMPanel_6_0;
	private: System::Windows::Forms::Label^  dDay_6_0;
	private: System::Windows::Forms::Panel^  dMPanel_6_3;
	private: System::Windows::Forms::Label^  dDay_6_3;
	private: System::Windows::Forms::Panel^  dMPanel_6_6;
	private: System::Windows::Forms::Label^  dDay_6_6;
	private: System::Windows::Forms::Panel^  dMPanel_6_5;
	private: System::Windows::Forms::Label^  dDay_6_5;
	private: System::Windows::Forms::Panel^  dMPanel_6_4;
	private: System::Windows::Forms::Label^  dDay_6_4;
	private: System::Windows::Forms::TextBox^  display_day;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
				 this->monthly_cal = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->mPanel_6_6 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_6_6 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_6_5 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_6_5 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_6_4 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_6_4 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_6_3 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_6_3 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_6_2 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_6_2 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_6_1 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_6_1 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_6_0 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_6_0 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_5_6 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_5_6 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_5_5 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_5_5 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_5_4 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_5_4 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_5_3 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_5_3 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_5_2 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_5_2 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_5_1 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_5_1 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_5_0 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_5_0 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_4_6 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_4_6 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_4_5 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_4_5 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_4_4 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_4_4 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_4_3 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_4_3 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_4_2 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_4_2 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_4_1 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_4_1 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_4_0 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_4_0 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_3_6 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_3_6 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_3_5 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_3_5 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_3_4 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_3_4 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_3_3 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_3_3 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_3_2 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_3_2 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_3_1 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_3_1 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_2_6 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_2_6 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_2_5 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_2_5 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_2_4 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_2_4 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_2_3 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_2_3 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_2_2 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_2_2 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_2_1 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_2_1 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_1_6 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_1_6 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_1_5 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_1_5 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_1_4 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_1_4 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_1_3 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_1_3 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_1_2 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_1_2 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_1_1 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_1_1 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_0_6 = (gcnew System::Windows::Forms::Panel());
				 this->mWDay_6 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_0_5 = (gcnew System::Windows::Forms::Panel());
				 this->mWDay_5 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_0_4 = (gcnew System::Windows::Forms::Panel());
				 this->mWDay_4 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_0_3 = (gcnew System::Windows::Forms::Panel());
				 this->mWDay_3 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_0_2 = (gcnew System::Windows::Forms::Panel());
				 this->mWDay_2 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_0_1 = (gcnew System::Windows::Forms::Panel());
				 this->mWDay_1 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_0_0 = (gcnew System::Windows::Forms::Panel());
				 this->mWDay_0 = (gcnew System::Windows::Forms::ComboBox());
				 this->mPanel_1_0 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_1_0 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_2_0 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_2_0 = (gcnew System::Windows::Forms::Label());
				 this->mPanel_3_0 = (gcnew System::Windows::Forms::Panel());
				 this->mDay_3_0 = (gcnew System::Windows::Forms::Label());
				 this->display_year = (gcnew System::Windows::Forms::TextBox());
				 this->display_month = (gcnew System::Windows::Forms::TextBox());
				 this->prev_btn = (gcnew System::Windows::Forms::Button());
				 this->next_btn = (gcnew System::Windows::Forms::Button());
				 this->monthly_type = (gcnew System::Windows::Forms::Button());
				 this->weekly_type = (gcnew System::Windows::Forms::Button());
				 this->daily_type = (gcnew System::Windows::Forms::Button());
				 this->now_btn = (gcnew System::Windows::Forms::Button());
				 this->mPanel = (gcnew System::Windows::Forms::Panel());
				 this->wPanel = (gcnew System::Windows::Forms::Panel());
				 this->wBtmLine = (gcnew System::Windows::Forms::Panel());
				 this->wTopLine = (gcnew System::Windows::Forms::Panel());
				 this->wPanel_head = (gcnew System::Windows::Forms::Panel());
				 this->weekly_cal_title = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->wPanel_0_1 = (gcnew System::Windows::Forms::Panel());
				 this->wWDay_0_1 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_0_2 = (gcnew System::Windows::Forms::Panel());
				 this->wWDay_0_2 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_0_3 = (gcnew System::Windows::Forms::Panel());
				 this->wWDay_0_3 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_0_4 = (gcnew System::Windows::Forms::Panel());
				 this->wWDay_0_4 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_0_5 = (gcnew System::Windows::Forms::Panel());
				 this->wWDay_0_5 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_0_6 = (gcnew System::Windows::Forms::Panel());
				 this->wWDay_0_6 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_0_7 = (gcnew System::Windows::Forms::Panel());
				 this->wWDay_0_7 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_body = (gcnew System::Windows::Forms::Panel());
				 this->weekly_cal = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->wPanel_1_7 = (gcnew System::Windows::Forms::Panel());
				 this->wPanel_1_6 = (gcnew System::Windows::Forms::Panel());
				 this->wPanel_1_5 = (gcnew System::Windows::Forms::Panel());
				 this->wPanel_1_4 = (gcnew System::Windows::Forms::Panel());
				 this->wPanel_1_3 = (gcnew System::Windows::Forms::Panel());
				 this->wPanel_1_2 = (gcnew System::Windows::Forms::Panel());
				 this->wPanel_18_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_18_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_17_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_17_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_16_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_16_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_15_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_15_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_14_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_14_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_13_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_13_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_12_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_12_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_11_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_11_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_10_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_10_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_9_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_9_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_8_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_8_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_7_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_7_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_6_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_6_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_4_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_4_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_2_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_2_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_3_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_3_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_5_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_5_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_24_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_24_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_23_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_23_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_22_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_22_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_21_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_21_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_20_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_20_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_19_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_19_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_1_0 = (gcnew System::Windows::Forms::Panel());
				 this->wHr_1_0 = (gcnew System::Windows::Forms::Label());
				 this->wPanel_1_1 = (gcnew System::Windows::Forms::Panel());
				 this->dPanel = (gcnew System::Windows::Forms::Panel());
				 this->daily_monthly_cal = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->dMPanel_6_2 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_6_2 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_6_1 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_6_1 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_6_0 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_6_0 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_6_3 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_6_3 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_6_6 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_6_6 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_6_5 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_6_5 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_6_4 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_6_4 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_5_6 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_5_6 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_5_5 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_5_5 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_5_4 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_5_4 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_5_3 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_5_3 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_5_2 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_5_2 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_5_1 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_5_1 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_5_0 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_5_0 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_4_6 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_4_6 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_4_5 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_4_5 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_4_4 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_4_4 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_4_3 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_4_3 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_4_2 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_4_2 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_4_1 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_4_1 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_4_0 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_4_0 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_3_6 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_3_6 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_3_5 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_3_5 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_3_4 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_3_4 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_3_3 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_3_3 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_3_2 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_3_2 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_3_1 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_3_1 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_3_0 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_3_0 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_2_6 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_2_6 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_2_5 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_2_5 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_2_4 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_2_4 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_2_3 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_2_3 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_2_2 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_2_2 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_2_1 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_2_1 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_2_0 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_2_0 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_1_6 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_1_6 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_1_5 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_1_5 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_1_4 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_1_4 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_1_3 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_1_3 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_1_2 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_1_2 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_1_1 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_1_1 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_1_0 = (gcnew System::Windows::Forms::Panel());
				 this->dDay_1_0 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_0_6 = (gcnew System::Windows::Forms::Panel());
				 this->dWDay_6 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_0_5 = (gcnew System::Windows::Forms::Panel());
				 this->dWDay_5 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_0_4 = (gcnew System::Windows::Forms::Panel());
				 this->dWDay_4 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_0_3 = (gcnew System::Windows::Forms::Panel());
				 this->dWDay_3 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_0_2 = (gcnew System::Windows::Forms::Panel());
				 this->dWDay_2 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_0_1 = (gcnew System::Windows::Forms::Panel());
				 this->dWDay_1 = (gcnew System::Windows::Forms::Label());
				 this->dMPanel_0_0 = (gcnew System::Windows::Forms::Panel());
				 this->dWDay_0 = (gcnew System::Windows::Forms::Label());
				 this->dWDay = (gcnew System::Windows::Forms::Label());
				 this->dDay = (gcnew System::Windows::Forms::Label());
				 this->dBtmLine = (gcnew System::Windows::Forms::Panel());
				 this->dTopLine = (gcnew System::Windows::Forms::Panel());
				 this->dPanel_body = (gcnew System::Windows::Forms::Panel());
				 this->daily_cal = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->dPanel_17_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_17_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_16_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_16_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_15_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_15_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_14_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_14_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_13_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_13_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_12_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_12_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_11_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_11_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_10_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_10_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_9_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_9_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_8_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_8_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_7_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_7_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_6_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_6_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_5_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_5_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_3_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_3_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_1_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_1_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_2_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_2_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_4_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_4_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_23_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_23_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_22_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_22_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_21_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_21_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_20_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_20_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_19_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_19_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_18_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_18_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_0_0 = (gcnew System::Windows::Forms::Panel());
				 this->dHr_0_0 = (gcnew System::Windows::Forms::Label());
				 this->dPanel_0_1 = (gcnew System::Windows::Forms::Panel());
				 this->display_week = (gcnew System::Windows::Forms::TextBox());
				 this->info_layout = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->display_day = (gcnew System::Windows::Forms::TextBox());
				 this->select_day_layout = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->type_layout = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->stat_btn = (gcnew System::Windows::Forms::Button());
				 this->monthly_cal->SuspendLayout();
				 this->mPanel_6_6->SuspendLayout();
				 this->mPanel_6_5->SuspendLayout();
				 this->mPanel_6_4->SuspendLayout();
				 this->mPanel_6_3->SuspendLayout();
				 this->mPanel_6_2->SuspendLayout();
				 this->mPanel_6_1->SuspendLayout();
				 this->mPanel_6_0->SuspendLayout();
				 this->mPanel_5_6->SuspendLayout();
				 this->mPanel_5_5->SuspendLayout();
				 this->mPanel_5_4->SuspendLayout();
				 this->mPanel_5_3->SuspendLayout();
				 this->mPanel_5_2->SuspendLayout();
				 this->mPanel_5_1->SuspendLayout();
				 this->mPanel_5_0->SuspendLayout();
				 this->mPanel_4_6->SuspendLayout();
				 this->mPanel_4_5->SuspendLayout();
				 this->mPanel_4_4->SuspendLayout();
				 this->mPanel_4_3->SuspendLayout();
				 this->mPanel_4_2->SuspendLayout();
				 this->mPanel_4_1->SuspendLayout();
				 this->mPanel_4_0->SuspendLayout();
				 this->mPanel_3_6->SuspendLayout();
				 this->mPanel_3_5->SuspendLayout();
				 this->mPanel_3_4->SuspendLayout();
				 this->mPanel_3_3->SuspendLayout();
				 this->mPanel_3_2->SuspendLayout();
				 this->mPanel_3_1->SuspendLayout();
				 this->mPanel_2_6->SuspendLayout();
				 this->mPanel_2_5->SuspendLayout();
				 this->mPanel_2_4->SuspendLayout();
				 this->mPanel_2_3->SuspendLayout();
				 this->mPanel_2_2->SuspendLayout();
				 this->mPanel_2_1->SuspendLayout();
				 this->mPanel_1_6->SuspendLayout();
				 this->mPanel_1_5->SuspendLayout();
				 this->mPanel_1_4->SuspendLayout();
				 this->mPanel_1_3->SuspendLayout();
				 this->mPanel_1_2->SuspendLayout();
				 this->mPanel_1_1->SuspendLayout();
				 this->mPanel_0_6->SuspendLayout();
				 this->mPanel_0_5->SuspendLayout();
				 this->mPanel_0_4->SuspendLayout();
				 this->mPanel_0_3->SuspendLayout();
				 this->mPanel_0_2->SuspendLayout();
				 this->mPanel_0_1->SuspendLayout();
				 this->mPanel_0_0->SuspendLayout();
				 this->mPanel_1_0->SuspendLayout();
				 this->mPanel_2_0->SuspendLayout();
				 this->mPanel_3_0->SuspendLayout();
				 this->mPanel->SuspendLayout();
				 this->wPanel->SuspendLayout();
				 this->wPanel_head->SuspendLayout();
				 this->weekly_cal_title->SuspendLayout();
				 this->wPanel_0_1->SuspendLayout();
				 this->wPanel_0_2->SuspendLayout();
				 this->wPanel_0_3->SuspendLayout();
				 this->wPanel_0_4->SuspendLayout();
				 this->wPanel_0_5->SuspendLayout();
				 this->wPanel_0_6->SuspendLayout();
				 this->wPanel_0_7->SuspendLayout();
				 this->wPanel_body->SuspendLayout();
				 this->weekly_cal->SuspendLayout();
				 this->wPanel_18_0->SuspendLayout();
				 this->wPanel_17_0->SuspendLayout();
				 this->wPanel_16_0->SuspendLayout();
				 this->wPanel_15_0->SuspendLayout();
				 this->wPanel_14_0->SuspendLayout();
				 this->wPanel_13_0->SuspendLayout();
				 this->wPanel_12_0->SuspendLayout();
				 this->wPanel_11_0->SuspendLayout();
				 this->wPanel_10_0->SuspendLayout();
				 this->wPanel_9_0->SuspendLayout();
				 this->wPanel_8_0->SuspendLayout();
				 this->wPanel_7_0->SuspendLayout();
				 this->wPanel_6_0->SuspendLayout();
				 this->wPanel_4_0->SuspendLayout();
				 this->wPanel_2_0->SuspendLayout();
				 this->wPanel_3_0->SuspendLayout();
				 this->wPanel_5_0->SuspendLayout();
				 this->wPanel_24_0->SuspendLayout();
				 this->wPanel_23_0->SuspendLayout();
				 this->wPanel_22_0->SuspendLayout();
				 this->wPanel_21_0->SuspendLayout();
				 this->wPanel_20_0->SuspendLayout();
				 this->wPanel_19_0->SuspendLayout();
				 this->wPanel_1_0->SuspendLayout();
				 this->dPanel->SuspendLayout();
				 this->daily_monthly_cal->SuspendLayout();
				 this->dMPanel_6_2->SuspendLayout();
				 this->dMPanel_6_1->SuspendLayout();
				 this->dMPanel_6_0->SuspendLayout();
				 this->dMPanel_6_3->SuspendLayout();
				 this->dMPanel_6_6->SuspendLayout();
				 this->dMPanel_6_5->SuspendLayout();
				 this->dMPanel_6_4->SuspendLayout();
				 this->dMPanel_5_6->SuspendLayout();
				 this->dMPanel_5_5->SuspendLayout();
				 this->dMPanel_5_4->SuspendLayout();
				 this->dMPanel_5_3->SuspendLayout();
				 this->dMPanel_5_2->SuspendLayout();
				 this->dMPanel_5_1->SuspendLayout();
				 this->dMPanel_5_0->SuspendLayout();
				 this->dMPanel_4_6->SuspendLayout();
				 this->dMPanel_4_5->SuspendLayout();
				 this->dMPanel_4_4->SuspendLayout();
				 this->dMPanel_4_3->SuspendLayout();
				 this->dMPanel_4_2->SuspendLayout();
				 this->dMPanel_4_1->SuspendLayout();
				 this->dMPanel_4_0->SuspendLayout();
				 this->dMPanel_3_6->SuspendLayout();
				 this->dMPanel_3_5->SuspendLayout();
				 this->dMPanel_3_4->SuspendLayout();
				 this->dMPanel_3_3->SuspendLayout();
				 this->dMPanel_3_2->SuspendLayout();
				 this->dMPanel_3_1->SuspendLayout();
				 this->dMPanel_3_0->SuspendLayout();
				 this->dMPanel_2_6->SuspendLayout();
				 this->dMPanel_2_5->SuspendLayout();
				 this->dMPanel_2_4->SuspendLayout();
				 this->dMPanel_2_3->SuspendLayout();
				 this->dMPanel_2_2->SuspendLayout();
				 this->dMPanel_2_1->SuspendLayout();
				 this->dMPanel_2_0->SuspendLayout();
				 this->dMPanel_1_6->SuspendLayout();
				 this->dMPanel_1_5->SuspendLayout();
				 this->dMPanel_1_4->SuspendLayout();
				 this->dMPanel_1_3->SuspendLayout();
				 this->dMPanel_1_2->SuspendLayout();
				 this->dMPanel_1_1->SuspendLayout();
				 this->dMPanel_1_0->SuspendLayout();
				 this->dMPanel_0_6->SuspendLayout();
				 this->dMPanel_0_5->SuspendLayout();
				 this->dMPanel_0_4->SuspendLayout();
				 this->dMPanel_0_3->SuspendLayout();
				 this->dMPanel_0_2->SuspendLayout();
				 this->dMPanel_0_1->SuspendLayout();
				 this->dMPanel_0_0->SuspendLayout();
				 this->dPanel_body->SuspendLayout();
				 this->daily_cal->SuspendLayout();
				 this->dPanel_17_0->SuspendLayout();
				 this->dPanel_16_0->SuspendLayout();
				 this->dPanel_15_0->SuspendLayout();
				 this->dPanel_14_0->SuspendLayout();
				 this->dPanel_13_0->SuspendLayout();
				 this->dPanel_12_0->SuspendLayout();
				 this->dPanel_11_0->SuspendLayout();
				 this->dPanel_10_0->SuspendLayout();
				 this->dPanel_9_0->SuspendLayout();
				 this->dPanel_8_0->SuspendLayout();
				 this->dPanel_7_0->SuspendLayout();
				 this->dPanel_6_0->SuspendLayout();
				 this->dPanel_5_0->SuspendLayout();
				 this->dPanel_3_0->SuspendLayout();
				 this->dPanel_1_0->SuspendLayout();
				 this->dPanel_2_0->SuspendLayout();
				 this->dPanel_4_0->SuspendLayout();
				 this->dPanel_23_0->SuspendLayout();
				 this->dPanel_22_0->SuspendLayout();
				 this->dPanel_21_0->SuspendLayout();
				 this->dPanel_20_0->SuspendLayout();
				 this->dPanel_19_0->SuspendLayout();
				 this->dPanel_18_0->SuspendLayout();
				 this->dPanel_0_0->SuspendLayout();
				 this->info_layout->SuspendLayout();
				 this->select_day_layout->SuspendLayout();
				 this->type_layout->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // monthly_cal
				 // 
				 this->monthly_cal->AutoSize = true;
				 this->monthly_cal->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->monthly_cal->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->monthly_cal->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->monthly_cal->ColumnCount = 7;
				 this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 180)));
				 this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 180)));
				 this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 180)));
				 this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 180)));
				 this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 180)));
				 this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 180)));
				 this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 180)));
				 this->monthly_cal->Controls->Add(this->mPanel_6_6, 6, 6);
				 this->monthly_cal->Controls->Add(this->mPanel_6_5, 5, 6);
				 this->monthly_cal->Controls->Add(this->mPanel_6_4, 4, 6);
				 this->monthly_cal->Controls->Add(this->mPanel_6_3, 3, 6);
				 this->monthly_cal->Controls->Add(this->mPanel_6_2, 2, 6);
				 this->monthly_cal->Controls->Add(this->mPanel_6_1, 1, 6);
				 this->monthly_cal->Controls->Add(this->mPanel_6_0, 0, 6);
				 this->monthly_cal->Controls->Add(this->mPanel_5_6, 6, 5);
				 this->monthly_cal->Controls->Add(this->mPanel_5_5, 5, 5);
				 this->monthly_cal->Controls->Add(this->mPanel_5_4, 4, 5);
				 this->monthly_cal->Controls->Add(this->mPanel_5_3, 3, 5);
				 this->monthly_cal->Controls->Add(this->mPanel_5_2, 2, 5);
				 this->monthly_cal->Controls->Add(this->mPanel_5_1, 1, 5);
				 this->monthly_cal->Controls->Add(this->mPanel_5_0, 0, 5);
				 this->monthly_cal->Controls->Add(this->mPanel_4_6, 6, 4);
				 this->monthly_cal->Controls->Add(this->mPanel_4_5, 5, 4);
				 this->monthly_cal->Controls->Add(this->mPanel_4_4, 4, 4);
				 this->monthly_cal->Controls->Add(this->mPanel_4_3, 3, 4);
				 this->monthly_cal->Controls->Add(this->mPanel_4_2, 2, 4);
				 this->monthly_cal->Controls->Add(this->mPanel_4_1, 1, 4);
				 this->monthly_cal->Controls->Add(this->mPanel_4_0, 0, 4);
				 this->monthly_cal->Controls->Add(this->mPanel_3_6, 6, 3);
				 this->monthly_cal->Controls->Add(this->mPanel_3_5, 5, 3);
				 this->monthly_cal->Controls->Add(this->mPanel_3_4, 4, 3);
				 this->monthly_cal->Controls->Add(this->mPanel_3_3, 3, 3);
				 this->monthly_cal->Controls->Add(this->mPanel_3_2, 2, 3);
				 this->monthly_cal->Controls->Add(this->mPanel_3_1, 1, 3);
				 this->monthly_cal->Controls->Add(this->mPanel_2_6, 6, 2);
				 this->monthly_cal->Controls->Add(this->mPanel_2_5, 5, 2);
				 this->monthly_cal->Controls->Add(this->mPanel_2_4, 4, 2);
				 this->monthly_cal->Controls->Add(this->mPanel_2_3, 3, 2);
				 this->monthly_cal->Controls->Add(this->mPanel_2_2, 2, 2);
				 this->monthly_cal->Controls->Add(this->mPanel_2_1, 1, 2);
				 this->monthly_cal->Controls->Add(this->mPanel_1_6, 6, 1);
				 this->monthly_cal->Controls->Add(this->mPanel_1_5, 5, 1);
				 this->monthly_cal->Controls->Add(this->mPanel_1_4, 4, 1);
				 this->monthly_cal->Controls->Add(this->mPanel_1_3, 3, 1);
				 this->monthly_cal->Controls->Add(this->mPanel_1_2, 2, 1);
				 this->monthly_cal->Controls->Add(this->mPanel_1_1, 1, 1);
				 this->monthly_cal->Controls->Add(this->mPanel_0_6, 6, 0);
				 this->monthly_cal->Controls->Add(this->mPanel_0_5, 5, 0);
				 this->monthly_cal->Controls->Add(this->mPanel_0_4, 4, 0);
				 this->monthly_cal->Controls->Add(this->mPanel_0_3, 3, 0);
				 this->monthly_cal->Controls->Add(this->mPanel_0_2, 2, 0);
				 this->monthly_cal->Controls->Add(this->mPanel_0_1, 1, 0);
				 this->monthly_cal->Controls->Add(this->mPanel_0_0, 0, 0);
				 this->monthly_cal->Controls->Add(this->mPanel_1_0, 0, 1);
				 this->monthly_cal->Controls->Add(this->mPanel_2_0, 0, 2);
				 this->monthly_cal->Controls->Add(this->mPanel_3_0, 0, 3);
				 this->monthly_cal->Location = System::Drawing::Point(58, 0);
				 this->monthly_cal->Margin = System::Windows::Forms::Padding(0);
				 this->monthly_cal->Name = L"monthly_cal";
				 this->monthly_cal->RowCount = 7;
				 this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 40)));
				 this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 138)));
				 this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 138)));
				 this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 138)));
				 this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 138)));
				 this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 138)));
				 this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 138)));
				 this->monthly_cal->Size = System::Drawing::Size(1268, 876);
				 this->monthly_cal->TabIndex = 1;
				 // 
				 // mPanel_6_6
				 // 
				 this->mPanel_6_6->Controls->Add(this->mDay_6_6);
				 this->mPanel_6_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_6_6->Location = System::Drawing::Point(1087, 737);
				 this->mPanel_6_6->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_6_6->Name = L"mPanel_6_6";
				 this->mPanel_6_6->Size = System::Drawing::Size(180, 138);
				 this->mPanel_6_6->TabIndex = 97;
				 this->mPanel_6_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_6_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_6_6
				 // 
				 this->mDay_6_6->AutoSize = true;
				 this->mDay_6_6->Location = System::Drawing::Point(3, 5);
				 this->mDay_6_6->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_6_6->Name = L"mDay_6_6";
				 this->mDay_6_6->Size = System::Drawing::Size(51, 20);
				 this->mDay_6_6->TabIndex = 48;
				 this->mDay_6_6->Text = L"label7";
				 this->mDay_6_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_6_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_6_5
				 // 
				 this->mPanel_6_5->Controls->Add(this->mDay_6_5);
				 this->mPanel_6_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_6_5->Location = System::Drawing::Point(906, 737);
				 this->mPanel_6_5->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_6_5->Name = L"mPanel_6_5";
				 this->mPanel_6_5->Size = System::Drawing::Size(180, 138);
				 this->mPanel_6_5->TabIndex = 96;
				 this->mPanel_6_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_6_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_6_5
				 // 
				 this->mDay_6_5->AutoSize = true;
				 this->mDay_6_5->Location = System::Drawing::Point(3, 5);
				 this->mDay_6_5->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_6_5->Name = L"mDay_6_5";
				 this->mDay_6_5->Size = System::Drawing::Size(51, 20);
				 this->mDay_6_5->TabIndex = 47;
				 this->mDay_6_5->Text = L"label6";
				 this->mDay_6_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_6_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_6_4
				 // 
				 this->mPanel_6_4->Controls->Add(this->mDay_6_4);
				 this->mPanel_6_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_6_4->Location = System::Drawing::Point(725, 737);
				 this->mPanel_6_4->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_6_4->Name = L"mPanel_6_4";
				 this->mPanel_6_4->Size = System::Drawing::Size(180, 138);
				 this->mPanel_6_4->TabIndex = 95;
				 this->mPanel_6_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_6_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_6_4
				 // 
				 this->mDay_6_4->AutoSize = true;
				 this->mDay_6_4->Location = System::Drawing::Point(3, 5);
				 this->mDay_6_4->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_6_4->Name = L"mDay_6_4";
				 this->mDay_6_4->Size = System::Drawing::Size(51, 20);
				 this->mDay_6_4->TabIndex = 46;
				 this->mDay_6_4->Text = L"label5";
				 this->mDay_6_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_6_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_6_3
				 // 
				 this->mPanel_6_3->Controls->Add(this->mDay_6_3);
				 this->mPanel_6_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_6_3->Location = System::Drawing::Point(544, 737);
				 this->mPanel_6_3->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_6_3->Name = L"mPanel_6_3";
				 this->mPanel_6_3->Size = System::Drawing::Size(180, 138);
				 this->mPanel_6_3->TabIndex = 94;
				 this->mPanel_6_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_6_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_6_3
				 // 
				 this->mDay_6_3->AutoSize = true;
				 this->mDay_6_3->Location = System::Drawing::Point(3, 5);
				 this->mDay_6_3->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_6_3->Name = L"mDay_6_3";
				 this->mDay_6_3->Size = System::Drawing::Size(51, 20);
				 this->mDay_6_3->TabIndex = 45;
				 this->mDay_6_3->Text = L"label4";
				 this->mDay_6_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_6_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_6_2
				 // 
				 this->mPanel_6_2->Controls->Add(this->mDay_6_2);
				 this->mPanel_6_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_6_2->Location = System::Drawing::Point(363, 737);
				 this->mPanel_6_2->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_6_2->Name = L"mPanel_6_2";
				 this->mPanel_6_2->Size = System::Drawing::Size(180, 138);
				 this->mPanel_6_2->TabIndex = 93;
				 this->mPanel_6_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_6_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_6_2
				 // 
				 this->mDay_6_2->AutoSize = true;
				 this->mDay_6_2->Location = System::Drawing::Point(3, 5);
				 this->mDay_6_2->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_6_2->Name = L"mDay_6_2";
				 this->mDay_6_2->Size = System::Drawing::Size(51, 20);
				 this->mDay_6_2->TabIndex = 44;
				 this->mDay_6_2->Text = L"label3";
				 this->mDay_6_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_6_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_6_1
				 // 
				 this->mPanel_6_1->Controls->Add(this->mDay_6_1);
				 this->mPanel_6_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_6_1->Location = System::Drawing::Point(182, 737);
				 this->mPanel_6_1->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_6_1->Name = L"mPanel_6_1";
				 this->mPanel_6_1->Size = System::Drawing::Size(180, 138);
				 this->mPanel_6_1->TabIndex = 92;
				 this->mPanel_6_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_6_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_6_1
				 // 
				 this->mDay_6_1->AutoSize = true;
				 this->mDay_6_1->Location = System::Drawing::Point(3, 5);
				 this->mDay_6_1->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_6_1->Name = L"mDay_6_1";
				 this->mDay_6_1->Size = System::Drawing::Size(51, 20);
				 this->mDay_6_1->TabIndex = 43;
				 this->mDay_6_1->Text = L"label2";
				 this->mDay_6_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_6_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_6_0
				 // 
				 this->mPanel_6_0->Controls->Add(this->mDay_6_0);
				 this->mPanel_6_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_6_0->Location = System::Drawing::Point(1, 737);
				 this->mPanel_6_0->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_6_0->Name = L"mPanel_6_0";
				 this->mPanel_6_0->Size = System::Drawing::Size(180, 138);
				 this->mPanel_6_0->TabIndex = 91;
				 this->mPanel_6_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_6_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_6_0
				 // 
				 this->mDay_6_0->AutoSize = true;
				 this->mDay_6_0->Location = System::Drawing::Point(3, 5);
				 this->mDay_6_0->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_6_0->Name = L"mDay_6_0";
				 this->mDay_6_0->Size = System::Drawing::Size(51, 20);
				 this->mDay_6_0->TabIndex = 42;
				 this->mDay_6_0->Text = L"label1";
				 this->mDay_6_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_6_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_5_6
				 // 
				 this->mPanel_5_6->Controls->Add(this->mDay_5_6);
				 this->mPanel_5_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_5_6->Location = System::Drawing::Point(1087, 598);
				 this->mPanel_5_6->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_5_6->Name = L"mPanel_5_6";
				 this->mPanel_5_6->Size = System::Drawing::Size(180, 138);
				 this->mPanel_5_6->TabIndex = 90;
				 this->mPanel_5_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_5_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_5_6
				 // 
				 this->mDay_5_6->AutoSize = true;
				 this->mDay_5_6->Location = System::Drawing::Point(3, 5);
				 this->mDay_5_6->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_5_6->Name = L"mDay_5_6";
				 this->mDay_5_6->Size = System::Drawing::Size(51, 20);
				 this->mDay_5_6->TabIndex = 41;
				 this->mDay_5_6->Text = L"label7";
				 this->mDay_5_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_5_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_5_5
				 // 
				 this->mPanel_5_5->Controls->Add(this->mDay_5_5);
				 this->mPanel_5_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_5_5->Location = System::Drawing::Point(906, 598);
				 this->mPanel_5_5->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_5_5->Name = L"mPanel_5_5";
				 this->mPanel_5_5->Size = System::Drawing::Size(180, 138);
				 this->mPanel_5_5->TabIndex = 89;
				 this->mPanel_5_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_5_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_5_5
				 // 
				 this->mDay_5_5->AutoSize = true;
				 this->mDay_5_5->Location = System::Drawing::Point(3, 5);
				 this->mDay_5_5->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_5_5->Name = L"mDay_5_5";
				 this->mDay_5_5->Size = System::Drawing::Size(51, 20);
				 this->mDay_5_5->TabIndex = 40;
				 this->mDay_5_5->Text = L"label6";
				 this->mDay_5_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_5_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_5_4
				 // 
				 this->mPanel_5_4->Controls->Add(this->mDay_5_4);
				 this->mPanel_5_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_5_4->Location = System::Drawing::Point(725, 598);
				 this->mPanel_5_4->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_5_4->Name = L"mPanel_5_4";
				 this->mPanel_5_4->Size = System::Drawing::Size(180, 138);
				 this->mPanel_5_4->TabIndex = 88;
				 this->mPanel_5_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_5_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_5_4
				 // 
				 this->mDay_5_4->AutoSize = true;
				 this->mDay_5_4->Location = System::Drawing::Point(3, 5);
				 this->mDay_5_4->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_5_4->Name = L"mDay_5_4";
				 this->mDay_5_4->Size = System::Drawing::Size(51, 20);
				 this->mDay_5_4->TabIndex = 39;
				 this->mDay_5_4->Text = L"label5";
				 this->mDay_5_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_5_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_5_3
				 // 
				 this->mPanel_5_3->Controls->Add(this->mDay_5_3);
				 this->mPanel_5_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_5_3->Location = System::Drawing::Point(544, 598);
				 this->mPanel_5_3->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_5_3->Name = L"mPanel_5_3";
				 this->mPanel_5_3->Size = System::Drawing::Size(180, 138);
				 this->mPanel_5_3->TabIndex = 87;
				 this->mPanel_5_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_5_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_5_3
				 // 
				 this->mDay_5_3->AutoSize = true;
				 this->mDay_5_3->Location = System::Drawing::Point(3, 5);
				 this->mDay_5_3->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_5_3->Name = L"mDay_5_3";
				 this->mDay_5_3->Size = System::Drawing::Size(51, 20);
				 this->mDay_5_3->TabIndex = 38;
				 this->mDay_5_3->Text = L"label4";
				 this->mDay_5_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_5_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_5_2
				 // 
				 this->mPanel_5_2->Controls->Add(this->mDay_5_2);
				 this->mPanel_5_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_5_2->Location = System::Drawing::Point(363, 598);
				 this->mPanel_5_2->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_5_2->Name = L"mPanel_5_2";
				 this->mPanel_5_2->Size = System::Drawing::Size(180, 138);
				 this->mPanel_5_2->TabIndex = 86;
				 this->mPanel_5_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_5_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_5_2
				 // 
				 this->mDay_5_2->AutoSize = true;
				 this->mDay_5_2->Location = System::Drawing::Point(3, 5);
				 this->mDay_5_2->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_5_2->Name = L"mDay_5_2";
				 this->mDay_5_2->Size = System::Drawing::Size(51, 20);
				 this->mDay_5_2->TabIndex = 37;
				 this->mDay_5_2->Text = L"label3";
				 this->mDay_5_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_5_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_5_1
				 // 
				 this->mPanel_5_1->Controls->Add(this->mDay_5_1);
				 this->mPanel_5_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_5_1->Location = System::Drawing::Point(182, 598);
				 this->mPanel_5_1->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_5_1->Name = L"mPanel_5_1";
				 this->mPanel_5_1->Size = System::Drawing::Size(180, 138);
				 this->mPanel_5_1->TabIndex = 85;
				 this->mPanel_5_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_5_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_5_1
				 // 
				 this->mDay_5_1->AutoSize = true;
				 this->mDay_5_1->Location = System::Drawing::Point(3, 5);
				 this->mDay_5_1->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_5_1->Name = L"mDay_5_1";
				 this->mDay_5_1->Size = System::Drawing::Size(51, 20);
				 this->mDay_5_1->TabIndex = 36;
				 this->mDay_5_1->Text = L"label2";
				 this->mDay_5_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_5_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_5_0
				 // 
				 this->mPanel_5_0->Controls->Add(this->mDay_5_0);
				 this->mPanel_5_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_5_0->Location = System::Drawing::Point(1, 598);
				 this->mPanel_5_0->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_5_0->Name = L"mPanel_5_0";
				 this->mPanel_5_0->Size = System::Drawing::Size(180, 138);
				 this->mPanel_5_0->TabIndex = 84;
				 this->mPanel_5_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_5_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_5_0
				 // 
				 this->mDay_5_0->AutoSize = true;
				 this->mDay_5_0->Location = System::Drawing::Point(3, 5);
				 this->mDay_5_0->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_5_0->Name = L"mDay_5_0";
				 this->mDay_5_0->Size = System::Drawing::Size(51, 20);
				 this->mDay_5_0->TabIndex = 35;
				 this->mDay_5_0->Text = L"label1";
				 this->mDay_5_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_5_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_4_6
				 // 
				 this->mPanel_4_6->Controls->Add(this->mDay_4_6);
				 this->mPanel_4_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_4_6->Location = System::Drawing::Point(1087, 459);
				 this->mPanel_4_6->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_4_6->Name = L"mPanel_4_6";
				 this->mPanel_4_6->Size = System::Drawing::Size(180, 138);
				 this->mPanel_4_6->TabIndex = 83;
				 this->mPanel_4_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_4_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_4_6
				 // 
				 this->mDay_4_6->AutoSize = true;
				 this->mDay_4_6->Location = System::Drawing::Point(3, 5);
				 this->mDay_4_6->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_4_6->Name = L"mDay_4_6";
				 this->mDay_4_6->Size = System::Drawing::Size(51, 20);
				 this->mDay_4_6->TabIndex = 34;
				 this->mDay_4_6->Text = L"label7";
				 this->mDay_4_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_4_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_4_5
				 // 
				 this->mPanel_4_5->Controls->Add(this->mDay_4_5);
				 this->mPanel_4_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_4_5->Location = System::Drawing::Point(906, 459);
				 this->mPanel_4_5->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_4_5->Name = L"mPanel_4_5";
				 this->mPanel_4_5->Size = System::Drawing::Size(180, 138);
				 this->mPanel_4_5->TabIndex = 82;
				 this->mPanel_4_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_4_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_4_5
				 // 
				 this->mDay_4_5->AutoSize = true;
				 this->mDay_4_5->Location = System::Drawing::Point(3, 5);
				 this->mDay_4_5->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_4_5->Name = L"mDay_4_5";
				 this->mDay_4_5->Size = System::Drawing::Size(51, 20);
				 this->mDay_4_5->TabIndex = 33;
				 this->mDay_4_5->Text = L"label6";
				 this->mDay_4_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_4_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_4_4
				 // 
				 this->mPanel_4_4->Controls->Add(this->mDay_4_4);
				 this->mPanel_4_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_4_4->Location = System::Drawing::Point(725, 459);
				 this->mPanel_4_4->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_4_4->Name = L"mPanel_4_4";
				 this->mPanel_4_4->Size = System::Drawing::Size(180, 138);
				 this->mPanel_4_4->TabIndex = 81;
				 this->mPanel_4_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_4_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_4_4
				 // 
				 this->mDay_4_4->AutoSize = true;
				 this->mDay_4_4->Location = System::Drawing::Point(3, 5);
				 this->mDay_4_4->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_4_4->Name = L"mDay_4_4";
				 this->mDay_4_4->Size = System::Drawing::Size(51, 20);
				 this->mDay_4_4->TabIndex = 32;
				 this->mDay_4_4->Text = L"label5";
				 this->mDay_4_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_4_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_4_3
				 // 
				 this->mPanel_4_3->Controls->Add(this->mDay_4_3);
				 this->mPanel_4_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_4_3->Location = System::Drawing::Point(544, 459);
				 this->mPanel_4_3->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_4_3->Name = L"mPanel_4_3";
				 this->mPanel_4_3->Size = System::Drawing::Size(180, 138);
				 this->mPanel_4_3->TabIndex = 80;
				 this->mPanel_4_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_4_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_4_3
				 // 
				 this->mDay_4_3->AutoSize = true;
				 this->mDay_4_3->Location = System::Drawing::Point(3, 5);
				 this->mDay_4_3->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_4_3->Name = L"mDay_4_3";
				 this->mDay_4_3->Size = System::Drawing::Size(51, 20);
				 this->mDay_4_3->TabIndex = 31;
				 this->mDay_4_3->Text = L"label4";
				 this->mDay_4_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_4_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_4_2
				 // 
				 this->mPanel_4_2->Controls->Add(this->mDay_4_2);
				 this->mPanel_4_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_4_2->Location = System::Drawing::Point(363, 459);
				 this->mPanel_4_2->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_4_2->Name = L"mPanel_4_2";
				 this->mPanel_4_2->Size = System::Drawing::Size(180, 138);
				 this->mPanel_4_2->TabIndex = 79;
				 this->mPanel_4_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_4_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_4_2
				 // 
				 this->mDay_4_2->AutoSize = true;
				 this->mDay_4_2->Location = System::Drawing::Point(3, 5);
				 this->mDay_4_2->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_4_2->Name = L"mDay_4_2";
				 this->mDay_4_2->Size = System::Drawing::Size(51, 20);
				 this->mDay_4_2->TabIndex = 30;
				 this->mDay_4_2->Text = L"label3";
				 this->mDay_4_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_4_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_4_1
				 // 
				 this->mPanel_4_1->Controls->Add(this->mDay_4_1);
				 this->mPanel_4_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_4_1->Location = System::Drawing::Point(182, 459);
				 this->mPanel_4_1->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_4_1->Name = L"mPanel_4_1";
				 this->mPanel_4_1->Size = System::Drawing::Size(180, 138);
				 this->mPanel_4_1->TabIndex = 78;
				 this->mPanel_4_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_4_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_4_1
				 // 
				 this->mDay_4_1->AutoSize = true;
				 this->mDay_4_1->Location = System::Drawing::Point(3, 5);
				 this->mDay_4_1->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_4_1->Name = L"mDay_4_1";
				 this->mDay_4_1->Size = System::Drawing::Size(51, 20);
				 this->mDay_4_1->TabIndex = 29;
				 this->mDay_4_1->Text = L"label2";
				 this->mDay_4_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_4_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_4_0
				 // 
				 this->mPanel_4_0->Controls->Add(this->mDay_4_0);
				 this->mPanel_4_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_4_0->Location = System::Drawing::Point(1, 459);
				 this->mPanel_4_0->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_4_0->Name = L"mPanel_4_0";
				 this->mPanel_4_0->Size = System::Drawing::Size(180, 138);
				 this->mPanel_4_0->TabIndex = 77;
				 this->mPanel_4_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_4_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_4_0
				 // 
				 this->mDay_4_0->AutoSize = true;
				 this->mDay_4_0->Location = System::Drawing::Point(3, 5);
				 this->mDay_4_0->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_4_0->Name = L"mDay_4_0";
				 this->mDay_4_0->Size = System::Drawing::Size(51, 20);
				 this->mDay_4_0->TabIndex = 28;
				 this->mDay_4_0->Text = L"label1";
				 this->mDay_4_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_4_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_3_6
				 // 
				 this->mPanel_3_6->Controls->Add(this->mDay_3_6);
				 this->mPanel_3_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_3_6->Location = System::Drawing::Point(1087, 320);
				 this->mPanel_3_6->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_3_6->Name = L"mPanel_3_6";
				 this->mPanel_3_6->Size = System::Drawing::Size(180, 138);
				 this->mPanel_3_6->TabIndex = 76;
				 this->mPanel_3_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_3_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_3_6
				 // 
				 this->mDay_3_6->AutoSize = true;
				 this->mDay_3_6->Location = System::Drawing::Point(3, 5);
				 this->mDay_3_6->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_3_6->Name = L"mDay_3_6";
				 this->mDay_3_6->Size = System::Drawing::Size(51, 20);
				 this->mDay_3_6->TabIndex = 27;
				 this->mDay_3_6->Text = L"label7";
				 this->mDay_3_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_3_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_3_5
				 // 
				 this->mPanel_3_5->Controls->Add(this->mDay_3_5);
				 this->mPanel_3_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_3_5->Location = System::Drawing::Point(906, 320);
				 this->mPanel_3_5->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_3_5->Name = L"mPanel_3_5";
				 this->mPanel_3_5->Size = System::Drawing::Size(180, 138);
				 this->mPanel_3_5->TabIndex = 75;
				 this->mPanel_3_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_3_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_3_5
				 // 
				 this->mDay_3_5->AutoSize = true;
				 this->mDay_3_5->Location = System::Drawing::Point(3, 5);
				 this->mDay_3_5->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_3_5->Name = L"mDay_3_5";
				 this->mDay_3_5->Size = System::Drawing::Size(51, 20);
				 this->mDay_3_5->TabIndex = 26;
				 this->mDay_3_5->Text = L"label6";
				 this->mDay_3_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_3_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_3_4
				 // 
				 this->mPanel_3_4->Controls->Add(this->mDay_3_4);
				 this->mPanel_3_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_3_4->Location = System::Drawing::Point(725, 320);
				 this->mPanel_3_4->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_3_4->Name = L"mPanel_3_4";
				 this->mPanel_3_4->Size = System::Drawing::Size(180, 138);
				 this->mPanel_3_4->TabIndex = 74;
				 this->mPanel_3_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_3_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_3_4
				 // 
				 this->mDay_3_4->AutoSize = true;
				 this->mDay_3_4->Location = System::Drawing::Point(3, 5);
				 this->mDay_3_4->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_3_4->Name = L"mDay_3_4";
				 this->mDay_3_4->Size = System::Drawing::Size(51, 20);
				 this->mDay_3_4->TabIndex = 25;
				 this->mDay_3_4->Text = L"label5";
				 this->mDay_3_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_3_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_3_3
				 // 
				 this->mPanel_3_3->Controls->Add(this->mDay_3_3);
				 this->mPanel_3_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_3_3->Location = System::Drawing::Point(544, 320);
				 this->mPanel_3_3->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_3_3->Name = L"mPanel_3_3";
				 this->mPanel_3_3->Size = System::Drawing::Size(180, 138);
				 this->mPanel_3_3->TabIndex = 73;
				 this->mPanel_3_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_3_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_3_3
				 // 
				 this->mDay_3_3->AutoSize = true;
				 this->mDay_3_3->Location = System::Drawing::Point(3, 5);
				 this->mDay_3_3->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_3_3->Name = L"mDay_3_3";
				 this->mDay_3_3->Size = System::Drawing::Size(51, 20);
				 this->mDay_3_3->TabIndex = 24;
				 this->mDay_3_3->Text = L"label4";
				 this->mDay_3_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_3_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_3_2
				 // 
				 this->mPanel_3_2->Controls->Add(this->mDay_3_2);
				 this->mPanel_3_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_3_2->Location = System::Drawing::Point(363, 320);
				 this->mPanel_3_2->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_3_2->Name = L"mPanel_3_2";
				 this->mPanel_3_2->Size = System::Drawing::Size(180, 138);
				 this->mPanel_3_2->TabIndex = 72;
				 this->mPanel_3_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_3_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_3_2
				 // 
				 this->mDay_3_2->AutoSize = true;
				 this->mDay_3_2->Location = System::Drawing::Point(3, 5);
				 this->mDay_3_2->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_3_2->Name = L"mDay_3_2";
				 this->mDay_3_2->Size = System::Drawing::Size(51, 20);
				 this->mDay_3_2->TabIndex = 23;
				 this->mDay_3_2->Text = L"label3";
				 this->mDay_3_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_3_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_3_1
				 // 
				 this->mPanel_3_1->Controls->Add(this->mDay_3_1);
				 this->mPanel_3_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_3_1->Location = System::Drawing::Point(182, 320);
				 this->mPanel_3_1->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_3_1->Name = L"mPanel_3_1";
				 this->mPanel_3_1->Size = System::Drawing::Size(180, 138);
				 this->mPanel_3_1->TabIndex = 71;
				 this->mPanel_3_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_3_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_3_1
				 // 
				 this->mDay_3_1->AutoSize = true;
				 this->mDay_3_1->Location = System::Drawing::Point(3, 5);
				 this->mDay_3_1->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_3_1->Name = L"mDay_3_1";
				 this->mDay_3_1->Size = System::Drawing::Size(51, 20);
				 this->mDay_3_1->TabIndex = 22;
				 this->mDay_3_1->Text = L"label2";
				 this->mDay_3_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_3_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_2_6
				 // 
				 this->mPanel_2_6->Controls->Add(this->mDay_2_6);
				 this->mPanel_2_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_2_6->Location = System::Drawing::Point(1087, 181);
				 this->mPanel_2_6->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_2_6->Name = L"mPanel_2_6";
				 this->mPanel_2_6->Size = System::Drawing::Size(180, 138);
				 this->mPanel_2_6->TabIndex = 69;
				 this->mPanel_2_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_2_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_2_6
				 // 
				 this->mDay_2_6->AutoSize = true;
				 this->mDay_2_6->Location = System::Drawing::Point(3, 5);
				 this->mDay_2_6->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_2_6->Name = L"mDay_2_6";
				 this->mDay_2_6->Size = System::Drawing::Size(51, 20);
				 this->mDay_2_6->TabIndex = 20;
				 this->mDay_2_6->Text = L"label7";
				 this->mDay_2_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_2_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_2_5
				 // 
				 this->mPanel_2_5->Controls->Add(this->mDay_2_5);
				 this->mPanel_2_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_2_5->Location = System::Drawing::Point(906, 181);
				 this->mPanel_2_5->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_2_5->Name = L"mPanel_2_5";
				 this->mPanel_2_5->Size = System::Drawing::Size(180, 138);
				 this->mPanel_2_5->TabIndex = 68;
				 this->mPanel_2_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_2_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_2_5
				 // 
				 this->mDay_2_5->AutoSize = true;
				 this->mDay_2_5->Location = System::Drawing::Point(3, 5);
				 this->mDay_2_5->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_2_5->Name = L"mDay_2_5";
				 this->mDay_2_5->Size = System::Drawing::Size(51, 20);
				 this->mDay_2_5->TabIndex = 19;
				 this->mDay_2_5->Text = L"label6";
				 this->mDay_2_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_2_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_2_4
				 // 
				 this->mPanel_2_4->Controls->Add(this->mDay_2_4);
				 this->mPanel_2_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_2_4->Location = System::Drawing::Point(725, 181);
				 this->mPanel_2_4->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_2_4->Name = L"mPanel_2_4";
				 this->mPanel_2_4->Size = System::Drawing::Size(180, 138);
				 this->mPanel_2_4->TabIndex = 67;
				 this->mPanel_2_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_2_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_2_4
				 // 
				 this->mDay_2_4->AutoSize = true;
				 this->mDay_2_4->Location = System::Drawing::Point(3, 5);
				 this->mDay_2_4->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_2_4->Name = L"mDay_2_4";
				 this->mDay_2_4->Size = System::Drawing::Size(51, 20);
				 this->mDay_2_4->TabIndex = 18;
				 this->mDay_2_4->Text = L"label5";
				 this->mDay_2_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_2_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_2_3
				 // 
				 this->mPanel_2_3->Controls->Add(this->mDay_2_3);
				 this->mPanel_2_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_2_3->Location = System::Drawing::Point(544, 181);
				 this->mPanel_2_3->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_2_3->Name = L"mPanel_2_3";
				 this->mPanel_2_3->Size = System::Drawing::Size(180, 138);
				 this->mPanel_2_3->TabIndex = 66;
				 this->mPanel_2_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_2_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_2_3
				 // 
				 this->mDay_2_3->AutoSize = true;
				 this->mDay_2_3->Location = System::Drawing::Point(3, 5);
				 this->mDay_2_3->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_2_3->Name = L"mDay_2_3";
				 this->mDay_2_3->Size = System::Drawing::Size(51, 20);
				 this->mDay_2_3->TabIndex = 17;
				 this->mDay_2_3->Text = L"label4";
				 this->mDay_2_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_2_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_2_2
				 // 
				 this->mPanel_2_2->Controls->Add(this->mDay_2_2);
				 this->mPanel_2_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_2_2->Location = System::Drawing::Point(363, 181);
				 this->mPanel_2_2->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_2_2->Name = L"mPanel_2_2";
				 this->mPanel_2_2->Size = System::Drawing::Size(180, 138);
				 this->mPanel_2_2->TabIndex = 65;
				 this->mPanel_2_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_2_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_2_2
				 // 
				 this->mDay_2_2->AutoSize = true;
				 this->mDay_2_2->Location = System::Drawing::Point(3, 5);
				 this->mDay_2_2->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_2_2->Name = L"mDay_2_2";
				 this->mDay_2_2->Size = System::Drawing::Size(51, 20);
				 this->mDay_2_2->TabIndex = 16;
				 this->mDay_2_2->Text = L"label3";
				 this->mDay_2_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_2_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_2_1
				 // 
				 this->mPanel_2_1->Controls->Add(this->mDay_2_1);
				 this->mPanel_2_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_2_1->Location = System::Drawing::Point(182, 181);
				 this->mPanel_2_1->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_2_1->Name = L"mPanel_2_1";
				 this->mPanel_2_1->Size = System::Drawing::Size(180, 138);
				 this->mPanel_2_1->TabIndex = 64;
				 this->mPanel_2_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_2_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_2_1
				 // 
				 this->mDay_2_1->AutoSize = true;
				 this->mDay_2_1->Location = System::Drawing::Point(3, 5);
				 this->mDay_2_1->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_2_1->Name = L"mDay_2_1";
				 this->mDay_2_1->Size = System::Drawing::Size(51, 20);
				 this->mDay_2_1->TabIndex = 15;
				 this->mDay_2_1->Text = L"label2";
				 this->mDay_2_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_2_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_1_6
				 // 
				 this->mPanel_1_6->Controls->Add(this->mDay_1_6);
				 this->mPanel_1_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_1_6->Location = System::Drawing::Point(1087, 42);
				 this->mPanel_1_6->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_1_6->Name = L"mPanel_1_6";
				 this->mPanel_1_6->Size = System::Drawing::Size(180, 138);
				 this->mPanel_1_6->TabIndex = 62;
				 this->mPanel_1_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_1_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_1_6
				 // 
				 this->mDay_1_6->AutoSize = true;
				 this->mDay_1_6->Location = System::Drawing::Point(3, 5);
				 this->mDay_1_6->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_1_6->Name = L"mDay_1_6";
				 this->mDay_1_6->Size = System::Drawing::Size(51, 20);
				 this->mDay_1_6->TabIndex = 13;
				 this->mDay_1_6->Text = L"label7";
				 this->mDay_1_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_1_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_1_5
				 // 
				 this->mPanel_1_5->Controls->Add(this->mDay_1_5);
				 this->mPanel_1_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_1_5->Location = System::Drawing::Point(906, 42);
				 this->mPanel_1_5->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_1_5->Name = L"mPanel_1_5";
				 this->mPanel_1_5->Size = System::Drawing::Size(180, 138);
				 this->mPanel_1_5->TabIndex = 61;
				 this->mPanel_1_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_1_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_1_5
				 // 
				 this->mDay_1_5->AutoSize = true;
				 this->mDay_1_5->Location = System::Drawing::Point(3, 5);
				 this->mDay_1_5->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_1_5->Name = L"mDay_1_5";
				 this->mDay_1_5->Size = System::Drawing::Size(51, 20);
				 this->mDay_1_5->TabIndex = 12;
				 this->mDay_1_5->Text = L"label6";
				 this->mDay_1_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_1_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_1_4
				 // 
				 this->mPanel_1_4->Controls->Add(this->mDay_1_4);
				 this->mPanel_1_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_1_4->Location = System::Drawing::Point(725, 42);
				 this->mPanel_1_4->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_1_4->Name = L"mPanel_1_4";
				 this->mPanel_1_4->Size = System::Drawing::Size(180, 138);
				 this->mPanel_1_4->TabIndex = 60;
				 this->mPanel_1_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_1_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_1_4
				 // 
				 this->mDay_1_4->AutoSize = true;
				 this->mDay_1_4->Location = System::Drawing::Point(3, 5);
				 this->mDay_1_4->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_1_4->Name = L"mDay_1_4";
				 this->mDay_1_4->Size = System::Drawing::Size(51, 20);
				 this->mDay_1_4->TabIndex = 11;
				 this->mDay_1_4->Text = L"label5";
				 this->mDay_1_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_1_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_1_3
				 // 
				 this->mPanel_1_3->Controls->Add(this->mDay_1_3);
				 this->mPanel_1_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_1_3->Location = System::Drawing::Point(544, 42);
				 this->mPanel_1_3->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_1_3->Name = L"mPanel_1_3";
				 this->mPanel_1_3->Size = System::Drawing::Size(180, 138);
				 this->mPanel_1_3->TabIndex = 59;
				 this->mPanel_1_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_1_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_1_3
				 // 
				 this->mDay_1_3->AutoSize = true;
				 this->mDay_1_3->Location = System::Drawing::Point(3, 5);
				 this->mDay_1_3->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_1_3->Name = L"mDay_1_3";
				 this->mDay_1_3->Size = System::Drawing::Size(51, 20);
				 this->mDay_1_3->TabIndex = 10;
				 this->mDay_1_3->Text = L"label4";
				 this->mDay_1_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_1_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_1_2
				 // 
				 this->mPanel_1_2->Controls->Add(this->mDay_1_2);
				 this->mPanel_1_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_1_2->Location = System::Drawing::Point(363, 42);
				 this->mPanel_1_2->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_1_2->Name = L"mPanel_1_2";
				 this->mPanel_1_2->Size = System::Drawing::Size(180, 138);
				 this->mPanel_1_2->TabIndex = 58;
				 this->mPanel_1_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_1_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_1_2
				 // 
				 this->mDay_1_2->AutoSize = true;
				 this->mDay_1_2->Location = System::Drawing::Point(3, 5);
				 this->mDay_1_2->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_1_2->Name = L"mDay_1_2";
				 this->mDay_1_2->Size = System::Drawing::Size(51, 20);
				 this->mDay_1_2->TabIndex = 9;
				 this->mDay_1_2->Text = L"label3";
				 this->mDay_1_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_1_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_1_1
				 // 
				 this->mPanel_1_1->Controls->Add(this->mDay_1_1);
				 this->mPanel_1_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_1_1->Location = System::Drawing::Point(182, 42);
				 this->mPanel_1_1->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_1_1->Name = L"mPanel_1_1";
				 this->mPanel_1_1->Size = System::Drawing::Size(180, 138);
				 this->mPanel_1_1->TabIndex = 57;
				 this->mPanel_1_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_1_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_1_1
				 // 
				 this->mDay_1_1->AutoSize = true;
				 this->mDay_1_1->Location = System::Drawing::Point(3, 5);
				 this->mDay_1_1->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_1_1->Name = L"mDay_1_1";
				 this->mDay_1_1->Size = System::Drawing::Size(51, 20);
				 this->mDay_1_1->TabIndex = 8;
				 this->mDay_1_1->Text = L"label2";
				 this->mDay_1_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_1_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_0_6
				 // 
				 this->mPanel_0_6->Controls->Add(this->mWDay_6);
				 this->mPanel_0_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_0_6->Location = System::Drawing::Point(1087, 1);
				 this->mPanel_0_6->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_0_6->Name = L"mPanel_0_6";
				 this->mPanel_0_6->Size = System::Drawing::Size(180, 40);
				 this->mPanel_0_6->TabIndex = 55;
				 // 
				 // mWDay_6
				 // 
				 this->mWDay_6->AutoSize = true;
				 this->mWDay_6->Location = System::Drawing::Point(3, 9);
				 this->mWDay_6->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->mWDay_6->Name = L"mWDay_6";
				 this->mWDay_6->Size = System::Drawing::Size(51, 20);
				 this->mWDay_6->TabIndex = 6;
				 this->mWDay_6->Text = L"label7";
				 // 
				 // mPanel_0_5
				 // 
				 this->mPanel_0_5->Controls->Add(this->mWDay_5);
				 this->mPanel_0_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_0_5->Location = System::Drawing::Point(906, 1);
				 this->mPanel_0_5->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_0_5->Name = L"mPanel_0_5";
				 this->mPanel_0_5->Size = System::Drawing::Size(180, 40);
				 this->mPanel_0_5->TabIndex = 54;
				 // 
				 // mWDay_5
				 // 
				 this->mWDay_5->AutoSize = true;
				 this->mWDay_5->Location = System::Drawing::Point(3, 9);
				 this->mWDay_5->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->mWDay_5->Name = L"mWDay_5";
				 this->mWDay_5->Size = System::Drawing::Size(51, 20);
				 this->mWDay_5->TabIndex = 5;
				 this->mWDay_5->Text = L"label6";
				 // 
				 // mPanel_0_4
				 // 
				 this->mPanel_0_4->Controls->Add(this->mWDay_4);
				 this->mPanel_0_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_0_4->Location = System::Drawing::Point(725, 1);
				 this->mPanel_0_4->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_0_4->Name = L"mPanel_0_4";
				 this->mPanel_0_4->Size = System::Drawing::Size(180, 40);
				 this->mPanel_0_4->TabIndex = 53;
				 // 
				 // mWDay_4
				 // 
				 this->mWDay_4->AutoSize = true;
				 this->mWDay_4->Location = System::Drawing::Point(3, 9);
				 this->mWDay_4->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->mWDay_4->Name = L"mWDay_4";
				 this->mWDay_4->Size = System::Drawing::Size(51, 20);
				 this->mWDay_4->TabIndex = 4;
				 this->mWDay_4->Text = L"label5";
				 // 
				 // mPanel_0_3
				 // 
				 this->mPanel_0_3->Controls->Add(this->mWDay_3);
				 this->mPanel_0_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_0_3->Location = System::Drawing::Point(544, 1);
				 this->mPanel_0_3->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_0_3->Name = L"mPanel_0_3";
				 this->mPanel_0_3->Size = System::Drawing::Size(180, 40);
				 this->mPanel_0_3->TabIndex = 52;
				 // 
				 // mWDay_3
				 // 
				 this->mWDay_3->AutoSize = true;
				 this->mWDay_3->Location = System::Drawing::Point(3, 9);
				 this->mWDay_3->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->mWDay_3->Name = L"mWDay_3";
				 this->mWDay_3->Size = System::Drawing::Size(51, 20);
				 this->mWDay_3->TabIndex = 3;
				 this->mWDay_3->Text = L"label4";
				 // 
				 // mPanel_0_2
				 // 
				 this->mPanel_0_2->Controls->Add(this->mWDay_2);
				 this->mPanel_0_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_0_2->Location = System::Drawing::Point(363, 1);
				 this->mPanel_0_2->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_0_2->Name = L"mPanel_0_2";
				 this->mPanel_0_2->Size = System::Drawing::Size(180, 40);
				 this->mPanel_0_2->TabIndex = 51;
				 // 
				 // mWDay_2
				 // 
				 this->mWDay_2->AutoSize = true;
				 this->mWDay_2->Location = System::Drawing::Point(3, 9);
				 this->mWDay_2->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->mWDay_2->Name = L"mWDay_2";
				 this->mWDay_2->Size = System::Drawing::Size(51, 20);
				 this->mWDay_2->TabIndex = 2;
				 this->mWDay_2->Text = L"label3";
				 // 
				 // mPanel_0_1
				 // 
				 this->mPanel_0_1->Controls->Add(this->mWDay_1);
				 this->mPanel_0_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_0_1->Location = System::Drawing::Point(182, 1);
				 this->mPanel_0_1->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_0_1->Name = L"mPanel_0_1";
				 this->mPanel_0_1->Size = System::Drawing::Size(180, 40);
				 this->mPanel_0_1->TabIndex = 50;
				 // 
				 // mWDay_1
				 // 
				 this->mWDay_1->AutoSize = true;
				 this->mWDay_1->Location = System::Drawing::Point(3, 9);
				 this->mWDay_1->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->mWDay_1->Name = L"mWDay_1";
				 this->mWDay_1->Size = System::Drawing::Size(51, 20);
				 this->mWDay_1->TabIndex = 1;
				 this->mWDay_1->Text = L"label2";
				 // 
				 // mPanel_0_0
				 // 
				 this->mPanel_0_0->Controls->Add(this->mWDay_0);
				 this->mPanel_0_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_0_0->Location = System::Drawing::Point(1, 1);
				 this->mPanel_0_0->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_0_0->Name = L"mPanel_0_0";
				 this->mPanel_0_0->Size = System::Drawing::Size(180, 40);
				 this->mPanel_0_0->TabIndex = 49;
				 // 
				 // mWDay_0
				 // 
				 this->mWDay_0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->mWDay_0->FormattingEnabled = true;
				 this->mWDay_0->Items->AddRange(gcnew cli::array< System::Object^  >(7) {L"Sunday", L"Monday", L"Tuesday", L"Wednesday", L"Thursday", 
					 L"Friday", L"Saturday"});
				 this->mWDay_0->Location = System::Drawing::Point(2, 5);
				 this->mWDay_0->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				 this->mWDay_0->Name = L"mWDay_0";
				 this->mWDay_0->Size = System::Drawing::Size(172, 28);
				 this->mWDay_0->TabIndex = 7;
				 this->mWDay_0->Text = L"Sunday";
				 this->mWDay_0->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::wmDay_0_SelectedIndexChanged);
				 // 
				 // mPanel_1_0
				 // 
				 this->mPanel_1_0->Controls->Add(this->mDay_1_0);
				 this->mPanel_1_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_1_0->Location = System::Drawing::Point(1, 42);
				 this->mPanel_1_0->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_1_0->Name = L"mPanel_1_0";
				 this->mPanel_1_0->Size = System::Drawing::Size(180, 138);
				 this->mPanel_1_0->TabIndex = 56;
				 this->mPanel_1_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_1_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_1_0
				 // 
				 this->mDay_1_0->AutoSize = true;
				 this->mDay_1_0->Location = System::Drawing::Point(3, 5);
				 this->mDay_1_0->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_1_0->Name = L"mDay_1_0";
				 this->mDay_1_0->Size = System::Drawing::Size(51, 20);
				 this->mDay_1_0->TabIndex = 7;
				 this->mDay_1_0->Text = L"label1";
				 this->mDay_1_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_1_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_2_0
				 // 
				 this->mPanel_2_0->Controls->Add(this->mDay_2_0);
				 this->mPanel_2_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_2_0->Location = System::Drawing::Point(1, 181);
				 this->mPanel_2_0->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_2_0->Name = L"mPanel_2_0";
				 this->mPanel_2_0->Size = System::Drawing::Size(180, 138);
				 this->mPanel_2_0->TabIndex = 63;
				 this->mPanel_2_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_2_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_2_0
				 // 
				 this->mDay_2_0->AutoSize = true;
				 this->mDay_2_0->Location = System::Drawing::Point(3, 5);
				 this->mDay_2_0->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_2_0->Name = L"mDay_2_0";
				 this->mDay_2_0->Size = System::Drawing::Size(51, 20);
				 this->mDay_2_0->TabIndex = 14;
				 this->mDay_2_0->Text = L"label1";
				 this->mDay_2_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_2_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mPanel_3_0
				 // 
				 this->mPanel_3_0->Controls->Add(this->mDay_3_0);
				 this->mPanel_3_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->mPanel_3_0->Location = System::Drawing::Point(1, 320);
				 this->mPanel_3_0->Margin = System::Windows::Forms::Padding(0);
				 this->mPanel_3_0->Name = L"mPanel_3_0";
				 this->mPanel_3_0->Size = System::Drawing::Size(180, 138);
				 this->mPanel_3_0->TabIndex = 70;
				 this->mPanel_3_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mPanel_3_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // mDay_3_0
				 // 
				 this->mDay_3_0->AutoSize = true;
				 this->mDay_3_0->Location = System::Drawing::Point(3, 5);
				 this->mDay_3_0->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
				 this->mDay_3_0->Name = L"mDay_3_0";
				 this->mDay_3_0->Size = System::Drawing::Size(51, 20);
				 this->mDay_3_0->TabIndex = 21;
				 this->mDay_3_0->Text = L"label1";
				 this->mDay_3_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->mDay_3_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // display_year
				 // 
				 this->display_year->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
				 this->display_year->BackColor = System::Drawing::SystemColors::Control;
				 this->display_year->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->display_year->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->display_year->Location = System::Drawing::Point(339, 6);
				 this->display_year->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
				 this->display_year->MaxLength = 4;
				 this->display_year->Name = L"display_year";
				 this->display_year->Size = System::Drawing::Size(74, 44);
				 this->display_year->TabIndex = 2;
				 this->display_year->Text = L"2014";
				 this->display_year->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->display_year->Click += gcnew System::EventHandler(this, &Form1::select_all_Click);
				 this->display_year->TextChanged += gcnew System::EventHandler(this, &Form1::resize_TextChanged);
				 this->display_year->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::int_only_KeyPress);
				 this->display_year->Leave += gcnew System::EventHandler(this, &Form1::display_year_Leave);
				 // 
				 // display_month
				 // 
				 this->display_month->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
				 this->display_month->BackColor = System::Drawing::SystemColors::Control;
				 this->display_month->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->display_month->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->display_month->Location = System::Drawing::Point(165, 6);
				 this->display_month->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
				 this->display_month->MaxLength = 9;
				 this->display_month->Name = L"display_month";
				 this->display_month->Size = System::Drawing::Size(168, 44);
				 this->display_month->TabIndex = 1;
				 this->display_month->Text = L"September";
				 this->display_month->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->display_month->Click += gcnew System::EventHandler(this, &Form1::select_all_Click);
				 this->display_month->TextChanged += gcnew System::EventHandler(this, &Form1::resize_TextChanged);
				 this->display_month->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::int_or_char_KeyPress);
				 this->display_month->Leave += gcnew System::EventHandler(this, &Form1::display_month_Leave);
				 // 
				 // prev_btn
				 // 
				 this->prev_btn->Location = System::Drawing::Point(2, 0);
				 this->prev_btn->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->prev_btn->Name = L"prev_btn";
				 this->prev_btn->Size = System::Drawing::Size(38, 35);
				 this->prev_btn->TabIndex = 0;
				 this->prev_btn->Text = L"<";
				 this->prev_btn->UseVisualStyleBackColor = true;
				 this->prev_btn->Click += gcnew System::EventHandler(this, &Form1::prev_btn_Click);
				 // 
				 // next_btn
				 // 
				 this->next_btn->Location = System::Drawing::Point(124, 0);
				 this->next_btn->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->next_btn->Name = L"next_btn";
				 this->next_btn->Size = System::Drawing::Size(38, 35);
				 this->next_btn->TabIndex = 2;
				 this->next_btn->Text = L">";
				 this->next_btn->UseVisualStyleBackColor = true;
				 this->next_btn->Click += gcnew System::EventHandler(this, &Form1::next_btn_Click);
				 // 
				 // monthly_type
				 // 
				 this->monthly_type->Location = System::Drawing::Point(2, 0);
				 this->monthly_type->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->monthly_type->Name = L"monthly_type";
				 this->monthly_type->Size = System::Drawing::Size(112, 35);
				 this->monthly_type->TabIndex = 3;
				 this->monthly_type->Text = L"Month";
				 this->monthly_type->UseVisualStyleBackColor = true;
				 this->monthly_type->Click += gcnew System::EventHandler(this, &Form1::monthly_type_Click);
				 // 
				 // weekly_type
				 // 
				 this->weekly_type->Location = System::Drawing::Point(118, 0);
				 this->weekly_type->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->weekly_type->Name = L"weekly_type";
				 this->weekly_type->Size = System::Drawing::Size(112, 35);
				 this->weekly_type->TabIndex = 4;
				 this->weekly_type->Text = L"Week";
				 this->weekly_type->UseVisualStyleBackColor = true;
				 this->weekly_type->Click += gcnew System::EventHandler(this, &Form1::weekly_type_Click);
				 // 
				 // daily_type
				 // 
				 this->daily_type->Location = System::Drawing::Point(234, 0);
				 this->daily_type->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->daily_type->Name = L"daily_type";
				 this->daily_type->Size = System::Drawing::Size(112, 35);
				 this->daily_type->TabIndex = 5;
				 this->daily_type->Text = L"Day";
				 this->daily_type->UseVisualStyleBackColor = true;
				 this->daily_type->Click += gcnew System::EventHandler(this, &Form1::daily_type_Click);
				 // 
				 // now_btn
				 // 
				 this->now_btn->Location = System::Drawing::Point(44, 0);
				 this->now_btn->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->now_btn->Name = L"now_btn";
				 this->now_btn->Size = System::Drawing::Size(76, 35);
				 this->now_btn->TabIndex = 1;
				 this->now_btn->Text = L"Today";
				 this->now_btn->UseVisualStyleBackColor = true;
				 this->now_btn->Click += gcnew System::EventHandler(this, &Form1::now_btn_Click);
				 // 
				 // mPanel
				 // 
				 this->mPanel->Controls->Add(this->monthly_cal);
				 this->mPanel->Location = System::Drawing::Point(0, 88);
				 this->mPanel->Name = L"mPanel";
				 this->mPanel->Size = System::Drawing::Size(1389, 883);
				 this->mPanel->TabIndex = 2;
				 // 
				 // wPanel
				 // 
				 this->wPanel->AutoScroll = true;
				 this->wPanel->Controls->Add(this->wBtmLine);
				 this->wPanel->Controls->Add(this->wTopLine);
				 this->wPanel->Controls->Add(this->wPanel_head);
				 this->wPanel->Controls->Add(this->wPanel_body);
				 this->wPanel->Location = System::Drawing::Point(0, 88);
				 this->wPanel->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel->Name = L"wPanel";
				 this->wPanel->Size = System::Drawing::Size(1389, 883);
				 this->wPanel->TabIndex = 14;
				 // 
				 // wBtmLine
				 // 
				 this->wBtmLine->Location = System::Drawing::Point(0, 0);
				 this->wBtmLine->Name = L"wBtmLine";
				 this->wBtmLine->Size = System::Drawing::Size(2, 2);
				 this->wBtmLine->TabIndex = 1;
				 // 
				 // wTopLine
				 // 
				 this->wTopLine->Location = System::Drawing::Point(0, 0);
				 this->wTopLine->Name = L"wTopLine";
				 this->wTopLine->Size = System::Drawing::Size(2, 2);
				 this->wTopLine->TabIndex = 2;
				 // 
				 // wPanel_head
				 // 
				 this->wPanel_head->AutoSize = true;
				 this->wPanel_head->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->wPanel_head->Controls->Add(this->weekly_cal_title);
				 this->wPanel_head->Location = System::Drawing::Point(138, 0);
				 this->wPanel_head->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_head->Name = L"wPanel_head";
				 this->wPanel_head->Size = System::Drawing::Size(1184, 42);
				 this->wPanel_head->TabIndex = 16;
				 // 
				 // weekly_cal_title
				 // 
				 this->weekly_cal_title->AutoSize = true;
				 this->weekly_cal_title->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->weekly_cal_title->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->weekly_cal_title->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->weekly_cal_title->ColumnCount = 7;
				 this->weekly_cal_title->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->weekly_cal_title->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->weekly_cal_title->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->weekly_cal_title->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->weekly_cal_title->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->weekly_cal_title->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->weekly_cal_title->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->weekly_cal_title->Controls->Add(this->wPanel_0_1, 0, 0);
				 this->weekly_cal_title->Controls->Add(this->wPanel_0_2, 1, 0);
				 this->weekly_cal_title->Controls->Add(this->wPanel_0_3, 2, 0);
				 this->weekly_cal_title->Controls->Add(this->wPanel_0_4, 3, 0);
				 this->weekly_cal_title->Controls->Add(this->wPanel_0_5, 4, 0);
				 this->weekly_cal_title->Controls->Add(this->wPanel_0_6, 5, 0);
				 this->weekly_cal_title->Controls->Add(this->wPanel_0_7, 6, 0);
				 this->weekly_cal_title->Location = System::Drawing::Point(0, 0);
				 this->weekly_cal_title->Margin = System::Windows::Forms::Padding(0);
				 this->weekly_cal_title->Name = L"weekly_cal_title";
				 this->weekly_cal_title->RowCount = 1;
				 this->weekly_cal_title->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->weekly_cal_title->Size = System::Drawing::Size(1184, 42);
				 this->weekly_cal_title->TabIndex = 14;
				 // 
				 // wPanel_0_1
				 // 
				 this->wPanel_0_1->Controls->Add(this->wWDay_0_1);
				 this->wPanel_0_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_0_1->Location = System::Drawing::Point(1, 1);
				 this->wPanel_0_1->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_0_1->Name = L"wPanel_0_1";
				 this->wPanel_0_1->Size = System::Drawing::Size(168, 40);
				 this->wPanel_0_1->TabIndex = 49;
				 // 
				 // wWDay_0_1
				 // 
				 this->wWDay_0_1->AutoSize = true;
				 this->wWDay_0_1->Location = System::Drawing::Point(3, 9);
				 this->wWDay_0_1->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wWDay_0_1->Name = L"wWDay_0_1";
				 this->wWDay_0_1->Size = System::Drawing::Size(51, 20);
				 this->wWDay_0_1->TabIndex = 2;
				 this->wWDay_0_1->Text = L"label1";
				 // 
				 // wPanel_0_2
				 // 
				 this->wPanel_0_2->Controls->Add(this->wWDay_0_2);
				 this->wPanel_0_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_0_2->Location = System::Drawing::Point(170, 1);
				 this->wPanel_0_2->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_0_2->Name = L"wPanel_0_2";
				 this->wPanel_0_2->Size = System::Drawing::Size(168, 40);
				 this->wPanel_0_2->TabIndex = 50;
				 // 
				 // wWDay_0_2
				 // 
				 this->wWDay_0_2->AutoSize = true;
				 this->wWDay_0_2->Location = System::Drawing::Point(3, 9);
				 this->wWDay_0_2->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wWDay_0_2->Name = L"wWDay_0_2";
				 this->wWDay_0_2->Size = System::Drawing::Size(51, 20);
				 this->wWDay_0_2->TabIndex = 1;
				 this->wWDay_0_2->Text = L"label2";
				 // 
				 // wPanel_0_3
				 // 
				 this->wPanel_0_3->Controls->Add(this->wWDay_0_3);
				 this->wPanel_0_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_0_3->Location = System::Drawing::Point(339, 1);
				 this->wPanel_0_3->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_0_3->Name = L"wPanel_0_3";
				 this->wPanel_0_3->Size = System::Drawing::Size(168, 40);
				 this->wPanel_0_3->TabIndex = 51;
				 // 
				 // wWDay_0_3
				 // 
				 this->wWDay_0_3->AutoSize = true;
				 this->wWDay_0_3->Location = System::Drawing::Point(3, 9);
				 this->wWDay_0_3->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wWDay_0_3->Name = L"wWDay_0_3";
				 this->wWDay_0_3->Size = System::Drawing::Size(51, 20);
				 this->wWDay_0_3->TabIndex = 2;
				 this->wWDay_0_3->Text = L"label3";
				 // 
				 // wPanel_0_4
				 // 
				 this->wPanel_0_4->Controls->Add(this->wWDay_0_4);
				 this->wPanel_0_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_0_4->Location = System::Drawing::Point(508, 1);
				 this->wPanel_0_4->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_0_4->Name = L"wPanel_0_4";
				 this->wPanel_0_4->Size = System::Drawing::Size(168, 40);
				 this->wPanel_0_4->TabIndex = 52;
				 // 
				 // wWDay_0_4
				 // 
				 this->wWDay_0_4->AutoSize = true;
				 this->wWDay_0_4->Location = System::Drawing::Point(3, 9);
				 this->wWDay_0_4->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wWDay_0_4->Name = L"wWDay_0_4";
				 this->wWDay_0_4->Size = System::Drawing::Size(51, 20);
				 this->wWDay_0_4->TabIndex = 3;
				 this->wWDay_0_4->Text = L"label4";
				 // 
				 // wPanel_0_5
				 // 
				 this->wPanel_0_5->Controls->Add(this->wWDay_0_5);
				 this->wPanel_0_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_0_5->Location = System::Drawing::Point(677, 1);
				 this->wPanel_0_5->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_0_5->Name = L"wPanel_0_5";
				 this->wPanel_0_5->Size = System::Drawing::Size(168, 40);
				 this->wPanel_0_5->TabIndex = 53;
				 // 
				 // wWDay_0_5
				 // 
				 this->wWDay_0_5->AutoSize = true;
				 this->wWDay_0_5->Location = System::Drawing::Point(3, 9);
				 this->wWDay_0_5->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wWDay_0_5->Name = L"wWDay_0_5";
				 this->wWDay_0_5->Size = System::Drawing::Size(51, 20);
				 this->wWDay_0_5->TabIndex = 4;
				 this->wWDay_0_5->Text = L"label5";
				 // 
				 // wPanel_0_6
				 // 
				 this->wPanel_0_6->Controls->Add(this->wWDay_0_6);
				 this->wPanel_0_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_0_6->Location = System::Drawing::Point(846, 1);
				 this->wPanel_0_6->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_0_6->Name = L"wPanel_0_6";
				 this->wPanel_0_6->Size = System::Drawing::Size(168, 40);
				 this->wPanel_0_6->TabIndex = 54;
				 // 
				 // wWDay_0_6
				 // 
				 this->wWDay_0_6->AutoSize = true;
				 this->wWDay_0_6->Location = System::Drawing::Point(3, 9);
				 this->wWDay_0_6->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wWDay_0_6->Name = L"wWDay_0_6";
				 this->wWDay_0_6->Size = System::Drawing::Size(51, 20);
				 this->wWDay_0_6->TabIndex = 5;
				 this->wWDay_0_6->Text = L"label6";
				 // 
				 // wPanel_0_7
				 // 
				 this->wPanel_0_7->Controls->Add(this->wWDay_0_7);
				 this->wPanel_0_7->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_0_7->Location = System::Drawing::Point(1015, 1);
				 this->wPanel_0_7->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_0_7->Name = L"wPanel_0_7";
				 this->wPanel_0_7->Size = System::Drawing::Size(168, 40);
				 this->wPanel_0_7->TabIndex = 55;
				 // 
				 // wWDay_0_7
				 // 
				 this->wWDay_0_7->AutoSize = true;
				 this->wWDay_0_7->Location = System::Drawing::Point(3, 9);
				 this->wWDay_0_7->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wWDay_0_7->Name = L"wWDay_0_7";
				 this->wWDay_0_7->Size = System::Drawing::Size(51, 20);
				 this->wWDay_0_7->TabIndex = 6;
				 this->wWDay_0_7->Text = L"label7";
				 // 
				 // wPanel_body
				 // 
				 this->wPanel_body->AutoScroll = true;
				 this->wPanel_body->Controls->Add(this->weekly_cal);
				 this->wPanel_body->Location = System::Drawing::Point(58, 42);
				 this->wPanel_body->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_body->Name = L"wPanel_body";
				 this->wPanel_body->Size = System::Drawing::Size(1293, 838);
				 this->wPanel_body->TabIndex = 15;
				 // 
				 // weekly_cal
				 // 
				 this->weekly_cal->AutoSize = true;
				 this->weekly_cal->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->weekly_cal->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->weekly_cal->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->weekly_cal->ColumnCount = 8;
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 78)));
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 168)));
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 168)));
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 168)));
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 168)));
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 168)));
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 168)));
				 this->weekly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 168)));
				 this->weekly_cal->Controls->Add(this->wPanel_1_7, 7, 0);
				 this->weekly_cal->Controls->Add(this->wPanel_1_6, 6, 0);
				 this->weekly_cal->Controls->Add(this->wPanel_1_5, 5, 0);
				 this->weekly_cal->Controls->Add(this->wPanel_1_4, 4, 0);
				 this->weekly_cal->Controls->Add(this->wPanel_1_3, 3, 0);
				 this->weekly_cal->Controls->Add(this->wPanel_1_2, 2, 0);
				 this->weekly_cal->Controls->Add(this->wPanel_18_0, 0, 34);
				 this->weekly_cal->Controls->Add(this->wPanel_17_0, 0, 32);
				 this->weekly_cal->Controls->Add(this->wPanel_16_0, 0, 30);
				 this->weekly_cal->Controls->Add(this->wPanel_15_0, 0, 28);
				 this->weekly_cal->Controls->Add(this->wPanel_14_0, 0, 26);
				 this->weekly_cal->Controls->Add(this->wPanel_13_0, 0, 24);
				 this->weekly_cal->Controls->Add(this->wPanel_12_0, 0, 22);
				 this->weekly_cal->Controls->Add(this->wPanel_11_0, 0, 20);
				 this->weekly_cal->Controls->Add(this->wPanel_10_0, 0, 18);
				 this->weekly_cal->Controls->Add(this->wPanel_9_0, 0, 16);
				 this->weekly_cal->Controls->Add(this->wPanel_8_0, 0, 14);
				 this->weekly_cal->Controls->Add(this->wPanel_7_0, 0, 12);
				 this->weekly_cal->Controls->Add(this->wPanel_6_0, 0, 10);
				 this->weekly_cal->Controls->Add(this->wPanel_4_0, 0, 6);
				 this->weekly_cal->Controls->Add(this->wPanel_2_0, 0, 2);
				 this->weekly_cal->Controls->Add(this->wPanel_3_0, 0, 4);
				 this->weekly_cal->Controls->Add(this->wPanel_5_0, 0, 8);
				 this->weekly_cal->Controls->Add(this->wPanel_24_0, 0, 46);
				 this->weekly_cal->Controls->Add(this->wPanel_23_0, 0, 44);
				 this->weekly_cal->Controls->Add(this->wPanel_22_0, 0, 42);
				 this->weekly_cal->Controls->Add(this->wPanel_21_0, 0, 40);
				 this->weekly_cal->Controls->Add(this->wPanel_20_0, 0, 38);
				 this->weekly_cal->Controls->Add(this->wPanel_19_0, 0, 36);
				 this->weekly_cal->Controls->Add(this->wPanel_1_0, 0, 0);
				 this->weekly_cal->Controls->Add(this->wPanel_1_1, 1, 0);
				 this->weekly_cal->Location = System::Drawing::Point(0, 0);
				 this->weekly_cal->Margin = System::Windows::Forms::Padding(0);
				 this->weekly_cal->Name = L"weekly_cal";
				 this->weekly_cal->RowCount = 48;
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->weekly_cal->Size = System::Drawing::Size(1263, 1729);
				 this->weekly_cal->TabIndex = 0;
				 // 
				 // wPanel_1_7
				 // 
				 this->wPanel_1_7->BackColor = System::Drawing::Color::Transparent;
				 this->wPanel_1_7->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_7->Location = System::Drawing::Point(1094, 1);
				 this->wPanel_1_7->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_7->Name = L"wPanel_1_7";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_7, 48);
				 this->wPanel_1_7->Size = System::Drawing::Size(168, 1727);
				 this->wPanel_1_7->TabIndex = 108;
				 this->wPanel_1_7->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->wPanel_1_7->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->wPanel_1_7->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wPanel_1_6
				 // 
				 this->wPanel_1_6->BackColor = System::Drawing::Color::Transparent;
				 this->wPanel_1_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_6->Location = System::Drawing::Point(925, 1);
				 this->wPanel_1_6->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_6->Name = L"wPanel_1_6";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_6, 48);
				 this->wPanel_1_6->Size = System::Drawing::Size(168, 1727);
				 this->wPanel_1_6->TabIndex = 107;
				 this->wPanel_1_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->wPanel_1_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->wPanel_1_6->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wPanel_1_5
				 // 
				 this->wPanel_1_5->BackColor = System::Drawing::Color::Transparent;
				 this->wPanel_1_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_5->Location = System::Drawing::Point(756, 1);
				 this->wPanel_1_5->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_5->Name = L"wPanel_1_5";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_5, 48);
				 this->wPanel_1_5->Size = System::Drawing::Size(168, 1727);
				 this->wPanel_1_5->TabIndex = 106;
				 this->wPanel_1_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->wPanel_1_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->wPanel_1_5->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wPanel_1_4
				 // 
				 this->wPanel_1_4->BackColor = System::Drawing::Color::Transparent;
				 this->wPanel_1_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_4->Location = System::Drawing::Point(587, 1);
				 this->wPanel_1_4->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_4->Name = L"wPanel_1_4";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_4, 48);
				 this->wPanel_1_4->Size = System::Drawing::Size(168, 1727);
				 this->wPanel_1_4->TabIndex = 105;
				 this->wPanel_1_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->wPanel_1_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->wPanel_1_4->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wPanel_1_3
				 // 
				 this->wPanel_1_3->BackColor = System::Drawing::Color::Transparent;
				 this->wPanel_1_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_3->Location = System::Drawing::Point(418, 1);
				 this->wPanel_1_3->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_3->Name = L"wPanel_1_3";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_3, 48);
				 this->wPanel_1_3->Size = System::Drawing::Size(168, 1727);
				 this->wPanel_1_3->TabIndex = 104;
				 this->wPanel_1_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->wPanel_1_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->wPanel_1_3->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wPanel_1_2
				 // 
				 this->wPanel_1_2->BackColor = System::Drawing::Color::Transparent;
				 this->wPanel_1_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_2->Location = System::Drawing::Point(249, 1);
				 this->wPanel_1_2->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_2->Name = L"wPanel_1_2";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_2, 48);
				 this->wPanel_1_2->Size = System::Drawing::Size(168, 1727);
				 this->wPanel_1_2->TabIndex = 103;
				 this->wPanel_1_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->wPanel_1_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->wPanel_1_2->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wPanel_18_0
				 // 
				 this->wPanel_18_0->Controls->Add(this->wHr_18_0);
				 this->wPanel_18_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_18_0->Location = System::Drawing::Point(1, 1225);
				 this->wPanel_18_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_18_0->Name = L"wPanel_18_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_18_0, 2);
				 this->wPanel_18_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_18_0->TabIndex = 99;
				 this->wPanel_18_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_18_0
				 // 
				 this->wHr_18_0->AutoSize = true;
				 this->wHr_18_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_18_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_18_0->Name = L"wHr_18_0";
				 this->wHr_18_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_18_0->TabIndex = 3;
				 this->wHr_18_0->Text = L"17:00";
				 this->wHr_18_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_17_0
				 // 
				 this->wPanel_17_0->Controls->Add(this->wHr_17_0);
				 this->wPanel_17_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_17_0->Location = System::Drawing::Point(1, 1153);
				 this->wPanel_17_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_17_0->Name = L"wPanel_17_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_17_0, 2);
				 this->wPanel_17_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_17_0->TabIndex = 99;
				 this->wPanel_17_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_17_0
				 // 
				 this->wHr_17_0->AutoSize = true;
				 this->wHr_17_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_17_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_17_0->Name = L"wHr_17_0";
				 this->wHr_17_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_17_0->TabIndex = 3;
				 this->wHr_17_0->Text = L"16:00";
				 this->wHr_17_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_16_0
				 // 
				 this->wPanel_16_0->Controls->Add(this->wHr_16_0);
				 this->wPanel_16_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_16_0->Location = System::Drawing::Point(1, 1081);
				 this->wPanel_16_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_16_0->Name = L"wPanel_16_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_16_0, 2);
				 this->wPanel_16_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_16_0->TabIndex = 99;
				 this->wPanel_16_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_16_0
				 // 
				 this->wHr_16_0->AutoSize = true;
				 this->wHr_16_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_16_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_16_0->Name = L"wHr_16_0";
				 this->wHr_16_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_16_0->TabIndex = 3;
				 this->wHr_16_0->Text = L"15:00";
				 this->wHr_16_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_15_0
				 // 
				 this->wPanel_15_0->Controls->Add(this->wHr_15_0);
				 this->wPanel_15_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_15_0->Location = System::Drawing::Point(1, 1009);
				 this->wPanel_15_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_15_0->Name = L"wPanel_15_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_15_0, 2);
				 this->wPanel_15_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_15_0->TabIndex = 99;
				 this->wPanel_15_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_15_0
				 // 
				 this->wHr_15_0->AutoSize = true;
				 this->wHr_15_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_15_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_15_0->Name = L"wHr_15_0";
				 this->wHr_15_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_15_0->TabIndex = 3;
				 this->wHr_15_0->Text = L"14:00";
				 this->wHr_15_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_14_0
				 // 
				 this->wPanel_14_0->Controls->Add(this->wHr_14_0);
				 this->wPanel_14_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_14_0->Location = System::Drawing::Point(1, 937);
				 this->wPanel_14_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_14_0->Name = L"wPanel_14_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_14_0, 2);
				 this->wPanel_14_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_14_0->TabIndex = 99;
				 this->wPanel_14_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_14_0
				 // 
				 this->wHr_14_0->AutoSize = true;
				 this->wHr_14_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_14_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_14_0->Name = L"wHr_14_0";
				 this->wHr_14_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_14_0->TabIndex = 3;
				 this->wHr_14_0->Text = L"13:00";
				 this->wHr_14_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_13_0
				 // 
				 this->wPanel_13_0->Controls->Add(this->wHr_13_0);
				 this->wPanel_13_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_13_0->Location = System::Drawing::Point(1, 865);
				 this->wPanel_13_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_13_0->Name = L"wPanel_13_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_13_0, 2);
				 this->wPanel_13_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_13_0->TabIndex = 99;
				 this->wPanel_13_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_13_0
				 // 
				 this->wHr_13_0->AutoSize = true;
				 this->wHr_13_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_13_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_13_0->Name = L"wHr_13_0";
				 this->wHr_13_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_13_0->TabIndex = 3;
				 this->wHr_13_0->Text = L"12:00";
				 this->wHr_13_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_12_0
				 // 
				 this->wPanel_12_0->Controls->Add(this->wHr_12_0);
				 this->wPanel_12_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_12_0->Location = System::Drawing::Point(1, 793);
				 this->wPanel_12_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_12_0->Name = L"wPanel_12_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_12_0, 2);
				 this->wPanel_12_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_12_0->TabIndex = 99;
				 this->wPanel_12_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_12_0
				 // 
				 this->wHr_12_0->AutoSize = true;
				 this->wHr_12_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_12_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_12_0->Name = L"wHr_12_0";
				 this->wHr_12_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_12_0->TabIndex = 3;
				 this->wHr_12_0->Text = L"11:00";
				 this->wHr_12_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_11_0
				 // 
				 this->wPanel_11_0->Controls->Add(this->wHr_11_0);
				 this->wPanel_11_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_11_0->Location = System::Drawing::Point(1, 721);
				 this->wPanel_11_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_11_0->Name = L"wPanel_11_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_11_0, 2);
				 this->wPanel_11_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_11_0->TabIndex = 99;
				 this->wPanel_11_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_11_0
				 // 
				 this->wHr_11_0->AutoSize = true;
				 this->wHr_11_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_11_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_11_0->Name = L"wHr_11_0";
				 this->wHr_11_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_11_0->TabIndex = 3;
				 this->wHr_11_0->Text = L"10:00";
				 this->wHr_11_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_10_0
				 // 
				 this->wPanel_10_0->Controls->Add(this->wHr_10_0);
				 this->wPanel_10_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_10_0->Location = System::Drawing::Point(1, 649);
				 this->wPanel_10_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_10_0->Name = L"wPanel_10_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_10_0, 2);
				 this->wPanel_10_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_10_0->TabIndex = 99;
				 this->wPanel_10_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_10_0
				 // 
				 this->wHr_10_0->AutoSize = true;
				 this->wHr_10_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_10_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_10_0->Name = L"wHr_10_0";
				 this->wHr_10_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_10_0->TabIndex = 3;
				 this->wHr_10_0->Text = L"09:00";
				 this->wHr_10_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_9_0
				 // 
				 this->wPanel_9_0->Controls->Add(this->wHr_9_0);
				 this->wPanel_9_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_9_0->Location = System::Drawing::Point(1, 577);
				 this->wPanel_9_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_9_0->Name = L"wPanel_9_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_9_0, 2);
				 this->wPanel_9_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_9_0->TabIndex = 99;
				 this->wPanel_9_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_9_0
				 // 
				 this->wHr_9_0->AutoSize = true;
				 this->wHr_9_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_9_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_9_0->Name = L"wHr_9_0";
				 this->wHr_9_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_9_0->TabIndex = 3;
				 this->wHr_9_0->Text = L"08:00";
				 this->wHr_9_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_8_0
				 // 
				 this->wPanel_8_0->Controls->Add(this->wHr_8_0);
				 this->wPanel_8_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_8_0->Location = System::Drawing::Point(1, 505);
				 this->wPanel_8_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_8_0->Name = L"wPanel_8_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_8_0, 2);
				 this->wPanel_8_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_8_0->TabIndex = 99;
				 this->wPanel_8_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_8_0
				 // 
				 this->wHr_8_0->AutoSize = true;
				 this->wHr_8_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_8_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_8_0->Name = L"wHr_8_0";
				 this->wHr_8_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_8_0->TabIndex = 3;
				 this->wHr_8_0->Text = L"07:00";
				 this->wHr_8_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_7_0
				 // 
				 this->wPanel_7_0->Controls->Add(this->wHr_7_0);
				 this->wPanel_7_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_7_0->Location = System::Drawing::Point(1, 433);
				 this->wPanel_7_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_7_0->Name = L"wPanel_7_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_7_0, 2);
				 this->wPanel_7_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_7_0->TabIndex = 99;
				 this->wPanel_7_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_7_0
				 // 
				 this->wHr_7_0->AutoSize = true;
				 this->wHr_7_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_7_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_7_0->Name = L"wHr_7_0";
				 this->wHr_7_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_7_0->TabIndex = 3;
				 this->wHr_7_0->Text = L"06:00";
				 this->wHr_7_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_6_0
				 // 
				 this->wPanel_6_0->Controls->Add(this->wHr_6_0);
				 this->wPanel_6_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_6_0->Location = System::Drawing::Point(1, 361);
				 this->wPanel_6_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_6_0->Name = L"wPanel_6_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_6_0, 2);
				 this->wPanel_6_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_6_0->TabIndex = 99;
				 this->wPanel_6_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_6_0
				 // 
				 this->wHr_6_0->AutoSize = true;
				 this->wHr_6_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_6_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_6_0->Name = L"wHr_6_0";
				 this->wHr_6_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_6_0->TabIndex = 3;
				 this->wHr_6_0->Text = L"05:00";
				 this->wHr_6_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_4_0
				 // 
				 this->wPanel_4_0->Controls->Add(this->wHr_4_0);
				 this->wPanel_4_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_4_0->Location = System::Drawing::Point(1, 217);
				 this->wPanel_4_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_4_0->Name = L"wPanel_4_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_4_0, 2);
				 this->wPanel_4_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_4_0->TabIndex = 99;
				 this->wPanel_4_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_4_0
				 // 
				 this->wHr_4_0->AutoSize = true;
				 this->wHr_4_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_4_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_4_0->Name = L"wHr_4_0";
				 this->wHr_4_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_4_0->TabIndex = 3;
				 this->wHr_4_0->Text = L"03:00";
				 this->wHr_4_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_2_0
				 // 
				 this->wPanel_2_0->Controls->Add(this->wHr_2_0);
				 this->wPanel_2_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_2_0->Location = System::Drawing::Point(1, 73);
				 this->wPanel_2_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_2_0->Name = L"wPanel_2_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_2_0, 2);
				 this->wPanel_2_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_2_0->TabIndex = 99;
				 this->wPanel_2_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_2_0
				 // 
				 this->wHr_2_0->AutoSize = true;
				 this->wHr_2_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_2_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_2_0->Name = L"wHr_2_0";
				 this->wHr_2_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_2_0->TabIndex = 3;
				 this->wHr_2_0->Text = L"01:00";
				 this->wHr_2_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_3_0
				 // 
				 this->wPanel_3_0->Controls->Add(this->wHr_3_0);
				 this->wPanel_3_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_3_0->Location = System::Drawing::Point(1, 145);
				 this->wPanel_3_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_3_0->Name = L"wPanel_3_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_3_0, 2);
				 this->wPanel_3_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_3_0->TabIndex = 100;
				 this->wPanel_3_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_3_0
				 // 
				 this->wHr_3_0->AutoSize = true;
				 this->wHr_3_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_3_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_3_0->Name = L"wHr_3_0";
				 this->wHr_3_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_3_0->TabIndex = 3;
				 this->wHr_3_0->Text = L"02:00";
				 this->wHr_3_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_5_0
				 // 
				 this->wPanel_5_0->Controls->Add(this->wHr_5_0);
				 this->wPanel_5_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_5_0->Location = System::Drawing::Point(1, 289);
				 this->wPanel_5_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_5_0->Name = L"wPanel_5_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_5_0, 2);
				 this->wPanel_5_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_5_0->TabIndex = 101;
				 this->wPanel_5_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_5_0
				 // 
				 this->wHr_5_0->AutoSize = true;
				 this->wHr_5_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_5_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_5_0->Name = L"wHr_5_0";
				 this->wHr_5_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_5_0->TabIndex = 3;
				 this->wHr_5_0->Text = L"04:00";
				 this->wHr_5_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_24_0
				 // 
				 this->wPanel_24_0->Controls->Add(this->wHr_24_0);
				 this->wPanel_24_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_24_0->Location = System::Drawing::Point(1, 1657);
				 this->wPanel_24_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_24_0->Name = L"wPanel_24_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_24_0, 2);
				 this->wPanel_24_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_24_0->TabIndex = 99;
				 this->wPanel_24_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_24_0
				 // 
				 this->wHr_24_0->AutoSize = true;
				 this->wHr_24_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_24_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_24_0->Name = L"wHr_24_0";
				 this->wHr_24_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_24_0->TabIndex = 3;
				 this->wHr_24_0->Text = L"23:00";
				 this->wHr_24_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_23_0
				 // 
				 this->wPanel_23_0->Controls->Add(this->wHr_23_0);
				 this->wPanel_23_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_23_0->Location = System::Drawing::Point(1, 1585);
				 this->wPanel_23_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_23_0->Name = L"wPanel_23_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_23_0, 2);
				 this->wPanel_23_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_23_0->TabIndex = 99;
				 this->wPanel_23_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_23_0
				 // 
				 this->wHr_23_0->AutoSize = true;
				 this->wHr_23_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_23_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_23_0->Name = L"wHr_23_0";
				 this->wHr_23_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_23_0->TabIndex = 3;
				 this->wHr_23_0->Text = L"22:00";
				 this->wHr_23_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_22_0
				 // 
				 this->wPanel_22_0->Controls->Add(this->wHr_22_0);
				 this->wPanel_22_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_22_0->Location = System::Drawing::Point(1, 1513);
				 this->wPanel_22_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_22_0->Name = L"wPanel_22_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_22_0, 2);
				 this->wPanel_22_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_22_0->TabIndex = 99;
				 this->wPanel_22_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_22_0
				 // 
				 this->wHr_22_0->AutoSize = true;
				 this->wHr_22_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_22_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_22_0->Name = L"wHr_22_0";
				 this->wHr_22_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_22_0->TabIndex = 3;
				 this->wHr_22_0->Text = L"21:00";
				 this->wHr_22_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_21_0
				 // 
				 this->wPanel_21_0->Controls->Add(this->wHr_21_0);
				 this->wPanel_21_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_21_0->Location = System::Drawing::Point(1, 1441);
				 this->wPanel_21_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_21_0->Name = L"wPanel_21_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_21_0, 2);
				 this->wPanel_21_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_21_0->TabIndex = 99;
				 this->wPanel_21_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_21_0
				 // 
				 this->wHr_21_0->AutoSize = true;
				 this->wHr_21_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_21_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_21_0->Name = L"wHr_21_0";
				 this->wHr_21_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_21_0->TabIndex = 3;
				 this->wHr_21_0->Text = L"20:00";
				 this->wHr_21_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_20_0
				 // 
				 this->wPanel_20_0->Controls->Add(this->wHr_20_0);
				 this->wPanel_20_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_20_0->Location = System::Drawing::Point(1, 1369);
				 this->wPanel_20_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_20_0->Name = L"wPanel_20_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_20_0, 2);
				 this->wPanel_20_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_20_0->TabIndex = 99;
				 this->wPanel_20_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_20_0
				 // 
				 this->wHr_20_0->AutoSize = true;
				 this->wHr_20_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_20_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_20_0->Name = L"wHr_20_0";
				 this->wHr_20_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_20_0->TabIndex = 3;
				 this->wHr_20_0->Text = L"19:00";
				 this->wHr_20_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_19_0
				 // 
				 this->wPanel_19_0->Controls->Add(this->wHr_19_0);
				 this->wPanel_19_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_19_0->Location = System::Drawing::Point(1, 1297);
				 this->wPanel_19_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_19_0->Name = L"wPanel_19_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_19_0, 2);
				 this->wPanel_19_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_19_0->TabIndex = 99;
				 this->wPanel_19_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_19_0
				 // 
				 this->wHr_19_0->AutoSize = true;
				 this->wHr_19_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_19_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_19_0->Name = L"wHr_19_0";
				 this->wHr_19_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_19_0->TabIndex = 3;
				 this->wHr_19_0->Text = L"18:00";
				 this->wHr_19_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_1_0
				 // 
				 this->wPanel_1_0->Controls->Add(this->wHr_1_0);
				 this->wPanel_1_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_0->Location = System::Drawing::Point(1, 1);
				 this->wPanel_1_0->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_0->Name = L"wPanel_1_0";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_0, 2);
				 this->wPanel_1_0->Size = System::Drawing::Size(78, 71);
				 this->wPanel_1_0->TabIndex = 98;
				 this->wPanel_1_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // wHr_1_0
				 // 
				 this->wHr_1_0->AutoSize = true;
				 this->wHr_1_0->Location = System::Drawing::Point(27, 5);
				 this->wHr_1_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->wHr_1_0->Name = L"wHr_1_0";
				 this->wHr_1_0->Size = System::Drawing::Size(49, 20);
				 this->wHr_1_0->TabIndex = 3;
				 this->wHr_1_0->Text = L"00:00";
				 this->wHr_1_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // wPanel_1_1
				 // 
				 this->wPanel_1_1->BackColor = System::Drawing::Color::Transparent;
				 this->wPanel_1_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->wPanel_1_1->Location = System::Drawing::Point(80, 1);
				 this->wPanel_1_1->Margin = System::Windows::Forms::Padding(0);
				 this->wPanel_1_1->Name = L"wPanel_1_1";
				 this->weekly_cal->SetRowSpan(this->wPanel_1_1, 48);
				 this->wPanel_1_1->Size = System::Drawing::Size(168, 1727);
				 this->wPanel_1_1->TabIndex = 102;
				 this->wPanel_1_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->wPanel_1_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->wPanel_1_1->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dPanel
				 // 
				 this->dPanel->Controls->Add(this->daily_monthly_cal);
				 this->dPanel->Controls->Add(this->dWDay);
				 this->dPanel->Controls->Add(this->dDay);
				 this->dPanel->Controls->Add(this->dBtmLine);
				 this->dPanel->Controls->Add(this->dTopLine);
				 this->dPanel->Controls->Add(this->dPanel_body);
				 this->dPanel->Location = System::Drawing::Point(0, 88);
				 this->dPanel->Name = L"dPanel";
				 this->dPanel->Size = System::Drawing::Size(1389, 883);
				 this->dPanel->TabIndex = 15;
				 // 
				 // daily_monthly_cal
				 // 
				 this->daily_monthly_cal->AutoSize = true;
				 this->daily_monthly_cal->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->daily_monthly_cal->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->daily_monthly_cal->ColumnCount = 7;
				 this->daily_monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 81)));
				 this->daily_monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 81)));
				 this->daily_monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 81)));
				 this->daily_monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 81)));
				 this->daily_monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 81)));
				 this->daily_monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 81)));
				 this->daily_monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 81)));
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_6_2, 2, 6);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_6_1, 1, 6);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_6_0, 0, 6);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_6_3, 3, 6);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_6_6, 6, 6);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_6_5, 5, 6);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_6_4, 4, 6);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_5_6, 6, 5);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_5_5, 5, 5);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_5_4, 4, 5);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_5_3, 3, 5);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_5_2, 2, 5);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_5_1, 1, 5);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_5_0, 0, 5);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_4_6, 6, 4);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_4_5, 5, 4);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_4_4, 4, 4);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_4_3, 3, 4);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_4_2, 2, 4);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_4_1, 1, 4);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_4_0, 0, 4);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_3_6, 6, 3);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_3_5, 5, 3);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_3_4, 4, 3);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_3_3, 3, 3);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_3_2, 2, 3);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_3_1, 1, 3);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_3_0, 0, 3);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_2_6, 6, 2);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_2_5, 5, 2);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_2_4, 4, 2);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_2_3, 3, 2);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_2_2, 2, 2);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_2_1, 1, 2);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_2_0, 0, 2);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_1_6, 6, 1);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_1_5, 5, 1);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_1_4, 4, 1);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_1_3, 3, 1);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_1_2, 2, 1);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_1_1, 1, 1);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_1_0, 0, 1);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_0_6, 6, 0);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_0_5, 5, 0);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_0_4, 4, 0);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_0_3, 3, 0);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_0_2, 2, 0);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_0_1, 1, 0);
				 this->daily_monthly_cal->Controls->Add(this->dMPanel_0_0, 0, 0);
				 this->daily_monthly_cal->Location = System::Drawing::Point(58, 337);
				 this->daily_monthly_cal->Margin = System::Windows::Forms::Padding(0);
				 this->daily_monthly_cal->Name = L"daily_monthly_cal";
				 this->daily_monthly_cal->RowCount = 7;
				 this->daily_monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 43)));
				 this->daily_monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 69)));
				 this->daily_monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 69)));
				 this->daily_monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 69)));
				 this->daily_monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 69)));
				 this->daily_monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 69)));
				 this->daily_monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 69)));
				 this->daily_monthly_cal->Size = System::Drawing::Size(575, 465);
				 this->daily_monthly_cal->TabIndex = 3;
				 // 
				 // dMPanel_6_2
				 // 
				 this->dMPanel_6_2->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_6_2->Controls->Add(this->dDay_6_2);
				 this->dMPanel_6_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_6_2->Location = System::Drawing::Point(165, 395);
				 this->dMPanel_6_2->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_6_2->Name = L"dMPanel_6_2";
				 this->dMPanel_6_2->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_6_2->TabIndex = 48;
				 // 
				 // dDay_6_2
				 // 
				 this->dDay_6_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_6_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_6_2->Location = System::Drawing::Point(0, 0);
				 this->dDay_6_2->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_6_2->Name = L"dDay_6_2";
				 this->dDay_6_2->Size = System::Drawing::Size(81, 69);
				 this->dDay_6_2->TabIndex = 1;
				 this->dDay_6_2->Text = L"label49";
				 this->dDay_6_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_6_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_6_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_6_1
				 // 
				 this->dMPanel_6_1->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_6_1->Controls->Add(this->dDay_6_1);
				 this->dMPanel_6_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_6_1->Location = System::Drawing::Point(83, 395);
				 this->dMPanel_6_1->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_6_1->Name = L"dMPanel_6_1";
				 this->dMPanel_6_1->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_6_1->TabIndex = 47;
				 // 
				 // dDay_6_1
				 // 
				 this->dDay_6_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_6_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_6_1->Location = System::Drawing::Point(0, 0);
				 this->dDay_6_1->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_6_1->Name = L"dDay_6_1";
				 this->dDay_6_1->Size = System::Drawing::Size(81, 69);
				 this->dDay_6_1->TabIndex = 1;
				 this->dDay_6_1->Text = L"label48";
				 this->dDay_6_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_6_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_6_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_6_0
				 // 
				 this->dMPanel_6_0->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_6_0->Controls->Add(this->dDay_6_0);
				 this->dMPanel_6_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_6_0->Location = System::Drawing::Point(1, 395);
				 this->dMPanel_6_0->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_6_0->Name = L"dMPanel_6_0";
				 this->dMPanel_6_0->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_6_0->TabIndex = 46;
				 // 
				 // dDay_6_0
				 // 
				 this->dDay_6_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_6_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_6_0->Location = System::Drawing::Point(0, 0);
				 this->dDay_6_0->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_6_0->Name = L"dDay_6_0";
				 this->dDay_6_0->Size = System::Drawing::Size(81, 69);
				 this->dDay_6_0->TabIndex = 1;
				 this->dDay_6_0->Text = L"label47";
				 this->dDay_6_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_6_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_6_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_6_3
				 // 
				 this->dMPanel_6_3->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_6_3->Controls->Add(this->dDay_6_3);
				 this->dMPanel_6_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_6_3->Location = System::Drawing::Point(247, 395);
				 this->dMPanel_6_3->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_6_3->Name = L"dMPanel_6_3";
				 this->dMPanel_6_3->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_6_3->TabIndex = 45;
				 // 
				 // dDay_6_3
				 // 
				 this->dDay_6_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_6_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_6_3->Location = System::Drawing::Point(0, 0);
				 this->dDay_6_3->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_6_3->Name = L"dDay_6_3";
				 this->dDay_6_3->Size = System::Drawing::Size(81, 69);
				 this->dDay_6_3->TabIndex = 1;
				 this->dDay_6_3->Text = L"label46";
				 this->dDay_6_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_6_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_6_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_6_6
				 // 
				 this->dMPanel_6_6->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_6_6->Controls->Add(this->dDay_6_6);
				 this->dMPanel_6_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_6_6->Location = System::Drawing::Point(493, 395);
				 this->dMPanel_6_6->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_6_6->Name = L"dMPanel_6_6";
				 this->dMPanel_6_6->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_6_6->TabIndex = 44;
				 // 
				 // dDay_6_6
				 // 
				 this->dDay_6_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_6_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_6_6->Location = System::Drawing::Point(0, 0);
				 this->dDay_6_6->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_6_6->Name = L"dDay_6_6";
				 this->dDay_6_6->Size = System::Drawing::Size(81, 69);
				 this->dDay_6_6->TabIndex = 1;
				 this->dDay_6_6->Text = L"label45";
				 this->dDay_6_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_6_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_6_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_6_5
				 // 
				 this->dMPanel_6_5->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_6_5->Controls->Add(this->dDay_6_5);
				 this->dMPanel_6_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_6_5->Location = System::Drawing::Point(411, 395);
				 this->dMPanel_6_5->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_6_5->Name = L"dMPanel_6_5";
				 this->dMPanel_6_5->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_6_5->TabIndex = 43;
				 // 
				 // dDay_6_5
				 // 
				 this->dDay_6_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_6_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_6_5->Location = System::Drawing::Point(0, 0);
				 this->dDay_6_5->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_6_5->Name = L"dDay_6_5";
				 this->dDay_6_5->Size = System::Drawing::Size(81, 69);
				 this->dDay_6_5->TabIndex = 1;
				 this->dDay_6_5->Text = L"label44";
				 this->dDay_6_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_6_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_6_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_6_4
				 // 
				 this->dMPanel_6_4->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_6_4->Controls->Add(this->dDay_6_4);
				 this->dMPanel_6_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_6_4->Location = System::Drawing::Point(329, 395);
				 this->dMPanel_6_4->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_6_4->Name = L"dMPanel_6_4";
				 this->dMPanel_6_4->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_6_4->TabIndex = 42;
				 // 
				 // dDay_6_4
				 // 
				 this->dDay_6_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_6_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_6_4->Location = System::Drawing::Point(0, 0);
				 this->dDay_6_4->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_6_4->Name = L"dDay_6_4";
				 this->dDay_6_4->Size = System::Drawing::Size(81, 69);
				 this->dDay_6_4->TabIndex = 1;
				 this->dDay_6_4->Text = L"label43";
				 this->dDay_6_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_6_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_6_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_5_6
				 // 
				 this->dMPanel_5_6->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_5_6->Controls->Add(this->dDay_5_6);
				 this->dMPanel_5_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_5_6->Location = System::Drawing::Point(493, 325);
				 this->dMPanel_5_6->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_5_6->Name = L"dMPanel_5_6";
				 this->dMPanel_5_6->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_5_6->TabIndex = 41;
				 // 
				 // dDay_5_6
				 // 
				 this->dDay_5_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_5_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_5_6->Location = System::Drawing::Point(0, 0);
				 this->dDay_5_6->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_5_6->Name = L"dDay_5_6";
				 this->dDay_5_6->Size = System::Drawing::Size(81, 69);
				 this->dDay_5_6->TabIndex = 1;
				 this->dDay_5_6->Text = L"label42";
				 this->dDay_5_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_5_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_5_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_5_5
				 // 
				 this->dMPanel_5_5->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_5_5->Controls->Add(this->dDay_5_5);
				 this->dMPanel_5_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_5_5->Location = System::Drawing::Point(411, 325);
				 this->dMPanel_5_5->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_5_5->Name = L"dMPanel_5_5";
				 this->dMPanel_5_5->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_5_5->TabIndex = 40;
				 // 
				 // dDay_5_5
				 // 
				 this->dDay_5_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_5_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_5_5->Location = System::Drawing::Point(0, 0);
				 this->dDay_5_5->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_5_5->Name = L"dDay_5_5";
				 this->dDay_5_5->Size = System::Drawing::Size(81, 69);
				 this->dDay_5_5->TabIndex = 1;
				 this->dDay_5_5->Text = L"label41";
				 this->dDay_5_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_5_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_5_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_5_4
				 // 
				 this->dMPanel_5_4->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_5_4->Controls->Add(this->dDay_5_4);
				 this->dMPanel_5_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_5_4->Location = System::Drawing::Point(329, 325);
				 this->dMPanel_5_4->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_5_4->Name = L"dMPanel_5_4";
				 this->dMPanel_5_4->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_5_4->TabIndex = 39;
				 // 
				 // dDay_5_4
				 // 
				 this->dDay_5_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_5_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_5_4->Location = System::Drawing::Point(0, 0);
				 this->dDay_5_4->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_5_4->Name = L"dDay_5_4";
				 this->dDay_5_4->Size = System::Drawing::Size(81, 69);
				 this->dDay_5_4->TabIndex = 1;
				 this->dDay_5_4->Text = L"label40";
				 this->dDay_5_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_5_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_5_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_5_3
				 // 
				 this->dMPanel_5_3->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_5_3->Controls->Add(this->dDay_5_3);
				 this->dMPanel_5_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_5_3->Location = System::Drawing::Point(247, 325);
				 this->dMPanel_5_3->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_5_3->Name = L"dMPanel_5_3";
				 this->dMPanel_5_3->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_5_3->TabIndex = 38;
				 // 
				 // dDay_5_3
				 // 
				 this->dDay_5_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_5_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_5_3->Location = System::Drawing::Point(0, 0);
				 this->dDay_5_3->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_5_3->Name = L"dDay_5_3";
				 this->dDay_5_3->Size = System::Drawing::Size(81, 69);
				 this->dDay_5_3->TabIndex = 1;
				 this->dDay_5_3->Text = L"label39";
				 this->dDay_5_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_5_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_5_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_5_2
				 // 
				 this->dMPanel_5_2->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_5_2->Controls->Add(this->dDay_5_2);
				 this->dMPanel_5_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_5_2->Location = System::Drawing::Point(165, 325);
				 this->dMPanel_5_2->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_5_2->Name = L"dMPanel_5_2";
				 this->dMPanel_5_2->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_5_2->TabIndex = 37;
				 // 
				 // dDay_5_2
				 // 
				 this->dDay_5_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_5_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_5_2->Location = System::Drawing::Point(0, 0);
				 this->dDay_5_2->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_5_2->Name = L"dDay_5_2";
				 this->dDay_5_2->Size = System::Drawing::Size(81, 69);
				 this->dDay_5_2->TabIndex = 1;
				 this->dDay_5_2->Text = L"label38";
				 this->dDay_5_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_5_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_5_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_5_1
				 // 
				 this->dMPanel_5_1->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_5_1->Controls->Add(this->dDay_5_1);
				 this->dMPanel_5_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_5_1->Location = System::Drawing::Point(83, 325);
				 this->dMPanel_5_1->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_5_1->Name = L"dMPanel_5_1";
				 this->dMPanel_5_1->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_5_1->TabIndex = 36;
				 // 
				 // dDay_5_1
				 // 
				 this->dDay_5_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_5_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_5_1->Location = System::Drawing::Point(0, 0);
				 this->dDay_5_1->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_5_1->Name = L"dDay_5_1";
				 this->dDay_5_1->Size = System::Drawing::Size(81, 69);
				 this->dDay_5_1->TabIndex = 1;
				 this->dDay_5_1->Text = L"label37";
				 this->dDay_5_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_5_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_5_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_5_0
				 // 
				 this->dMPanel_5_0->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_5_0->Controls->Add(this->dDay_5_0);
				 this->dMPanel_5_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_5_0->Location = System::Drawing::Point(1, 325);
				 this->dMPanel_5_0->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_5_0->Name = L"dMPanel_5_0";
				 this->dMPanel_5_0->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_5_0->TabIndex = 35;
				 // 
				 // dDay_5_0
				 // 
				 this->dDay_5_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_5_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_5_0->Location = System::Drawing::Point(0, 0);
				 this->dDay_5_0->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_5_0->Name = L"dDay_5_0";
				 this->dDay_5_0->Size = System::Drawing::Size(81, 69);
				 this->dDay_5_0->TabIndex = 1;
				 this->dDay_5_0->Text = L"label36";
				 this->dDay_5_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_5_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_5_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_4_6
				 // 
				 this->dMPanel_4_6->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_4_6->Controls->Add(this->dDay_4_6);
				 this->dMPanel_4_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_4_6->Location = System::Drawing::Point(493, 255);
				 this->dMPanel_4_6->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_4_6->Name = L"dMPanel_4_6";
				 this->dMPanel_4_6->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_4_6->TabIndex = 34;
				 // 
				 // dDay_4_6
				 // 
				 this->dDay_4_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_4_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_4_6->Location = System::Drawing::Point(0, 0);
				 this->dDay_4_6->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_4_6->Name = L"dDay_4_6";
				 this->dDay_4_6->Size = System::Drawing::Size(81, 69);
				 this->dDay_4_6->TabIndex = 1;
				 this->dDay_4_6->Text = L"label35";
				 this->dDay_4_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_4_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_4_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_4_5
				 // 
				 this->dMPanel_4_5->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_4_5->Controls->Add(this->dDay_4_5);
				 this->dMPanel_4_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_4_5->Location = System::Drawing::Point(411, 255);
				 this->dMPanel_4_5->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_4_5->Name = L"dMPanel_4_5";
				 this->dMPanel_4_5->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_4_5->TabIndex = 33;
				 // 
				 // dDay_4_5
				 // 
				 this->dDay_4_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_4_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_4_5->Location = System::Drawing::Point(0, 0);
				 this->dDay_4_5->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_4_5->Name = L"dDay_4_5";
				 this->dDay_4_5->Size = System::Drawing::Size(81, 69);
				 this->dDay_4_5->TabIndex = 1;
				 this->dDay_4_5->Text = L"label34";
				 this->dDay_4_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_4_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_4_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_4_4
				 // 
				 this->dMPanel_4_4->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_4_4->Controls->Add(this->dDay_4_4);
				 this->dMPanel_4_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_4_4->Location = System::Drawing::Point(329, 255);
				 this->dMPanel_4_4->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_4_4->Name = L"dMPanel_4_4";
				 this->dMPanel_4_4->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_4_4->TabIndex = 32;
				 // 
				 // dDay_4_4
				 // 
				 this->dDay_4_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_4_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_4_4->Location = System::Drawing::Point(0, 0);
				 this->dDay_4_4->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_4_4->Name = L"dDay_4_4";
				 this->dDay_4_4->Size = System::Drawing::Size(81, 69);
				 this->dDay_4_4->TabIndex = 1;
				 this->dDay_4_4->Text = L"label33";
				 this->dDay_4_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_4_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_4_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_4_3
				 // 
				 this->dMPanel_4_3->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_4_3->Controls->Add(this->dDay_4_3);
				 this->dMPanel_4_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_4_3->Location = System::Drawing::Point(247, 255);
				 this->dMPanel_4_3->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_4_3->Name = L"dMPanel_4_3";
				 this->dMPanel_4_3->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_4_3->TabIndex = 31;
				 // 
				 // dDay_4_3
				 // 
				 this->dDay_4_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_4_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_4_3->Location = System::Drawing::Point(0, 0);
				 this->dDay_4_3->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_4_3->Name = L"dDay_4_3";
				 this->dDay_4_3->Size = System::Drawing::Size(81, 69);
				 this->dDay_4_3->TabIndex = 1;
				 this->dDay_4_3->Text = L"label32";
				 this->dDay_4_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_4_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_4_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_4_2
				 // 
				 this->dMPanel_4_2->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_4_2->Controls->Add(this->dDay_4_2);
				 this->dMPanel_4_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_4_2->Location = System::Drawing::Point(165, 255);
				 this->dMPanel_4_2->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_4_2->Name = L"dMPanel_4_2";
				 this->dMPanel_4_2->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_4_2->TabIndex = 30;
				 // 
				 // dDay_4_2
				 // 
				 this->dDay_4_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_4_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_4_2->Location = System::Drawing::Point(0, 0);
				 this->dDay_4_2->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_4_2->Name = L"dDay_4_2";
				 this->dDay_4_2->Size = System::Drawing::Size(81, 69);
				 this->dDay_4_2->TabIndex = 1;
				 this->dDay_4_2->Text = L"label31";
				 this->dDay_4_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_4_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_4_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_4_1
				 // 
				 this->dMPanel_4_1->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_4_1->Controls->Add(this->dDay_4_1);
				 this->dMPanel_4_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_4_1->Location = System::Drawing::Point(83, 255);
				 this->dMPanel_4_1->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_4_1->Name = L"dMPanel_4_1";
				 this->dMPanel_4_1->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_4_1->TabIndex = 29;
				 // 
				 // dDay_4_1
				 // 
				 this->dDay_4_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_4_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_4_1->Location = System::Drawing::Point(0, 0);
				 this->dDay_4_1->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_4_1->Name = L"dDay_4_1";
				 this->dDay_4_1->Size = System::Drawing::Size(81, 69);
				 this->dDay_4_1->TabIndex = 1;
				 this->dDay_4_1->Text = L"label30";
				 this->dDay_4_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_4_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_4_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_4_0
				 // 
				 this->dMPanel_4_0->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_4_0->Controls->Add(this->dDay_4_0);
				 this->dMPanel_4_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_4_0->Location = System::Drawing::Point(1, 255);
				 this->dMPanel_4_0->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_4_0->Name = L"dMPanel_4_0";
				 this->dMPanel_4_0->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_4_0->TabIndex = 28;
				 // 
				 // dDay_4_0
				 // 
				 this->dDay_4_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_4_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_4_0->Location = System::Drawing::Point(0, 0);
				 this->dDay_4_0->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_4_0->Name = L"dDay_4_0";
				 this->dDay_4_0->Size = System::Drawing::Size(81, 69);
				 this->dDay_4_0->TabIndex = 1;
				 this->dDay_4_0->Text = L"label29";
				 this->dDay_4_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_4_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_4_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_3_6
				 // 
				 this->dMPanel_3_6->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_3_6->Controls->Add(this->dDay_3_6);
				 this->dMPanel_3_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_3_6->Location = System::Drawing::Point(493, 185);
				 this->dMPanel_3_6->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_3_6->Name = L"dMPanel_3_6";
				 this->dMPanel_3_6->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_3_6->TabIndex = 27;
				 // 
				 // dDay_3_6
				 // 
				 this->dDay_3_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_3_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_3_6->Location = System::Drawing::Point(0, 0);
				 this->dDay_3_6->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_3_6->Name = L"dDay_3_6";
				 this->dDay_3_6->Size = System::Drawing::Size(81, 69);
				 this->dDay_3_6->TabIndex = 1;
				 this->dDay_3_6->Text = L"label28";
				 this->dDay_3_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_3_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_3_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_3_5
				 // 
				 this->dMPanel_3_5->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_3_5->Controls->Add(this->dDay_3_5);
				 this->dMPanel_3_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_3_5->Location = System::Drawing::Point(411, 185);
				 this->dMPanel_3_5->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_3_5->Name = L"dMPanel_3_5";
				 this->dMPanel_3_5->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_3_5->TabIndex = 26;
				 // 
				 // dDay_3_5
				 // 
				 this->dDay_3_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_3_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_3_5->Location = System::Drawing::Point(0, 0);
				 this->dDay_3_5->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_3_5->Name = L"dDay_3_5";
				 this->dDay_3_5->Size = System::Drawing::Size(81, 69);
				 this->dDay_3_5->TabIndex = 1;
				 this->dDay_3_5->Text = L"label27";
				 this->dDay_3_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_3_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_3_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_3_4
				 // 
				 this->dMPanel_3_4->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_3_4->Controls->Add(this->dDay_3_4);
				 this->dMPanel_3_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_3_4->Location = System::Drawing::Point(329, 185);
				 this->dMPanel_3_4->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_3_4->Name = L"dMPanel_3_4";
				 this->dMPanel_3_4->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_3_4->TabIndex = 25;
				 // 
				 // dDay_3_4
				 // 
				 this->dDay_3_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_3_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_3_4->Location = System::Drawing::Point(0, 0);
				 this->dDay_3_4->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_3_4->Name = L"dDay_3_4";
				 this->dDay_3_4->Size = System::Drawing::Size(81, 69);
				 this->dDay_3_4->TabIndex = 1;
				 this->dDay_3_4->Text = L"label26";
				 this->dDay_3_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_3_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_3_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_3_3
				 // 
				 this->dMPanel_3_3->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_3_3->Controls->Add(this->dDay_3_3);
				 this->dMPanel_3_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_3_3->Location = System::Drawing::Point(247, 185);
				 this->dMPanel_3_3->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_3_3->Name = L"dMPanel_3_3";
				 this->dMPanel_3_3->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_3_3->TabIndex = 24;
				 // 
				 // dDay_3_3
				 // 
				 this->dDay_3_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_3_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_3_3->Location = System::Drawing::Point(0, 0);
				 this->dDay_3_3->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_3_3->Name = L"dDay_3_3";
				 this->dDay_3_3->Size = System::Drawing::Size(81, 69);
				 this->dDay_3_3->TabIndex = 1;
				 this->dDay_3_3->Text = L"label25";
				 this->dDay_3_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_3_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_3_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_3_2
				 // 
				 this->dMPanel_3_2->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_3_2->Controls->Add(this->dDay_3_2);
				 this->dMPanel_3_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_3_2->Location = System::Drawing::Point(165, 185);
				 this->dMPanel_3_2->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_3_2->Name = L"dMPanel_3_2";
				 this->dMPanel_3_2->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_3_2->TabIndex = 23;
				 // 
				 // dDay_3_2
				 // 
				 this->dDay_3_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_3_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_3_2->Location = System::Drawing::Point(0, 0);
				 this->dDay_3_2->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_3_2->Name = L"dDay_3_2";
				 this->dDay_3_2->Size = System::Drawing::Size(81, 69);
				 this->dDay_3_2->TabIndex = 1;
				 this->dDay_3_2->Text = L"label24";
				 this->dDay_3_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_3_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_3_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_3_1
				 // 
				 this->dMPanel_3_1->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_3_1->Controls->Add(this->dDay_3_1);
				 this->dMPanel_3_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_3_1->Location = System::Drawing::Point(83, 185);
				 this->dMPanel_3_1->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_3_1->Name = L"dMPanel_3_1";
				 this->dMPanel_3_1->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_3_1->TabIndex = 22;
				 // 
				 // dDay_3_1
				 // 
				 this->dDay_3_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_3_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_3_1->Location = System::Drawing::Point(0, 0);
				 this->dDay_3_1->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_3_1->Name = L"dDay_3_1";
				 this->dDay_3_1->Size = System::Drawing::Size(81, 69);
				 this->dDay_3_1->TabIndex = 1;
				 this->dDay_3_1->Text = L"label23";
				 this->dDay_3_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_3_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_3_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_3_0
				 // 
				 this->dMPanel_3_0->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_3_0->Controls->Add(this->dDay_3_0);
				 this->dMPanel_3_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_3_0->Location = System::Drawing::Point(1, 185);
				 this->dMPanel_3_0->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_3_0->Name = L"dMPanel_3_0";
				 this->dMPanel_3_0->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_3_0->TabIndex = 21;
				 // 
				 // dDay_3_0
				 // 
				 this->dDay_3_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_3_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_3_0->Location = System::Drawing::Point(0, 0);
				 this->dDay_3_0->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_3_0->Name = L"dDay_3_0";
				 this->dDay_3_0->Size = System::Drawing::Size(81, 69);
				 this->dDay_3_0->TabIndex = 1;
				 this->dDay_3_0->Text = L"label22";
				 this->dDay_3_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_3_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_3_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_2_6
				 // 
				 this->dMPanel_2_6->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_2_6->Controls->Add(this->dDay_2_6);
				 this->dMPanel_2_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_2_6->Location = System::Drawing::Point(493, 115);
				 this->dMPanel_2_6->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_2_6->Name = L"dMPanel_2_6";
				 this->dMPanel_2_6->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_2_6->TabIndex = 20;
				 // 
				 // dDay_2_6
				 // 
				 this->dDay_2_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_2_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_2_6->Location = System::Drawing::Point(0, 0);
				 this->dDay_2_6->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_2_6->Name = L"dDay_2_6";
				 this->dDay_2_6->Size = System::Drawing::Size(81, 69);
				 this->dDay_2_6->TabIndex = 1;
				 this->dDay_2_6->Text = L"label21";
				 this->dDay_2_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_2_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_2_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_2_5
				 // 
				 this->dMPanel_2_5->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_2_5->Controls->Add(this->dDay_2_5);
				 this->dMPanel_2_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_2_5->Location = System::Drawing::Point(411, 115);
				 this->dMPanel_2_5->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_2_5->Name = L"dMPanel_2_5";
				 this->dMPanel_2_5->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_2_5->TabIndex = 19;
				 // 
				 // dDay_2_5
				 // 
				 this->dDay_2_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_2_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_2_5->Location = System::Drawing::Point(0, 0);
				 this->dDay_2_5->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_2_5->Name = L"dDay_2_5";
				 this->dDay_2_5->Size = System::Drawing::Size(81, 69);
				 this->dDay_2_5->TabIndex = 1;
				 this->dDay_2_5->Text = L"label20";
				 this->dDay_2_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_2_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_2_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_2_4
				 // 
				 this->dMPanel_2_4->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_2_4->Controls->Add(this->dDay_2_4);
				 this->dMPanel_2_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_2_4->Location = System::Drawing::Point(329, 115);
				 this->dMPanel_2_4->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_2_4->Name = L"dMPanel_2_4";
				 this->dMPanel_2_4->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_2_4->TabIndex = 18;
				 // 
				 // dDay_2_4
				 // 
				 this->dDay_2_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_2_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_2_4->Location = System::Drawing::Point(0, 0);
				 this->dDay_2_4->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_2_4->Name = L"dDay_2_4";
				 this->dDay_2_4->Size = System::Drawing::Size(81, 69);
				 this->dDay_2_4->TabIndex = 1;
				 this->dDay_2_4->Text = L"label19";
				 this->dDay_2_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_2_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_2_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_2_3
				 // 
				 this->dMPanel_2_3->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_2_3->Controls->Add(this->dDay_2_3);
				 this->dMPanel_2_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_2_3->Location = System::Drawing::Point(247, 115);
				 this->dMPanel_2_3->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_2_3->Name = L"dMPanel_2_3";
				 this->dMPanel_2_3->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_2_3->TabIndex = 17;
				 // 
				 // dDay_2_3
				 // 
				 this->dDay_2_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_2_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_2_3->Location = System::Drawing::Point(0, 0);
				 this->dDay_2_3->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_2_3->Name = L"dDay_2_3";
				 this->dDay_2_3->Size = System::Drawing::Size(81, 69);
				 this->dDay_2_3->TabIndex = 1;
				 this->dDay_2_3->Text = L"label18";
				 this->dDay_2_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_2_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_2_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_2_2
				 // 
				 this->dMPanel_2_2->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_2_2->Controls->Add(this->dDay_2_2);
				 this->dMPanel_2_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_2_2->Location = System::Drawing::Point(165, 115);
				 this->dMPanel_2_2->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_2_2->Name = L"dMPanel_2_2";
				 this->dMPanel_2_2->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_2_2->TabIndex = 16;
				 // 
				 // dDay_2_2
				 // 
				 this->dDay_2_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_2_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_2_2->Location = System::Drawing::Point(0, 0);
				 this->dDay_2_2->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_2_2->Name = L"dDay_2_2";
				 this->dDay_2_2->Size = System::Drawing::Size(81, 69);
				 this->dDay_2_2->TabIndex = 1;
				 this->dDay_2_2->Text = L"label17";
				 this->dDay_2_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_2_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_2_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_2_1
				 // 
				 this->dMPanel_2_1->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_2_1->Controls->Add(this->dDay_2_1);
				 this->dMPanel_2_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_2_1->Location = System::Drawing::Point(83, 115);
				 this->dMPanel_2_1->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_2_1->Name = L"dMPanel_2_1";
				 this->dMPanel_2_1->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_2_1->TabIndex = 15;
				 // 
				 // dDay_2_1
				 // 
				 this->dDay_2_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_2_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_2_1->Location = System::Drawing::Point(0, 0);
				 this->dDay_2_1->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_2_1->Name = L"dDay_2_1";
				 this->dDay_2_1->Size = System::Drawing::Size(81, 69);
				 this->dDay_2_1->TabIndex = 1;
				 this->dDay_2_1->Text = L"label16";
				 this->dDay_2_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_2_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_2_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_2_0
				 // 
				 this->dMPanel_2_0->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_2_0->Controls->Add(this->dDay_2_0);
				 this->dMPanel_2_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_2_0->Location = System::Drawing::Point(1, 115);
				 this->dMPanel_2_0->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_2_0->Name = L"dMPanel_2_0";
				 this->dMPanel_2_0->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_2_0->TabIndex = 14;
				 // 
				 // dDay_2_0
				 // 
				 this->dDay_2_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_2_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_2_0->Location = System::Drawing::Point(0, 0);
				 this->dDay_2_0->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_2_0->Name = L"dDay_2_0";
				 this->dDay_2_0->Size = System::Drawing::Size(81, 69);
				 this->dDay_2_0->TabIndex = 1;
				 this->dDay_2_0->Text = L"label15";
				 this->dDay_2_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_2_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_2_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_1_6
				 // 
				 this->dMPanel_1_6->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_1_6->Controls->Add(this->dDay_1_6);
				 this->dMPanel_1_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_1_6->Location = System::Drawing::Point(493, 45);
				 this->dMPanel_1_6->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_1_6->Name = L"dMPanel_1_6";
				 this->dMPanel_1_6->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_1_6->TabIndex = 13;
				 // 
				 // dDay_1_6
				 // 
				 this->dDay_1_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_1_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_1_6->Location = System::Drawing::Point(0, 0);
				 this->dDay_1_6->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_1_6->Name = L"dDay_1_6";
				 this->dDay_1_6->Size = System::Drawing::Size(81, 69);
				 this->dDay_1_6->TabIndex = 1;
				 this->dDay_1_6->Text = L"label14";
				 this->dDay_1_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_1_6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_1_6->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_1_5
				 // 
				 this->dMPanel_1_5->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_1_5->Controls->Add(this->dDay_1_5);
				 this->dMPanel_1_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_1_5->Location = System::Drawing::Point(411, 45);
				 this->dMPanel_1_5->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_1_5->Name = L"dMPanel_1_5";
				 this->dMPanel_1_5->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_1_5->TabIndex = 12;
				 // 
				 // dDay_1_5
				 // 
				 this->dDay_1_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_1_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_1_5->Location = System::Drawing::Point(0, 0);
				 this->dDay_1_5->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_1_5->Name = L"dDay_1_5";
				 this->dDay_1_5->Size = System::Drawing::Size(81, 69);
				 this->dDay_1_5->TabIndex = 1;
				 this->dDay_1_5->Text = L"label13";
				 this->dDay_1_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_1_5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_1_5->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_1_4
				 // 
				 this->dMPanel_1_4->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_1_4->Controls->Add(this->dDay_1_4);
				 this->dMPanel_1_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_1_4->Location = System::Drawing::Point(329, 45);
				 this->dMPanel_1_4->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_1_4->Name = L"dMPanel_1_4";
				 this->dMPanel_1_4->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_1_4->TabIndex = 11;
				 // 
				 // dDay_1_4
				 // 
				 this->dDay_1_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_1_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_1_4->Location = System::Drawing::Point(0, 0);
				 this->dDay_1_4->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_1_4->Name = L"dDay_1_4";
				 this->dDay_1_4->Size = System::Drawing::Size(81, 69);
				 this->dDay_1_4->TabIndex = 1;
				 this->dDay_1_4->Text = L"label12";
				 this->dDay_1_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_1_4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_1_4->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_1_3
				 // 
				 this->dMPanel_1_3->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_1_3->Controls->Add(this->dDay_1_3);
				 this->dMPanel_1_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_1_3->Location = System::Drawing::Point(247, 45);
				 this->dMPanel_1_3->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_1_3->Name = L"dMPanel_1_3";
				 this->dMPanel_1_3->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_1_3->TabIndex = 10;
				 // 
				 // dDay_1_3
				 // 
				 this->dDay_1_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_1_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_1_3->Location = System::Drawing::Point(0, 0);
				 this->dDay_1_3->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_1_3->Name = L"dDay_1_3";
				 this->dDay_1_3->Size = System::Drawing::Size(81, 69);
				 this->dDay_1_3->TabIndex = 1;
				 this->dDay_1_3->Text = L"label11";
				 this->dDay_1_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_1_3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_1_3->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_1_2
				 // 
				 this->dMPanel_1_2->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_1_2->Controls->Add(this->dDay_1_2);
				 this->dMPanel_1_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_1_2->Location = System::Drawing::Point(165, 45);
				 this->dMPanel_1_2->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_1_2->Name = L"dMPanel_1_2";
				 this->dMPanel_1_2->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_1_2->TabIndex = 9;
				 // 
				 // dDay_1_2
				 // 
				 this->dDay_1_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_1_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_1_2->Location = System::Drawing::Point(0, 0);
				 this->dDay_1_2->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_1_2->Name = L"dDay_1_2";
				 this->dDay_1_2->Size = System::Drawing::Size(81, 69);
				 this->dDay_1_2->TabIndex = 1;
				 this->dDay_1_2->Text = L"label10";
				 this->dDay_1_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_1_2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_1_2->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_1_1
				 // 
				 this->dMPanel_1_1->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_1_1->Controls->Add(this->dDay_1_1);
				 this->dMPanel_1_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_1_1->Location = System::Drawing::Point(83, 45);
				 this->dMPanel_1_1->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_1_1->Name = L"dMPanel_1_1";
				 this->dMPanel_1_1->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_1_1->TabIndex = 8;
				 // 
				 // dDay_1_1
				 // 
				 this->dDay_1_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_1_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_1_1->Location = System::Drawing::Point(0, 0);
				 this->dDay_1_1->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_1_1->Name = L"dDay_1_1";
				 this->dDay_1_1->Size = System::Drawing::Size(81, 69);
				 this->dDay_1_1->TabIndex = 1;
				 this->dDay_1_1->Text = L"label9";
				 this->dDay_1_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_1_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_1_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_1_0
				 // 
				 this->dMPanel_1_0->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_1_0->Controls->Add(this->dDay_1_0);
				 this->dMPanel_1_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_1_0->Location = System::Drawing::Point(1, 45);
				 this->dMPanel_1_0->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_1_0->Name = L"dMPanel_1_0";
				 this->dMPanel_1_0->Size = System::Drawing::Size(81, 69);
				 this->dMPanel_1_0->TabIndex = 7;
				 // 
				 // dDay_1_0
				 // 
				 this->dDay_1_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dDay_1_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dDay_1_0->Location = System::Drawing::Point(0, 0);
				 this->dDay_1_0->Margin = System::Windows::Forms::Padding(0);
				 this->dDay_1_0->Name = L"dDay_1_0";
				 this->dDay_1_0->Size = System::Drawing::Size(81, 69);
				 this->dDay_1_0->TabIndex = 1;
				 this->dDay_1_0->Text = L"label8";
				 this->dDay_1_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->dDay_1_0->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dDay_1_0->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 // 
				 // dMPanel_0_6
				 // 
				 this->dMPanel_0_6->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_0_6->Controls->Add(this->dWDay_6);
				 this->dMPanel_0_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_0_6->Location = System::Drawing::Point(493, 1);
				 this->dMPanel_0_6->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_0_6->Name = L"dMPanel_0_6";
				 this->dMPanel_0_6->Size = System::Drawing::Size(81, 43);
				 this->dMPanel_0_6->TabIndex = 6;
				 // 
				 // dWDay_6
				 // 
				 this->dWDay_6->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dWDay_6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay_6->Location = System::Drawing::Point(0, 0);
				 this->dWDay_6->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay_6->Name = L"dWDay_6";
				 this->dWDay_6->Size = System::Drawing::Size(81, 43);
				 this->dWDay_6->TabIndex = 1;
				 this->dWDay_6->Text = L"Sat";
				 this->dWDay_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dMPanel_0_5
				 // 
				 this->dMPanel_0_5->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_0_5->Controls->Add(this->dWDay_5);
				 this->dMPanel_0_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_0_5->Location = System::Drawing::Point(411, 1);
				 this->dMPanel_0_5->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_0_5->Name = L"dMPanel_0_5";
				 this->dMPanel_0_5->Size = System::Drawing::Size(81, 43);
				 this->dMPanel_0_5->TabIndex = 5;
				 // 
				 // dWDay_5
				 // 
				 this->dWDay_5->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dWDay_5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay_5->Location = System::Drawing::Point(0, 0);
				 this->dWDay_5->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay_5->Name = L"dWDay_5";
				 this->dWDay_5->Size = System::Drawing::Size(81, 43);
				 this->dWDay_5->TabIndex = 1;
				 this->dWDay_5->Text = L"Fri";
				 this->dWDay_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dMPanel_0_4
				 // 
				 this->dMPanel_0_4->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_0_4->Controls->Add(this->dWDay_4);
				 this->dMPanel_0_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_0_4->Location = System::Drawing::Point(329, 1);
				 this->dMPanel_0_4->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_0_4->Name = L"dMPanel_0_4";
				 this->dMPanel_0_4->Size = System::Drawing::Size(81, 43);
				 this->dMPanel_0_4->TabIndex = 4;
				 // 
				 // dWDay_4
				 // 
				 this->dWDay_4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dWDay_4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay_4->Location = System::Drawing::Point(0, 0);
				 this->dWDay_4->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay_4->Name = L"dWDay_4";
				 this->dWDay_4->Size = System::Drawing::Size(81, 43);
				 this->dWDay_4->TabIndex = 1;
				 this->dWDay_4->Text = L"Thu";
				 this->dWDay_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dMPanel_0_3
				 // 
				 this->dMPanel_0_3->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_0_3->Controls->Add(this->dWDay_3);
				 this->dMPanel_0_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_0_3->Location = System::Drawing::Point(247, 1);
				 this->dMPanel_0_3->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_0_3->Name = L"dMPanel_0_3";
				 this->dMPanel_0_3->Size = System::Drawing::Size(81, 43);
				 this->dMPanel_0_3->TabIndex = 3;
				 // 
				 // dWDay_3
				 // 
				 this->dWDay_3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dWDay_3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay_3->Location = System::Drawing::Point(0, 0);
				 this->dWDay_3->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay_3->Name = L"dWDay_3";
				 this->dWDay_3->Size = System::Drawing::Size(81, 43);
				 this->dWDay_3->TabIndex = 1;
				 this->dWDay_3->Text = L"Wed";
				 this->dWDay_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dMPanel_0_2
				 // 
				 this->dMPanel_0_2->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_0_2->Controls->Add(this->dWDay_2);
				 this->dMPanel_0_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_0_2->Location = System::Drawing::Point(165, 1);
				 this->dMPanel_0_2->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_0_2->Name = L"dMPanel_0_2";
				 this->dMPanel_0_2->Size = System::Drawing::Size(81, 43);
				 this->dMPanel_0_2->TabIndex = 2;
				 // 
				 // dWDay_2
				 // 
				 this->dWDay_2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dWDay_2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay_2->Location = System::Drawing::Point(0, 0);
				 this->dWDay_2->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay_2->Name = L"dWDay_2";
				 this->dWDay_2->Size = System::Drawing::Size(81, 43);
				 this->dWDay_2->TabIndex = 1;
				 this->dWDay_2->Text = L"Tue";
				 this->dWDay_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dMPanel_0_1
				 // 
				 this->dMPanel_0_1->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_0_1->Controls->Add(this->dWDay_1);
				 this->dMPanel_0_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_0_1->Location = System::Drawing::Point(83, 1);
				 this->dMPanel_0_1->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_0_1->Name = L"dMPanel_0_1";
				 this->dMPanel_0_1->Size = System::Drawing::Size(81, 43);
				 this->dMPanel_0_1->TabIndex = 1;
				 // 
				 // dWDay_1
				 // 
				 this->dWDay_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dWDay_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay_1->Location = System::Drawing::Point(0, 0);
				 this->dWDay_1->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay_1->Name = L"dWDay_1";
				 this->dWDay_1->Size = System::Drawing::Size(81, 43);
				 this->dWDay_1->TabIndex = 1;
				 this->dWDay_1->Text = L"Mon";
				 this->dWDay_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dMPanel_0_0
				 // 
				 this->dMPanel_0_0->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->dMPanel_0_0->Controls->Add(this->dWDay_0);
				 this->dMPanel_0_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dMPanel_0_0->Location = System::Drawing::Point(1, 1);
				 this->dMPanel_0_0->Margin = System::Windows::Forms::Padding(0);
				 this->dMPanel_0_0->Name = L"dMPanel_0_0";
				 this->dMPanel_0_0->Size = System::Drawing::Size(81, 43);
				 this->dMPanel_0_0->TabIndex = 0;
				 // 
				 // dWDay_0
				 // 
				 this->dWDay_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dWDay_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay_0->Location = System::Drawing::Point(0, 0);
				 this->dWDay_0->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay_0->Name = L"dWDay_0";
				 this->dWDay_0->Size = System::Drawing::Size(81, 43);
				 this->dWDay_0->TabIndex = 0;
				 this->dWDay_0->Text = L"Sun";
				 this->dWDay_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dWDay
				 // 
				 this->dWDay->AutoSize = true;
				 this->dWDay->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->dWDay->Location = System::Drawing::Point(303, 228);
				 this->dWDay->Margin = System::Windows::Forms::Padding(0);
				 this->dWDay->Name = L"dWDay";
				 this->dWDay->Size = System::Drawing::Size(304, 96);
				 this->dWDay->TabIndex = 2;
				 this->dWDay->Text = L"Saturday";
				 this->dWDay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dDay
				 // 
				 this->dDay->AutoSize = true;
				 this->dDay->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 90));
				 this->dDay->Location = System::Drawing::Point(16, 112);
				 this->dDay->Margin = System::Windows::Forms::Padding(0);
				 this->dDay->Name = L"dDay";
				 this->dDay->Size = System::Drawing::Size(326, 239);
				 this->dDay->TabIndex = 1;
				 this->dDay->Text = L"30,";
				 this->dDay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // dBtmLine
				 // 
				 this->dBtmLine->Location = System::Drawing::Point(0, 0);
				 this->dBtmLine->Name = L"dBtmLine";
				 this->dBtmLine->Size = System::Drawing::Size(0, 0);
				 this->dBtmLine->TabIndex = 5;
				 // 
				 // dTopLine
				 // 
				 this->dTopLine->Location = System::Drawing::Point(0, 0);
				 this->dTopLine->Name = L"dTopLine";
				 this->dTopLine->Size = System::Drawing::Size(0, 0);
				 this->dTopLine->TabIndex = 4;
				 // 
				 // dPanel_body
				 // 
				 this->dPanel_body->AutoScroll = true;
				 this->dPanel_body->Controls->Add(this->daily_cal);
				 this->dPanel_body->Location = System::Drawing::Point(694, 0);
				 this->dPanel_body->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_body->Name = L"dPanel_body";
				 this->dPanel_body->Size = System::Drawing::Size(660, 880);
				 this->dPanel_body->TabIndex = 0;
				 // 
				 // daily_cal
				 // 
				 this->daily_cal->AutoSize = true;
				 this->daily_cal->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->daily_cal->BackColor = System::Drawing::SystemColors::ControlLightLight;
				 this->daily_cal->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->daily_cal->ColumnCount = 2;
				 this->daily_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 78)));
				 this->daily_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 550)));
				 this->daily_cal->Controls->Add(this->dPanel_17_0, 0, 34);
				 this->daily_cal->Controls->Add(this->dPanel_16_0, 0, 32);
				 this->daily_cal->Controls->Add(this->dPanel_15_0, 0, 30);
				 this->daily_cal->Controls->Add(this->dPanel_14_0, 0, 28);
				 this->daily_cal->Controls->Add(this->dPanel_13_0, 0, 26);
				 this->daily_cal->Controls->Add(this->dPanel_12_0, 0, 24);
				 this->daily_cal->Controls->Add(this->dPanel_11_0, 0, 22);
				 this->daily_cal->Controls->Add(this->dPanel_10_0, 0, 20);
				 this->daily_cal->Controls->Add(this->dPanel_9_0, 0, 18);
				 this->daily_cal->Controls->Add(this->dPanel_8_0, 0, 16);
				 this->daily_cal->Controls->Add(this->dPanel_7_0, 0, 14);
				 this->daily_cal->Controls->Add(this->dPanel_6_0, 0, 12);
				 this->daily_cal->Controls->Add(this->dPanel_5_0, 0, 10);
				 this->daily_cal->Controls->Add(this->dPanel_3_0, 0, 6);
				 this->daily_cal->Controls->Add(this->dPanel_1_0, 0, 2);
				 this->daily_cal->Controls->Add(this->dPanel_2_0, 0, 4);
				 this->daily_cal->Controls->Add(this->dPanel_4_0, 0, 8);
				 this->daily_cal->Controls->Add(this->dPanel_23_0, 0, 46);
				 this->daily_cal->Controls->Add(this->dPanel_22_0, 0, 44);
				 this->daily_cal->Controls->Add(this->dPanel_21_0, 0, 42);
				 this->daily_cal->Controls->Add(this->dPanel_20_0, 0, 40);
				 this->daily_cal->Controls->Add(this->dPanel_19_0, 0, 38);
				 this->daily_cal->Controls->Add(this->dPanel_18_0, 0, 36);
				 this->daily_cal->Controls->Add(this->dPanel_0_0, 0, 0);
				 this->daily_cal->Controls->Add(this->dPanel_0_1, 1, 0);
				 this->daily_cal->Location = System::Drawing::Point(0, 0);
				 this->daily_cal->Margin = System::Windows::Forms::Padding(0);
				 this->daily_cal->Name = L"daily_cal";
				 this->daily_cal->RowCount = 48;
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 35)));
				 this->daily_cal->Size = System::Drawing::Size(631, 1729);
				 this->daily_cal->TabIndex = 5;
				 // 
				 // dPanel_17_0
				 // 
				 this->dPanel_17_0->Controls->Add(this->dHr_17_0);
				 this->dPanel_17_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_17_0->Location = System::Drawing::Point(1, 1225);
				 this->dPanel_17_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_17_0->Name = L"dPanel_17_0";
				 this->daily_cal->SetRowSpan(this->dPanel_17_0, 2);
				 this->dPanel_17_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_17_0->TabIndex = 99;
				 this->dPanel_17_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_17_0
				 // 
				 this->dHr_17_0->AutoSize = true;
				 this->dHr_17_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_17_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_17_0->Name = L"dHr_17_0";
				 this->dHr_17_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_17_0->TabIndex = 3;
				 this->dHr_17_0->Text = L"17:00";
				 this->dHr_17_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_16_0
				 // 
				 this->dPanel_16_0->Controls->Add(this->dHr_16_0);
				 this->dPanel_16_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_16_0->Location = System::Drawing::Point(1, 1153);
				 this->dPanel_16_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_16_0->Name = L"dPanel_16_0";
				 this->daily_cal->SetRowSpan(this->dPanel_16_0, 2);
				 this->dPanel_16_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_16_0->TabIndex = 99;
				 this->dPanel_16_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_16_0
				 // 
				 this->dHr_16_0->AutoSize = true;
				 this->dHr_16_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_16_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_16_0->Name = L"dHr_16_0";
				 this->dHr_16_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_16_0->TabIndex = 3;
				 this->dHr_16_0->Text = L"16:00";
				 this->dHr_16_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_15_0
				 // 
				 this->dPanel_15_0->Controls->Add(this->dHr_15_0);
				 this->dPanel_15_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_15_0->Location = System::Drawing::Point(1, 1081);
				 this->dPanel_15_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_15_0->Name = L"dPanel_15_0";
				 this->daily_cal->SetRowSpan(this->dPanel_15_0, 2);
				 this->dPanel_15_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_15_0->TabIndex = 99;
				 this->dPanel_15_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_15_0
				 // 
				 this->dHr_15_0->AutoSize = true;
				 this->dHr_15_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_15_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_15_0->Name = L"dHr_15_0";
				 this->dHr_15_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_15_0->TabIndex = 3;
				 this->dHr_15_0->Text = L"15:00";
				 this->dHr_15_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_14_0
				 // 
				 this->dPanel_14_0->Controls->Add(this->dHr_14_0);
				 this->dPanel_14_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_14_0->Location = System::Drawing::Point(1, 1009);
				 this->dPanel_14_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_14_0->Name = L"dPanel_14_0";
				 this->daily_cal->SetRowSpan(this->dPanel_14_0, 2);
				 this->dPanel_14_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_14_0->TabIndex = 99;
				 this->dPanel_14_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_14_0
				 // 
				 this->dHr_14_0->AutoSize = true;
				 this->dHr_14_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_14_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_14_0->Name = L"dHr_14_0";
				 this->dHr_14_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_14_0->TabIndex = 3;
				 this->dHr_14_0->Text = L"14:00";
				 this->dHr_14_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_13_0
				 // 
				 this->dPanel_13_0->Controls->Add(this->dHr_13_0);
				 this->dPanel_13_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_13_0->Location = System::Drawing::Point(1, 937);
				 this->dPanel_13_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_13_0->Name = L"dPanel_13_0";
				 this->daily_cal->SetRowSpan(this->dPanel_13_0, 2);
				 this->dPanel_13_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_13_0->TabIndex = 99;
				 this->dPanel_13_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_13_0
				 // 
				 this->dHr_13_0->AutoSize = true;
				 this->dHr_13_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_13_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_13_0->Name = L"dHr_13_0";
				 this->dHr_13_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_13_0->TabIndex = 3;
				 this->dHr_13_0->Text = L"13:00";
				 this->dHr_13_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_12_0
				 // 
				 this->dPanel_12_0->Controls->Add(this->dHr_12_0);
				 this->dPanel_12_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_12_0->Location = System::Drawing::Point(1, 865);
				 this->dPanel_12_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_12_0->Name = L"dPanel_12_0";
				 this->daily_cal->SetRowSpan(this->dPanel_12_0, 2);
				 this->dPanel_12_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_12_0->TabIndex = 99;
				 this->dPanel_12_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_12_0
				 // 
				 this->dHr_12_0->AutoSize = true;
				 this->dHr_12_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_12_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_12_0->Name = L"dHr_12_0";
				 this->dHr_12_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_12_0->TabIndex = 3;
				 this->dHr_12_0->Text = L"12:00";
				 this->dHr_12_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_11_0
				 // 
				 this->dPanel_11_0->Controls->Add(this->dHr_11_0);
				 this->dPanel_11_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_11_0->Location = System::Drawing::Point(1, 793);
				 this->dPanel_11_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_11_0->Name = L"dPanel_11_0";
				 this->daily_cal->SetRowSpan(this->dPanel_11_0, 2);
				 this->dPanel_11_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_11_0->TabIndex = 99;
				 this->dPanel_11_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_11_0
				 // 
				 this->dHr_11_0->AutoSize = true;
				 this->dHr_11_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_11_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_11_0->Name = L"dHr_11_0";
				 this->dHr_11_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_11_0->TabIndex = 3;
				 this->dHr_11_0->Text = L"11:00";
				 this->dHr_11_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_10_0
				 // 
				 this->dPanel_10_0->Controls->Add(this->dHr_10_0);
				 this->dPanel_10_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_10_0->Location = System::Drawing::Point(1, 721);
				 this->dPanel_10_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_10_0->Name = L"dPanel_10_0";
				 this->daily_cal->SetRowSpan(this->dPanel_10_0, 2);
				 this->dPanel_10_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_10_0->TabIndex = 99;
				 this->dPanel_10_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_10_0
				 // 
				 this->dHr_10_0->AutoSize = true;
				 this->dHr_10_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_10_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_10_0->Name = L"dHr_10_0";
				 this->dHr_10_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_10_0->TabIndex = 3;
				 this->dHr_10_0->Text = L"10:00";
				 this->dHr_10_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_9_0
				 // 
				 this->dPanel_9_0->Controls->Add(this->dHr_9_0);
				 this->dPanel_9_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_9_0->Location = System::Drawing::Point(1, 649);
				 this->dPanel_9_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_9_0->Name = L"dPanel_9_0";
				 this->daily_cal->SetRowSpan(this->dPanel_9_0, 2);
				 this->dPanel_9_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_9_0->TabIndex = 99;
				 this->dPanel_9_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_9_0
				 // 
				 this->dHr_9_0->AutoSize = true;
				 this->dHr_9_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_9_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_9_0->Name = L"dHr_9_0";
				 this->dHr_9_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_9_0->TabIndex = 3;
				 this->dHr_9_0->Text = L"09:00";
				 this->dHr_9_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_8_0
				 // 
				 this->dPanel_8_0->Controls->Add(this->dHr_8_0);
				 this->dPanel_8_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_8_0->Location = System::Drawing::Point(1, 577);
				 this->dPanel_8_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_8_0->Name = L"dPanel_8_0";
				 this->daily_cal->SetRowSpan(this->dPanel_8_0, 2);
				 this->dPanel_8_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_8_0->TabIndex = 99;
				 this->dPanel_8_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_8_0
				 // 
				 this->dHr_8_0->AutoSize = true;
				 this->dHr_8_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_8_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_8_0->Name = L"dHr_8_0";
				 this->dHr_8_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_8_0->TabIndex = 3;
				 this->dHr_8_0->Text = L"08:00";
				 this->dHr_8_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_7_0
				 // 
				 this->dPanel_7_0->Controls->Add(this->dHr_7_0);
				 this->dPanel_7_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_7_0->Location = System::Drawing::Point(1, 505);
				 this->dPanel_7_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_7_0->Name = L"dPanel_7_0";
				 this->daily_cal->SetRowSpan(this->dPanel_7_0, 2);
				 this->dPanel_7_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_7_0->TabIndex = 99;
				 this->dPanel_7_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_7_0
				 // 
				 this->dHr_7_0->AutoSize = true;
				 this->dHr_7_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_7_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_7_0->Name = L"dHr_7_0";
				 this->dHr_7_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_7_0->TabIndex = 3;
				 this->dHr_7_0->Text = L"07:00";
				 this->dHr_7_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_6_0
				 // 
				 this->dPanel_6_0->Controls->Add(this->dHr_6_0);
				 this->dPanel_6_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_6_0->Location = System::Drawing::Point(1, 433);
				 this->dPanel_6_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_6_0->Name = L"dPanel_6_0";
				 this->daily_cal->SetRowSpan(this->dPanel_6_0, 2);
				 this->dPanel_6_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_6_0->TabIndex = 99;
				 this->dPanel_6_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_6_0
				 // 
				 this->dHr_6_0->AutoSize = true;
				 this->dHr_6_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_6_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_6_0->Name = L"dHr_6_0";
				 this->dHr_6_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_6_0->TabIndex = 3;
				 this->dHr_6_0->Text = L"06:00";
				 this->dHr_6_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_5_0
				 // 
				 this->dPanel_5_0->Controls->Add(this->dHr_5_0);
				 this->dPanel_5_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_5_0->Location = System::Drawing::Point(1, 361);
				 this->dPanel_5_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_5_0->Name = L"dPanel_5_0";
				 this->daily_cal->SetRowSpan(this->dPanel_5_0, 2);
				 this->dPanel_5_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_5_0->TabIndex = 99;
				 this->dPanel_5_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_5_0
				 // 
				 this->dHr_5_0->AutoSize = true;
				 this->dHr_5_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_5_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_5_0->Name = L"dHr_5_0";
				 this->dHr_5_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_5_0->TabIndex = 3;
				 this->dHr_5_0->Text = L"05:00";
				 this->dHr_5_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_3_0
				 // 
				 this->dPanel_3_0->Controls->Add(this->dHr_3_0);
				 this->dPanel_3_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_3_0->Location = System::Drawing::Point(1, 217);
				 this->dPanel_3_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_3_0->Name = L"dPanel_3_0";
				 this->daily_cal->SetRowSpan(this->dPanel_3_0, 2);
				 this->dPanel_3_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_3_0->TabIndex = 99;
				 this->dPanel_3_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_3_0
				 // 
				 this->dHr_3_0->AutoSize = true;
				 this->dHr_3_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_3_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_3_0->Name = L"dHr_3_0";
				 this->dHr_3_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_3_0->TabIndex = 3;
				 this->dHr_3_0->Text = L"03:00";
				 this->dHr_3_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_1_0
				 // 
				 this->dPanel_1_0->Controls->Add(this->dHr_1_0);
				 this->dPanel_1_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_1_0->Location = System::Drawing::Point(1, 73);
				 this->dPanel_1_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_1_0->Name = L"dPanel_1_0";
				 this->daily_cal->SetRowSpan(this->dPanel_1_0, 2);
				 this->dPanel_1_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_1_0->TabIndex = 99;
				 this->dPanel_1_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_1_0
				 // 
				 this->dHr_1_0->AutoSize = true;
				 this->dHr_1_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_1_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_1_0->Name = L"dHr_1_0";
				 this->dHr_1_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_1_0->TabIndex = 3;
				 this->dHr_1_0->Text = L"01:00";
				 this->dHr_1_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_2_0
				 // 
				 this->dPanel_2_0->Controls->Add(this->dHr_2_0);
				 this->dPanel_2_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_2_0->Location = System::Drawing::Point(1, 145);
				 this->dPanel_2_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_2_0->Name = L"dPanel_2_0";
				 this->daily_cal->SetRowSpan(this->dPanel_2_0, 2);
				 this->dPanel_2_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_2_0->TabIndex = 100;
				 this->dPanel_2_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_2_0
				 // 
				 this->dHr_2_0->AutoSize = true;
				 this->dHr_2_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_2_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_2_0->Name = L"dHr_2_0";
				 this->dHr_2_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_2_0->TabIndex = 3;
				 this->dHr_2_0->Text = L"02:00";
				 this->dHr_2_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_4_0
				 // 
				 this->dPanel_4_0->Controls->Add(this->dHr_4_0);
				 this->dPanel_4_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_4_0->Location = System::Drawing::Point(1, 289);
				 this->dPanel_4_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_4_0->Name = L"dPanel_4_0";
				 this->daily_cal->SetRowSpan(this->dPanel_4_0, 2);
				 this->dPanel_4_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_4_0->TabIndex = 101;
				 this->dPanel_4_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_4_0
				 // 
				 this->dHr_4_0->AutoSize = true;
				 this->dHr_4_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_4_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_4_0->Name = L"dHr_4_0";
				 this->dHr_4_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_4_0->TabIndex = 3;
				 this->dHr_4_0->Text = L"04:00";
				 this->dHr_4_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_23_0
				 // 
				 this->dPanel_23_0->Controls->Add(this->dHr_23_0);
				 this->dPanel_23_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_23_0->Location = System::Drawing::Point(1, 1657);
				 this->dPanel_23_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_23_0->Name = L"dPanel_23_0";
				 this->daily_cal->SetRowSpan(this->dPanel_23_0, 2);
				 this->dPanel_23_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_23_0->TabIndex = 99;
				 this->dPanel_23_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_23_0
				 // 
				 this->dHr_23_0->AutoSize = true;
				 this->dHr_23_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_23_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_23_0->Name = L"dHr_23_0";
				 this->dHr_23_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_23_0->TabIndex = 3;
				 this->dHr_23_0->Text = L"23:00";
				 this->dHr_23_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_22_0
				 // 
				 this->dPanel_22_0->Controls->Add(this->dHr_22_0);
				 this->dPanel_22_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_22_0->Location = System::Drawing::Point(1, 1585);
				 this->dPanel_22_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_22_0->Name = L"dPanel_22_0";
				 this->daily_cal->SetRowSpan(this->dPanel_22_0, 2);
				 this->dPanel_22_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_22_0->TabIndex = 99;
				 this->dPanel_22_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_22_0
				 // 
				 this->dHr_22_0->AutoSize = true;
				 this->dHr_22_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_22_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_22_0->Name = L"dHr_22_0";
				 this->dHr_22_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_22_0->TabIndex = 3;
				 this->dHr_22_0->Text = L"22:00";
				 this->dHr_22_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_21_0
				 // 
				 this->dPanel_21_0->Controls->Add(this->dHr_21_0);
				 this->dPanel_21_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_21_0->Location = System::Drawing::Point(1, 1513);
				 this->dPanel_21_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_21_0->Name = L"dPanel_21_0";
				 this->daily_cal->SetRowSpan(this->dPanel_21_0, 2);
				 this->dPanel_21_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_21_0->TabIndex = 99;
				 this->dPanel_21_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_21_0
				 // 
				 this->dHr_21_0->AutoSize = true;
				 this->dHr_21_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_21_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_21_0->Name = L"dHr_21_0";
				 this->dHr_21_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_21_0->TabIndex = 3;
				 this->dHr_21_0->Text = L"21:00";
				 this->dHr_21_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_20_0
				 // 
				 this->dPanel_20_0->Controls->Add(this->dHr_20_0);
				 this->dPanel_20_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_20_0->Location = System::Drawing::Point(1, 1441);
				 this->dPanel_20_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_20_0->Name = L"dPanel_20_0";
				 this->daily_cal->SetRowSpan(this->dPanel_20_0, 2);
				 this->dPanel_20_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_20_0->TabIndex = 99;
				 this->dPanel_20_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_20_0
				 // 
				 this->dHr_20_0->AutoSize = true;
				 this->dHr_20_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_20_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_20_0->Name = L"dHr_20_0";
				 this->dHr_20_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_20_0->TabIndex = 3;
				 this->dHr_20_0->Text = L"20:00";
				 this->dHr_20_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_19_0
				 // 
				 this->dPanel_19_0->Controls->Add(this->dHr_19_0);
				 this->dPanel_19_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_19_0->Location = System::Drawing::Point(1, 1369);
				 this->dPanel_19_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_19_0->Name = L"dPanel_19_0";
				 this->daily_cal->SetRowSpan(this->dPanel_19_0, 2);
				 this->dPanel_19_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_19_0->TabIndex = 99;
				 this->dPanel_19_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_19_0
				 // 
				 this->dHr_19_0->AutoSize = true;
				 this->dHr_19_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_19_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_19_0->Name = L"dHr_19_0";
				 this->dHr_19_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_19_0->TabIndex = 3;
				 this->dHr_19_0->Text = L"19:00";
				 this->dHr_19_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_18_0
				 // 
				 this->dPanel_18_0->Controls->Add(this->dHr_18_0);
				 this->dPanel_18_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_18_0->Location = System::Drawing::Point(1, 1297);
				 this->dPanel_18_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_18_0->Name = L"dPanel_18_0";
				 this->daily_cal->SetRowSpan(this->dPanel_18_0, 2);
				 this->dPanel_18_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_18_0->TabIndex = 99;
				 this->dPanel_18_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_18_0
				 // 
				 this->dHr_18_0->AutoSize = true;
				 this->dHr_18_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_18_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_18_0->Name = L"dHr_18_0";
				 this->dHr_18_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_18_0->TabIndex = 3;
				 this->dHr_18_0->Text = L"18:00";
				 this->dHr_18_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_0_0
				 // 
				 this->dPanel_0_0->Controls->Add(this->dHr_0_0);
				 this->dPanel_0_0->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_0_0->Location = System::Drawing::Point(1, 1);
				 this->dPanel_0_0->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_0_0->Name = L"dPanel_0_0";
				 this->daily_cal->SetRowSpan(this->dPanel_0_0, 2);
				 this->dPanel_0_0->Size = System::Drawing::Size(78, 71);
				 this->dPanel_0_0->TabIndex = 98;
				 this->dPanel_0_0->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // dHr_0_0
				 // 
				 this->dHr_0_0->AutoSize = true;
				 this->dHr_0_0->Location = System::Drawing::Point(27, 5);
				 this->dHr_0_0->Margin = System::Windows::Forms::Padding(3, 9, 3, 0);
				 this->dHr_0_0->Name = L"dHr_0_0";
				 this->dHr_0_0->Size = System::Drawing::Size(49, 20);
				 this->dHr_0_0->TabIndex = 3;
				 this->dHr_0_0->Text = L"00:00";
				 this->dHr_0_0->TextAlign = System::Drawing::ContentAlignment::TopRight;
				 // 
				 // dPanel_0_1
				 // 
				 this->dPanel_0_1->BackColor = System::Drawing::Color::Transparent;
				 this->dPanel_0_1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dPanel_0_1->Location = System::Drawing::Point(80, 1);
				 this->dPanel_0_1->Margin = System::Windows::Forms::Padding(0);
				 this->dPanel_0_1->Name = L"dPanel_0_1";
				 this->daily_cal->SetRowSpan(this->dPanel_0_1, 48);
				 this->dPanel_0_1->Size = System::Drawing::Size(550, 1727);
				 this->dPanel_0_1->TabIndex = 102;
				 this->dPanel_0_1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseClick);
				 this->dPanel_0_1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::all_date_MouseDoubleClick);
				 this->dPanel_0_1->MouseHover += gcnew System::EventHandler(this, &Form1::scollbar_MouseHover);
				 // 
				 // display_week
				 // 
				 this->display_week->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
				 this->display_week->BackColor = System::Drawing::SystemColors::Control;
				 this->display_week->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->display_week->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 12.2F));
				 this->display_week->Location = System::Drawing::Point(49, 16);
				 this->display_week->Margin = System::Windows::Forms::Padding(3, 5, 3, 6);
				 this->display_week->MaxLength = 7;
				 this->display_week->Name = L"display_week";
				 this->display_week->Size = System::Drawing::Size(110, 33);
				 this->display_week->TabIndex = 0;
				 this->display_week->Text = L"Week 52";
				 this->display_week->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->display_week->Visible = false;
				 this->display_week->Click += gcnew System::EventHandler(this, &Form1::display_week_Click);
				 this->display_week->TextChanged += gcnew System::EventHandler(this, &Form1::resize_TextChanged);
				 this->display_week->Enter += gcnew System::EventHandler(this, &Form1::display_week_Enter);
				 this->display_week->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::int_only_KeyPress);
				 this->display_week->Leave += gcnew System::EventHandler(this, &Form1::display_week_Leave);
				 // 
				 // info_layout
				 // 
				 this->info_layout->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->info_layout->AutoSize = true;
				 this->info_layout->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->info_layout->ColumnCount = 4;
				 this->info_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->info_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->info_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->info_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->info_layout->Controls->Add(this->display_day, 0, 0);
				 this->info_layout->Controls->Add(this->display_week, 1, 0);
				 this->info_layout->Controls->Add(this->display_year, 3, 0);
				 this->info_layout->Controls->Add(this->display_month, 2, 0);
				 this->info_layout->Location = System::Drawing::Point(916, 23);
				 this->info_layout->Name = L"info_layout";
				 this->info_layout->RowCount = 1;
				 this->info_layout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->info_layout->Size = System::Drawing::Size(416, 55);
				 this->info_layout->TabIndex = 6;
				 // 
				 // display_day
				 // 
				 this->display_day->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
				 this->display_day->BackColor = System::Drawing::SystemColors::Control;
				 this->display_day->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->display_day->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 16.2F));
				 this->display_day->Location = System::Drawing::Point(3, 5);
				 this->display_day->Margin = System::Windows::Forms::Padding(3, 5, 3, 6);
				 this->display_day->MaxLength = 7;
				 this->display_day->Name = L"display_day";
				 this->display_day->Size = System::Drawing::Size(40, 44);
				 this->display_day->TabIndex = 3;
				 this->display_day->Text = L"30";
				 this->display_day->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->display_day->Visible = false;
				 this->display_day->Click += gcnew System::EventHandler(this, &Form1::select_all_Click);
				 this->display_day->TextChanged += gcnew System::EventHandler(this, &Form1::resize_TextChanged);
				 this->display_day->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::int_only_KeyPress);
				 this->display_day->Leave += gcnew System::EventHandler(this, &Form1::display_day_Leave);
				 // 
				 // select_day_layout
				 // 
				 this->select_day_layout->AutoSize = true;
				 this->select_day_layout->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->select_day_layout->ColumnCount = 3;
				 this->select_day_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->select_day_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->select_day_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->select_day_layout->Controls->Add(this->prev_btn, 0, 0);
				 this->select_day_layout->Controls->Add(this->now_btn, 1, 0);
				 this->select_day_layout->Controls->Add(this->next_btn, 2, 0);
				 this->select_day_layout->Location = System::Drawing::Point(57, 40);
				 this->select_day_layout->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				 this->select_day_layout->Name = L"select_day_layout";
				 this->select_day_layout->RowCount = 1;
				 this->select_day_layout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->select_day_layout->Size = System::Drawing::Size(164, 35);
				 this->select_day_layout->TabIndex = 16;
				 // 
				 // type_layout
				 // 
				 this->type_layout->AutoSize = true;
				 this->type_layout->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->type_layout->ColumnCount = 3;
				 this->type_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->type_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->type_layout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				 this->type_layout->Controls->Add(this->monthly_type, 0, 0);
				 this->type_layout->Controls->Add(this->weekly_type, 1, 0);
				 this->type_layout->Controls->Add(this->daily_type, 2, 0);
				 this->type_layout->Location = System::Drawing::Point(519, 40);
				 this->type_layout->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				 this->type_layout->Name = L"type_layout";
				 this->type_layout->RowCount = 1;
				 this->type_layout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->type_layout->Size = System::Drawing::Size(348, 35);
				 this->type_layout->TabIndex = 17;
				 // 
				 // stat_btn
				 // 
				 this->stat_btn->Location = System::Drawing::Point(1221, 983);
				 this->stat_btn->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
				 this->stat_btn->Name = L"stat_btn";
				 this->stat_btn->Size = System::Drawing::Size(112, 35);
				 this->stat_btn->TabIndex = 7;
				 this->stat_btn->Text = L"Statisitics";
				 this->stat_btn->UseVisualStyleBackColor = true;
				 this->stat_btn->Click += gcnew System::EventHandler(this, &Form1::stat_btn_Click);
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(1383, 1048);
				 this->Controls->Add(this->dPanel);
				 this->Controls->Add(this->wPanel);
				 this->Controls->Add(this->mPanel);
				 this->Controls->Add(this->type_layout);
				 this->Controls->Add(this->select_day_layout);
				 this->Controls->Add(this->info_layout);
				 this->Controls->Add(this->stat_btn);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				 this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				 this->Name = L"Form1";
				 this->Text = L"My Calendar";
				 this->Shown += gcnew System::EventHandler(this, &Form1::Form1_Shown);
				 this->monthly_cal->ResumeLayout(false);
				 this->mPanel_6_6->ResumeLayout(false);
				 this->mPanel_6_6->PerformLayout();
				 this->mPanel_6_5->ResumeLayout(false);
				 this->mPanel_6_5->PerformLayout();
				 this->mPanel_6_4->ResumeLayout(false);
				 this->mPanel_6_4->PerformLayout();
				 this->mPanel_6_3->ResumeLayout(false);
				 this->mPanel_6_3->PerformLayout();
				 this->mPanel_6_2->ResumeLayout(false);
				 this->mPanel_6_2->PerformLayout();
				 this->mPanel_6_1->ResumeLayout(false);
				 this->mPanel_6_1->PerformLayout();
				 this->mPanel_6_0->ResumeLayout(false);
				 this->mPanel_6_0->PerformLayout();
				 this->mPanel_5_6->ResumeLayout(false);
				 this->mPanel_5_6->PerformLayout();
				 this->mPanel_5_5->ResumeLayout(false);
				 this->mPanel_5_5->PerformLayout();
				 this->mPanel_5_4->ResumeLayout(false);
				 this->mPanel_5_4->PerformLayout();
				 this->mPanel_5_3->ResumeLayout(false);
				 this->mPanel_5_3->PerformLayout();
				 this->mPanel_5_2->ResumeLayout(false);
				 this->mPanel_5_2->PerformLayout();
				 this->mPanel_5_1->ResumeLayout(false);
				 this->mPanel_5_1->PerformLayout();
				 this->mPanel_5_0->ResumeLayout(false);
				 this->mPanel_5_0->PerformLayout();
				 this->mPanel_4_6->ResumeLayout(false);
				 this->mPanel_4_6->PerformLayout();
				 this->mPanel_4_5->ResumeLayout(false);
				 this->mPanel_4_5->PerformLayout();
				 this->mPanel_4_4->ResumeLayout(false);
				 this->mPanel_4_4->PerformLayout();
				 this->mPanel_4_3->ResumeLayout(false);
				 this->mPanel_4_3->PerformLayout();
				 this->mPanel_4_2->ResumeLayout(false);
				 this->mPanel_4_2->PerformLayout();
				 this->mPanel_4_1->ResumeLayout(false);
				 this->mPanel_4_1->PerformLayout();
				 this->mPanel_4_0->ResumeLayout(false);
				 this->mPanel_4_0->PerformLayout();
				 this->mPanel_3_6->ResumeLayout(false);
				 this->mPanel_3_6->PerformLayout();
				 this->mPanel_3_5->ResumeLayout(false);
				 this->mPanel_3_5->PerformLayout();
				 this->mPanel_3_4->ResumeLayout(false);
				 this->mPanel_3_4->PerformLayout();
				 this->mPanel_3_3->ResumeLayout(false);
				 this->mPanel_3_3->PerformLayout();
				 this->mPanel_3_2->ResumeLayout(false);
				 this->mPanel_3_2->PerformLayout();
				 this->mPanel_3_1->ResumeLayout(false);
				 this->mPanel_3_1->PerformLayout();
				 this->mPanel_2_6->ResumeLayout(false);
				 this->mPanel_2_6->PerformLayout();
				 this->mPanel_2_5->ResumeLayout(false);
				 this->mPanel_2_5->PerformLayout();
				 this->mPanel_2_4->ResumeLayout(false);
				 this->mPanel_2_4->PerformLayout();
				 this->mPanel_2_3->ResumeLayout(false);
				 this->mPanel_2_3->PerformLayout();
				 this->mPanel_2_2->ResumeLayout(false);
				 this->mPanel_2_2->PerformLayout();
				 this->mPanel_2_1->ResumeLayout(false);
				 this->mPanel_2_1->PerformLayout();
				 this->mPanel_1_6->ResumeLayout(false);
				 this->mPanel_1_6->PerformLayout();
				 this->mPanel_1_5->ResumeLayout(false);
				 this->mPanel_1_5->PerformLayout();
				 this->mPanel_1_4->ResumeLayout(false);
				 this->mPanel_1_4->PerformLayout();
				 this->mPanel_1_3->ResumeLayout(false);
				 this->mPanel_1_3->PerformLayout();
				 this->mPanel_1_2->ResumeLayout(false);
				 this->mPanel_1_2->PerformLayout();
				 this->mPanel_1_1->ResumeLayout(false);
				 this->mPanel_1_1->PerformLayout();
				 this->mPanel_0_6->ResumeLayout(false);
				 this->mPanel_0_6->PerformLayout();
				 this->mPanel_0_5->ResumeLayout(false);
				 this->mPanel_0_5->PerformLayout();
				 this->mPanel_0_4->ResumeLayout(false);
				 this->mPanel_0_4->PerformLayout();
				 this->mPanel_0_3->ResumeLayout(false);
				 this->mPanel_0_3->PerformLayout();
				 this->mPanel_0_2->ResumeLayout(false);
				 this->mPanel_0_2->PerformLayout();
				 this->mPanel_0_1->ResumeLayout(false);
				 this->mPanel_0_1->PerformLayout();
				 this->mPanel_0_0->ResumeLayout(false);
				 this->mPanel_1_0->ResumeLayout(false);
				 this->mPanel_1_0->PerformLayout();
				 this->mPanel_2_0->ResumeLayout(false);
				 this->mPanel_2_0->PerformLayout();
				 this->mPanel_3_0->ResumeLayout(false);
				 this->mPanel_3_0->PerformLayout();
				 this->mPanel->ResumeLayout(false);
				 this->mPanel->PerformLayout();
				 this->wPanel->ResumeLayout(false);
				 this->wPanel->PerformLayout();
				 this->wPanel_head->ResumeLayout(false);
				 this->wPanel_head->PerformLayout();
				 this->weekly_cal_title->ResumeLayout(false);
				 this->wPanel_0_1->ResumeLayout(false);
				 this->wPanel_0_1->PerformLayout();
				 this->wPanel_0_2->ResumeLayout(false);
				 this->wPanel_0_2->PerformLayout();
				 this->wPanel_0_3->ResumeLayout(false);
				 this->wPanel_0_3->PerformLayout();
				 this->wPanel_0_4->ResumeLayout(false);
				 this->wPanel_0_4->PerformLayout();
				 this->wPanel_0_5->ResumeLayout(false);
				 this->wPanel_0_5->PerformLayout();
				 this->wPanel_0_6->ResumeLayout(false);
				 this->wPanel_0_6->PerformLayout();
				 this->wPanel_0_7->ResumeLayout(false);
				 this->wPanel_0_7->PerformLayout();
				 this->wPanel_body->ResumeLayout(false);
				 this->wPanel_body->PerformLayout();
				 this->weekly_cal->ResumeLayout(false);
				 this->wPanel_18_0->ResumeLayout(false);
				 this->wPanel_18_0->PerformLayout();
				 this->wPanel_17_0->ResumeLayout(false);
				 this->wPanel_17_0->PerformLayout();
				 this->wPanel_16_0->ResumeLayout(false);
				 this->wPanel_16_0->PerformLayout();
				 this->wPanel_15_0->ResumeLayout(false);
				 this->wPanel_15_0->PerformLayout();
				 this->wPanel_14_0->ResumeLayout(false);
				 this->wPanel_14_0->PerformLayout();
				 this->wPanel_13_0->ResumeLayout(false);
				 this->wPanel_13_0->PerformLayout();
				 this->wPanel_12_0->ResumeLayout(false);
				 this->wPanel_12_0->PerformLayout();
				 this->wPanel_11_0->ResumeLayout(false);
				 this->wPanel_11_0->PerformLayout();
				 this->wPanel_10_0->ResumeLayout(false);
				 this->wPanel_10_0->PerformLayout();
				 this->wPanel_9_0->ResumeLayout(false);
				 this->wPanel_9_0->PerformLayout();
				 this->wPanel_8_0->ResumeLayout(false);
				 this->wPanel_8_0->PerformLayout();
				 this->wPanel_7_0->ResumeLayout(false);
				 this->wPanel_7_0->PerformLayout();
				 this->wPanel_6_0->ResumeLayout(false);
				 this->wPanel_6_0->PerformLayout();
				 this->wPanel_4_0->ResumeLayout(false);
				 this->wPanel_4_0->PerformLayout();
				 this->wPanel_2_0->ResumeLayout(false);
				 this->wPanel_2_0->PerformLayout();
				 this->wPanel_3_0->ResumeLayout(false);
				 this->wPanel_3_0->PerformLayout();
				 this->wPanel_5_0->ResumeLayout(false);
				 this->wPanel_5_0->PerformLayout();
				 this->wPanel_24_0->ResumeLayout(false);
				 this->wPanel_24_0->PerformLayout();
				 this->wPanel_23_0->ResumeLayout(false);
				 this->wPanel_23_0->PerformLayout();
				 this->wPanel_22_0->ResumeLayout(false);
				 this->wPanel_22_0->PerformLayout();
				 this->wPanel_21_0->ResumeLayout(false);
				 this->wPanel_21_0->PerformLayout();
				 this->wPanel_20_0->ResumeLayout(false);
				 this->wPanel_20_0->PerformLayout();
				 this->wPanel_19_0->ResumeLayout(false);
				 this->wPanel_19_0->PerformLayout();
				 this->wPanel_1_0->ResumeLayout(false);
				 this->wPanel_1_0->PerformLayout();
				 this->dPanel->ResumeLayout(false);
				 this->dPanel->PerformLayout();
				 this->daily_monthly_cal->ResumeLayout(false);
				 this->dMPanel_6_2->ResumeLayout(false);
				 this->dMPanel_6_1->ResumeLayout(false);
				 this->dMPanel_6_0->ResumeLayout(false);
				 this->dMPanel_6_3->ResumeLayout(false);
				 this->dMPanel_6_6->ResumeLayout(false);
				 this->dMPanel_6_5->ResumeLayout(false);
				 this->dMPanel_6_4->ResumeLayout(false);
				 this->dMPanel_5_6->ResumeLayout(false);
				 this->dMPanel_5_5->ResumeLayout(false);
				 this->dMPanel_5_4->ResumeLayout(false);
				 this->dMPanel_5_3->ResumeLayout(false);
				 this->dMPanel_5_2->ResumeLayout(false);
				 this->dMPanel_5_1->ResumeLayout(false);
				 this->dMPanel_5_0->ResumeLayout(false);
				 this->dMPanel_4_6->ResumeLayout(false);
				 this->dMPanel_4_5->ResumeLayout(false);
				 this->dMPanel_4_4->ResumeLayout(false);
				 this->dMPanel_4_3->ResumeLayout(false);
				 this->dMPanel_4_2->ResumeLayout(false);
				 this->dMPanel_4_1->ResumeLayout(false);
				 this->dMPanel_4_0->ResumeLayout(false);
				 this->dMPanel_3_6->ResumeLayout(false);
				 this->dMPanel_3_5->ResumeLayout(false);
				 this->dMPanel_3_4->ResumeLayout(false);
				 this->dMPanel_3_3->ResumeLayout(false);
				 this->dMPanel_3_2->ResumeLayout(false);
				 this->dMPanel_3_1->ResumeLayout(false);
				 this->dMPanel_3_0->ResumeLayout(false);
				 this->dMPanel_2_6->ResumeLayout(false);
				 this->dMPanel_2_5->ResumeLayout(false);
				 this->dMPanel_2_4->ResumeLayout(false);
				 this->dMPanel_2_3->ResumeLayout(false);
				 this->dMPanel_2_2->ResumeLayout(false);
				 this->dMPanel_2_1->ResumeLayout(false);
				 this->dMPanel_2_0->ResumeLayout(false);
				 this->dMPanel_1_6->ResumeLayout(false);
				 this->dMPanel_1_5->ResumeLayout(false);
				 this->dMPanel_1_4->ResumeLayout(false);
				 this->dMPanel_1_3->ResumeLayout(false);
				 this->dMPanel_1_2->ResumeLayout(false);
				 this->dMPanel_1_1->ResumeLayout(false);
				 this->dMPanel_1_0->ResumeLayout(false);
				 this->dMPanel_0_6->ResumeLayout(false);
				 this->dMPanel_0_5->ResumeLayout(false);
				 this->dMPanel_0_4->ResumeLayout(false);
				 this->dMPanel_0_3->ResumeLayout(false);
				 this->dMPanel_0_2->ResumeLayout(false);
				 this->dMPanel_0_1->ResumeLayout(false);
				 this->dMPanel_0_0->ResumeLayout(false);
				 this->dPanel_body->ResumeLayout(false);
				 this->dPanel_body->PerformLayout();
				 this->daily_cal->ResumeLayout(false);
				 this->dPanel_17_0->ResumeLayout(false);
				 this->dPanel_17_0->PerformLayout();
				 this->dPanel_16_0->ResumeLayout(false);
				 this->dPanel_16_0->PerformLayout();
				 this->dPanel_15_0->ResumeLayout(false);
				 this->dPanel_15_0->PerformLayout();
				 this->dPanel_14_0->ResumeLayout(false);
				 this->dPanel_14_0->PerformLayout();
				 this->dPanel_13_0->ResumeLayout(false);
				 this->dPanel_13_0->PerformLayout();
				 this->dPanel_12_0->ResumeLayout(false);
				 this->dPanel_12_0->PerformLayout();
				 this->dPanel_11_0->ResumeLayout(false);
				 this->dPanel_11_0->PerformLayout();
				 this->dPanel_10_0->ResumeLayout(false);
				 this->dPanel_10_0->PerformLayout();
				 this->dPanel_9_0->ResumeLayout(false);
				 this->dPanel_9_0->PerformLayout();
				 this->dPanel_8_0->ResumeLayout(false);
				 this->dPanel_8_0->PerformLayout();
				 this->dPanel_7_0->ResumeLayout(false);
				 this->dPanel_7_0->PerformLayout();
				 this->dPanel_6_0->ResumeLayout(false);
				 this->dPanel_6_0->PerformLayout();
				 this->dPanel_5_0->ResumeLayout(false);
				 this->dPanel_5_0->PerformLayout();
				 this->dPanel_3_0->ResumeLayout(false);
				 this->dPanel_3_0->PerformLayout();
				 this->dPanel_1_0->ResumeLayout(false);
				 this->dPanel_1_0->PerformLayout();
				 this->dPanel_2_0->ResumeLayout(false);
				 this->dPanel_2_0->PerformLayout();
				 this->dPanel_4_0->ResumeLayout(false);
				 this->dPanel_4_0->PerformLayout();
				 this->dPanel_23_0->ResumeLayout(false);
				 this->dPanel_23_0->PerformLayout();
				 this->dPanel_22_0->ResumeLayout(false);
				 this->dPanel_22_0->PerformLayout();
				 this->dPanel_21_0->ResumeLayout(false);
				 this->dPanel_21_0->PerformLayout();
				 this->dPanel_20_0->ResumeLayout(false);
				 this->dPanel_20_0->PerformLayout();
				 this->dPanel_19_0->ResumeLayout(false);
				 this->dPanel_19_0->PerformLayout();
				 this->dPanel_18_0->ResumeLayout(false);
				 this->dPanel_18_0->PerformLayout();
				 this->dPanel_0_0->ResumeLayout(false);
				 this->dPanel_0_0->PerformLayout();
				 this->info_layout->ResumeLayout(false);
				 this->info_layout->PerformLayout();
				 this->select_day_layout->ResumeLayout(false);
				 this->type_layout->ResumeLayout(false);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
			 //Event for dropdown box, update startday and monthly cal if changed
	private: System::Void wmDay_0_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 startday = (WEEKDAY) mWDay_0->SelectedIndex;
				 setStartDay(startday);
				 drawMonthlyCal(monthly_cal);
			 }
			 //Year textbox event, check if the input year valid, otherwise return old value. Assume input numbers only
			 //Format: 2009
	private: System::Void display_year_Leave(System::Object^  sender, System::EventArgs^  e) {
				 int day = activeDay;
				 int month = activeMonth;
				 int intYear = activeYear;

				 String ^ year = display_year->Text;
				 char *charYear = (char*)Marshal::StringToHGlobalAnsi(year).ToPointer();
				 if(isInteger(charYear)){
					 int strInt = System::Convert::ToInt32(year);
					 if(strInt >= 2000 && strInt <= 9999){
						 intYear = strInt;
					 }
				 }

				 switch (displayType){
				 case 0:
					 setMonths(intYear, month);
					 setStartDay(startday);
					 drawMonthlyCal(monthly_cal);
					 break;
				 case 1:
					 setWeeks(intYear, getWeekInYearFromDate(intYear, activeMonth, activeDay));
					 drawWeeklyCal();				 
					 break;
				 case 2:
					 setDays(intYear, month, day);
					 drawDailyCal();
					 break;
				 default: 
					 break;
				 }		 
			 }
			 //Month textbox event, check if the input month valid, otherwise return old value. Assume input numbers and chars
			 //Format: March or 3
	private: System::Void display_month_Leave(System::Object^  sender, System::EventArgs^  e) {
				 int day = activeDay;
				 int intMonth = activeMonth;
				 int year = activeYear;

				 String ^ month = display_month->Text;
				 if(!String::IsNullOrEmpty(month)){
					 char *charMonth = (char*)Marshal::StringToHGlobalAnsi(month).ToPointer();
					 if(isInteger(charMonth)){
						 int strInt = System::Convert::ToInt32(month);
						 if(strInt > 0 && strInt < 13){
							 intMonth = strInt;
						 }
					 } else {
						 for(int i=1; i<13; i++){
							 String ^ stdMonth = Enum::GetName(MONTH::typeid, i);
							 int result_long = String::Compare(stdMonth, month, true);
							 int result_short = String::Compare(stdMonth->Substring(0, 3), month, true);
							 if(result_long == 0 || result_short == 0){
								 intMonth = i;
								 break;
							 }
						 }
					 }
				 }

				 switch (displayType){
				 case 0:
					 setMonths(year, intMonth);
					 setStartDay(startday);
					 drawMonthlyCal(monthly_cal);				 
					 break;
				 case 1:
					 setWeeks(year, getWeekInYearFromDate(year, intMonth, activeDay));
					 drawWeeklyCal();				 
					 break;
				 case 2:
					 setDays(year, intMonth, day);
					 drawDailyCal();
					 break;
				 default: 
					 break;
				 }
			 }
			 //Week textbox event, check if the input week valid, otherwise return old value. Assume input numbers and chars
			 //Format: Week 31 or 31
	private: System::Void display_week_Leave(System::Object^  sender, System::EventArgs^  e) {
				 int year = activeYear;
				 int intWeek = activeWeek;

				 String ^ week = display_week->Text;
				 if(!String::IsNullOrEmpty(week) && String::Compare(week, "Week ", true) != 0){
					 char *charWeek = (char*)Marshal::StringToHGlobalAnsi(week).ToPointer();
					 if(isInteger(charWeek)){
						 int strInt = System::Convert::ToInt32(week);
						 if(strInt > 0 && strInt <= getNoOfWeeksInYear(year)){
							 intWeek = strInt;
						 }
					 } else {
						 week = week->Trim()->Substring(4, week->Length-4);
						 char *charWeek = (char*)Marshal::StringToHGlobalAnsi(week).ToPointer();
						 if(isInteger(charWeek)){
							 int strInt = System::Convert::ToInt32(week);
							 if(strInt > 0 && strInt <= getNoOfWeeksInYear(year)){
								 intWeek = strInt;
							 }
						 }
					 }
				 }
				 setWeeks(year, intWeek);
				 drawWeeklyCal();
			 }
			 //Day textbox event, check if the input day valid, otherwise return old value. Assume input numbers only
			 //Format: 31
	private: System::Void display_day_Leave(System::Object^  sender, System::EventArgs^  e) {
				 int intDay = activeDay;
				 int month = activeMonth;
				 int year = activeYear;

				 String ^ day = display_day->Text;
				 char *charDay = (char*)Marshal::StringToHGlobalAnsi(day).ToPointer();
				 if(isInteger(charDay)){
					 int strInt = System::Convert::ToInt32(day);
					 if(strInt >= 1 && strInt <= getDaysInMonth(month, year)){
						 intDay = strInt;
					 }
				 }
				 setDays(year, month, intDay);
				 drawDailyCal();
			 }
			 //Week textbox event, when clicked, reset the textbox to "Week " to allow user input easily
	private: System::Void display_week_Enter(System::Object^  sender, System::EventArgs^  e) {
				 display_week->Text = "Week ";
			 }
			 //Week textbox event, when clicked, make sure the cursor is set to the end to allow user input easily
	private: System::Void display_week_Click(System::Object^  sender, System::EventArgs^  e) {
				 display_week->SelectionStart = 5;
				 display_week->SelectionLength = 0;
			 }
			 //Day, Month, Year textbox event, when clicked, select everthing to allow user input easily
	private: System::Void select_all_Click(System::Object^  sender, System::EventArgs^  e) {
				 TextBox ^ tBox = safe_cast<TextBox^>(sender);
				 tBox->SelectAll();		 
			 }
			 //Update the textbox width if the text exceeded the with of textbox
	private: System::Void resize_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 TextBox^ tBox = safe_cast<TextBox^>(sender);
				 int newWidth = (int)CreateGraphics()->MeasureString(tBox->Text, tBox->Font).Width - 5;
				 if(newWidth > tBox->Width){
					 tBox->Width = newWidth;
				 }
			 }
			 //Handle keypress and filter out everything but numbers and chars
			 //If enter key pressed, reset the focus (simulate jumping out of the textbox)
	private: System::Void int_or_char_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if (e->KeyChar == (char)13){//13 = enter
					 e->Handled = true; 
					 prev_btn->Focus();
				 }
				 if (!Char::IsDigit(e->KeyChar) && !Char::IsLetter(e->KeyChar) && e->KeyChar != 0x08){//0x08 = backspace
					 e->Handled = true;
				 }
			 }
			 //Handle keypress and filter out everything but numbers
			 //If enter key pressed, reset the focus (simulate jumping out of the textbox)
	private: System::Void int_only_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if (e->KeyChar == (char)13){//13 = enter
					 e->Handled = true; 
					 prev_btn->Focus();
				 }
				 if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08){//0x08 = backspace
					 e->Handled = true;
				 }
			 }
			 //Event for "<" button
	private: System::Void prev_btn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(displayType == TYPE::Monthly){
					 if(!(thisMonth->GetYear() == 2000 && thisMonth->GetMonthNo() == 1)){
						 int lastMonthY = activeYear;
						 int lastMonthM = activeMonth;
						 decMonth(&lastMonthY, &lastMonthM);
						 setMonths(lastMonthY, lastMonthM);
						 setStartDay(startday);
						 drawMonthlyCal(monthly_cal);
					 }
				 }
				 if(displayType == TYPE::Weekly){
					 if(!(thisWeek->GetYear() == 2000 && thisWeek->GetWeek() == 1)){
						 int lastWeekY = activeYear;
						 int lastWeekW = activeWeek;
						 decWeek(&lastWeekY, &lastWeekW);
						 setWeeks(lastWeekY, lastWeekW);
						 drawWeeklyCal();
					 }
				 }
				 if(displayType == TYPE::Daily){
					 int lastDayY = activeYear;
					 int lastDayM = activeMonth;
					 int lastDayD = activeDay;
					 if(!(lastDayY == 2000 && lastDayM == 1 && lastDayD == 1)){
						 decDay(&lastDayY, &lastDayM, &lastDayD);
						 setDays(lastDayY, lastDayM, lastDayD);
						 drawDailyCal();
					 }
				 }
			 }
			 //Event for "Today" button
	private: System::Void now_btn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(displayType == TYPE::Monthly){
					 setMonths(getTime('y'), getTime('m'));
					 setStartDay(startday);
					 drawMonthlyCal(monthly_cal);
				 }
				 if(displayType == TYPE::Weekly){
					 setWeeks(getTime('y'), getTime('w'));
					 drawWeeklyCal();
				 }
				 if(displayType == TYPE::Daily){
					 setDays(getTime('y'), getTime('m'), getTime('d'));
					 drawDailyCal();
				 }
			 }
			 //Event for ">" button
	private: System::Void next_btn_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(displayType == TYPE::Monthly){
					 if(!(thisMonth->GetYear() == 9999 && thisMonth->GetMonthNo() == 12)){
						 int nextMonthY = activeYear;
						 int nextMonthM = activeMonth;
						 incMonth(&nextMonthY, &nextMonthM);
						 setMonths(nextMonthY, nextMonthM);
						 setStartDay(startday);
						 drawMonthlyCal(monthly_cal);
					 }
				 }
				 if(displayType == TYPE::Weekly){
					 if(!(thisWeek->GetYear() == 9999 && thisWeek->GetWeek() == getNoOfWeeksInYear(9999))){
						 int nextWeekY = activeYear;
						 int nextWeekW = activeWeek;
						 incWeek(&nextWeekY, &nextWeekW);
						 setWeeks(nextWeekY, nextWeekW);
						 drawWeeklyCal();
					 }
				 }
				 if(displayType == TYPE::Daily){
					 int nextDayY = activeYear;
					 int nextDayM = activeMonth;
					 int nextDayD = activeDay;
					 if(!(nextDayY == 9999 && nextDayM == 12 && nextDayD == getDaysInMonth(activeYear, activeYear))){
						 incDay(&nextDayY, &nextDayM, &nextDayD);
						 setDays(nextDayY, nextDayM, nextDayD);
						 drawDailyCal();
					 }
				 }
			 }
			 //Event for "Month" button, switch to monthly view
	private: System::Void monthly_type_Click(System::Object^  sender, System::EventArgs^  e) {
				 setMonths(activeYear, activeMonth);
				 setStartDay(startday);
				 drawCal(TYPE::Monthly);
			 }
			 //Event for "Week" button, switch to weekly view
	private: System::Void weekly_type_Click(System::Object^  sender, System::EventArgs^  e) {
				 setWeeks(activeYear, activeWeek);
				 drawCal(TYPE::Weekly);
			 }
			 //Event for "Daily" button, switch to daily view
	private: System::Void daily_type_Click(System::Object^  sender, System::EventArgs^  e) {
				 WEEKDAY tmp = startday; //save for monthly_cal
				 setDays(activeYear, activeMonth, activeDay);
				 setStartDay(WEEKDAY::Sunday);
				 drawCal(TYPE::Daily);

				 setStartDay(tmp);//restore startday set for monthly_cal
			 }
			 //Event for setting activeDate when clicked on a date
	private: System::Void all_date_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 Control ^ ctl = safe_cast<Control^>(sender);
				 String ^ date = safe_cast<String^>(ctl->Tag);
				 setActiveDate(date);
				 if(ctl->Name->StartsWith("wPanel") || ctl->Name->StartsWith("dPanel")){
					 int hr, min;
					 getTimeFromPos(e->Y, &hr, &min);
					 //				 MessageBox::Show(date + " " + e->X + ", " + e->Y + " " + hr + ", " + min);
					 setActiveDate(activeYear, activeMonth, activeDay, activeWeek, hr, min);
				 }
				 if(ctl->Name->StartsWith("dDay")){
					 setDays(activeYear, activeMonth, activeDay);
					 drawDailyCal();//update the calender when clicked on the mini monthly cal
				 }
			 }
			 //Event for adding/editing event when clicked on a date
	private: System::Void all_date_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 event_form ^ EForm = gcnew event_form(activeYear, activeMonth,activeDay, userName);
				 EForm->ShowDialog();
				 if(!loadevent(events, fileName)){
					 MessageBox::Show("Error In reading file!");
				 }
				 drawCal(displayType);
			 }

			 //Set weelky cal / daily cal on focus to enable the scollbar when using mouse wheel
	private: System::Void scollbar_MouseHover(System::Object^  sender, System::EventArgs^  e) {
				 if(displayType == TYPE::Weekly){
					 weekly_cal->Focus();
				 }
				 if(displayType == TYPE::Daily){
					 daily_cal->Focus();
				 }
			 }
			 //When the form load, show the calendar first than promote login
	private: System::Void Form1_Shown(System::Object^  sender, System::EventArgs^  e) {
				 login_form ^ LForm = gcnew login_form();
				 LForm->ShowDialog();
				 userName = LForm->userName;
				 fileName=(char*)Marshal::StringToHGlobalAnsi(".\\db\\"+userName+".txt").ToPointer();
				 if(!loadevent(events, fileName)){
					 MessageBox::Show("Error In reading file!");
				 }
				 drawMonthlyCal(monthly_cal); //Redraw to show event
			 }
			 //Load the statistic form
	private: System::Void stat_btn_Click(System::Object^  sender, System::EventArgs^  e) {
				 stat_form ^ SForm = gcnew stat_form(activeYear, events);
				 SForm->ShowDialog();
			 }
	};
}


