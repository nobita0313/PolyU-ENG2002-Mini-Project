#pragma once
#include <stdlib.h>
#include <string.h>
namespace Calendar {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for stat_form
	/// </summary>
	public ref class stat_form : public System::Windows::Forms::Form
	{
	public:
		stat_form(int year, char *** buff)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			thisYear = year;
			events = buff;
			
			char charY[5];
			int c1 = 0, c2 = 0,c3 = 0, c4 = 0, c5 = 0;

			itoa(thisYear, charY, 10);

			for(int i=0; i<1000; i++){
				if(events[i][0][0]==charY[0] && events[i][0][1]==charY[1] && events[i][0][2]==charY[2] && events[i][0][3]==charY[3]){
					switch(events[i][3][0]){
					case '1': c1++; break;
					case '2': c2++; break;
					case '3': c3++; break;
					case '4': c4++; break;
					case '5': c5++; break;
					default: break;
					}
				}
			}

			//Clear default setting
			chart1->Series->Clear();

			//Chart settings
			chart1->Series->Add("Series1");
            Title^ title = gcnew Title();
            title->Text = "Summary of " + thisYear;
            title->Alignment = ContentAlignment::MiddleCenter;
            title->Font = gcnew System::Drawing::Font("Segoe UI Light", 35.0F);
            chart1->Titles->Add(title);

            //ChartArea setting
            chart1->ChartAreas["ChartArea1"]->Area3DStyle->Enable3D = true; //3D effect
            chart1->ChartAreas["ChartArea1"]->Area3DStyle->Rotation = 40; //Set angle of view
            chart1->ChartAreas["ChartArea1"]->Area3DStyle->Inclination = 50; //Set angle of view
            chart1->ChartAreas["ChartArea1"]->Area3DStyle->PointDepth = 30; //Set thickness of bar
            chart1->ChartAreas["ChartArea1"]->Area3DStyle->WallWidth = 0; //Set thickness of wall
            chart1->ChartAreas["ChartArea1"]->Area3DStyle->LightStyle = LightStyle::Realistic; //Ligthing
            chart1->ChartAreas["ChartArea1"]->BackColor = Color::FromArgb(240, 240, 240);
            //Y axis color
            chart1->ChartAreas["ChartArea1"]->AxisY->MajorGrid->LineColor = Color::FromArgb(150, 150, 150);
            //X axis color
            chart1->ChartAreas["ChartArea1"]->AxisX->MajorGrid->LineColor = Color::FromArgb(150, 150, 150); 
            chart1->ChartAreas["ChartArea1"]->AxisY->LabelStyle->Format = "#,###";//Number format

			
			chart1->Series[0]->ChartType = SeriesChartType::Column;

			chart1->Series[0]->Points->AddXY("Shopping", c1);
			chart1->Series[0]->Points->AddXY("Study", c2);
			chart1->Series[0]->Points->AddXY("Date", c3);
			chart1->Series[0]->Points->AddXY("Sporting", c4);
			chart1->Series[0]->Points->AddXY("Brithday", c5);
            chart1->Series[0]->LabelFormat = "#,###"; //Number format
            chart1->Series[0]->MarkerSize = 8; //Label size
            chart1->Series[0]->LabelForeColor = Color::FromArgb(0, 90, 255); 
            chart1->Series[0]->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F, FontStyle::Bold);

            //Label setting
            chart1->Series[0]->LabelBackColor = Color::FromArgb(150, 255, 255, 255); 
            chart1->Series[0]->Color = Color::FromArgb(240, 65, 140, 240); 
            chart1->Series[0]->IsValueShownAsLabel = true; // Show data points labels
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~stat_form()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		char *** events;





	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
			 int thisYear;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			this->chart1->BackColor = System::Drawing::Color::Transparent;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(22, 35);
			this->chart1->Margin = System::Windows::Forms::Padding(2);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(600, 350);
			this->chart1->TabIndex = 5;
			this->chart1->Text = L"chart1";
			// 
			// stat_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(644, 421);
			this->Controls->Add(this->chart1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"stat_form";
			this->Text = L"Statistics";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
