#pragma once
#include "registration_form.h"
#include <fstream>
#include <string.h>

namespace Calendar {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for login_form
	/// </summary>
	public ref class login_form : public System::Windows::Forms::Form
	{
	public:
		String^ userName;
		login_form(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			loginFlag = false;
			this->AcceptButton = button1;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~login_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: bool loginFlag;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button1;


	private: System::Windows::Forms::Button^  button2;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(login_form::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(78, 31);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Username:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(80, 55);
			this->textBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->textBox1->MaxLength = 15;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(268, 26);
			this->textBox1->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(78, 105);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Password:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(80, 129);
			this->textBox2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->textBox2->MaxLength = 15;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(268, 26);
			this->textBox2->TabIndex = 3;
			this->textBox2->UseSystemPasswordChar = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(80, 186);
			this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(112, 35);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Login";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &login_form::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(237, 186);
			this->button2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(112, 35);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Register";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &login_form::button2_Click);
			// 
			// login_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(426, 248);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"login_form";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Login";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &login_form::login_form_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		//			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 char message [100]="Hello ";
				 String^tbstr=textBox1->Text ;
				 char*name=(char*)Marshal::StringToHGlobalAnsi(tbstr).ToPointer();
				 String^tbstr2=textBox2->Text ;
				 char*pass=(char*)Marshal::StringToHGlobalAnsi(tbstr2).ToPointer();
				 strcat(message,name);
				 String^Mmge=Marshal::PtrToStringAnsi((IntPtr)message);
				 String^title="Welcome!";
				 String^title2="Wrong Password or Username dosen't exist";
				 String^message2="Please input your password again or sign up";
				 char buff[31];
				 strcpy (buff,name);
				 strcat (buff,",");
				 strcat (buff,pass);
				 ifstream fin(".\\db\\users.txt");
				 char a[31];
				 int i;
				 while(fin.getline(a,31))
				 {
				 if (strcmp(a,buff)==0)
				 {	i=0;
				 break;
				 }
				 else
				 {
					 i=1;
					 continue;

				 }
				 }

				 if(i==1)
				 {
					 MessageBox::Show(message2,title2);
				 }
				 else
				 {

					 MessageBox::Show(Mmge,title);
					 userName = textBox1->Text;
					 loginFlag = true;
					 Close();
				 }


			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 registration_form ^ RForm = gcnew registration_form(this);
				 RForm->ShowDialog(); 
			 }
	private: System::Void login_form_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 if (!loginFlag){
					 Application::Exit();
				 }
			 }
	};
}
