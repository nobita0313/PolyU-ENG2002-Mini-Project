#include <iostream>
#include <string>
#include "Month.h"
#pragma once



namespace Calender {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
		//tmp
		public enum class WEEKDAY {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};


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
			Month current_month(getTime('Y'), getTime('M'));
			if (getTime('M') == 1){
				Month last_month(getTime('Y')-1, getTime('M')-1);
			} else {
				Month last_month(getTime('Y'), getTime('M')-1);
			}
			display_year->Text = current_month.GetYear().ToString();
			display_month->Text = current_month.GetMonthNo().ToString();
			WEEKDAY startday = WEEKDAY::Sunday;
			setStartDay(startday);
			
		}

	private: 
//tmp
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
	case 'D': return now.Day;
				break;
	case 'M': return now.Month;
				break;
	case 'Y': return now.Year;
				break;		
	default:	return 0;
				break;
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
			for(int i=0; i<7; i++){
				if (fday > WEEKDAY::Saturday){
					fday = WEEKDAY::Sunday;
				}
				String^ wday = Enum::GetName(WEEKDAY::typeid, fday++);
				setDayInfo(monthly_cal, 0, i, "wday", wday);
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
	private: System::Windows::Forms::Label^  wday_0;
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
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Button^  button2;
private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::Button^  button5;
private: System::Windows::Forms::Button^  button6;












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
			this->wday_0 = (gcnew System::Windows::Forms::Label());
			this->wday_1 = (gcnew System::Windows::Forms::Label());
			this->wday_2 = (gcnew System::Windows::Forms::Label());
			this->wday_3 = (gcnew System::Windows::Forms::Label());
			this->wday_4 = (gcnew System::Windows::Forms::Label());
			this->wday_5 = (gcnew System::Windows::Forms::Label());
			this->wday_6 = (gcnew System::Windows::Forms::Label());
			this->display_year = (gcnew System::Windows::Forms::TextBox());
			this->display_month = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
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
			this->monthly_cal->Controls->Add(this->wday_0, 0, 0);
			this->monthly_cal->Controls->Add(this->wday_1, 1, 0);
			this->monthly_cal->Controls->Add(this->wday_2, 2, 0);
			this->monthly_cal->Controls->Add(this->wday_3, 3, 0);
			this->monthly_cal->Controls->Add(this->wday_4, 4, 0);
			this->monthly_cal->Controls->Add(this->wday_5, 5, 0);
			this->monthly_cal->Controls->Add(this->wday_6, 6, 0);
			this->monthly_cal->Location = System::Drawing::Point(34, 57);
			this->monthly_cal->Margin = System::Windows::Forms::Padding(2, 1, 2, 1);
			this->monthly_cal->Name = L"monthly_cal";
			this->monthly_cal->RowCount = 7;
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthly_cal->Size = System::Drawing::Size(600, 260);
			this->monthly_cal->TabIndex = 1;
			this->monthly_cal->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::tableLayoutPanel1_Paint);
			// 
			// day_6_0
			// 
			this->day_6_0->AutoSize = true;
			this->day_6_0->Location = System::Drawing::Point(3, 217);
			this->day_6_0->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_6_0->Name = L"day_6_0";
			this->day_6_0->Size = System::Drawing::Size(35, 13);
			this->day_6_0->TabIndex = 42;
			this->day_6_0->Text = L"label1";
			// 
			// day_6_1
			// 
			this->day_6_1->AutoSize = true;
			this->day_6_1->Location = System::Drawing::Point(88, 217);
			this->day_6_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_6_1->Name = L"day_6_1";
			this->day_6_1->Size = System::Drawing::Size(35, 13);
			this->day_6_1->TabIndex = 43;
			this->day_6_1->Text = L"label2";
			// 
			// day_6_2
			// 
			this->day_6_2->AutoSize = true;
			this->day_6_2->Location = System::Drawing::Point(173, 217);
			this->day_6_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_6_2->Name = L"day_6_2";
			this->day_6_2->Size = System::Drawing::Size(35, 13);
			this->day_6_2->TabIndex = 44;
			this->day_6_2->Text = L"label3";
			// 
			// day_6_3
			// 
			this->day_6_3->AutoSize = true;
			this->day_6_3->Location = System::Drawing::Point(258, 217);
			this->day_6_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_6_3->Name = L"day_6_3";
			this->day_6_3->Size = System::Drawing::Size(35, 13);
			this->day_6_3->TabIndex = 45;
			this->day_6_3->Text = L"label4";
			// 
			// day_6_4
			// 
			this->day_6_4->AutoSize = true;
			this->day_6_4->Location = System::Drawing::Point(343, 217);
			this->day_6_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_6_4->Name = L"day_6_4";
			this->day_6_4->Size = System::Drawing::Size(35, 13);
			this->day_6_4->TabIndex = 46;
			this->day_6_4->Text = L"label5";
			// 
			// day_6_5
			// 
			this->day_6_5->AutoSize = true;
			this->day_6_5->Location = System::Drawing::Point(428, 217);
			this->day_6_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_6_5->Name = L"day_6_5";
			this->day_6_5->Size = System::Drawing::Size(35, 13);
			this->day_6_5->TabIndex = 47;
			this->day_6_5->Text = L"label6";
			// 
			// day_6_6
			// 
			this->day_6_6->AutoSize = true;
			this->day_6_6->Location = System::Drawing::Point(513, 217);
			this->day_6_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_6_6->Name = L"day_6_6";
			this->day_6_6->Size = System::Drawing::Size(35, 13);
			this->day_6_6->TabIndex = 48;
			this->day_6_6->Text = L"label7";
			// 
			// day_5_0
			// 
			this->day_5_0->AutoSize = true;
			this->day_5_0->Location = System::Drawing::Point(3, 181);
			this->day_5_0->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_5_0->Name = L"day_5_0";
			this->day_5_0->Size = System::Drawing::Size(35, 13);
			this->day_5_0->TabIndex = 35;
			this->day_5_0->Text = L"label1";
			// 
			// day_5_1
			// 
			this->day_5_1->AutoSize = true;
			this->day_5_1->Location = System::Drawing::Point(88, 181);
			this->day_5_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_5_1->Name = L"day_5_1";
			this->day_5_1->Size = System::Drawing::Size(35, 13);
			this->day_5_1->TabIndex = 36;
			this->day_5_1->Text = L"label2";
			// 
			// day_5_2
			// 
			this->day_5_2->AutoSize = true;
			this->day_5_2->Location = System::Drawing::Point(173, 181);
			this->day_5_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_5_2->Name = L"day_5_2";
			this->day_5_2->Size = System::Drawing::Size(35, 13);
			this->day_5_2->TabIndex = 37;
			this->day_5_2->Text = L"label3";
			// 
			// day_5_3
			// 
			this->day_5_3->AutoSize = true;
			this->day_5_3->Location = System::Drawing::Point(258, 181);
			this->day_5_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_5_3->Name = L"day_5_3";
			this->day_5_3->Size = System::Drawing::Size(35, 13);
			this->day_5_3->TabIndex = 38;
			this->day_5_3->Text = L"label4";
			// 
			// day_5_4
			// 
			this->day_5_4->AutoSize = true;
			this->day_5_4->Location = System::Drawing::Point(343, 181);
			this->day_5_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_5_4->Name = L"day_5_4";
			this->day_5_4->Size = System::Drawing::Size(35, 13);
			this->day_5_4->TabIndex = 39;
			this->day_5_4->Text = L"label5";
			// 
			// day_5_5
			// 
			this->day_5_5->AutoSize = true;
			this->day_5_5->Location = System::Drawing::Point(428, 181);
			this->day_5_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_5_5->Name = L"day_5_5";
			this->day_5_5->Size = System::Drawing::Size(35, 13);
			this->day_5_5->TabIndex = 40;
			this->day_5_5->Text = L"label6";
			// 
			// day_5_6
			// 
			this->day_5_6->AutoSize = true;
			this->day_5_6->Location = System::Drawing::Point(513, 181);
			this->day_5_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_5_6->Name = L"day_5_6";
			this->day_5_6->Size = System::Drawing::Size(35, 13);
			this->day_5_6->TabIndex = 41;
			this->day_5_6->Text = L"label7";
			// 
			// day_4_0
			// 
			this->day_4_0->AutoSize = true;
			this->day_4_0->Location = System::Drawing::Point(3, 145);
			this->day_4_0->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_4_0->Name = L"day_4_0";
			this->day_4_0->Size = System::Drawing::Size(35, 13);
			this->day_4_0->TabIndex = 28;
			this->day_4_0->Text = L"label1";
			// 
			// day_4_1
			// 
			this->day_4_1->AutoSize = true;
			this->day_4_1->Location = System::Drawing::Point(88, 145);
			this->day_4_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_4_1->Name = L"day_4_1";
			this->day_4_1->Size = System::Drawing::Size(35, 13);
			this->day_4_1->TabIndex = 29;
			this->day_4_1->Text = L"label2";
			// 
			// day_4_2
			// 
			this->day_4_2->AutoSize = true;
			this->day_4_2->Location = System::Drawing::Point(173, 145);
			this->day_4_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_4_2->Name = L"day_4_2";
			this->day_4_2->Size = System::Drawing::Size(35, 13);
			this->day_4_2->TabIndex = 30;
			this->day_4_2->Text = L"label3";
			// 
			// day_4_3
			// 
			this->day_4_3->AutoSize = true;
			this->day_4_3->Location = System::Drawing::Point(258, 145);
			this->day_4_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_4_3->Name = L"day_4_3";
			this->day_4_3->Size = System::Drawing::Size(35, 13);
			this->day_4_3->TabIndex = 31;
			this->day_4_3->Text = L"label4";
			// 
			// day_4_4
			// 
			this->day_4_4->AutoSize = true;
			this->day_4_4->Location = System::Drawing::Point(343, 145);
			this->day_4_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_4_4->Name = L"day_4_4";
			this->day_4_4->Size = System::Drawing::Size(35, 13);
			this->day_4_4->TabIndex = 32;
			this->day_4_4->Text = L"label5";
			// 
			// day_4_5
			// 
			this->day_4_5->AutoSize = true;
			this->day_4_5->Location = System::Drawing::Point(428, 145);
			this->day_4_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_4_5->Name = L"day_4_5";
			this->day_4_5->Size = System::Drawing::Size(35, 13);
			this->day_4_5->TabIndex = 33;
			this->day_4_5->Text = L"label6";
			// 
			// day_4_6
			// 
			this->day_4_6->AutoSize = true;
			this->day_4_6->Location = System::Drawing::Point(513, 145);
			this->day_4_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_4_6->Name = L"day_4_6";
			this->day_4_6->Size = System::Drawing::Size(35, 13);
			this->day_4_6->TabIndex = 34;
			this->day_4_6->Text = L"label7";
			// 
			// day_3_0
			// 
			this->day_3_0->AutoSize = true;
			this->day_3_0->Location = System::Drawing::Point(3, 109);
			this->day_3_0->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_3_0->Name = L"day_3_0";
			this->day_3_0->Size = System::Drawing::Size(35, 13);
			this->day_3_0->TabIndex = 21;
			this->day_3_0->Text = L"label1";
			// 
			// day_3_1
			// 
			this->day_3_1->AutoSize = true;
			this->day_3_1->Location = System::Drawing::Point(88, 109);
			this->day_3_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_3_1->Name = L"day_3_1";
			this->day_3_1->Size = System::Drawing::Size(35, 13);
			this->day_3_1->TabIndex = 22;
			this->day_3_1->Text = L"label2";
			// 
			// day_3_2
			// 
			this->day_3_2->AutoSize = true;
			this->day_3_2->Location = System::Drawing::Point(173, 109);
			this->day_3_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_3_2->Name = L"day_3_2";
			this->day_3_2->Size = System::Drawing::Size(35, 13);
			this->day_3_2->TabIndex = 23;
			this->day_3_2->Text = L"label3";
			// 
			// day_3_3
			// 
			this->day_3_3->AutoSize = true;
			this->day_3_3->Location = System::Drawing::Point(258, 109);
			this->day_3_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_3_3->Name = L"day_3_3";
			this->day_3_3->Size = System::Drawing::Size(35, 13);
			this->day_3_3->TabIndex = 24;
			this->day_3_3->Text = L"label4";
			// 
			// day_3_4
			// 
			this->day_3_4->AutoSize = true;
			this->day_3_4->Location = System::Drawing::Point(343, 109);
			this->day_3_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_3_4->Name = L"day_3_4";
			this->day_3_4->Size = System::Drawing::Size(35, 13);
			this->day_3_4->TabIndex = 25;
			this->day_3_4->Text = L"label5";
			// 
			// day_3_5
			// 
			this->day_3_5->AutoSize = true;
			this->day_3_5->Location = System::Drawing::Point(428, 109);
			this->day_3_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_3_5->Name = L"day_3_5";
			this->day_3_5->Size = System::Drawing::Size(35, 13);
			this->day_3_5->TabIndex = 26;
			this->day_3_5->Text = L"label6";
			// 
			// day_3_6
			// 
			this->day_3_6->AutoSize = true;
			this->day_3_6->Location = System::Drawing::Point(513, 109);
			this->day_3_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_3_6->Name = L"day_3_6";
			this->day_3_6->Size = System::Drawing::Size(35, 13);
			this->day_3_6->TabIndex = 27;
			this->day_3_6->Text = L"label7";
			// 
			// day_2_0
			// 
			this->day_2_0->AutoSize = true;
			this->day_2_0->Location = System::Drawing::Point(3, 73);
			this->day_2_0->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_2_0->Name = L"day_2_0";
			this->day_2_0->Size = System::Drawing::Size(35, 13);
			this->day_2_0->TabIndex = 14;
			this->day_2_0->Text = L"label1";
			// 
			// day_2_1
			// 
			this->day_2_1->AutoSize = true;
			this->day_2_1->Location = System::Drawing::Point(88, 73);
			this->day_2_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_2_1->Name = L"day_2_1";
			this->day_2_1->Size = System::Drawing::Size(35, 13);
			this->day_2_1->TabIndex = 15;
			this->day_2_1->Text = L"label2";
			// 
			// day_2_2
			// 
			this->day_2_2->AutoSize = true;
			this->day_2_2->Location = System::Drawing::Point(173, 73);
			this->day_2_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_2_2->Name = L"day_2_2";
			this->day_2_2->Size = System::Drawing::Size(35, 13);
			this->day_2_2->TabIndex = 16;
			this->day_2_2->Text = L"label3";
			// 
			// day_2_3
			// 
			this->day_2_3->AutoSize = true;
			this->day_2_3->Location = System::Drawing::Point(258, 73);
			this->day_2_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_2_3->Name = L"day_2_3";
			this->day_2_3->Size = System::Drawing::Size(35, 13);
			this->day_2_3->TabIndex = 17;
			this->day_2_3->Text = L"label4";
			// 
			// day_2_4
			// 
			this->day_2_4->AutoSize = true;
			this->day_2_4->Location = System::Drawing::Point(343, 73);
			this->day_2_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_2_4->Name = L"day_2_4";
			this->day_2_4->Size = System::Drawing::Size(35, 13);
			this->day_2_4->TabIndex = 18;
			this->day_2_4->Text = L"label5";
			// 
			// day_2_5
			// 
			this->day_2_5->AutoSize = true;
			this->day_2_5->Location = System::Drawing::Point(428, 73);
			this->day_2_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_2_5->Name = L"day_2_5";
			this->day_2_5->Size = System::Drawing::Size(35, 13);
			this->day_2_5->TabIndex = 19;
			this->day_2_5->Text = L"label6";
			// 
			// day_2_6
			// 
			this->day_2_6->AutoSize = true;
			this->day_2_6->Location = System::Drawing::Point(513, 73);
			this->day_2_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_2_6->Name = L"day_2_6";
			this->day_2_6->Size = System::Drawing::Size(35, 13);
			this->day_2_6->TabIndex = 20;
			this->day_2_6->Text = L"label7";
			// 
			// day_1_0
			// 
			this->day_1_0->AutoSize = true;
			this->day_1_0->Location = System::Drawing::Point(3, 37);
			this->day_1_0->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_1_0->Name = L"day_1_0";
			this->day_1_0->Size = System::Drawing::Size(35, 13);
			this->day_1_0->TabIndex = 7;
			this->day_1_0->Text = L"label1";
			// 
			// day_1_1
			// 
			this->day_1_1->AutoSize = true;
			this->day_1_1->Location = System::Drawing::Point(88, 37);
			this->day_1_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_1_1->Name = L"day_1_1";
			this->day_1_1->Size = System::Drawing::Size(35, 13);
			this->day_1_1->TabIndex = 8;
			this->day_1_1->Text = L"label2";
			// 
			// day_1_2
			// 
			this->day_1_2->AutoSize = true;
			this->day_1_2->Location = System::Drawing::Point(173, 37);
			this->day_1_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_1_2->Name = L"day_1_2";
			this->day_1_2->Size = System::Drawing::Size(35, 13);
			this->day_1_2->TabIndex = 9;
			this->day_1_2->Text = L"label3";
			// 
			// day_1_3
			// 
			this->day_1_3->AutoSize = true;
			this->day_1_3->Location = System::Drawing::Point(258, 37);
			this->day_1_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_1_3->Name = L"day_1_3";
			this->day_1_3->Size = System::Drawing::Size(35, 13);
			this->day_1_3->TabIndex = 10;
			this->day_1_3->Text = L"label4";
			// 
			// day_1_4
			// 
			this->day_1_4->AutoSize = true;
			this->day_1_4->Location = System::Drawing::Point(343, 37);
			this->day_1_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_1_4->Name = L"day_1_4";
			this->day_1_4->Size = System::Drawing::Size(35, 13);
			this->day_1_4->TabIndex = 11;
			this->day_1_4->Text = L"label5";
			// 
			// day_1_5
			// 
			this->day_1_5->AutoSize = true;
			this->day_1_5->Location = System::Drawing::Point(428, 37);
			this->day_1_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_1_5->Name = L"day_1_5";
			this->day_1_5->Size = System::Drawing::Size(35, 13);
			this->day_1_5->TabIndex = 12;
			this->day_1_5->Text = L"label6";
			// 
			// day_1_6
			// 
			this->day_1_6->AutoSize = true;
			this->day_1_6->Location = System::Drawing::Point(513, 37);
			this->day_1_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->day_1_6->Name = L"day_1_6";
			this->day_1_6->Size = System::Drawing::Size(35, 13);
			this->day_1_6->TabIndex = 13;
			this->day_1_6->Text = L"label7";
			// 
			// wday_0
			// 
			this->wday_0->AutoSize = true;
			this->wday_0->Location = System::Drawing::Point(3, 1);
			this->wday_0->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->wday_0->Name = L"wday_0";
			this->wday_0->Size = System::Drawing::Size(35, 13);
			this->wday_0->TabIndex = 0;
			this->wday_0->Text = L"label1";
			// 
			// wday_1
			// 
			this->wday_1->AutoSize = true;
			this->wday_1->Location = System::Drawing::Point(88, 1);
			this->wday_1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->wday_1->Name = L"wday_1";
			this->wday_1->Size = System::Drawing::Size(35, 13);
			this->wday_1->TabIndex = 1;
			this->wday_1->Text = L"label2";
			// 
			// wday_2
			// 
			this->wday_2->AutoSize = true;
			this->wday_2->Location = System::Drawing::Point(173, 1);
			this->wday_2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->wday_2->Name = L"wday_2";
			this->wday_2->Size = System::Drawing::Size(35, 13);
			this->wday_2->TabIndex = 2;
			this->wday_2->Text = L"label3";
			// 
			// wday_3
			// 
			this->wday_3->AutoSize = true;
			this->wday_3->Location = System::Drawing::Point(258, 1);
			this->wday_3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->wday_3->Name = L"wday_3";
			this->wday_3->Size = System::Drawing::Size(35, 13);
			this->wday_3->TabIndex = 3;
			this->wday_3->Text = L"label4";
			// 
			// wday_4
			// 
			this->wday_4->AutoSize = true;
			this->wday_4->Location = System::Drawing::Point(343, 1);
			this->wday_4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->wday_4->Name = L"wday_4";
			this->wday_4->Size = System::Drawing::Size(35, 13);
			this->wday_4->TabIndex = 4;
			this->wday_4->Text = L"label5";
			// 
			// wday_5
			// 
			this->wday_5->AutoSize = true;
			this->wday_5->Location = System::Drawing::Point(428, 1);
			this->wday_5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->wday_5->Name = L"wday_5";
			this->wday_5->Size = System::Drawing::Size(35, 13);
			this->wday_5->TabIndex = 5;
			this->wday_5->Text = L"label6";
			// 
			// wday_6
			// 
			this->wday_6->AutoSize = true;
			this->wday_6->Location = System::Drawing::Point(513, 1);
			this->wday_6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->wday_6->Name = L"wday_6";
			this->wday_6->Size = System::Drawing::Size(35, 13);
			this->wday_6->TabIndex = 6;
			this->wday_6->Text = L"label7";
			// 
			// display_year
			// 
			this->display_year->Location = System::Drawing::Point(497, 28);
			this->display_year->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->display_year->Name = L"display_year";
			this->display_year->Size = System::Drawing::Size(50, 20);
			this->display_year->TabIndex = 2;
			this->display_year->TextChanged += gcnew System::EventHandler(this, &Form1::display_year_TextChanged);
			// 
			// display_month
			// 
			this->display_month->Location = System::Drawing::Point(553, 28);
			this->display_month->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
			this->display_month->Name = L"display_month";
			this->display_month->Size = System::Drawing::Size(50, 20);
			this->display_month->TabIndex = 3;
			this->display_month->TextChanged += gcnew System::EventHandler(this, &Form1::display_month_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(466, 26);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(25, 23);
			this->button1->TabIndex = 4;
			this->button1->Text = L"<";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(609, 26);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(25, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L">";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(219, 26);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Month";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(297, 26);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Week";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(375, 26);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 8;
			this->button5->Text = L"Day";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(34, 26);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 9;
			this->button6->Text = L"Statisitics";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(668, 368);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->display_month);
			this->Controls->Add(this->display_year);
			this->Controls->Add(this->monthly_cal);
			this->Margin = System::Windows::Forms::Padding(2, 1, 2, 1);
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
private: System::Void display_month_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

