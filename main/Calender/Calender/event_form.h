#pragma once
#include "Event.h"
#include <string.h>
#include <fstream>
#include <stdlib.h>
//load funtion (native C++ content only, managed code continued in batabase test click handler)

namespace Calendar {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices; 
	using namespace std;

	/// <summary>
	/// Summary for event_form
	/// </summary>
	public ref class event_form : public System::Windows::Forms::Form
	{
	public:
		event_form(int F1year, int F1month, int F1day, String ^ uName)
		{
			InitializeComponent();

			eve=new even[5];
			show="0";
			addthis="0";
			num=0;
			numref = new int[5];
			filename=(char*)Marshal::StringToHGlobalAnsi(".\\db\\"+ uName+".txt").ToPointer();
			a=0;
			myYear = F1year;
			myMonth = F1month;
			myDay = F1day;

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
				strcat(date,addthis);
				strcat(date,mbuff);
				strcat(date,addthis);
				strcat(date,dbuff);
			}

			else
			{
				strcat(date,addthis);
				strcat(date,mbuff);
				strcat(date,dbuff);
			}
		}
		else
		{
			if(d<10)
			{

				strcat(date,mbuff);
				strcat(date,addthis);
				strcat(date,dbuff);
			}
			else
			{
				strcat(date,mbuff);
				strcat(date,dbuff);
			}

		}
		String^ mm = Marshal::PtrToStringAnsi((IntPtr)mbuff);
		String^ dd = Marshal::PtrToStringAnsi((IntPtr)dbuff);
		this->Text = "Events - " + myYear + "/"+ mm + "/"+ dd;



			buff = new char**[1000];
			for(int i=0; i<1000; i++){
				buff[i] = new char*[5];
				for(int j=0; j<5; j++){
					buff[i][j] = new char[30];
				}
			}

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~event_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		void evecreate()
		{    num=0;
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
				strcat(date,addthis);
				strcat(date,mbuff);
				strcat(date,addthis);
				strcat(date,dbuff);
			}

			else
			{
				strcat(date,addthis);
				strcat(date,mbuff);
				strcat(date,dbuff);
			}
		}
		else
		{
			if(d<10)
			{

				strcat(date,mbuff);
				strcat(date,addthis);
				strcat(date,dbuff);
			}
			else
			{
				strcat(date,mbuff);
				strcat(date,dbuff);
			}

		}
		int i=0;
		int j=0;
		while(i<a)
		{
			if(strcmp(buff[i][0],date)==0)
			{
				eve[num].setname(buff[i][1]);
				eve[num].setdate(buff[i][0]);
				int load1=atoi(buff[i][2]);
				eve[num].setloe(load1);
				int load2=atoi(buff[i][3]);
				eve[num].setcat(load2);
				eve[num].settime(buff[i][4]);
				numref[num]=i;
				num++;
			}
			i++;
		}
		};
		void load_nativelanguage()

		{

			ifstream fin(filename);
			int i=0;
			int j=0;
			if(!fin)
			{
				show="Data missing";
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
				evecreate();
			}
			fin.close();

		}

	private: System::Windows::Forms::RadioButton^  radioButton1;
	protected: 
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::RadioButton^  radioButton8;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::RadioButton^  radioButton9;
	private: System::Windows::Forms::RadioButton^  radioButton10;
	private: System::Windows::Forms::RadioButton^  radioButton11;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::RadioButton^  radioButton12;
	private: System::Windows::Forms::RadioButton^  radioButton13;
	private: System::Windows::Forms::RadioButton^  radioButton14;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::RadioButton^  radioButton15;
	private: System::Windows::Forms::RadioButton^  radioButton16;
	private: System::Windows::Forms::RadioButton^  radioButton17;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::TextBox^  textBox18;
	private: System::Windows::Forms::TextBox^  textBox19;
	private: System::Windows::Forms::TextBox^  textBox20;
	private: System::Windows::Forms::TextBox^  textBox21;
	private: System::Windows::Forms::RadioButton^  radioButton18;
	private: System::Windows::Forms::RadioButton^  radioButton19;
	private: System::Windows::Forms::RadioButton^  radioButton20;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;

	private: System::Windows::Forms::Label^  label26;










	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		char *** buff;
		even *eve;
		char*show;
		char*addthis;
		int num;
		int *numref;
		char*filename;
		int myYear, myMonth, myDay;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label41;
private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::Label^  label43;
private: System::Windows::Forms::Label^  label44;

		int a;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(event_form::typeid));
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton8 = (gcnew System::Windows::Forms::RadioButton());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton9 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton10 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton11 = (gcnew System::Windows::Forms::RadioButton());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton12 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton13 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton14 = (gcnew System::Windows::Forms::RadioButton());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton15 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton16 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton17 = (gcnew System::Windows::Forms::RadioButton());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton18 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton19 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton20 = (gcnew System::Windows::Forms::RadioButton());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(17, 71);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(70, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Shopping";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(101, 71);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(52, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->Text = L"Study";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(167, 71);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(48, 17);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->Text = L"Date";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(17, 94);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(64, 17);
			this->radioButton4->TabIndex = 3;
			this->radioButton4->Text = L"Sporting";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(101, 94);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(63, 17);
			this->radioButton5->TabIndex = 4;
			this->radioButton5->Text = L"Birthday";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(55, 24);
			this->textBox1->MaxLength = 30;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(159, 20);
			this->textBox1->TabIndex = 5;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label44);
			this->groupBox1->Controls->Add(this->label26);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->radioButton5);
			this->groupBox1->Controls->Add(this->radioButton4);
			this->groupBox1->Controls->Add(this->radioButton3);
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Location = System::Drawing::Point(300, 359);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(233, 117);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"New Event";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(13, 52);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(52, 13);
			this->label44->TabIndex = 7;
			this->label44->Text = L"Category:";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(13, 26);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(38, 13);
			this->label26->TabIndex = 6;
			this->label26->Text = L"Name:";
			this->label26->Click += gcnew System::EventHandler(this, &event_form::label26_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(459, 485);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Add";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &event_form::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(61, 37);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 8;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(61, 81);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 9;
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(17, 45);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(47, 17);
			this->radioButton6->TabIndex = 10;
			this->radioButton6->Text = L"High";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Location = System::Drawing::Point(83, 45);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(62, 17);
			this->radioButton7->TabIndex = 11;
			this->radioButton7->Text = L"Medium";
			this->radioButton7->UseVisualStyleBackColor = true;
			// 
			// radioButton8
			// 
			this->radioButton8->AutoSize = true;
			this->radioButton8->Location = System::Drawing::Point(164, 45);
			this->radioButton8->Name = L"radioButton8";
			this->radioButton8->Size = System::Drawing::Size(45, 17);
			this->radioButton8->TabIndex = 12;
			this->radioButton8->Text = L"Low";
			this->radioButton8->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->ForeColor = System::Drawing::Color::Black;
			this->textBox2->Location = System::Drawing::Point(17, 88);
			this->textBox2->MaxLength = 2;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(24, 20);
			this->textBox2->TabIndex = 13;
			this->textBox2->Text = L"00";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox2->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(52, 88);
			this->textBox3->MaxLength = 2;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(24, 20);
			this->textBox3->TabIndex = 14;
			this->textBox3->Text = L"00";
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox3->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(87, 88);
			this->textBox4->MaxLength = 2;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(24, 20);
			this->textBox4->TabIndex = 15;
			this->textBox4->Text = L"00";
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox4->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(121, 88);
			this->textBox5->MaxLength = 2;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(24, 20);
			this->textBox5->TabIndex = 16;
			this->textBox5->Text = L"00";
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox5->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(42, 89);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(10, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L":";
			this->label3->Click += gcnew System::EventHandler(this, &event_form::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(111, 89);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(10, 13);
			this->label4->TabIndex = 18;
			this->label4->Text = L":";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(77, 89);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(10, 13);
			this->label5->TabIndex = 19;
			this->label5->Text = L"-";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label35);
			this->groupBox2->Controls->Add(this->label34);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->textBox5);
			this->groupBox2->Controls->Add(this->textBox4);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->radioButton8);
			this->groupBox2->Controls->Add(this->radioButton7);
			this->groupBox2->Controls->Add(this->radioButton6);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Location = System::Drawing::Point(21, 23);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(233, 117);
			this->groupBox2->TabIndex = 20;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"groupBox2";
			this->groupBox2->Visible = false;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(13, 26);
			this->label35->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(41, 13);
			this->label35->TabIndex = 21;
			this->label35->Text = L"Priority:";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(13, 68);
			this->label34->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(33, 13);
			this->label34->TabIndex = 20;
			this->label34->Text = L"Time:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(21, 149);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 21;
			this->button2->Text = L"Delete";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &event_form::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(180, 149);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 22;
			this->button3->Text = L"Save";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &event_form::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(101, 149);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 23;
			this->button4->Text = L"Check";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &event_form::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(101, 317);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 27;
			this->button5->Text = L"Check";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Visible = false;
			this->button5->Click += gcnew System::EventHandler(this, &event_form::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(180, 317);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 26;
			this->button6->Text = L"Save";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Visible = false;
			this->button6->Click += gcnew System::EventHandler(this, &event_form::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(21, 317);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 23);
			this->button7->TabIndex = 25;
			this->button7->Text = L"Delete";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			this->button7->Click += gcnew System::EventHandler(this, &event_form::button7_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label36);
			this->groupBox3->Controls->Add(this->label37);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->textBox6);
			this->groupBox3->Controls->Add(this->textBox7);
			this->groupBox3->Controls->Add(this->textBox8);
			this->groupBox3->Controls->Add(this->textBox9);
			this->groupBox3->Controls->Add(this->radioButton9);
			this->groupBox3->Controls->Add(this->radioButton10);
			this->groupBox3->Controls->Add(this->radioButton11);
			this->groupBox3->Controls->Add(this->label9);
			this->groupBox3->Controls->Add(this->label10);
			this->groupBox3->Location = System::Drawing::Point(21, 191);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(233, 117);
			this->groupBox3->TabIndex = 24;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"groupBox3";
			this->groupBox3->Visible = false;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(13, 26);
			this->label36->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(41, 13);
			this->label36->TabIndex = 23;
			this->label36->Text = L"Priority:";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(13, 68);
			this->label37->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(33, 13);
			this->label37->TabIndex = 22;
			this->label37->Text = L"Time:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(77, 89);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(10, 13);
			this->label6->TabIndex = 19;
			this->label6->Text = L"-";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(111, 89);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(10, 13);
			this->label7->TabIndex = 18;
			this->label7->Text = L":";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(42, 89);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(10, 13);
			this->label8->TabIndex = 17;
			this->label8->Text = L":";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(121, 88);
			this->textBox6->MaxLength = 2;
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(24, 20);
			this->textBox6->TabIndex = 16;
			this->textBox6->Text = L"00";
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox6->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(87, 88);
			this->textBox7->MaxLength = 2;
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(24, 20);
			this->textBox7->TabIndex = 15;
			this->textBox7->Text = L"00";
			this->textBox7->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox7->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(52, 88);
			this->textBox8->MaxLength = 2;
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(24, 20);
			this->textBox8->TabIndex = 14;
			this->textBox8->Text = L"00";
			this->textBox8->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox8->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(17, 88);
			this->textBox9->MaxLength = 2;
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(24, 20);
			this->textBox9->TabIndex = 13;
			this->textBox9->Text = L"00";
			this->textBox9->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox9->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// radioButton9
			// 
			this->radioButton9->AutoSize = true;
			this->radioButton9->Location = System::Drawing::Point(164, 45);
			this->radioButton9->Name = L"radioButton9";
			this->radioButton9->Size = System::Drawing::Size(45, 17);
			this->radioButton9->TabIndex = 12;
			this->radioButton9->Text = L"Low";
			this->radioButton9->UseVisualStyleBackColor = true;
			// 
			// radioButton10
			// 
			this->radioButton10->AutoSize = true;
			this->radioButton10->Location = System::Drawing::Point(83, 45);
			this->radioButton10->Name = L"radioButton10";
			this->radioButton10->Size = System::Drawing::Size(62, 17);
			this->radioButton10->TabIndex = 11;
			this->radioButton10->Text = L"Medium";
			this->radioButton10->UseVisualStyleBackColor = true;
			// 
			// radioButton11
			// 
			this->radioButton11->AutoSize = true;
			this->radioButton11->Location = System::Drawing::Point(17, 45);
			this->radioButton11->Name = L"radioButton11";
			this->radioButton11->Size = System::Drawing::Size(47, 17);
			this->radioButton11->TabIndex = 10;
			this->radioButton11->Text = L"High";
			this->radioButton11->UseVisualStyleBackColor = true;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(61, 81);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(0, 13);
			this->label9->TabIndex = 9;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(61, 37);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(0, 13);
			this->label10->TabIndex = 8;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(101, 485);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(75, 23);
			this->button8->TabIndex = 27;
			this->button8->Text = L"Check";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Visible = false;
			this->button8->Click += gcnew System::EventHandler(this, &event_form::button8_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(180, 485);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 26;
			this->button9->Text = L"Save";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Visible = false;
			this->button9->Click += gcnew System::EventHandler(this, &event_form::button9_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(21, 485);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(75, 23);
			this->button10->TabIndex = 25;
			this->button10->Text = L"Delete";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Visible = false;
			this->button10->Click += gcnew System::EventHandler(this, &event_form::button10_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->label38);
			this->groupBox4->Controls->Add(this->label39);
			this->groupBox4->Controls->Add(this->label11);
			this->groupBox4->Controls->Add(this->label12);
			this->groupBox4->Controls->Add(this->label13);
			this->groupBox4->Controls->Add(this->textBox10);
			this->groupBox4->Controls->Add(this->textBox11);
			this->groupBox4->Controls->Add(this->textBox12);
			this->groupBox4->Controls->Add(this->textBox13);
			this->groupBox4->Controls->Add(this->radioButton12);
			this->groupBox4->Controls->Add(this->radioButton13);
			this->groupBox4->Controls->Add(this->radioButton14);
			this->groupBox4->Controls->Add(this->label14);
			this->groupBox4->Controls->Add(this->label15);
			this->groupBox4->Location = System::Drawing::Point(21, 359);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(233, 117);
			this->groupBox4->TabIndex = 24;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"groupBox4";
			this->groupBox4->Visible = false;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(13, 26);
			this->label38->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(41, 13);
			this->label38->TabIndex = 23;
			this->label38->Text = L"Priority:";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(13, 68);
			this->label39->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(33, 13);
			this->label39->TabIndex = 22;
			this->label39->Text = L"Time:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(77, 89);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(10, 13);
			this->label11->TabIndex = 19;
			this->label11->Text = L"-";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(111, 89);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(10, 13);
			this->label12->TabIndex = 18;
			this->label12->Text = L":";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(42, 89);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(10, 13);
			this->label13->TabIndex = 17;
			this->label13->Text = L":";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(121, 88);
			this->textBox10->MaxLength = 2;
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(24, 20);
			this->textBox10->TabIndex = 16;
			this->textBox10->Text = L"00";
			this->textBox10->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox10->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox10->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(87, 88);
			this->textBox11->MaxLength = 2;
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(24, 20);
			this->textBox11->TabIndex = 15;
			this->textBox11->Text = L"00";
			this->textBox11->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox11->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox11->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(52, 88);
			this->textBox12->MaxLength = 2;
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(24, 20);
			this->textBox12->TabIndex = 14;
			this->textBox12->Text = L"00";
			this->textBox12->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox12->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox12->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(17, 88);
			this->textBox13->MaxLength = 2;
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(24, 20);
			this->textBox13->TabIndex = 13;
			this->textBox13->Text = L"00";
			this->textBox13->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox13->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox13->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// radioButton12
			// 
			this->radioButton12->AutoSize = true;
			this->radioButton12->Location = System::Drawing::Point(164, 45);
			this->radioButton12->Name = L"radioButton12";
			this->radioButton12->Size = System::Drawing::Size(45, 17);
			this->radioButton12->TabIndex = 12;
			this->radioButton12->Text = L"Low";
			this->radioButton12->UseVisualStyleBackColor = true;
			// 
			// radioButton13
			// 
			this->radioButton13->AutoSize = true;
			this->radioButton13->Location = System::Drawing::Point(83, 45);
			this->radioButton13->Name = L"radioButton13";
			this->radioButton13->Size = System::Drawing::Size(62, 17);
			this->radioButton13->TabIndex = 11;
			this->radioButton13->Text = L"Medium";
			this->radioButton13->UseVisualStyleBackColor = true;
			// 
			// radioButton14
			// 
			this->radioButton14->AutoSize = true;
			this->radioButton14->Location = System::Drawing::Point(17, 45);
			this->radioButton14->Name = L"radioButton14";
			this->radioButton14->Size = System::Drawing::Size(47, 17);
			this->radioButton14->TabIndex = 10;
			this->radioButton14->Text = L"High";
			this->radioButton14->UseVisualStyleBackColor = true;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(61, 81);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(0, 13);
			this->label14->TabIndex = 9;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(61, 37);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(0, 13);
			this->label15->TabIndex = 8;
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(379, 149);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(75, 23);
			this->button11->TabIndex = 27;
			this->button11->Text = L"Check";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Visible = false;
			this->button11->Click += gcnew System::EventHandler(this, &event_form::button11_Click);
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(459, 149);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(75, 23);
			this->button12->TabIndex = 26;
			this->button12->Text = L"Save";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Visible = false;
			this->button12->Click += gcnew System::EventHandler(this, &event_form::button12_Click);
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(300, 149);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(75, 23);
			this->button13->TabIndex = 25;
			this->button13->Text = L"Delete";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Visible = false;
			this->button13->Click += gcnew System::EventHandler(this, &event_form::button13_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->label40);
			this->groupBox5->Controls->Add(this->label41);
			this->groupBox5->Controls->Add(this->label16);
			this->groupBox5->Controls->Add(this->label17);
			this->groupBox5->Controls->Add(this->label18);
			this->groupBox5->Controls->Add(this->textBox14);
			this->groupBox5->Controls->Add(this->textBox15);
			this->groupBox5->Controls->Add(this->textBox16);
			this->groupBox5->Controls->Add(this->textBox17);
			this->groupBox5->Controls->Add(this->radioButton15);
			this->groupBox5->Controls->Add(this->radioButton16);
			this->groupBox5->Controls->Add(this->radioButton17);
			this->groupBox5->Controls->Add(this->label19);
			this->groupBox5->Controls->Add(this->label20);
			this->groupBox5->Location = System::Drawing::Point(300, 23);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(233, 117);
			this->groupBox5->TabIndex = 24;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"groupBox5";
			this->groupBox5->Visible = false;
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(13, 26);
			this->label40->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(41, 13);
			this->label40->TabIndex = 23;
			this->label40->Text = L"Priority:";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(13, 68);
			this->label41->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(33, 13);
			this->label41->TabIndex = 22;
			this->label41->Text = L"Time:";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(77, 89);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(10, 13);
			this->label16->TabIndex = 19;
			this->label16->Text = L"-";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(111, 89);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(10, 13);
			this->label17->TabIndex = 18;
			this->label17->Text = L":";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(42, 89);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(10, 13);
			this->label18->TabIndex = 17;
			this->label18->Text = L":";
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(121, 88);
			this->textBox14->MaxLength = 2;
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(24, 20);
			this->textBox14->TabIndex = 16;
			this->textBox14->Text = L"00";
			this->textBox14->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox14->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox14->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(87, 88);
			this->textBox15->MaxLength = 2;
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(24, 20);
			this->textBox15->TabIndex = 15;
			this->textBox15->Text = L"00";
			this->textBox15->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox15->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox15->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(52, 88);
			this->textBox16->MaxLength = 2;
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(24, 20);
			this->textBox16->TabIndex = 14;
			this->textBox16->Text = L"00";
			this->textBox16->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox16->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox16->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(17, 88);
			this->textBox17->MaxLength = 2;
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(24, 20);
			this->textBox17->TabIndex = 13;
			this->textBox17->Text = L"00";
			this->textBox17->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox17->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox17->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// radioButton15
			// 
			this->radioButton15->AutoSize = true;
			this->radioButton15->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->radioButton15->Location = System::Drawing::Point(164, 45);
			this->radioButton15->Name = L"radioButton15";
			this->radioButton15->Size = System::Drawing::Size(45, 17);
			this->radioButton15->TabIndex = 12;
			this->radioButton15->Text = L"Low";
			this->radioButton15->UseVisualStyleBackColor = true;
			// 
			// radioButton16
			// 
			this->radioButton16->AutoSize = true;
			this->radioButton16->Location = System::Drawing::Point(83, 45);
			this->radioButton16->Name = L"radioButton16";
			this->radioButton16->Size = System::Drawing::Size(62, 17);
			this->radioButton16->TabIndex = 11;
			this->radioButton16->Text = L"Medium";
			this->radioButton16->UseVisualStyleBackColor = true;
			// 
			// radioButton17
			// 
			this->radioButton17->AutoSize = true;
			this->radioButton17->BackColor = System::Drawing::Color::Transparent;
			this->radioButton17->Location = System::Drawing::Point(17, 45);
			this->radioButton17->Name = L"radioButton17";
			this->radioButton17->Size = System::Drawing::Size(47, 17);
			this->radioButton17->TabIndex = 10;
			this->radioButton17->Text = L"High";
			this->radioButton17->UseVisualStyleBackColor = false;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(61, 81);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(0, 13);
			this->label19->TabIndex = 9;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(61, 37);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(0, 13);
			this->label20->TabIndex = 8;
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(379, 317);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(75, 23);
			this->button14->TabIndex = 27;
			this->button14->Text = L"Check";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Visible = false;
			this->button14->Click += gcnew System::EventHandler(this, &event_form::button14_Click);
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(459, 317);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(75, 23);
			this->button15->TabIndex = 26;
			this->button15->Text = L"Save";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Visible = false;
			this->button15->Click += gcnew System::EventHandler(this, &event_form::button15_Click);
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(300, 317);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(75, 23);
			this->button16->TabIndex = 25;
			this->button16->Text = L"Delete";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Visible = false;
			this->button16->Click += gcnew System::EventHandler(this, &event_form::button16_Click);
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->label42);
			this->groupBox6->Controls->Add(this->label43);
			this->groupBox6->Controls->Add(this->label21);
			this->groupBox6->Controls->Add(this->label22);
			this->groupBox6->Controls->Add(this->label23);
			this->groupBox6->Controls->Add(this->textBox18);
			this->groupBox6->Controls->Add(this->textBox19);
			this->groupBox6->Controls->Add(this->textBox20);
			this->groupBox6->Controls->Add(this->textBox21);
			this->groupBox6->Controls->Add(this->radioButton18);
			this->groupBox6->Controls->Add(this->radioButton19);
			this->groupBox6->Controls->Add(this->radioButton20);
			this->groupBox6->Controls->Add(this->label24);
			this->groupBox6->Controls->Add(this->label25);
			this->groupBox6->Location = System::Drawing::Point(300, 191);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(233, 117);
			this->groupBox6->TabIndex = 24;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"groupBox6";
			this->groupBox6->Visible = false;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(13, 26);
			this->label42->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(41, 13);
			this->label42->TabIndex = 23;
			this->label42->Text = L"Priority:";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(13, 68);
			this->label43->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(33, 13);
			this->label43->TabIndex = 22;
			this->label43->Text = L"Time:";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(77, 89);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(10, 13);
			this->label21->TabIndex = 19;
			this->label21->Text = L"-";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(111, 89);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(10, 13);
			this->label22->TabIndex = 18;
			this->label22->Text = L":";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(42, 89);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(10, 13);
			this->label23->TabIndex = 17;
			this->label23->Text = L":";
			// 
			// textBox18
			// 
			this->textBox18->Location = System::Drawing::Point(121, 88);
			this->textBox18->MaxLength = 2;
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(24, 20);
			this->textBox18->TabIndex = 16;
			this->textBox18->Text = L"00";
			this->textBox18->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox18->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox18->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox19
			// 
			this->textBox19->Location = System::Drawing::Point(87, 88);
			this->textBox19->MaxLength = 2;
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(24, 20);
			this->textBox19->TabIndex = 15;
			this->textBox19->Text = L"00";
			this->textBox19->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox19->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox19->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox20
			// 
			this->textBox20->Location = System::Drawing::Point(52, 88);
			this->textBox20->MaxLength = 2;
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(24, 20);
			this->textBox20->TabIndex = 14;
			this->textBox20->Text = L"00";
			this->textBox20->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox20->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox20->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// textBox21
			// 
			this->textBox21->Location = System::Drawing::Point(17, 88);
			this->textBox21->MaxLength = 2;
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(24, 20);
			this->textBox21->TabIndex = 13;
			this->textBox21->Text = L"00";
			this->textBox21->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox21->Click += gcnew System::EventHandler(this, &event_form::select_all_Click);
			this->textBox21->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &event_form::int_only_KeyPress);
			// 
			// radioButton18
			// 
			this->radioButton18->AutoSize = true;
			this->radioButton18->Location = System::Drawing::Point(164, 45);
			this->radioButton18->Name = L"radioButton18";
			this->radioButton18->Size = System::Drawing::Size(45, 17);
			this->radioButton18->TabIndex = 12;
			this->radioButton18->Text = L"Low";
			this->radioButton18->UseVisualStyleBackColor = true;
			// 
			// radioButton19
			// 
			this->radioButton19->AutoSize = true;
			this->radioButton19->Location = System::Drawing::Point(83, 45);
			this->radioButton19->Name = L"radioButton19";
			this->radioButton19->Size = System::Drawing::Size(62, 17);
			this->radioButton19->TabIndex = 11;
			this->radioButton19->Text = L"Medium";
			this->radioButton19->UseVisualStyleBackColor = true;
			// 
			// radioButton20
			// 
			this->radioButton20->AutoSize = true;
			this->radioButton20->Location = System::Drawing::Point(17, 45);
			this->radioButton20->Name = L"radioButton20";
			this->radioButton20->Size = System::Drawing::Size(47, 17);
			this->radioButton20->TabIndex = 10;
			this->radioButton20->Text = L"High";
			this->radioButton20->UseVisualStyleBackColor = true;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(61, 81);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(0, 13);
			this->label24->TabIndex = 9;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(61, 37);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(0, 13);
			this->label25->TabIndex = 8;
			// 
			// event_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(554, 531);
			this->Controls->Add(this->button14);
			this->Controls->Add(this->button11);
			this->Controls->Add(this->button15);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button16);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"event_form";
			this->Text = L"Events";
			this->Load += gcnew System::EventHandler(this, &event_form::event_form_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void event_form_Load(System::Object^  sender, System::EventArgs^  e) {
				 // the unmanaged code for load
				 load_nativelanguage();
				 //the managed code for load
				 switch(num)
				 {
				 case 0:
					 {
						 break;
					 }
				 case 1:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;

						 if(eve[0].getloe()==1)
						 {
							 radioButton6->Checked=true;
						 }
						 if(eve[0].getloe()==2)
						 {
							 radioButton7->Checked=true;
						 }
						 if(eve[0].getloe()==3)
						 {
							 radioButton8->Checked=true;
						 }
						 if(eve[0].getloe()==4)
						 {
							 this->button4->Text="Uncheck";
						 }

						 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
						 load1[0]=load[0];
						 load1[1]=load[1];
						 load2[0]=load[2];
						 load2[1]=load[3];
						 load3[0]=load[5];
						 load3[1]=load[6];
						 load4[0]=load[7];
						 load4[1]=load[8];
						 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
						 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
						 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
						 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
						 this->textBox2->Text = Load1;
						 this->textBox3->Text = Load2;
						 this->textBox4->Text = Load3;
						 this->textBox5->Text = Load4;
						 break;
					 }
				 case 2:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 break;
					 }
				 case 3:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;


						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }




						 break;
					 }
				 case 4:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;






						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }




						 break;
					 }
				 case 5:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;
						 this->groupBox6->Visible = true;
						 this->button14->Visible = true;
						 this->button15->Visible = true;
						 this->button16->Visible = true;
						 char*message5=eve[4].getname();
						 String ^ mmg5 = Marshal::PtrToStringAnsi((IntPtr)message5);
						 this->groupBox6->Text = mmg5;



						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }


						 {	  	
							 if(eve[4].getloe()==1)
							 {
								 radioButton20->Checked=true;
							 }
							 if(eve[4].getloe()==2)
							 {
								 radioButton19->Checked=true;
							 }
							 if(eve[4].getloe()==3)
							 {
								 radioButton18->Checked=true;
							 }
							 if(eve[4].getloe()==4)
							 {
								 this->button14->Text="Uncheck";
							 }

							 char*load=eve[4].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox21->Text = Load1;
							 this->textBox20->Text = Load2;
							 this->textBox19->Text = Load3;
							 this->textBox18->Text = Load4;
						 }



						 break;
					 }
				 }

				 //end of test code
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(num<5){
				 if(!String::IsNullOrEmpty(textBox1->Text)){
					 

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
							 strcat(date,addthis);
							 strcat(date,mbuff);
							 strcat(date,addthis);
							 strcat(date,dbuff);
						 }

						 else
						 {
							 strcat(date,addthis);
							 strcat(date,mbuff);
							 strcat(date,dbuff);
						 }
					 }
					 else
					 {
						 if(d<10)
						 {

							 strcat(date,mbuff);
							 strcat(date,addthis);
							 strcat(date,dbuff);
						 }
						 else
						 {
							 strcat(date,mbuff);
							 strcat(date,dbuff);
						 }

					 }


					 char *n="0";
					 int c=0;
					 int em=0;
					 char du[100]="0000,0000";
					 String ^ tbstr;
					 if (radioButton1->Checked)
					 {
						 c=1; 
						 tbstr = textBox1->Text;
//						 tbstr = "Shopping: "+textBox1->Text;
					 }
					 if (radioButton2->Checked)
					 {c = 2;
					 tbstr = textBox1->Text;
//					 tbstr = "Study: "+textBox1->Text;
					 }
					 if (radioButton3->Checked)
					 {
						 c = 3; 
						 tbstr = textBox1->Text;
//						 tbstr = "Date: "+textBox1->Text;
					 }
					 if (radioButton4->Checked)
					 {
						 c = 4; 
						 tbstr = textBox1->Text;
//						 tbstr = "Sporting: "+textBox1->Text;
					 }
					 if (radioButton5->Checked)
					 {
						 c = 5;
						 tbstr = textBox1->Text;
//						 tbstr = "Birthday: "+textBox1->Text;
					 }
						 radioButton1->Checked = true;
					 textBox1->Text = "";
					 n=(char*)Marshal::StringToHGlobalAnsi(tbstr).ToPointer();

					 eve[num].setname(n);
					 eve[num].setcat(c);
					 eve[num].setloe(em);
					 eve[num].setdate(date);
					 eve[num].settime(du);
					 strcpy( buff[a][1],eve[num].getname());
					 itoa(eve[num].getcat(),buff[a][3],10);
					 itoa( eve[num].getloe(),buff[a][2],10);
					 strcpy( buff[a][0],eve[num].getdate());
					 strcpy( buff[a][4],eve[num].gettime());
					 numref[num]=a;
					 a++;
					 num++;
					 switch(num)
					 {
					 case 1:
						 {
							 this->groupBox2->Visible = true;
							 this->button2->Visible = true;
							 this->button3->Visible = true;
							 this->button4->Visible = true;
							 char*message=eve[0].getname();
							 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
							 this->groupBox2->Text = mmg;
							 radioButton8->Checked = true;
							 break;
						 }
					 case 2:
						 {
							 this->groupBox3->Visible = true;
							 this->button5->Visible = true;
							 this->button6->Visible = true;
							 this->button7->Visible = true;
							 char*message2=eve[1].getname();
							 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
							 this->groupBox3->Text = mmg2;
							 radioButton9->Checked = true;
							 break;
						 }
					 case 3:
						 {
							 this->groupBox4->Visible = true;
							 this->button8->Visible = true;
							 this->button9->Visible = true;
							 this->button10->Visible = true;
							 char*message3=eve[2].getname();
							 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
							 this->groupBox4->Text = mmg3;
							 radioButton12->Checked = true;
							 break;
						 }
					 case 4:
						 {
							 this->groupBox5->Visible = true;
							 this->button11->Visible = true;
							 this->button12->Visible = true;
							 this->button13->Visible = true;
							 char*message4=eve[3].getname();
							 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
							 this->groupBox5->Text = mmg4;
							 radioButton15->Checked = true;
							 break;
						 }
					 case 5:
						 {
							 this->groupBox6->Visible = true;
							 this->button14->Visible = true;
							 this->button15->Visible = true;
							 this->button16->Visible = true;
							 char*message5=eve[4].getname();
							 String ^ mmg5 = Marshal::PtrToStringAnsi((IntPtr)message5);
							 this->groupBox6->Text = mmg5;
							 radioButton18->Checked = true;
							 break;
						 }
					 }



					 int i=0,j=0;
					 ofstream fout(filename,ios::trunc);
					 while(i<a)
					 {
						 fout<<buff[i][j]<<endl;
						 if(j<4)
							 j++;
						 else
						 {
							 j=0;
							 i++;
						 }
					 }
					 fout.close();
					 } else {
					 MessageBox::Show("Please input the event name!");
					 }
				 } 
				 else
				 {
					 MessageBox::Show("You already reach the maximum number of event per day!");
				 } 
			 }

	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
			 //remember to delete after test!
	private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label26_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(!(String::Compare(textBox2->Text, textBox4->Text) == 0 && String::Compare(textBox3->Text, textBox5->Text) == 0)){
				 int loe;
				 if(radioButton6->Checked)
				 {
					 loe=1;
					 eve[0].setloe( loe);
					 this->button4->Text="Check";
				 }
				 if(radioButton7->Checked)
				 {
					 loe=2;
					 eve[0].setloe( loe);
					 this->button4->Text="Check";
				 }
				 if(radioButton8->Checked)
				 {
					 loe=3;
					 eve[0].setloe( loe);
					 this->button4->Text="Check";
				 }
				 itoa(eve[0].getloe(),buff[numref[0]][2],10);

				 String ^ tbstr;
				 tbstr =textBox2->Text+textBox3->Text+","+textBox4->Text+textBox5->Text;
				 char*time;
				 time=(char*)Marshal::StringToHGlobalAnsi(tbstr).ToPointer();
				 if(time[0]==',')
				 {
					 time="0000,0000";
				 }
				 eve[0].settime(time);
				 strcpy( buff[numref[0]][4],eve[0].gettime());
				 int i=0;
				 int j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
				 } else {
					 MessageBox::Show("Event cannot have same start time and end time!");
				 }
			 }
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(!(String::Compare(textBox9->Text, textBox7->Text) == 0 && String::Compare(textBox8->Text, textBox6->Text) == 0)){
				 int loe;
				 if(radioButton11->Checked)
				 {
					 loe=1;
					 eve[1].setloe( loe);
					 this->button5->Text="Check";
				 }
				 if(radioButton10->Checked)
				 {
					 loe=2;
					 eve[1].setloe( loe);
					 this->button5->Text="Check";
				 }
				 if(radioButton9->Checked)
				 {
					 loe=3;
					 eve[1].setloe( loe);
					 this->button5->Text="Check";
				 }
				 itoa(eve[1].getloe(),buff[numref[1]][2],10);

				 String ^ tbstr;
				 tbstr =textBox9->Text+textBox8->Text+","+textBox7->Text+textBox6->Text;
				 char*time;
				 time=(char*)Marshal::StringToHGlobalAnsi(tbstr).ToPointer();
				 if(time[0]==',')
				 {
					 time="0000,0000";
				 }
				 eve[1].settime(time);
				 strcpy( buff[numref[1]][4],eve[1].gettime());
				 int i=0;
				 int j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
				 } else {
					 MessageBox::Show("Event cannot have same start time and end time!");
				 }
			 }
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(!(String::Compare(textBox13->Text, textBox11->Text) == 0 && String::Compare(textBox12->Text, textBox10->Text) == 0)){
				 int loe;
				 if(radioButton14->Checked)
				 {
					 loe=1;
					 eve[2].setloe( loe);
					 this->button8->Text="Check";
				 }
				 if(radioButton13->Checked)
				 {
					 loe=2;
					 eve[2].setloe( loe);
					 this->button8->Text="Check";
				 }
				 if(radioButton12->Checked)
				 {
					 loe=3;
					 eve[2].setloe( loe);
					 this->button8->Text="Check";
				 }
				 itoa(eve[2].getloe(),buff[numref[2]][2],10);

				 String ^ tbstr;
				 tbstr =textBox13->Text+textBox12->Text+","+textBox11->Text+textBox10->Text;
				 char*time;
				 time=(char*)Marshal::StringToHGlobalAnsi(tbstr).ToPointer();
				 if(time[0]==',')
				 {
					 time="0000,0000";
				 }
				 eve[2].settime(time);
				 strcpy( buff[numref[2]][4],eve[2].gettime());
				 int i=0;
				 int j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
				 } else {
					 MessageBox::Show("Event cannot have same start time and end time!");
				 }
			 }
	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(!(String::Compare(textBox17->Text, textBox15->Text) == 0 && String::Compare(textBox16->Text, textBox14->Text) == 0)){
				 int loe;
				 if(radioButton17->Checked)
				 {
					 loe=1;
					 eve[3].setloe( loe);
					 this->button11->Text="Check";
				 }
				 if(radioButton16->Checked)
				 {
					 loe=2;
					 eve[3].setloe( loe);
					 this->button11->Text="Check";
				 }
				 if(radioButton15->Checked)
				 {
					 loe=3;
					 eve[3].setloe( loe);
					 this->button11->Text="Check";
				 }
				 itoa(eve[3].getloe(),buff[numref[3]][2],10);

				 String ^ tbstr;
				 tbstr =textBox17->Text+textBox16->Text+","+textBox15->Text+textBox14->Text;
				 char*time;
				 time=(char*)Marshal::StringToHGlobalAnsi(tbstr).ToPointer();
				 if(time[0]==',')
				 {
					 time="0000,0000";
				 }
				 eve[3].settime(time);
				 strcpy( buff[numref[3]][4],eve[3].gettime());
				 int i=0;
				 int j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
				 } else {
					 MessageBox::Show("Event cannot have same start time and end time!");
				 }
			 }
	private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(!(String::Compare(textBox21->Text, textBox19->Text) == 0 && String::Compare(textBox20->Text, textBox18->Text) == 0)){
				 int loe;
				 if(radioButton20->Checked)
				 {
					 loe=1;
					 eve[4].setloe( loe);
					 this->button14->Text="Check";
				 }
				 if(radioButton19->Checked)
				 {
					 loe=2;
					 eve[4].setloe( loe);
					 this->button14->Text="Check";
				 }
				 if(radioButton18->Checked)
				 {
					 loe=3;
					 eve[4].setloe( loe);
					 this->button14->Text="Check";
				 }
				 itoa(eve[4].getloe(),buff[numref[4]][2],10);

				 String ^ tbstr;
				 tbstr =textBox21->Text+textBox20->Text+","+textBox19->Text+textBox18->Text;
				 char*time;
				 time=(char*)Marshal::StringToHGlobalAnsi(tbstr).ToPointer();
				 if(time[0]==',')
				 {
					 time="0000,0000";
				 }
				 eve[4].settime(time);
				 strcpy( buff[numref[4]][4],eve[4].gettime());
				 int i=0;
				 int j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
				 } else {
					 MessageBox::Show("Event cannot have same start time and end time!");
				 }
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 strcpy(buff[numref[0]][0],addthis);
				 strcpy(buff[numref[0]][1],addthis);
				 strcpy(buff[numref[0]][2],addthis);
				 strcpy(buff[numref[0]][3],addthis);
				 strcpy(buff[numref[0]][4],addthis);
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();

				 this->groupBox2->Visible=false;
				 this->groupBox3->Visible=false;
				 this->groupBox4->Visible=false;
				 this->groupBox5->Visible=false;
				 this->groupBox6->Visible=false;
				 this->button2->Visible=false;
				 this->button3->Visible=false;
				 this->button4->Visible=false;
				 this->button5->Visible=false;
				 this->button6->Visible=false;
				 this->button7->Visible=false;
				 this->button8->Visible=false;
				 this->button9->Visible=false;
				 this->button10->Visible=false;
				 this->button11->Visible=false;
				 this->button12->Visible=false;
				 this->button13->Visible=false;
				 this->button14->Visible=false;
				 this->button15->Visible=false;
				 this->button16->Visible=false;
				 this->button4->Text="Check";
				 this->button5->Text="Check";
				 this->button8->Text="Check";
				 this->button11->Text="Check";
				 this->button14->Text="Check";
				 evecreate();
				 //managed code for recreating after delete

				 switch(num)
				 {
				 case 0:
					 {
						 break;
					 }
				 case 1:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;

						 if(eve[0].getloe()==1)
						 {
							 radioButton6->Checked=true;
						 }
						 if(eve[0].getloe()==2)
						 {
							 radioButton7->Checked=true;
						 }
						 if(eve[0].getloe()==3)
						 {
							 radioButton8->Checked=true;
						 }
						 if(eve[0].getloe()==4)
						 {
							 this->button4->Text="Uncheck";
						 }

						 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
						 load1[0]=load[0];
						 load1[1]=load[1];
						 load2[0]=load[2];
						 load2[1]=load[3];
						 load3[0]=load[5];
						 load3[1]=load[6];
						 load4[0]=load[7];
						 load4[1]=load[8];
						 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
						 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
						 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
						 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
						 this->textBox2->Text = Load1;
						 this->textBox3->Text = Load2;
						 this->textBox4->Text = Load3;
						 this->textBox5->Text = Load4;
						 break;
					 }
				 case 2:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 break;
					 }
				 case 3:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;


						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }




						 break;
					 }
				 case 4:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;






						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }




						 break;
					 }
				 case 5:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;
						 this->groupBox6->Visible = true;
						 this->button14->Visible = true;
						 this->button15->Visible = true;
						 this->button16->Visible = true;
						 char*message5=eve[4].getname();
						 String ^ mmg5 = Marshal::PtrToStringAnsi((IntPtr)message5);
						 this->groupBox6->Text = mmg5;



						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }


						 {	  	
							 if(eve[4].getloe()==1)
							 {
								 radioButton20->Checked=true;
							 }
							 if(eve[4].getloe()==2)
							 {
								 radioButton19->Checked=true;
							 }
							 if(eve[4].getloe()==3)
							 {
								 radioButton18->Checked=true;
							 }
							 if(eve[4].getloe()==4)
							 {
								 this->button14->Text="Uncheck";
							 }

							 char*load=eve[4].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox21->Text = Load1;
							 this->textBox20->Text = Load2;
							 this->textBox19->Text = Load3;
							 this->textBox18->Text = Load4;
						 }



						 break;
					 }
				 }


/*				 if( this->label27->Visible ==true)
				 {
					 this->label27->Visible=false;
					 this->label28->Visible=false;
				 }*/
			 }
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
				 strcpy(buff[numref[1]][0],addthis);
				 strcpy(buff[numref[1]][1],addthis);
				 strcpy(buff[numref[1]][2],addthis);
				 strcpy(buff[numref[1]][3],addthis);
				 strcpy(buff[numref[1]][4],addthis);
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();

				 this->groupBox2->Visible=false;
				 this->groupBox3->Visible=false;
				 this->groupBox4->Visible=false;
				 this->groupBox5->Visible=false;
				 this->groupBox6->Visible=false;
				 this->button2->Visible=false;
				 this->button3->Visible=false;
				 this->button4->Visible=false;
				 this->button5->Visible=false;
				 this->button6->Visible=false;
				 this->button7->Visible=false;
				 this->button8->Visible=false;
				 this->button9->Visible=false;
				 this->button10->Visible=false;
				 this->button11->Visible=false;
				 this->button12->Visible=false;
				 this->button13->Visible=false;
				 this->button14->Visible=false;
				 this->button15->Visible=false;
				 this->button16->Visible=false;
				 this->button4->Text="Check";
				 this->button5->Text="Check";
				 this->button8->Text="Check";
				 this->button11->Text="Check";
				 this->button14->Text="Check";
				 evecreate();
				 //managed code for recreating after delete
				 switch(num)
				 {
				 case 0:
					 {
						 break;
					 }
				 case 1:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;

						 if(eve[0].getloe()==1)
						 {
							 radioButton6->Checked=true;
						 }
						 if(eve[0].getloe()==2)
						 {
							 radioButton7->Checked=true;
						 }
						 if(eve[0].getloe()==3)
						 {
							 radioButton8->Checked=true;
						 }
						 if(eve[0].getloe()==4)
						 {
							 this->button4->Text="Uncheck";
						 }

						 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
						 load1[0]=load[0];
						 load1[1]=load[1];
						 load2[0]=load[2];
						 load2[1]=load[3];
						 load3[0]=load[5];
						 load3[1]=load[6];
						 load4[0]=load[7];
						 load4[1]=load[8];
						 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
						 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
						 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
						 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
						 this->textBox2->Text = Load1;
						 this->textBox3->Text = Load2;
						 this->textBox4->Text = Load3;
						 this->textBox5->Text = Load4;
						 break;
					 }
				 case 2:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 break;
					 }
				 case 3:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;


						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }




						 break;
					 }
				 case 4:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;






						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }




						 break;
					 }
				 case 5:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;
						 this->groupBox6->Visible = true;
						 this->button14->Visible = true;
						 this->button15->Visible = true;
						 this->button16->Visible = true;
						 char*message5=eve[4].getname();
						 String ^ mmg5 = Marshal::PtrToStringAnsi((IntPtr)message5);
						 this->groupBox6->Text = mmg5;



						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }


						 {	  	
							 if(eve[4].getloe()==1)
							 {
								 radioButton20->Checked=true;
							 }
							 if(eve[4].getloe()==2)
							 {
								 radioButton19->Checked=true;
							 }
							 if(eve[4].getloe()==3)
							 {
								 radioButton18->Checked=true;
							 }
							 if(eve[4].getloe()==4)
							 {
								 this->button14->Text="Uncheck";
							 }

							 char*load=eve[4].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox21->Text = Load1;
							 this->textBox20->Text = Load2;
							 this->textBox19->Text = Load3;
							 this->textBox18->Text = Load4;
						 }



						 break;
					 }
				 }


/*
				 if( this->label27->Visible ==true)
				 {
					 this->label27->Visible=false;
					 this->label28->Visible=false;
				 }
*/
			 }
	private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
				 strcpy(buff[numref[2]][0],addthis);
				 strcpy(buff[numref[2]][1],addthis);
				 strcpy(buff[numref[2]][2],addthis);
				 strcpy(buff[numref[2]][3],addthis);
				 strcpy(buff[numref[2]][4],addthis);
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();

				 this->groupBox2->Visible=false;
				 this->groupBox3->Visible=false;
				 this->groupBox4->Visible=false;
				 this->groupBox5->Visible=false;
				 this->groupBox6->Visible=false;
				 this->button2->Visible=false;
				 this->button3->Visible=false;
				 this->button4->Visible=false;
				 this->button5->Visible=false;
				 this->button6->Visible=false;
				 this->button7->Visible=false;
				 this->button8->Visible=false;
				 this->button9->Visible=false;
				 this->button10->Visible=false;
				 this->button11->Visible=false;
				 this->button12->Visible=false;
				 this->button13->Visible=false;
				 this->button14->Visible=false;
				 this->button15->Visible=false;
				 this->button16->Visible=false;
				 this->button4->Text="Check";
				 this->button5->Text="Check";
				 this->button8->Text="Check";
				 this->button11->Text="Check";
				 this->button14->Text="Check";
				 evecreate();
				 //managed code for recreating after delete
				 switch(num)
				 {
				 case 0:
					 {
						 break;
					 }
				 case 1:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;

						 if(eve[0].getloe()==1)
						 {
							 radioButton6->Checked=true;
						 }
						 if(eve[0].getloe()==2)
						 {
							 radioButton7->Checked=true;
						 }
						 if(eve[0].getloe()==3)
						 {
							 radioButton8->Checked=true;
						 }
						 if(eve[0].getloe()==4)
						 {
							 this->button4->Text="Uncheck";
						 }

						 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
						 load1[0]=load[0];
						 load1[1]=load[1];
						 load2[0]=load[2];
						 load2[1]=load[3];
						 load3[0]=load[5];
						 load3[1]=load[6];
						 load4[0]=load[7];
						 load4[1]=load[8];
						 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
						 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
						 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
						 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
						 this->textBox2->Text = Load1;
						 this->textBox3->Text = Load2;
						 this->textBox4->Text = Load3;
						 this->textBox5->Text = Load4;
						 break;
					 }
				 case 2:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 break;
					 }
				 case 3:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;


						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }




						 break;
					 }
				 case 4:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;






						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }




						 break;
					 }
				 case 5:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;
						 this->groupBox6->Visible = true;
						 this->button14->Visible = true;
						 this->button15->Visible = true;
						 this->button16->Visible = true;
						 char*message5=eve[4].getname();
						 String ^ mmg5 = Marshal::PtrToStringAnsi((IntPtr)message5);
						 this->groupBox6->Text = mmg5;



						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }


						 {	  	
							 if(eve[4].getloe()==1)
							 {
								 radioButton20->Checked=true;
							 }
							 if(eve[4].getloe()==2)
							 {
								 radioButton19->Checked=true;
							 }
							 if(eve[4].getloe()==3)
							 {
								 radioButton18->Checked=true;
							 }
							 if(eve[4].getloe()==4)
							 {
								 this->button14->Text="Uncheck";
							 }

							 char*load=eve[4].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox21->Text = Load1;
							 this->textBox20->Text = Load2;
							 this->textBox19->Text = Load3;
							 this->textBox18->Text = Load4;
						 }



						 break;
					 }
				 }


/*
				 if( this->label27->Visible ==true)
				 {
					 this->label27->Visible=false;
					 this->label28->Visible=false;
				 }
*/
			 }
	private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
				 strcpy(buff[numref[3]][0],addthis);
				 strcpy(buff[numref[3]][1],addthis);
				 strcpy(buff[numref[3]][2],addthis);
				 strcpy(buff[numref[3]][3],addthis);
				 strcpy(buff[numref[3]][4],addthis);
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();

				 this->groupBox2->Visible=false;
				 this->groupBox3->Visible=false;
				 this->groupBox4->Visible=false;
				 this->groupBox5->Visible=false;
				 this->groupBox6->Visible=false;
				 this->button2->Visible=false;
				 this->button3->Visible=false;
				 this->button4->Visible=false;
				 this->button5->Visible=false;
				 this->button6->Visible=false;
				 this->button7->Visible=false;
				 this->button8->Visible=false;
				 this->button9->Visible=false;
				 this->button10->Visible=false;
				 this->button11->Visible=false;
				 this->button12->Visible=false;
				 this->button13->Visible=false;
				 this->button14->Visible=false;
				 this->button15->Visible=false;
				 this->button16->Visible=false;
				 this->button4->Text="Check";
				 this->button5->Text="Check";
				 this->button8->Text="Check";
				 this->button11->Text="Check";
				 this->button14->Text="Check";
				 evecreate();
				 //managed code for recreating after delete
				 switch(num)
				 {
				 case 0:
					 {
						 break;
					 }
				 case 1:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;

						 if(eve[0].getloe()==1)
						 {
							 radioButton6->Checked=true;
						 }
						 if(eve[0].getloe()==2)
						 {
							 radioButton7->Checked=true;
						 }
						 if(eve[0].getloe()==3)
						 {
							 radioButton8->Checked=true;
						 }
						 if(eve[0].getloe()==4)
						 {
							 this->button4->Text="Uncheck";
						 }

						 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
						 load1[0]=load[0];
						 load1[1]=load[1];
						 load2[0]=load[2];
						 load2[1]=load[3];
						 load3[0]=load[5];
						 load3[1]=load[6];
						 load4[0]=load[7];
						 load4[1]=load[8];
						 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
						 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
						 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
						 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
						 this->textBox2->Text = Load1;
						 this->textBox3->Text = Load2;
						 this->textBox4->Text = Load3;
						 this->textBox5->Text = Load4;
						 break;
					 }
				 case 2:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 break;
					 }
				 case 3:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;


						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }




						 break;
					 }
				 case 4:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;






						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }




						 break;
					 }
				 case 5:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;
						 this->groupBox6->Visible = true;
						 this->button14->Visible = true;
						 this->button15->Visible = true;
						 this->button16->Visible = true;
						 char*message5=eve[4].getname();
						 String ^ mmg5 = Marshal::PtrToStringAnsi((IntPtr)message5);
						 this->groupBox6->Text = mmg5;



						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }


						 {	  	
							 if(eve[4].getloe()==1)
							 {
								 radioButton20->Checked=true;
							 }
							 if(eve[4].getloe()==2)
							 {
								 radioButton19->Checked=true;
							 }
							 if(eve[4].getloe()==3)
							 {
								 radioButton18->Checked=true;
							 }
							 if(eve[4].getloe()==4)
							 {
								 this->button14->Text="Uncheck";
							 }

							 char*load=eve[4].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox21->Text = Load1;
							 this->textBox20->Text = Load2;
							 this->textBox19->Text = Load3;
							 this->textBox18->Text = Load4;
						 }



						 break;
					 }
				 }


/*
				 if( this->label27->Visible ==true)
				 {
					 this->label27->Visible=false;
					 this->label28->Visible=false;
				 }
*/			 }
	private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
				 strcpy(buff[numref[4]][0],addthis);
				 strcpy(buff[numref[4]][1],addthis);
				 strcpy(buff[numref[4]][2],addthis);
				 strcpy(buff[numref[4]][3],addthis);
				 strcpy(buff[numref[4]][4],addthis);
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();

				 this->groupBox2->Visible=false;
				 this->groupBox3->Visible=false;
				 this->groupBox4->Visible=false;
				 this->groupBox5->Visible=false;
				 this->groupBox6->Visible=false;
				 this->button2->Visible=false;
				 this->button3->Visible=false;
				 this->button4->Visible=false;
				 this->button5->Visible=false;
				 this->button6->Visible=false;
				 this->button7->Visible=false;
				 this->button8->Visible=false;
				 this->button9->Visible=false;
				 this->button10->Visible=false;
				 this->button11->Visible=false;
				 this->button12->Visible=false;
				 this->button13->Visible=false;
				 this->button14->Visible=false;
				 this->button15->Visible=false;
				 this->button4->Text="Check";
				 this->button5->Text="Check";
				 this->button8->Text="Check";
				 this->button11->Text="Check";
				 this->button14->Text="Check";
				 this->button16->Visible=false;

				 evecreate();
				 //managed code for recreating after delete

				 switch(num)
				 {
				 case 0:
					 {
						 break;
					 }
				 case 1:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;

						 if(eve[0].getloe()==1)
						 {
							 radioButton6->Checked=true;
						 }
						 if(eve[0].getloe()==2)
						 {
							 radioButton7->Checked=true;
						 }
						 if(eve[0].getloe()==3)
						 {
							 radioButton8->Checked=true;
						 }
						 if(eve[0].getloe()==4)
						 {
							 this->button4->Text="Uncheck";
						 }

						 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
						 load1[0]=load[0];
						 load1[1]=load[1];
						 load2[0]=load[2];
						 load2[1]=load[3];
						 load3[0]=load[5];
						 load3[1]=load[6];
						 load4[0]=load[7];
						 load4[1]=load[8];
						 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
						 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
						 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
						 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
						 this->textBox2->Text = Load1;
						 this->textBox3->Text = Load2;
						 this->textBox4->Text = Load3;
						 this->textBox5->Text = Load4;
						 break;
					 }
				 case 2:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 break;
					 }
				 case 3:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;


						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }




						 break;
					 }
				 case 4:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;






						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }




						 break;
					 }
				 case 5:
					 {
						 this->groupBox2->Visible = true;
						 this->button2->Visible = true;
						 this->button3->Visible = true;
						 this->button4->Visible = true;
						 char*message=eve[0].getname();
						 String ^ mmg = Marshal::PtrToStringAnsi((IntPtr)message);
						 this->groupBox2->Text = mmg;
						 this->groupBox3->Visible = true;
						 this->button5->Visible = true;
						 this->button6->Visible = true;
						 this->button7->Visible = true;
						 char*message2=eve[1].getname();
						 String ^ mmg2 = Marshal::PtrToStringAnsi((IntPtr)message2);
						 this->groupBox3->Text = mmg2;
						 this->groupBox4->Visible = true;
						 this->button8->Visible = true;
						 this->button9->Visible = true;
						 this->button10->Visible = true;
						 char*message3=eve[2].getname();
						 String ^ mmg3 = Marshal::PtrToStringAnsi((IntPtr)message3);
						 this->groupBox4->Text = mmg3;
						 this->groupBox5->Visible = true;
						 this->button11->Visible = true;
						 this->button12->Visible = true;
						 this->button13->Visible = true;
						 char*message4=eve[3].getname();
						 String ^ mmg4 = Marshal::PtrToStringAnsi((IntPtr)message4);
						 this->groupBox5->Text = mmg4;
						 this->groupBox6->Visible = true;
						 this->button14->Visible = true;
						 this->button15->Visible = true;
						 this->button16->Visible = true;
						 char*message5=eve[4].getname();
						 String ^ mmg5 = Marshal::PtrToStringAnsi((IntPtr)message5);
						 this->groupBox6->Text = mmg5;



						 {

							 if(eve[0].getloe()==1)
							 {
								 radioButton6->Checked=true;
							 }
							 if(eve[0].getloe()==2)
							 {
								 radioButton7->Checked=true;
							 }
							 if(eve[0].getloe()==3)
							 {
								 radioButton8->Checked=true;
							 }
							 if(eve[0].getloe()==4)
							 {
								 this->button4->Text="Uncheck";
							 }

							 char*load=eve[0].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox2->Text = Load1;
							 this->textBox3->Text = Load2;
							 this->textBox4->Text = Load3;
							 this->textBox5->Text = Load4;
						 }
						 {	  	
							 if(eve[1].getloe()==1)
							 {
								 radioButton11->Checked=true;
							 }
							 if(eve[1].getloe()==2)
							 {
								 radioButton10->Checked=true;
							 }
							 if(eve[1].getloe()==3)
							 {
								 radioButton9->Checked=true;
							 }
							 if(eve[1].getloe()==4)
							 {
								 this->button5->Text="Uncheck";
							 }

							 char*load=eve[1].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox9->Text = Load1;
							 this->textBox8->Text = Load2;
							 this->textBox7->Text = Load3;
							 this->textBox6->Text = Load4;
						 }
						 {	  	
							 if(eve[2].getloe()==1)
							 {
								 radioButton14->Checked=true;
							 }
							 if(eve[2].getloe()==2)
							 {
								 radioButton13->Checked=true;
							 }
							 if(eve[2].getloe()==3)
							 {
								 radioButton12->Checked=true;
							 }
							 if(eve[2].getloe()==4)
							 {
								 this->button8->Text="Uncheck";
							 }

							 char*load=eve[2].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox13->Text = Load1;
							 this->textBox12->Text = Load2;
							 this->textBox11->Text = Load3;
							 this->textBox10->Text = Load4;
						 }
						 {	  	
							 if(eve[3].getloe()==1)
							 {
								 radioButton17->Checked=true;
							 }
							 if(eve[3].getloe()==2)
							 {
								 radioButton16->Checked=true;
							 }
							 if(eve[3].getloe()==3)
							 {
								 radioButton15->Checked=true;
							 }
							 if(eve[3].getloe()==4)
							 {
								 this->button11->Text="Uncheck";
							 }

							 char*load=eve[3].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox17->Text = Load1;
							 this->textBox16->Text = Load2;
							 this->textBox15->Text = Load3;
							 this->textBox14->Text = Load4;
						 }


						 {	  	
							 if(eve[4].getloe()==1)
							 {
								 radioButton20->Checked=true;
							 }
							 if(eve[4].getloe()==2)
							 {
								 radioButton19->Checked=true;
							 }
							 if(eve[4].getloe()==3)
							 {
								 radioButton18->Checked=true;
							 }
							 if(eve[4].getloe()==4)
							 {
								 this->button14->Text="Uncheck";
							 }

							 char*load=eve[4].gettime() ,load1[]="00",load2[]="00",load3[]="00",load4[]="00";
							 load1[0]=load[0];
							 load1[1]=load[1];
							 load2[0]=load[2];
							 load2[1]=load[3];
							 load3[0]=load[5];
							 load3[1]=load[6];
							 load4[0]=load[7];
							 load4[1]=load[8];
							 String ^ Load1 = Marshal::PtrToStringAnsi((IntPtr)load1);
							 String ^ Load2 = Marshal::PtrToStringAnsi((IntPtr)load2);
							 String ^ Load3 = Marshal::PtrToStringAnsi((IntPtr)load3);
							 String ^ Load4 = Marshal::PtrToStringAnsi((IntPtr)load4);
							 this->textBox21->Text = Load1;
							 this->textBox20->Text = Load2;
							 this->textBox19->Text = Load3;
							 this->textBox18->Text = Load4;
						 }



						 break;
					 }
				 }


/*
				 if( this->label27->Visible ==true)
				 {
					 this->label27->Visible=false;
					 this->label28->Visible=false;
				 }
*/
			 }
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
				 int a=4;
				 int b=0;
				 if (String::Compare(this->button4->Text, "Uncheck") == 0)
				 {
					 this->button4->Text="Check";
					 eve[0].setloe(b);
					 strcpy(buff[numref[0]][2],"0");
				 }
				 else
				 {
					 this->button4->Text="Uncheck";
					 this->radioButton6->Checked=false;
					 this->radioButton7->Checked=false;
					 this->radioButton8->Checked=false;
					 eve[0].setloe(a);
					 strcpy(buff[numref[0]][2],"4");
				 }
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
			 }
	private: System::Void label29_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label32_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
				 int a=4;
				 int b=0;
				 if (String::Compare(this->button5->Text, "Uncheck") == 0)
				 {
					 this->button5->Text = "Check";
					 eve[1].setloe(b);
					 strcpy(buff[numref[1]][2],"0");
				 }
				 else
				 {
					 this->button5->Text = "Uncheck";
					 this->radioButton9->Checked=false;
					 this->radioButton10->Checked=false;
					 this->radioButton11->Checked=false;
					 eve[1].setloe(a);
					 strcpy(buff[numref[1]][2],"4");
				 }
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
			 }
	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {

				 int a=4;
				 int b=0;
				 if (String::Compare(this->button8->Text, "Uncheck") == 0)
				 {
					 this->button8->Text = "Check";
					 eve[2].setloe(b);
					 strcpy(buff[numref[2]][2],"0");
				 }
				 else
				 {
					 this->button8->Text = "Uncheck";
					 this->radioButton14->Checked=false;
					 this->radioButton13->Checked=false;
					 this->radioButton12->Checked=false;
					 eve[2].setloe(a);
					 strcpy(buff[numref[2]][2],"4");
				 }
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
			 }
	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {

				 int a=4;
				 int b=0;
				 if (String::Compare(this->button11->Text, "Uncheck") == 0)
				 {
					 this->button11->Text = "Check";
					 eve[3].setloe(b);
					 strcpy(buff[numref[3]][2],"0");
				 }
				 else
				 {
					 this->button11->Text = "Uncheck";
					 this->radioButton15->Checked=false;
					 this->radioButton16->Checked=false;
					 this->radioButton17->Checked=false;
					 eve[3].setloe(a);
					 strcpy(buff[numref[3]][2],"4");
				 }
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
			 }
	private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {

				 int a=4;
				 int b=0;
				 if (String::Compare(this->button14->Text, "Uncheck") == 0)
				 {
					 this->button14->Text = "Check";
					 eve[4].setloe(b);
					 strcpy(buff[numref[4]][2],"0");
				 }
				 else
				 {
					 this->button14->Text = "Uncheck";
					 this->radioButton18->Checked=false;
					 this->radioButton19->Checked=false;
					 this->radioButton20->Checked=false;
					 eve[4].setloe(a);
					 strcpy(buff[numref[4]][2],"4");
				 }
				 int i=0,j=0;
				 ofstream fout(filename,ios::trunc);
				 while(i<a)
				 {
					 fout<<buff[i][j]<<endl;
					 if(j<4)
						 j++;
					 else
					 {
						 j=0;
						 i++;
					 }
				 }
				 fout.close();
			 }
	private: System::Void int_only_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08){//0x08 = backspace
					 e->Handled = true;
				 }
			 }
			 //When clicked, select everthing to allow user input easily
	private: System::Void select_all_Click(System::Object^  sender, System::EventArgs^  e) {
				 TextBox ^ tBox = safe_cast<TextBox^>(sender);
				 tBox->SelectAll();		 
			 }
	};
}

