#include <iostream>
#include <string>
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
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			setStartDay();
		}
	private: 
		void setStartDay(){
//			string wday[] = {wday_1, wday_2, wday_3, wday_4, wday_5, wday_6, wday_7};
//			System::Windows::Forms::Label()* weekday[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//			switch (day){
//			case 'def': 
//			}
//			while(weekday<=7){
//				for (int j=1; j<=7; j++){
					wday_1->Text = L"weekday";
//					weekday = weekday+1;
//				}
//			}
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
	private: System::Windows::Forms::MonthCalendar^  monthCalendar1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  wday_1;
	private: System::Windows::Forms::Label^  wday_2;
	private: System::Windows::Forms::Label^  wday_3;
	private: System::Windows::Forms::Label^  wday_4;
	private: System::Windows::Forms::Label^  wday_5;
	private: System::Windows::Forms::Label^  wday_6;
	private: System::Windows::Forms::Label^  wday_7;
	private: System::Windows::Forms::Label^  day_6_1;
	private: System::Windows::Forms::Label^  day_6_2;
	private: System::Windows::Forms::Label^  day_6_3;
	private: System::Windows::Forms::Label^  day_6_4;
	private: System::Windows::Forms::Label^  day_6_5;
	private: System::Windows::Forms::Label^  day_6_6;
	private: System::Windows::Forms::Label^  day_6_7;
	private: System::Windows::Forms::Label^  day_5_1;
	private: System::Windows::Forms::Label^  day_5_2;
	private: System::Windows::Forms::Label^  day_5_3;
	private: System::Windows::Forms::Label^  day_5_4;
	private: System::Windows::Forms::Label^  day_5_5;
	private: System::Windows::Forms::Label^  day_5_6;
	private: System::Windows::Forms::Label^  day_5_7;
	private: System::Windows::Forms::Label^  day_4_1;
	private: System::Windows::Forms::Label^  day_4_2;
	private: System::Windows::Forms::Label^  day_4_3;
	private: System::Windows::Forms::Label^  day_4_4;
	private: System::Windows::Forms::Label^  day_4_5;
	private: System::Windows::Forms::Label^  day_4_6;
	private: System::Windows::Forms::Label^  day_4_7;
	private: System::Windows::Forms::Label^  day_3_1;
	private: System::Windows::Forms::Label^  day_3_2;
	private: System::Windows::Forms::Label^  day_3_3;
	private: System::Windows::Forms::Label^  day_3_4;
	private: System::Windows::Forms::Label^  day_3_5;
	private: System::Windows::Forms::Label^  day_3_6;
	private: System::Windows::Forms::Label^  day_3_7;
	private: System::Windows::Forms::Label^  day_2_1;
	private: System::Windows::Forms::Label^  day_2_2;
	private: System::Windows::Forms::Label^  day_2_3;
	private: System::Windows::Forms::Label^  day_2_4;
	private: System::Windows::Forms::Label^  day_2_5;
	private: System::Windows::Forms::Label^  day_2_6;
	private: System::Windows::Forms::Label^  day_2_7;
	private: System::Windows::Forms::Label^  day_1_1;
	private: System::Windows::Forms::Label^  day_1_2;
	private: System::Windows::Forms::Label^  day_1_3;
	private: System::Windows::Forms::Label^  day_1_4;
	private: System::Windows::Forms::Label^  day_1_5;
	private: System::Windows::Forms::Label^  day_1_6;
	private: System::Windows::Forms::Label^  day_1_7;

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
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->day_6_1 = (gcnew System::Windows::Forms::Label());
			this->day_6_2 = (gcnew System::Windows::Forms::Label());
			this->day_6_3 = (gcnew System::Windows::Forms::Label());
			this->day_6_4 = (gcnew System::Windows::Forms::Label());
			this->day_6_5 = (gcnew System::Windows::Forms::Label());
			this->day_6_6 = (gcnew System::Windows::Forms::Label());
			this->day_6_7 = (gcnew System::Windows::Forms::Label());
			this->day_5_1 = (gcnew System::Windows::Forms::Label());
			this->day_5_2 = (gcnew System::Windows::Forms::Label());
			this->day_5_3 = (gcnew System::Windows::Forms::Label());
			this->day_5_4 = (gcnew System::Windows::Forms::Label());
			this->day_5_5 = (gcnew System::Windows::Forms::Label());
			this->day_5_6 = (gcnew System::Windows::Forms::Label());
			this->day_5_7 = (gcnew System::Windows::Forms::Label());
			this->day_4_1 = (gcnew System::Windows::Forms::Label());
			this->day_4_2 = (gcnew System::Windows::Forms::Label());
			this->day_4_3 = (gcnew System::Windows::Forms::Label());
			this->day_4_4 = (gcnew System::Windows::Forms::Label());
			this->day_4_5 = (gcnew System::Windows::Forms::Label());
			this->day_4_6 = (gcnew System::Windows::Forms::Label());
			this->day_4_7 = (gcnew System::Windows::Forms::Label());
			this->day_3_1 = (gcnew System::Windows::Forms::Label());
			this->day_3_2 = (gcnew System::Windows::Forms::Label());
			this->day_3_3 = (gcnew System::Windows::Forms::Label());
			this->day_3_4 = (gcnew System::Windows::Forms::Label());
			this->day_3_5 = (gcnew System::Windows::Forms::Label());
			this->day_3_6 = (gcnew System::Windows::Forms::Label());
			this->day_3_7 = (gcnew System::Windows::Forms::Label());
			this->day_2_1 = (gcnew System::Windows::Forms::Label());
			this->day_2_2 = (gcnew System::Windows::Forms::Label());
			this->day_2_3 = (gcnew System::Windows::Forms::Label());
			this->day_2_4 = (gcnew System::Windows::Forms::Label());
			this->day_2_5 = (gcnew System::Windows::Forms::Label());
			this->day_2_6 = (gcnew System::Windows::Forms::Label());
			this->day_2_7 = (gcnew System::Windows::Forms::Label());
			this->day_1_1 = (gcnew System::Windows::Forms::Label());
			this->day_1_2 = (gcnew System::Windows::Forms::Label());
			this->day_1_3 = (gcnew System::Windows::Forms::Label());
			this->day_1_4 = (gcnew System::Windows::Forms::Label());
			this->day_1_5 = (gcnew System::Windows::Forms::Label());
			this->day_1_6 = (gcnew System::Windows::Forms::Label());
			this->day_1_7 = (gcnew System::Windows::Forms::Label());
			this->wday_1 = (gcnew System::Windows::Forms::Label());
			this->wday_2 = (gcnew System::Windows::Forms::Label());
			this->wday_3 = (gcnew System::Windows::Forms::Label());
			this->wday_4 = (gcnew System::Windows::Forms::Label());
			this->wday_5 = (gcnew System::Windows::Forms::Label());
			this->wday_6 = (gcnew System::Windows::Forms::Label());
			this->wday_7 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->Location = System::Drawing::Point(387, 372);
			this->monthCalendar1->Margin = System::Windows::Forms::Padding(8, 7, 8, 7);
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->TabIndex = 0;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel1->ColumnCount = 7;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				14.28571F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				14.28571F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				14.28571F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				14.28571F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				14.28571F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				14.28571F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				14.28571F)));
			this->tableLayoutPanel1->Controls->Add(this->day_6_1, 0, 6);
			this->tableLayoutPanel1->Controls->Add(this->day_6_2, 1, 6);
			this->tableLayoutPanel1->Controls->Add(this->day_6_3, 2, 6);
			this->tableLayoutPanel1->Controls->Add(this->day_6_4, 3, 6);
			this->tableLayoutPanel1->Controls->Add(this->day_6_5, 4, 6);
			this->tableLayoutPanel1->Controls->Add(this->day_6_6, 5, 6);
			this->tableLayoutPanel1->Controls->Add(this->day_6_7, 6, 6);
			this->tableLayoutPanel1->Controls->Add(this->day_5_1, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->day_5_2, 1, 5);
			this->tableLayoutPanel1->Controls->Add(this->day_5_3, 2, 5);
			this->tableLayoutPanel1->Controls->Add(this->day_5_4, 3, 5);
			this->tableLayoutPanel1->Controls->Add(this->day_5_5, 4, 5);
			this->tableLayoutPanel1->Controls->Add(this->day_5_6, 5, 5);
			this->tableLayoutPanel1->Controls->Add(this->day_5_7, 6, 5);
			this->tableLayoutPanel1->Controls->Add(this->day_4_1, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->day_4_2, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->day_4_3, 2, 4);
			this->tableLayoutPanel1->Controls->Add(this->day_4_4, 3, 4);
			this->tableLayoutPanel1->Controls->Add(this->day_4_5, 4, 4);
			this->tableLayoutPanel1->Controls->Add(this->day_4_6, 5, 4);
			this->tableLayoutPanel1->Controls->Add(this->day_4_7, 6, 4);
			this->tableLayoutPanel1->Controls->Add(this->day_3_1, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->day_3_2, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->day_3_3, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->day_3_4, 3, 3);
			this->tableLayoutPanel1->Controls->Add(this->day_3_5, 4, 3);
			this->tableLayoutPanel1->Controls->Add(this->day_3_6, 5, 3);
			this->tableLayoutPanel1->Controls->Add(this->day_3_7, 6, 3);
			this->tableLayoutPanel1->Controls->Add(this->day_2_1, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->day_2_2, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->day_2_3, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->day_2_4, 3, 2);
			this->tableLayoutPanel1->Controls->Add(this->day_2_5, 4, 2);
			this->tableLayoutPanel1->Controls->Add(this->day_2_6, 5, 2);
			this->tableLayoutPanel1->Controls->Add(this->day_2_7, 6, 2);
			this->tableLayoutPanel1->Controls->Add(this->day_1_1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->day_1_2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->day_1_3, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->day_1_4, 3, 1);
			this->tableLayoutPanel1->Controls->Add(this->day_1_5, 4, 1);
			this->tableLayoutPanel1->Controls->Add(this->day_1_6, 5, 1);
			this->tableLayoutPanel1->Controls->Add(this->day_1_7, 6, 1);
			this->tableLayoutPanel1->Controls->Add(this->wday_1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->wday_2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->wday_3, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->wday_4, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->wday_5, 4, 0);
			this->tableLayoutPanel1->Controls->Add(this->wday_6, 5, 0);
			this->tableLayoutPanel1->Controls->Add(this->wday_7, 6, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(45, 79);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 7;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(800, 320);
			this->tableLayoutPanel1->TabIndex = 1;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::tableLayoutPanel1_Paint);
			// 
			// day_6_1
			// 
			this->day_6_1->AutoSize = true;
			this->day_6_1->Location = System::Drawing::Point(4, 271);
			this->day_6_1->Name = L"day_6_1";
			this->day_6_1->Size = System::Drawing::Size(46, 17);
			this->day_6_1->TabIndex = 42;
			this->day_6_1->Text = L"label1";
			// 
			// day_6_2
			// 
			this->day_6_2->AutoSize = true;
			this->day_6_2->Location = System::Drawing::Point(118, 271);
			this->day_6_2->Name = L"day_6_2";
			this->day_6_2->Size = System::Drawing::Size(46, 17);
			this->day_6_2->TabIndex = 43;
			this->day_6_2->Text = L"label2";
			// 
			// day_6_3
			// 
			this->day_6_3->AutoSize = true;
			this->day_6_3->Location = System::Drawing::Point(232, 271);
			this->day_6_3->Name = L"day_6_3";
			this->day_6_3->Size = System::Drawing::Size(46, 17);
			this->day_6_3->TabIndex = 44;
			this->day_6_3->Text = L"label3";
			// 
			// day_6_4
			// 
			this->day_6_4->AutoSize = true;
			this->day_6_4->Location = System::Drawing::Point(346, 271);
			this->day_6_4->Name = L"day_6_4";
			this->day_6_4->Size = System::Drawing::Size(46, 17);
			this->day_6_4->TabIndex = 45;
			this->day_6_4->Text = L"label4";
			// 
			// day_6_5
			// 
			this->day_6_5->AutoSize = true;
			this->day_6_5->Location = System::Drawing::Point(460, 271);
			this->day_6_5->Name = L"day_6_5";
			this->day_6_5->Size = System::Drawing::Size(46, 17);
			this->day_6_5->TabIndex = 46;
			this->day_6_5->Text = L"label5";
			// 
			// day_6_6
			// 
			this->day_6_6->AutoSize = true;
			this->day_6_6->Location = System::Drawing::Point(574, 271);
			this->day_6_6->Name = L"day_6_6";
			this->day_6_6->Size = System::Drawing::Size(46, 17);
			this->day_6_6->TabIndex = 47;
			this->day_6_6->Text = L"label6";
			// 
			// day_6_7
			// 
			this->day_6_7->AutoSize = true;
			this->day_6_7->Location = System::Drawing::Point(688, 271);
			this->day_6_7->Name = L"day_6_7";
			this->day_6_7->Size = System::Drawing::Size(46, 17);
			this->day_6_7->TabIndex = 48;
			this->day_6_7->Text = L"label7";
			// 
			// day_5_1
			// 
			this->day_5_1->AutoSize = true;
			this->day_5_1->Location = System::Drawing::Point(4, 226);
			this->day_5_1->Name = L"day_5_1";
			this->day_5_1->Size = System::Drawing::Size(46, 17);
			this->day_5_1->TabIndex = 35;
			this->day_5_1->Text = L"label1";
			// 
			// day_5_2
			// 
			this->day_5_2->AutoSize = true;
			this->day_5_2->Location = System::Drawing::Point(118, 226);
			this->day_5_2->Name = L"day_5_2";
			this->day_5_2->Size = System::Drawing::Size(46, 17);
			this->day_5_2->TabIndex = 36;
			this->day_5_2->Text = L"label2";
			// 
			// day_5_3
			// 
			this->day_5_3->AutoSize = true;
			this->day_5_3->Location = System::Drawing::Point(232, 226);
			this->day_5_3->Name = L"day_5_3";
			this->day_5_3->Size = System::Drawing::Size(46, 17);
			this->day_5_3->TabIndex = 37;
			this->day_5_3->Text = L"label3";
			// 
			// day_5_4
			// 
			this->day_5_4->AutoSize = true;
			this->day_5_4->Location = System::Drawing::Point(346, 226);
			this->day_5_4->Name = L"day_5_4";
			this->day_5_4->Size = System::Drawing::Size(46, 17);
			this->day_5_4->TabIndex = 38;
			this->day_5_4->Text = L"label4";
			// 
			// day_5_5
			// 
			this->day_5_5->AutoSize = true;
			this->day_5_5->Location = System::Drawing::Point(460, 226);
			this->day_5_5->Name = L"day_5_5";
			this->day_5_5->Size = System::Drawing::Size(46, 17);
			this->day_5_5->TabIndex = 39;
			this->day_5_5->Text = L"label5";
			// 
			// day_5_6
			// 
			this->day_5_6->AutoSize = true;
			this->day_5_6->Location = System::Drawing::Point(574, 226);
			this->day_5_6->Name = L"day_5_6";
			this->day_5_6->Size = System::Drawing::Size(46, 17);
			this->day_5_6->TabIndex = 40;
			this->day_5_6->Text = L"label6";
			// 
			// day_5_7
			// 
			this->day_5_7->AutoSize = true;
			this->day_5_7->Location = System::Drawing::Point(688, 226);
			this->day_5_7->Name = L"day_5_7";
			this->day_5_7->Size = System::Drawing::Size(46, 17);
			this->day_5_7->TabIndex = 41;
			this->day_5_7->Text = L"label7";
			// 
			// day_4_1
			// 
			this->day_4_1->AutoSize = true;
			this->day_4_1->Location = System::Drawing::Point(4, 181);
			this->day_4_1->Name = L"day_4_1";
			this->day_4_1->Size = System::Drawing::Size(46, 17);
			this->day_4_1->TabIndex = 28;
			this->day_4_1->Text = L"label1";
			// 
			// day_4_2
			// 
			this->day_4_2->AutoSize = true;
			this->day_4_2->Location = System::Drawing::Point(118, 181);
			this->day_4_2->Name = L"day_4_2";
			this->day_4_2->Size = System::Drawing::Size(46, 17);
			this->day_4_2->TabIndex = 29;
			this->day_4_2->Text = L"label2";
			// 
			// day_4_3
			// 
			this->day_4_3->AutoSize = true;
			this->day_4_3->Location = System::Drawing::Point(232, 181);
			this->day_4_3->Name = L"day_4_3";
			this->day_4_3->Size = System::Drawing::Size(46, 17);
			this->day_4_3->TabIndex = 30;
			this->day_4_3->Text = L"label3";
			// 
			// day_4_4
			// 
			this->day_4_4->AutoSize = true;
			this->day_4_4->Location = System::Drawing::Point(346, 181);
			this->day_4_4->Name = L"day_4_4";
			this->day_4_4->Size = System::Drawing::Size(46, 17);
			this->day_4_4->TabIndex = 31;
			this->day_4_4->Text = L"label4";
			// 
			// day_4_5
			// 
			this->day_4_5->AutoSize = true;
			this->day_4_5->Location = System::Drawing::Point(460, 181);
			this->day_4_5->Name = L"day_4_5";
			this->day_4_5->Size = System::Drawing::Size(46, 17);
			this->day_4_5->TabIndex = 32;
			this->day_4_5->Text = L"label5";
			// 
			// day_4_6
			// 
			this->day_4_6->AutoSize = true;
			this->day_4_6->Location = System::Drawing::Point(574, 181);
			this->day_4_6->Name = L"day_4_6";
			this->day_4_6->Size = System::Drawing::Size(46, 17);
			this->day_4_6->TabIndex = 33;
			this->day_4_6->Text = L"label6";
			// 
			// day_4_7
			// 
			this->day_4_7->AutoSize = true;
			this->day_4_7->Location = System::Drawing::Point(688, 181);
			this->day_4_7->Name = L"day_4_7";
			this->day_4_7->Size = System::Drawing::Size(46, 17);
			this->day_4_7->TabIndex = 34;
			this->day_4_7->Text = L"label7";
			// 
			// day_3_1
			// 
			this->day_3_1->AutoSize = true;
			this->day_3_1->Location = System::Drawing::Point(4, 136);
			this->day_3_1->Name = L"day_3_1";
			this->day_3_1->Size = System::Drawing::Size(46, 17);
			this->day_3_1->TabIndex = 21;
			this->day_3_1->Text = L"label1";
			// 
			// day_3_2
			// 
			this->day_3_2->AutoSize = true;
			this->day_3_2->Location = System::Drawing::Point(118, 136);
			this->day_3_2->Name = L"day_3_2";
			this->day_3_2->Size = System::Drawing::Size(46, 17);
			this->day_3_2->TabIndex = 22;
			this->day_3_2->Text = L"label2";
			// 
			// day_3_3
			// 
			this->day_3_3->AutoSize = true;
			this->day_3_3->Location = System::Drawing::Point(232, 136);
			this->day_3_3->Name = L"day_3_3";
			this->day_3_3->Size = System::Drawing::Size(46, 17);
			this->day_3_3->TabIndex = 23;
			this->day_3_3->Text = L"label3";
			// 
			// day_3_4
			// 
			this->day_3_4->AutoSize = true;
			this->day_3_4->Location = System::Drawing::Point(346, 136);
			this->day_3_4->Name = L"day_3_4";
			this->day_3_4->Size = System::Drawing::Size(46, 17);
			this->day_3_4->TabIndex = 24;
			this->day_3_4->Text = L"label4";
			// 
			// day_3_5
			// 
			this->day_3_5->AutoSize = true;
			this->day_3_5->Location = System::Drawing::Point(460, 136);
			this->day_3_5->Name = L"day_3_5";
			this->day_3_5->Size = System::Drawing::Size(46, 17);
			this->day_3_5->TabIndex = 25;
			this->day_3_5->Text = L"label5";
			// 
			// day_3_6
			// 
			this->day_3_6->AutoSize = true;
			this->day_3_6->Location = System::Drawing::Point(574, 136);
			this->day_3_6->Name = L"day_3_6";
			this->day_3_6->Size = System::Drawing::Size(46, 17);
			this->day_3_6->TabIndex = 26;
			this->day_3_6->Text = L"label6";
			// 
			// day_3_7
			// 
			this->day_3_7->AutoSize = true;
			this->day_3_7->Location = System::Drawing::Point(688, 136);
			this->day_3_7->Name = L"day_3_7";
			this->day_3_7->Size = System::Drawing::Size(46, 17);
			this->day_3_7->TabIndex = 27;
			this->day_3_7->Text = L"label7";
			// 
			// day_2_1
			// 
			this->day_2_1->AutoSize = true;
			this->day_2_1->Location = System::Drawing::Point(4, 91);
			this->day_2_1->Name = L"day_2_1";
			this->day_2_1->Size = System::Drawing::Size(46, 17);
			this->day_2_1->TabIndex = 14;
			this->day_2_1->Text = L"label1";
			// 
			// day_2_2
			// 
			this->day_2_2->AutoSize = true;
			this->day_2_2->Location = System::Drawing::Point(118, 91);
			this->day_2_2->Name = L"day_2_2";
			this->day_2_2->Size = System::Drawing::Size(46, 17);
			this->day_2_2->TabIndex = 15;
			this->day_2_2->Text = L"label2";
			// 
			// day_2_3
			// 
			this->day_2_3->AutoSize = true;
			this->day_2_3->Location = System::Drawing::Point(232, 91);
			this->day_2_3->Name = L"day_2_3";
			this->day_2_3->Size = System::Drawing::Size(46, 17);
			this->day_2_3->TabIndex = 16;
			this->day_2_3->Text = L"label3";
			// 
			// day_2_4
			// 
			this->day_2_4->AutoSize = true;
			this->day_2_4->Location = System::Drawing::Point(346, 91);
			this->day_2_4->Name = L"day_2_4";
			this->day_2_4->Size = System::Drawing::Size(46, 17);
			this->day_2_4->TabIndex = 17;
			this->day_2_4->Text = L"label4";
			// 
			// day_2_5
			// 
			this->day_2_5->AutoSize = true;
			this->day_2_5->Location = System::Drawing::Point(460, 91);
			this->day_2_5->Name = L"day_2_5";
			this->day_2_5->Size = System::Drawing::Size(46, 17);
			this->day_2_5->TabIndex = 18;
			this->day_2_5->Text = L"label5";
			// 
			// day_2_6
			// 
			this->day_2_6->AutoSize = true;
			this->day_2_6->Location = System::Drawing::Point(574, 91);
			this->day_2_6->Name = L"day_2_6";
			this->day_2_6->Size = System::Drawing::Size(46, 17);
			this->day_2_6->TabIndex = 19;
			this->day_2_6->Text = L"label6";
			// 
			// day_2_7
			// 
			this->day_2_7->AutoSize = true;
			this->day_2_7->Location = System::Drawing::Point(688, 91);
			this->day_2_7->Name = L"day_2_7";
			this->day_2_7->Size = System::Drawing::Size(46, 17);
			this->day_2_7->TabIndex = 20;
			this->day_2_7->Text = L"label7";
			// 
			// day_1_1
			// 
			this->day_1_1->AutoSize = true;
			this->day_1_1->Location = System::Drawing::Point(4, 46);
			this->day_1_1->Name = L"day_1_1";
			this->day_1_1->Size = System::Drawing::Size(46, 17);
			this->day_1_1->TabIndex = 7;
			this->day_1_1->Text = L"label1";
			// 
			// day_1_2
			// 
			this->day_1_2->AutoSize = true;
			this->day_1_2->Location = System::Drawing::Point(118, 46);
			this->day_1_2->Name = L"day_1_2";
			this->day_1_2->Size = System::Drawing::Size(46, 17);
			this->day_1_2->TabIndex = 8;
			this->day_1_2->Text = L"label2";
			// 
			// day_1_3
			// 
			this->day_1_3->AutoSize = true;
			this->day_1_3->Location = System::Drawing::Point(232, 46);
			this->day_1_3->Name = L"day_1_3";
			this->day_1_3->Size = System::Drawing::Size(46, 17);
			this->day_1_3->TabIndex = 9;
			this->day_1_3->Text = L"label3";
			// 
			// day_1_4
			// 
			this->day_1_4->AutoSize = true;
			this->day_1_4->Location = System::Drawing::Point(346, 46);
			this->day_1_4->Name = L"day_1_4";
			this->day_1_4->Size = System::Drawing::Size(46, 17);
			this->day_1_4->TabIndex = 10;
			this->day_1_4->Text = L"label4";
			// 
			// day_1_5
			// 
			this->day_1_5->AutoSize = true;
			this->day_1_5->Location = System::Drawing::Point(460, 46);
			this->day_1_5->Name = L"day_1_5";
			this->day_1_5->Size = System::Drawing::Size(46, 17);
			this->day_1_5->TabIndex = 11;
			this->day_1_5->Text = L"label5";
			// 
			// day_1_6
			// 
			this->day_1_6->AutoSize = true;
			this->day_1_6->Location = System::Drawing::Point(574, 46);
			this->day_1_6->Name = L"day_1_6";
			this->day_1_6->Size = System::Drawing::Size(46, 17);
			this->day_1_6->TabIndex = 12;
			this->day_1_6->Text = L"label6";
			// 
			// day_1_7
			// 
			this->day_1_7->AutoSize = true;
			this->day_1_7->Location = System::Drawing::Point(688, 46);
			this->day_1_7->Name = L"day_1_7";
			this->day_1_7->Size = System::Drawing::Size(46, 17);
			this->day_1_7->TabIndex = 13;
			this->day_1_7->Text = L"label7";
			// 
			// wday_1
			// 
			this->wday_1->AutoSize = true;
			this->wday_1->Location = System::Drawing::Point(4, 1);
			this->wday_1->Name = L"wday_1";
			this->wday_1->Size = System::Drawing::Size(46, 17);
			this->wday_1->TabIndex = 0;
			this->wday_1->Text = L"label1";
			// 
			// wday_2
			// 
			this->wday_2->AutoSize = true;
			this->wday_2->Location = System::Drawing::Point(118, 1);
			this->wday_2->Name = L"wday_2";
			this->wday_2->Size = System::Drawing::Size(46, 17);
			this->wday_2->TabIndex = 1;
			this->wday_2->Text = L"label2";
			// 
			// wday_3
			// 
			this->wday_3->AutoSize = true;
			this->wday_3->Location = System::Drawing::Point(232, 1);
			this->wday_3->Name = L"wday_3";
			this->wday_3->Size = System::Drawing::Size(46, 17);
			this->wday_3->TabIndex = 2;
			this->wday_3->Text = L"label3";
			// 
			// wday_4
			// 
			this->wday_4->AutoSize = true;
			this->wday_4->Location = System::Drawing::Point(346, 1);
			this->wday_4->Name = L"wday_4";
			this->wday_4->Size = System::Drawing::Size(46, 17);
			this->wday_4->TabIndex = 3;
			this->wday_4->Text = L"label4";
			// 
			// wday_5
			// 
			this->wday_5->AutoSize = true;
			this->wday_5->Location = System::Drawing::Point(460, 1);
			this->wday_5->Name = L"wday_5";
			this->wday_5->Size = System::Drawing::Size(46, 17);
			this->wday_5->TabIndex = 4;
			this->wday_5->Text = L"label5";
			// 
			// wday_6
			// 
			this->wday_6->AutoSize = true;
			this->wday_6->Location = System::Drawing::Point(574, 1);
			this->wday_6->Name = L"wday_6";
			this->wday_6->Size = System::Drawing::Size(46, 17);
			this->wday_6->TabIndex = 5;
			this->wday_6->Text = L"label6";
			// 
			// wday_7
			// 
			this->wday_7->AutoSize = true;
			this->wday_7->Location = System::Drawing::Point(688, 1);
			this->wday_7->Name = L"wday_7";
			this->wday_7->Size = System::Drawing::Size(46, 17);
			this->wday_7->TabIndex = 6;
			this->wday_7->Text = L"label7";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(891, 570);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->monthCalendar1);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Form1";
			this->Text = L"My Calender";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

			 }
};
}

