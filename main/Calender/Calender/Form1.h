#include <iostream>
#include <string>
#include "Months.h"
#include "Days.h"
#pragma once



namespace Calender {
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

	//tmp
	public enum class MONTH {January = 1, February, March, April, May, June, July, August, September, October, November, December};
	public enum class WEEKDAY {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
	WEEKDAY startday = WEEKDAY::Sunday;
	Months thisMonth, lastMonth, nextMonth;
	Days * thisMonthDate = new Days[31];
	Days * lastMonthDate = new Days[31];
	Days * nextMonthDate = new Days[31];
	//tmp

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->SetStyle(static_cast<ControlStyles>(
				ControlStyles::AllPaintingInWmPaint |
				ControlStyles::DoubleBuffer |
				ControlStyles::UserPaint), true); 
			this->UpdateStyles();
			setMonths(getTime('y'), getTime('m'));
			setStartDay(startday);
			drawMonthlyCal();
		}

	private: 
//tmp
bool isInteger(char * c){
	bool result;
	for(int i = 0; i < strlen(c); i++){
		if(! (c[i] >= '0' && c[i] <= '9' || c[i] == ' ') ){
			result = false;
			break;
		} else {
			result =  true;
		}
	}
	return result;
}
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
int getTime(char type){
	System::DateTime now = System::DateTime::Now;

	switch (type){
	case 'd': return now.Day;
				break;
	case 'm': return now.Month;
				break;
	case 'y': return now.Year;
				break;		
	default:	return 0;
				break;
	}
}
int decMonth(int year, int month, char type){
	if (month == 1){
		year -= 1;
		month = 12;
	} else {
		month -= 1;
	}
	switch(type){
	case 'y': return year; break;
	case 'm': return month; break;
	default: return 0; break;
	}
}

int incMonth(int year, int month, char type){
	if (month == 12){
		year += 1;
		month = 1;
	} else {
		month += 1;
	}
	switch(type){
	case 'y': return year; break;
	case 'm': return month; break;
	default: return 0; break;
	}
}
//tmp
		void setDayInfo(TableLayoutPanel^ parent, int r, int c, String^ name, String^ msg){
			for each ( Control ^ctl in parent->Controls ){
				if(parent->GetRow(ctl)==r && parent->GetColumn(ctl)==c && ctl->Name->StartsWith(name)){
					ctl->Text = msg;
				}
			}
		}
		void setStartDay(WEEKDAY fday){
			fday++; //skip the first combobox
			for(int i=0; i<6; i++){
				if (fday > WEEKDAY::Saturday){
					fday = WEEKDAY::Sunday;
				}
				String^ wday = Enum::GetName(WEEKDAY::typeid, fday++);
				setDayInfo(monthly_cal, 0, i+1, "wday", wday);
				for (int i=0; i<lastMonth.GetMaxDay(); i++){
					lastMonthDate[i].SetStartDay((int)fday);
				}				
				for (int i=0; i<thisMonth.GetMaxDay(); i++){
					thisMonthDate[i].SetStartDay((int)fday);
				}	
				for (int i=0; i<nextMonth.GetMaxDay(); i++){
					nextMonthDate[i].SetStartDay((int)fday);
				}	
			}
		}
		void setMonths(int year, int month){
			thisMonth.SetYM(year, month);
			lastMonth.SetYM(decMonth(year, month, 'y'), decMonth(year, month, 'm'));
			nextMonth.SetYM(incMonth(year, month, 'y'), incMonth(year, month, 'm'));

			for (int i=0; i<lastMonth.GetMaxDay(); i++){
				lastMonthDate[i].SetYMD(lastMonth.GetYear(), lastMonth.GetMonthNo(), i+1);
			}				
			for (int i=0; i<thisMonth.GetMaxDay(); i++){
				thisMonthDate[i].SetYMD(thisMonth.GetYear(), thisMonth.GetMonthNo(), i+1);
			}	
			for (int i=0; i<nextMonth.GetMaxDay(); i++){
				nextMonthDate[i].SetYMD(nextMonth.GetYear(), nextMonth.GetMonthNo(), i+1);
			}	
		}
		void drawMonthlyCal(){
			display_year->Text = thisMonth.GetYear().ToString();
			display_month->Text = Enum::GetName(MONTH::typeid, thisMonth.GetMonthNo());
			for (int i=(lastMonth.GetMaxDay() - thisMonthDate[0].GetXY('x')); i<lastMonth.GetMaxDay(); i++){
				setDayInfo(monthly_cal, 1, lastMonthDate[i].GetXY('x'), "day",  (i+1).ToString());
			}				
			for (int i=0; i<thisMonth.GetMaxDay(); i++){
				setDayInfo(monthly_cal, thisMonthDate[i].GetXY('y'), thisMonthDate[i].GetXY('x'), "day",  (i+1).ToString());
			}	
			int dayToShow = 6 - thisMonthDate[thisMonth.GetMaxDay()-1].GetXY('x');
			int rowCorrection = thisMonthDate[thisMonth.GetMaxDay()-1].GetXY('y') - 1;
			if(thisMonthDate[thisMonth.GetMaxDay()-1].GetXY('y') < 6 ){
				dayToShow += 7;
			}
			if(thisMonthDate[thisMonth.GetMaxDay()-1].GetXY('x') == 6){
				rowCorrection += 1;
			}
			for (int i=0; i<dayToShow; i++){
				setDayInfo(monthly_cal, nextMonthDate[i].GetXY('y') + rowCorrection, nextMonthDate[i].GetXY('x'), "day",  (i+1).ToString());
			}	
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  monthly_cal;

	private: System::Windows::Forms::Label^  wday_1;
	private: System::Windows::Forms::Label^  wday_2;
	private: System::Windows::Forms::Label^  wday_3;
	private: System::Windows::Forms::Label^  wday_4;
	private: System::Windows::Forms::Label^  wday_5;
	private: System::Windows::Forms::Label^  wday_6;
	private: System::Windows::Forms::Label^  day_6_0;
	private: System::Windows::Forms::Label^  day_6_1;
	private: System::Windows::Forms::Label^  day_6_2;
	private: System::Windows::Forms::Label^  day_6_3;
	private: System::Windows::Forms::Label^  day_6_4;
	private: System::Windows::Forms::Label^  day_6_5;
	private: System::Windows::Forms::Label^  day_6_6;
	protected: 

















	private: System::Windows::Forms::Label^  day_5_0;
	private: System::Windows::Forms::Label^  day_5_1;
	private: System::Windows::Forms::Label^  day_5_2;
	private: System::Windows::Forms::Label^  day_5_3;
	private: System::Windows::Forms::Label^  day_5_4;
	private: System::Windows::Forms::Label^  day_5_5;
	private: System::Windows::Forms::Label^  day_5_6;







	private: System::Windows::Forms::Label^  day_4_0;
	private: System::Windows::Forms::Label^  day_4_1;
	private: System::Windows::Forms::Label^  day_4_2;
	private: System::Windows::Forms::Label^  day_4_3;
	private: System::Windows::Forms::Label^  day_4_4;
	private: System::Windows::Forms::Label^  day_4_5;
	private: System::Windows::Forms::Label^  day_4_6;







	private: System::Windows::Forms::Label^  day_3_0;
	private: System::Windows::Forms::Label^  day_3_1;
	private: System::Windows::Forms::Label^  day_3_2;
	private: System::Windows::Forms::Label^  day_3_3;
	private: System::Windows::Forms::Label^  day_3_4;
	private: System::Windows::Forms::Label^  day_3_5;
	private: System::Windows::Forms::Label^  day_3_6;







private: System::Windows::Forms::Label^  day_2_0;
private: System::Windows::Forms::Label^  day_2_1;
private: System::Windows::Forms::Label^  day_2_2;
private: System::Windows::Forms::Label^  day_2_3;
private: System::Windows::Forms::Label^  day_2_4;
private: System::Windows::Forms::Label^  day_2_5;
private: System::Windows::Forms::Label^  day_2_6;







private: System::Windows::Forms::Label^  day_1_0;
private: System::Windows::Forms::Label^  day_1_1;
private: System::Windows::Forms::Label^  day_1_2;
private: System::Windows::Forms::Label^  day_1_3;
private: System::Windows::Forms::Label^  day_1_4;
private: System::Windows::Forms::Label^  day_1_5;
private: System::Windows::Forms::Label^  day_1_6;
private: System::Windows::Forms::TextBox^  display_year;
private: System::Windows::Forms::TextBox^  display_month;
private: System::Windows::Forms::Button^  last_month;
private: System::Windows::Forms::Button^  next_month;
private: System::Windows::Forms::Button^  monthly_type;
private: System::Windows::Forms::Button^  weekly_type;
private: System::Windows::Forms::Button^  daily_type;







private: System::Windows::Forms::Button^  button6;
private: System::Windows::Forms::ComboBox^  wday_0;
private: System::Windows::Forms::Button^  this_month;














	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->monthly_cal = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->day_6_0 = (gcnew System::Windows::Forms::Label());
			this->wday_0 = (gcnew System::Windows::Forms::ComboBox());
			this->day_6_1 = (gcnew System::Windows::Forms::Label());
			this->day_6_2 = (gcnew System::Windows::Forms::Label());
			this->day_6_3 = (gcnew System::Windows::Forms::Label());
			this->day_6_4 = (gcnew System::Windows::Forms::Label());
			this->day_6_5 = (gcnew System::Windows::Forms::Label());
			this->day_6_6 = (gcnew System::Windows::Forms::Label());
			this->day_5_0 = (gcnew System::Windows::Forms::Label());
			this->day_5_1 = (gcnew System::Windows::Forms::Label());
			this->day_5_2 = (gcnew System::Windows::Forms::Label());
			this->day_5_3 = (gcnew System::Windows::Forms::Label());
			this->day_5_4 = (gcnew System::Windows::Forms::Label());
			this->day_5_5 = (gcnew System::Windows::Forms::Label());
			this->day_5_6 = (gcnew System::Windows::Forms::Label());
			this->day_4_0 = (gcnew System::Windows::Forms::Label());
			this->day_4_1 = (gcnew System::Windows::Forms::Label());
			this->day_4_2 = (gcnew System::Windows::Forms::Label());
			this->day_4_3 = (gcnew System::Windows::Forms::Label());
			this->day_4_4 = (gcnew System::Windows::Forms::Label());
			this->day_4_5 = (gcnew System::Windows::Forms::Label());
			this->day_4_6 = (gcnew System::Windows::Forms::Label());
			this->day_3_0 = (gcnew System::Windows::Forms::Label());
			this->day_3_1 = (gcnew System::Windows::Forms::Label());
			this->day_3_2 = (gcnew System::Windows::Forms::Label());
			this->day_3_3 = (gcnew System::Windows::Forms::Label());
			this->day_3_4 = (gcnew System::Windows::Forms::Label());
			this->day_3_5 = (gcnew System::Windows::Forms::Label());
			this->day_3_6 = (gcnew System::Windows::Forms::Label());
			this->day_2_0 = (gcnew System::Windows::Forms::Label());
			this->day_2_1 = (gcnew System::Windows::Forms::Label());
			this->day_2_2 = (gcnew System::Windows::Forms::Label());
			this->day_2_3 = (gcnew System::Windows::Forms::Label());
			this->day_2_4 = (gcnew System::Windows::Forms::Label());
			this->day_2_5 = (gcnew System::Windows::Forms::Label());
			this->day_2_6 = (gcnew System::Windows::Forms::Label());
			this->day_1_0 = (gcnew System::Windows::Forms::Label());
			this->day_1_1 = (gcnew System::Windows::Forms::Label());
			this->day_1_2 = (gcnew System::Windows::Forms::Label());
			this->day_1_3 = (gcnew System::Windows::Forms::Label());
			this->day_1_4 = (gcnew System::Windows::Forms::Label());
			this->day_1_5 = (gcnew System::Windows::Forms::Label());
			this->day_1_6 = (gcnew System::Windows::Forms::Label());
			this->wday_1 = (gcnew System::Windows::Forms::Label());
			this->wday_2 = (gcnew System::Windows::Forms::Label());
			this->wday_3 = (gcnew System::Windows::Forms::Label());
			this->wday_4 = (gcnew System::Windows::Forms::Label());
			this->wday_5 = (gcnew System::Windows::Forms::Label());
			this->wday_6 = (gcnew System::Windows::Forms::Label());
			this->display_year = (gcnew System::Windows::Forms::TextBox());
			this->display_month = (gcnew System::Windows::Forms::TextBox());
			this->last_month = (gcnew System::Windows::Forms::Button());
			this->next_month = (gcnew System::Windows::Forms::Button());
			this->monthly_type = (gcnew System::Windows::Forms::Button());
			this->weekly_type = (gcnew System::Windows::Forms::Button());
			this->daily_type = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->this_month = (gcnew System::Windows::Forms::Button());
			this->monthly_cal->SuspendLayout();
			this->SuspendLayout();
			// 
			// monthly_cal
			// 
			this->monthly_cal->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->monthly_cal->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->monthly_cal->ColumnCount = 7;
			this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->Controls->Add(this->day_6_0, 0, 6);
			this->monthly_cal->Controls->Add(this->wday_0, 0, 0);
			this->monthly_cal->Controls->Add(this->day_6_1, 1, 6);
			this->monthly_cal->Controls->Add(this->day_6_2, 2, 6);
			this->monthly_cal->Controls->Add(this->day_6_3, 3, 6);
			this->monthly_cal->Controls->Add(this->day_6_4, 4, 6);
			this->monthly_cal->Controls->Add(this->day_6_5, 5, 6);
			this->monthly_cal->Controls->Add(this->day_6_6, 6, 6);
			this->monthly_cal->Controls->Add(this->day_5_0, 0, 5);
			this->monthly_cal->Controls->Add(this->day_5_1, 1, 5);
			this->monthly_cal->Controls->Add(this->day_5_2, 2, 5);
			this->monthly_cal->Controls->Add(this->day_5_3, 3, 5);
			this->monthly_cal->Controls->Add(this->day_5_4, 4, 5);
			this->monthly_cal->Controls->Add(this->day_5_5, 5, 5);
			this->monthly_cal->Controls->Add(this->day_5_6, 6, 5);
			this->monthly_cal->Controls->Add(this->day_4_0, 0, 4);
			this->monthly_cal->Controls->Add(this->day_4_1, 1, 4);
			this->monthly_cal->Controls->Add(this->day_4_2, 2, 4);
			this->monthly_cal->Controls->Add(this->day_4_3, 3, 4);
			this->monthly_cal->Controls->Add(this->day_4_4, 4, 4);
			this->monthly_cal->Controls->Add(this->day_4_5, 5, 4);
			this->monthly_cal->Controls->Add(this->day_4_6, 6, 4);
			this->monthly_cal->Controls->Add(this->day_3_0, 0, 3);
			this->monthly_cal->Controls->Add(this->day_3_1, 1, 3);
			this->monthly_cal->Controls->Add(this->day_3_2, 2, 3);
			this->monthly_cal->Controls->Add(this->day_3_3, 3, 3);
			this->monthly_cal->Controls->Add(this->day_3_4, 4, 3);
			this->monthly_cal->Controls->Add(this->day_3_5, 5, 3);
			this->monthly_cal->Controls->Add(this->day_3_6, 6, 3);
			this->monthly_cal->Controls->Add(this->day_2_0, 0, 2);
			this->monthly_cal->Controls->Add(this->day_2_1, 1, 2);
			this->monthly_cal->Controls->Add(this->day_2_2, 2, 2);
			this->monthly_cal->Controls->Add(this->day_2_3, 3, 2);
			this->monthly_cal->Controls->Add(this->day_2_4, 4, 2);
			this->monthly_cal->Controls->Add(this->day_2_5, 5, 2);
			this->monthly_cal->Controls->Add(this->day_2_6, 6, 2);
			this->monthly_cal->Controls->Add(this->day_1_0, 0, 1);
			this->monthly_cal->Controls->Add(this->day_1_1, 1, 1);
			this->monthly_cal->Controls->Add(this->day_1_2, 2, 1);
			this->monthly_cal->Controls->Add(this->day_1_3, 3, 1);
			this->monthly_cal->Controls->Add(this->day_1_4, 4, 1);
			this->monthly_cal->Controls->Add(this->day_1_5, 5, 1);
			this->monthly_cal->Controls->Add(this->day_1_6, 6, 1);
			this->monthly_cal->Controls->Add(this->wday_1, 1, 0);
			this->monthly_cal->Controls->Add(this->wday_2, 2, 0);
			this->monthly_cal->Controls->Add(this->wday_3, 3, 0);
			this->monthly_cal->Controls->Add(this->wday_4, 4, 0);
			this->monthly_cal->Controls->Add(this->wday_5, 5, 0);
			this->monthly_cal->Controls->Add(this->wday_6, 6, 0);
			this->monthly_cal->Location = System::Drawing::Point(45, 70);
			this->monthly_cal->Margin = System::Windows::Forms::Padding(3, 1, 3, 1);
			this->monthly_cal->Name = L"monthly_cal";
			this->monthly_cal->RowCount = 7;
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->Size = System::Drawing::Size(800, 320);
			this->monthly_cal->TabIndex = 1;
			this->monthly_cal->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::tableLayoutPanel1_Paint);
			// 
			// day_6_0
			// 
			this->day_6_0->AutoSize = true;
			this->day_6_0->Location = System::Drawing::Point(4, 271);
			this->day_6_0->Name = L"day_6_0";
			this->day_6_0->Size = System::Drawing::Size(46, 17);
			this->day_6_0->TabIndex = 42;
			this->day_6_0->Text = L"label1";
			// 
			// wday_0
			// 
			this->wday_0->FormattingEnabled = true;
			this->wday_0->Items->AddRange(gcnew cli::array< System::Object^  >(7) {L"Sunday", L"Monday", L"Tuesday", L"Wednesday", L"Thursday", 
				L"Friday", L"Saturday"});
			this->wday_0->Location = System::Drawing::Point(5, 5);
			this->wday_0->Margin = System::Windows::Forms::Padding(4);
			this->wday_0->Name = L"wday_0";
			this->wday_0->Size = System::Drawing::Size(103, 24);
			this->wday_0->TabIndex = 10;
			this->wday_0->Text = L"Sunday";
			this->wday_0->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::wday_0_SelectedIndexChanged);
			// 
			// day_6_1
			// 
			this->day_6_1->AutoSize = true;
			this->day_6_1->Location = System::Drawing::Point(118, 271);
			this->day_6_1->Name = L"day_6_1";
			this->day_6_1->Size = System::Drawing::Size(46, 17);
			this->day_6_1->TabIndex = 43;
			this->day_6_1->Text = L"label2";
			// 
			// day_6_2
			// 
			this->day_6_2->AutoSize = true;
			this->day_6_2->Location = System::Drawing::Point(232, 271);
			this->day_6_2->Name = L"day_6_2";
			this->day_6_2->Size = System::Drawing::Size(46, 17);
			this->day_6_2->TabIndex = 44;
			this->day_6_2->Text = L"label3";
			// 
			// day_6_3
			// 
			this->day_6_3->AutoSize = true;
			this->day_6_3->Location = System::Drawing::Point(346, 271);
			this->day_6_3->Name = L"day_6_3";
			this->day_6_3->Size = System::Drawing::Size(46, 17);
			this->day_6_3->TabIndex = 45;
			this->day_6_3->Text = L"label4";
			// 
			// day_6_4
			// 
			this->day_6_4->AutoSize = true;
			this->day_6_4->Location = System::Drawing::Point(460, 271);
			this->day_6_4->Name = L"day_6_4";
			this->day_6_4->Size = System::Drawing::Size(46, 17);
			this->day_6_4->TabIndex = 46;
			this->day_6_4->Text = L"label5";
			// 
			// day_6_5
			// 
			this->day_6_5->AutoSize = true;
			this->day_6_5->Location = System::Drawing::Point(574, 271);
			this->day_6_5->Name = L"day_6_5";
			this->day_6_5->Size = System::Drawing::Size(46, 17);
			this->day_6_5->TabIndex = 47;
			this->day_6_5->Text = L"label6";
			// 
			// day_6_6
			// 
			this->day_6_6->AutoSize = true;
			this->day_6_6->Location = System::Drawing::Point(688, 271);
			this->day_6_6->Name = L"day_6_6";
			this->day_6_6->Size = System::Drawing::Size(46, 17);
			this->day_6_6->TabIndex = 48;
			this->day_6_6->Text = L"label7";
			// 
			// day_5_0
			// 
			this->day_5_0->AutoSize = true;
			this->day_5_0->Location = System::Drawing::Point(4, 226);
			this->day_5_0->Name = L"day_5_0";
			this->day_5_0->Size = System::Drawing::Size(46, 17);
			this->day_5_0->TabIndex = 35;
			this->day_5_0->Text = L"label1";
			// 
			// day_5_1
			// 
			this->day_5_1->AutoSize = true;
			this->day_5_1->Location = System::Drawing::Point(118, 226);
			this->day_5_1->Name = L"day_5_1";
			this->day_5_1->Size = System::Drawing::Size(46, 17);
			this->day_5_1->TabIndex = 36;
			this->day_5_1->Text = L"label2";
			// 
			// day_5_2
			// 
			this->day_5_2->AutoSize = true;
			this->day_5_2->Location = System::Drawing::Point(232, 226);
			this->day_5_2->Name = L"day_5_2";
			this->day_5_2->Size = System::Drawing::Size(46, 17);
			this->day_5_2->TabIndex = 37;
			this->day_5_2->Text = L"label3";
			// 
			// day_5_3
			// 
			this->day_5_3->AutoSize = true;
			this->day_5_3->Location = System::Drawing::Point(346, 226);
			this->day_5_3->Name = L"day_5_3";
			this->day_5_3->Size = System::Drawing::Size(46, 17);
			this->day_5_3->TabIndex = 38;
			this->day_5_3->Text = L"label4";
			// 
			// day_5_4
			// 
			this->day_5_4->AutoSize = true;
			this->day_5_4->Location = System::Drawing::Point(460, 226);
			this->day_5_4->Name = L"day_5_4";
			this->day_5_4->Size = System::Drawing::Size(46, 17);
			this->day_5_4->TabIndex = 39;
			this->day_5_4->Text = L"label5";
			// 
			// day_5_5
			// 
			this->day_5_5->AutoSize = true;
			this->day_5_5->Location = System::Drawing::Point(574, 226);
			this->day_5_5->Name = L"day_5_5";
			this->day_5_5->Size = System::Drawing::Size(46, 17);
			this->day_5_5->TabIndex = 40;
			this->day_5_5->Text = L"label6";
			// 
			// day_5_6
			// 
			this->day_5_6->AutoSize = true;
			this->day_5_6->Location = System::Drawing::Point(688, 226);
			this->day_5_6->Name = L"day_5_6";
			this->day_5_6->Size = System::Drawing::Size(46, 17);
			this->day_5_6->TabIndex = 41;
			this->day_5_6->Text = L"label7";
			// 
			// day_4_0
			// 
			this->day_4_0->AutoSize = true;
			this->day_4_0->Location = System::Drawing::Point(4, 181);
			this->day_4_0->Name = L"day_4_0";
			this->day_4_0->Size = System::Drawing::Size(46, 17);
			this->day_4_0->TabIndex = 28;
			this->day_4_0->Text = L"label1";
			// 
			// day_4_1
			// 
			this->day_4_1->AutoSize = true;
			this->day_4_1->Location = System::Drawing::Point(118, 181);
			this->day_4_1->Name = L"day_4_1";
			this->day_4_1->Size = System::Drawing::Size(46, 17);
			this->day_4_1->TabIndex = 29;
			this->day_4_1->Text = L"label2";
			// 
			// day_4_2
			// 
			this->day_4_2->AutoSize = true;
			this->day_4_2->Location = System::Drawing::Point(232, 181);
			this->day_4_2->Name = L"day_4_2";
			this->day_4_2->Size = System::Drawing::Size(46, 17);
			this->day_4_2->TabIndex = 30;
			this->day_4_2->Text = L"label3";
			// 
			// day_4_3
			// 
			this->day_4_3->AutoSize = true;
			this->day_4_3->Location = System::Drawing::Point(346, 181);
			this->day_4_3->Name = L"day_4_3";
			this->day_4_3->Size = System::Drawing::Size(46, 17);
			this->day_4_3->TabIndex = 31;
			this->day_4_3->Text = L"label4";
			// 
			// day_4_4
			// 
			this->day_4_4->AutoSize = true;
			this->day_4_4->Location = System::Drawing::Point(460, 181);
			this->day_4_4->Name = L"day_4_4";
			this->day_4_4->Size = System::Drawing::Size(46, 17);
			this->day_4_4->TabIndex = 32;
			this->day_4_4->Text = L"label5";
			// 
			// day_4_5
			// 
			this->day_4_5->AutoSize = true;
			this->day_4_5->Location = System::Drawing::Point(574, 181);
			this->day_4_5->Name = L"day_4_5";
			this->day_4_5->Size = System::Drawing::Size(46, 17);
			this->day_4_5->TabIndex = 33;
			this->day_4_5->Text = L"label6";
			// 
			// day_4_6
			// 
			this->day_4_6->AutoSize = true;
			this->day_4_6->Location = System::Drawing::Point(688, 181);
			this->day_4_6->Name = L"day_4_6";
			this->day_4_6->Size = System::Drawing::Size(46, 17);
			this->day_4_6->TabIndex = 34;
			this->day_4_6->Text = L"label7";
			// 
			// day_3_0
			// 
			this->day_3_0->AutoSize = true;
			this->day_3_0->Location = System::Drawing::Point(4, 136);
			this->day_3_0->Name = L"day_3_0";
			this->day_3_0->Size = System::Drawing::Size(46, 17);
			this->day_3_0->TabIndex = 21;
			this->day_3_0->Text = L"label1";
			// 
			// day_3_1
			// 
			this->day_3_1->AutoSize = true;
			this->day_3_1->Location = System::Drawing::Point(118, 136);
			this->day_3_1->Name = L"day_3_1";
			this->day_3_1->Size = System::Drawing::Size(46, 17);
			this->day_3_1->TabIndex = 22;
			this->day_3_1->Text = L"label2";
			// 
			// day_3_2
			// 
			this->day_3_2->AutoSize = true;
			this->day_3_2->Location = System::Drawing::Point(232, 136);
			this->day_3_2->Name = L"day_3_2";
			this->day_3_2->Size = System::Drawing::Size(46, 17);
			this->day_3_2->TabIndex = 23;
			this->day_3_2->Text = L"label3";
			// 
			// day_3_3
			// 
			this->day_3_3->AutoSize = true;
			this->day_3_3->Location = System::Drawing::Point(346, 136);
			this->day_3_3->Name = L"day_3_3";
			this->day_3_3->Size = System::Drawing::Size(46, 17);
			this->day_3_3->TabIndex = 24;
			this->day_3_3->Text = L"label4";
			// 
			// day_3_4
			// 
			this->day_3_4->AutoSize = true;
			this->day_3_4->Location = System::Drawing::Point(460, 136);
			this->day_3_4->Name = L"day_3_4";
			this->day_3_4->Size = System::Drawing::Size(46, 17);
			this->day_3_4->TabIndex = 25;
			this->day_3_4->Text = L"label5";
			// 
			// day_3_5
			// 
			this->day_3_5->AutoSize = true;
			this->day_3_5->Location = System::Drawing::Point(574, 136);
			this->day_3_5->Name = L"day_3_5";
			this->day_3_5->Size = System::Drawing::Size(46, 17);
			this->day_3_5->TabIndex = 26;
			this->day_3_5->Text = L"label6";
			// 
			// day_3_6
			// 
			this->day_3_6->AutoSize = true;
			this->day_3_6->Location = System::Drawing::Point(688, 136);
			this->day_3_6->Name = L"day_3_6";
			this->day_3_6->Size = System::Drawing::Size(46, 17);
			this->day_3_6->TabIndex = 27;
			this->day_3_6->Text = L"label7";
			// 
			// day_2_0
			// 
			this->day_2_0->AutoSize = true;
			this->day_2_0->Location = System::Drawing::Point(4, 91);
			this->day_2_0->Name = L"day_2_0";
			this->day_2_0->Size = System::Drawing::Size(46, 17);
			this->day_2_0->TabIndex = 14;
			this->day_2_0->Text = L"label1";
			// 
			// day_2_1
			// 
			this->day_2_1->AutoSize = true;
			this->day_2_1->Location = System::Drawing::Point(118, 91);
			this->day_2_1->Name = L"day_2_1";
			this->day_2_1->Size = System::Drawing::Size(46, 17);
			this->day_2_1->TabIndex = 15;
			this->day_2_1->Text = L"label2";
			// 
			// day_2_2
			// 
			this->day_2_2->AutoSize = true;
			this->day_2_2->Location = System::Drawing::Point(232, 91);
			this->day_2_2->Name = L"day_2_2";
			this->day_2_2->Size = System::Drawing::Size(46, 17);
			this->day_2_2->TabIndex = 16;
			this->day_2_2->Text = L"label3";
			// 
			// day_2_3
			// 
			this->day_2_3->AutoSize = true;
			this->day_2_3->Location = System::Drawing::Point(346, 91);
			this->day_2_3->Name = L"day_2_3";
			this->day_2_3->Size = System::Drawing::Size(46, 17);
			this->day_2_3->TabIndex = 17;
			this->day_2_3->Text = L"label4";
			// 
			// day_2_4
			// 
			this->day_2_4->AutoSize = true;
			this->day_2_4->Location = System::Drawing::Point(460, 91);
			this->day_2_4->Name = L"day_2_4";
			this->day_2_4->Size = System::Drawing::Size(46, 17);
			this->day_2_4->TabIndex = 18;
			this->day_2_4->Text = L"label5";
			// 
			// day_2_5
			// 
			this->day_2_5->AutoSize = true;
			this->day_2_5->Location = System::Drawing::Point(574, 91);
			this->day_2_5->Name = L"day_2_5";
			this->day_2_5->Size = System::Drawing::Size(46, 17);
			this->day_2_5->TabIndex = 19;
			this->day_2_5->Text = L"label6";
			// 
			// day_2_6
			// 
			this->day_2_6->AutoSize = true;
			this->day_2_6->Location = System::Drawing::Point(688, 91);
			this->day_2_6->Name = L"day_2_6";
			this->day_2_6->Size = System::Drawing::Size(46, 17);
			this->day_2_6->TabIndex = 20;
			this->day_2_6->Text = L"label7";
			// 
			// day_1_0
			// 
			this->day_1_0->AutoSize = true;
			this->day_1_0->Location = System::Drawing::Point(4, 46);
			this->day_1_0->Name = L"day_1_0";
			this->day_1_0->Size = System::Drawing::Size(46, 17);
			this->day_1_0->TabIndex = 7;
			this->day_1_0->Text = L"label1";
			// 
			// day_1_1
			// 
			this->day_1_1->AutoSize = true;
			this->day_1_1->Location = System::Drawing::Point(118, 46);
			this->day_1_1->Name = L"day_1_1";
			this->day_1_1->Size = System::Drawing::Size(46, 17);
			this->day_1_1->TabIndex = 8;
			this->day_1_1->Text = L"label2";
			// 
			// day_1_2
			// 
			this->day_1_2->AutoSize = true;
			this->day_1_2->Location = System::Drawing::Point(232, 46);
			this->day_1_2->Name = L"day_1_2";
			this->day_1_2->Size = System::Drawing::Size(46, 17);
			this->day_1_2->TabIndex = 9;
			this->day_1_2->Text = L"label3";
			// 
			// day_1_3
			// 
			this->day_1_3->AutoSize = true;
			this->day_1_3->Location = System::Drawing::Point(346, 46);
			this->day_1_3->Name = L"day_1_3";
			this->day_1_3->Size = System::Drawing::Size(46, 17);
			this->day_1_3->TabIndex = 10;
			this->day_1_3->Text = L"label4";
			// 
			// day_1_4
			// 
			this->day_1_4->AutoSize = true;
			this->day_1_4->Location = System::Drawing::Point(460, 46);
			this->day_1_4->Name = L"day_1_4";
			this->day_1_4->Size = System::Drawing::Size(46, 17);
			this->day_1_4->TabIndex = 11;
			this->day_1_4->Text = L"label5";
			// 
			// day_1_5
			// 
			this->day_1_5->AutoSize = true;
			this->day_1_5->Location = System::Drawing::Point(574, 46);
			this->day_1_5->Name = L"day_1_5";
			this->day_1_5->Size = System::Drawing::Size(46, 17);
			this->day_1_5->TabIndex = 12;
			this->day_1_5->Text = L"label6";
			// 
			// day_1_6
			// 
			this->day_1_6->AutoSize = true;
			this->day_1_6->Location = System::Drawing::Point(688, 46);
			this->day_1_6->Name = L"day_1_6";
			this->day_1_6->Size = System::Drawing::Size(46, 17);
			this->day_1_6->TabIndex = 13;
			this->day_1_6->Text = L"label7";
			// 
			// wday_1
			// 
			this->wday_1->AutoSize = true;
			this->wday_1->Location = System::Drawing::Point(118, 1);
			this->wday_1->Name = L"wday_1";
			this->wday_1->Size = System::Drawing::Size(46, 17);
			this->wday_1->TabIndex = 1;
			this->wday_1->Text = L"label2";
			// 
			// wday_2
			// 
			this->wday_2->AutoSize = true;
			this->wday_2->Location = System::Drawing::Point(232, 1);
			this->wday_2->Name = L"wday_2";
			this->wday_2->Size = System::Drawing::Size(46, 17);
			this->wday_2->TabIndex = 2;
			this->wday_2->Text = L"label3";
			// 
			// wday_3
			// 
			this->wday_3->AutoSize = true;
			this->wday_3->Location = System::Drawing::Point(346, 1);
			this->wday_3->Name = L"wday_3";
			this->wday_3->Size = System::Drawing::Size(46, 17);
			this->wday_3->TabIndex = 3;
			this->wday_3->Text = L"label4";
			// 
			// wday_4
			// 
			this->wday_4->AutoSize = true;
			this->wday_4->Location = System::Drawing::Point(460, 1);
			this->wday_4->Name = L"wday_4";
			this->wday_4->Size = System::Drawing::Size(46, 17);
			this->wday_4->TabIndex = 4;
			this->wday_4->Text = L"label5";
			// 
			// wday_5
			// 
			this->wday_5->AutoSize = true;
			this->wday_5->Location = System::Drawing::Point(574, 1);
			this->wday_5->Name = L"wday_5";
			this->wday_5->Size = System::Drawing::Size(46, 17);
			this->wday_5->TabIndex = 5;
			this->wday_5->Text = L"label6";
			// 
			// wday_6
			// 
			this->wday_6->AutoSize = true;
			this->wday_6->Location = System::Drawing::Point(688, 1);
			this->wday_6->Name = L"wday_6";
			this->wday_6->Size = System::Drawing::Size(46, 17);
			this->wday_6->TabIndex = 6;
			this->wday_6->Text = L"label7";
			// 
			// display_year
			// 
			this->display_year->BackColor = System::Drawing::SystemColors::Control;
			this->display_year->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->display_year->Font = (gcnew System::Drawing::Font(L"Segoe UI Light", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->display_year->Location = System::Drawing::Point(784, 25);
			this->display_year->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->display_year->Name = L"display_year";
			this->display_year->Size = System::Drawing::Size(65, 36);
			this->display_year->TabIndex = 2;
			this->display_year->Text = L"2014";
			this->display_year->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->display_year->TextChanged += gcnew System::EventHandler(this, &Form1::display_year_TextChanged);
			// 
			// display_month
			// 
			this->display_month->BackColor = System::Drawing::SystemColors::Control;
			this->display_month->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->display_month->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->display_month->Location = System::Drawing::Point(633, 25);
			this->display_month->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->display_month->Name = L"display_month";
			this->display_month->Size = System::Drawing::Size(150, 36);
			this->display_month->TabIndex = 3;
			this->display_month->Text = L"December";
			this->display_month->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->display_month->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::display_month_KeyDown);
			this->display_month->LostFocus += gcnew System::EventHandler(this, &Form1::display_month_LostFocus);
			// 
			// last_month
			// 
			this->last_month->Location = System::Drawing::Point(44, 32);
			this->last_month->Margin = System::Windows::Forms::Padding(4);
			this->last_month->Name = L"last_month";
			this->last_month->Size = System::Drawing::Size(33, 28);
			this->last_month->TabIndex = 4;
			this->last_month->Text = L"<";
			this->last_month->UseVisualStyleBackColor = true;
			this->last_month->Click += gcnew System::EventHandler(this, &Form1::last_month_Click);
			// 
			// next_month
			// 
			this->next_month->Location = System::Drawing::Point(144, 32);
			this->next_month->Margin = System::Windows::Forms::Padding(4);
			this->next_month->Name = L"next_month";
			this->next_month->Size = System::Drawing::Size(33, 28);
			this->next_month->TabIndex = 5;
			this->next_month->Text = L">";
			this->next_month->UseVisualStyleBackColor = true;
			this->next_month->Click += gcnew System::EventHandler(this, &Form1::next_month_Click);
			// 
			// monthly_type
			// 
			this->monthly_type->Location = System::Drawing::Point(292, 32);
			this->monthly_type->Margin = System::Windows::Forms::Padding(4);
			this->monthly_type->Name = L"monthly_type";
			this->monthly_type->Size = System::Drawing::Size(100, 28);
			this->monthly_type->TabIndex = 6;
			this->monthly_type->Text = L"Month";
			this->monthly_type->UseVisualStyleBackColor = true;
			// 
			// weekly_type
			// 
			this->weekly_type->Location = System::Drawing::Point(396, 32);
			this->weekly_type->Margin = System::Windows::Forms::Padding(4);
			this->weekly_type->Name = L"weekly_type";
			this->weekly_type->Size = System::Drawing::Size(100, 28);
			this->weekly_type->TabIndex = 7;
			this->weekly_type->Text = L"Week";
			this->weekly_type->UseVisualStyleBackColor = true;
			// 
			// daily_type
			// 
			this->daily_type->Location = System::Drawing::Point(500, 32);
			this->daily_type->Margin = System::Windows::Forms::Padding(4);
			this->daily_type->Name = L"daily_type";
			this->daily_type->Size = System::Drawing::Size(100, 28);
			this->daily_type->TabIndex = 8;
			this->daily_type->Text = L"Day";
			this->daily_type->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(745, 395);
			this->button6->Margin = System::Windows::Forms::Padding(4);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(100, 28);
			this->button6->TabIndex = 9;
			this->button6->Text = L"Statisitics";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// this_month
			// 
			this->this_month->Location = System::Drawing::Point(77, 32);
			this->this_month->Margin = System::Windows::Forms::Padding(4);
			this->this_month->Name = L"this_month";
			this->this_month->Size = System::Drawing::Size(67, 28);
			this->this_month->TabIndex = 11;
			this->this_month->Text = L"Today";
			this->this_month->UseVisualStyleBackColor = true;
			this->this_month->Click += gcnew System::EventHandler(this, &Form1::this_month_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(891, 453);
			this->Controls->Add(this->this_month);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->daily_type);
			this->Controls->Add(this->weekly_type);
			this->Controls->Add(this->monthly_type);
			this->Controls->Add(this->next_month);
			this->Controls->Add(this->last_month);
			this->Controls->Add(this->display_month);
			this->Controls->Add(this->display_year);
			this->Controls->Add(this->monthly_cal);
			this->Margin = System::Windows::Forms::Padding(3, 1, 3, 1);
			this->Name = L"Form1";
			this->Text = L"My Calender";
			this->monthly_cal->ResumeLayout(false);
			this->monthly_cal->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

			 }
private: System::Void display_year_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void display_month_LostFocus(System::Object^  sender, System::EventArgs^  e) {
			 String ^ month = display_month->Text;
			 char *charMonth = (char*)Marshal::StringToHGlobalAnsi(month).ToPointer();
			 int year = thisMonth.GetYear();
			 int intMonth;
			 if(isInteger(charMonth)){
				 intMonth = System::Convert::ToInt32(month);
				 if(intMonth < 1 || intMonth > 12){
					 intMonth = thisMonth.GetMonthNo();
				 }
			 } else {
				 month = display_month->Text->Substring(0, 1)->ToUpper() + display_month->Text->Remove(0, 1);
				 for(int i=1; i<13; i++){
					 intMonth = thisMonth.GetMonthNo();
					 String ^ stdMonth = Enum::GetName(MONTH::typeid, i);
					 int result = String::Compare(stdMonth, month);
					 if(result == 0){
						 intMonth = i;
						 break;
					 }
				 }
			 }
			 setMonths(year, intMonth);
			 setStartDay(startday);
			 drawMonthlyCal();
		 }
private: System::Void wday_0_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 startday = (WEEKDAY) wday_0->SelectedIndex;
			 setStartDay(startday);
			 drawMonthlyCal();
		 }
private: System::Void last_month_Click(System::Object^  sender, System::EventArgs^  e) {
			 setMonths(decMonth(thisMonth.GetYear(), thisMonth.GetMonthNo(), 'y'),
				 decMonth(thisMonth.GetYear(), thisMonth.GetMonthNo(), 'm'));
			 setStartDay(startday);
			 drawMonthlyCal();
		 }
private: System::Void this_month_Click(System::Object^  sender, System::EventArgs^  e) {
			 setMonths(getTime('y'), getTime('m'));
			 setStartDay(startday);
			 drawMonthlyCal();
		 }
private: System::Void next_month_Click(System::Object^  sender, System::EventArgs^  e) {
			 setMonths(incMonth(thisMonth.GetYear(), thisMonth.GetMonthNo(), 'y'),
				 incMonth(thisMonth.GetYear(), thisMonth.GetMonthNo(), 'm'));
			 setStartDay(startday);
			 drawMonthlyCal();
		 }

private: System::Void display_month_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == Keys::Enter){
				 e->Handled = true; 
				 ProcessTabKey(true);
			 }
		 }
};
}

