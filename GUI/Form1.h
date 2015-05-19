#pragma once

#include "FunctionModule.h"

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace FunctionModule;

	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:

		static String^ NO_DEVICE_FOUND = gcnew String("No Device Found! PlugIn and Try Again!");
		static String^ START_RANDOM_COLLECTION = gcnew String("BD2A00011385");
		static int RET_FRAME_HEAD_LENGTH = 4;
		static int RET_ERR_SUB_CODE_LENGTH = 2;

		static String^ RET_SUCESS = "BD2A";
		static String^ RET_ERROR = "BDF0";
		static String^ TAG_NO_RESPONSE = "FFFF";
		static String^ TAG_CONFLICT_RESPONSE = "FFF0";
		static String^ TAG_ILLEGAL_RESPONSE = "FF00";
		static String^ TAG_UNKNOWN_RESPONSE = "F000";
		static String^ TAG_ERR_RESPONSE_IS = "标签返回错误码：";
		static byte	   TAG_ERR_RESPONSE_IS_CODE = 0x01;

		CP210x_STATUS nStatus;
		ComPortDevice^ ComPort;

		String^ strComPort;
		String^ strRetHeadType;
		String^ strErrSubCode;
	
		DWORD dwDeviceNum;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//

			nStatus = 0xFFFF;
			ComPort = gcnew ComPortDevice();
			strComPort = gcnew String("");
			strRetHeadType = gcnew String("");
			strErrSubCode = gcnew String("");

			dwDeviceNum = 0;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBoxComList;
	protected: 

	private: System::Windows::Forms::Button^  btnOpenCom;
	private: System::Windows::Forms::Button^  btnCloseCom;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  btnStartCollect;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxProcessBar;
    private: System::Windows::Forms::Button^  btnStopCollect;



	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxComList = (gcnew System::Windows::Forms::ComboBox());
			this->btnOpenCom = (gcnew System::Windows::Forms::Button());
			this->btnCloseCom = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->btnStartCollect = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxProcessBar = (gcnew System::Windows::Forms::TextBox());
			this->btnStopCollect = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"选择端口";
			// 
			// comboBoxComList
			// 
			this->comboBoxComList->FormattingEnabled = true;
			this->comboBoxComList->Location = System::Drawing::Point(71, 9);
			this->comboBoxComList->Name = L"comboBoxComList";
			this->comboBoxComList->Size = System::Drawing::Size(313, 20);
			this->comboBoxComList->TabIndex = 1;
			this->comboBoxComList->DropDown += gcnew System::EventHandler(this, &Form1::comboBoxComList_DropDown);
			this->comboBoxComList->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBoxComList_SelectedIndexChanged);
			// 
			// btnOpenCom
			// 
			this->btnOpenCom->Location = System::Drawing::Point(14, 47);
			this->btnOpenCom->Name = L"btnOpenCom";
			this->btnOpenCom->Size = System::Drawing::Size(74, 23);
			this->btnOpenCom->TabIndex = 2;
			this->btnOpenCom->Text = L"打开端口";
			this->btnOpenCom->UseVisualStyleBackColor = true;
			this->btnOpenCom->Click += gcnew System::EventHandler(this, &Form1::btnOpenCom_Click);
			// 
			// btnCloseCom
			// 
			this->btnCloseCom->Location = System::Drawing::Point(95, 47);
			this->btnCloseCom->Name = L"btnCloseCom";
			this->btnCloseCom->Size = System::Drawing::Size(75, 23);
			this->btnCloseCom->TabIndex = 3;
			this->btnCloseCom->Text = L"关闭端口";
			this->btnCloseCom->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(13, 93);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(371, 255);
			this->textBox1->TabIndex = 4;
			// 
			// btnStartCollect
			// 
			this->btnStartCollect->Location = System::Drawing::Point(204, 47);
			this->btnStartCollect->Name = L"btnStartCollect";
			this->btnStartCollect->Size = System::Drawing::Size(87, 23);
			this->btnStartCollect->TabIndex = 5;
			this->btnStartCollect->Text = L"开始采集";
			this->btnStartCollect->UseVisualStyleBackColor = true;
			this->btnStartCollect->Click += gcnew System::EventHandler(this, &Form1::btnStartCollect_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(92, 360);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(100, 16);
			this->progressBar1->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(11, 362);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 12);
			this->label2->TabIndex = 7;
			this->label2->Text = L"单次采集进度";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(223, 362);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(77, 12);
			this->label3->TabIndex = 8;
			this->label3->Text = L"总体采集进度";
			// 
			// textBoxProcessBar
			// 
			this->textBoxProcessBar->Location = System::Drawing::Point(309, 358);
			this->textBoxProcessBar->Name = L"textBoxProcessBar";
			this->textBoxProcessBar->Size = System::Drawing::Size(75, 21);
			this->textBoxProcessBar->TabIndex = 9;
			this->textBoxProcessBar->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnStopCollect
			// 
			this->btnStopCollect->Location = System::Drawing::Point(298, 47);
			this->btnStopCollect->Name = L"btnStopCollect";
			this->btnStopCollect->Size = System::Drawing::Size(87, 23);
			this->btnStopCollect->TabIndex = 10;
			this->btnStopCollect->Text = L"停止采集";
			this->btnStopCollect->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(397, 393);
			this->Controls->Add(this->btnStopCollect);
			this->Controls->Add(this->textBoxProcessBar);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->btnStartCollect);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->btnCloseCom);
			this->Controls->Add(this->btnOpenCom);
			this->Controls->Add(this->comboBoxComList);
			this->Controls->Add(this->label1);
			this->Name = L"Form1";
			this->Text = L"随机数采集软件";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	

private: System::Void comboBoxComList_DropDown(System::Object^  sender, System::EventArgs^  e) {

			 comboBoxComList->Items->Clear();
			 nStatus = ComPort->ComPort_GetDeviceList();
			 if(nStatus != CP210x_SUCCESS){
				 MessageBox::Show(NO_DEVICE_FOUND);
				 return;
			 }
			 for(int i = 0; ComPort->strDevList[i] != nullptr; i ++){
				 comboBoxComList->Items->Add(ComPort->strDevList[i]);
			 }

		 }


private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

			 btnOpenCom->Enabled = false;
			 btnCloseCom->Enabled = false;
			 btnStartCollect->Enabled = false;
			 btnStopCollect->Enabled = false;
		 }


private: System::Void comboBoxComList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

			 if(comboBoxComList->SelectedItem->ToString() != nullptr){
				 strComPort = comboBoxComList->SelectedItem->ToString();
				 btnOpenCom->Enabled = true;
			 }
		 }


private: System::Void btnOpenCom_Click(System::Object^  sender, System::EventArgs^  e) {

			 bool bRet = false;

			 if(ComPort->hDevHandle == 0){
				 nStatus = ComPort->ComPort_Open(strComPort);
				 if(CP210x_SUCCESS == nStatus){
					 textBox1->AppendText("### Open COM Sucess!###");
					 btnOpenCom->Enabled = false;
					 btnCloseCom->Enabled = true;
					 btnStartCollect->Enabled = true;
					 
				 }else{
					 MessageBox::Show("Open COM Failed! Please ReConnect Device.");
					 btnOpenCom->Enabled = false;
					 btnCloseCom->Enabled = false;
					 btnStartCollect->Enabled = false;
					 btnStopCollect->Enabled = false;
				 }
			 }
			 
			 
			 
		 }
private: System::Void btnStartCollect_Click(System::Object^  sender, System::EventArgs^  e) {

			 nStatus = ComPort->ComPort_Write(START_RANDOM_COLLECTION);
			 if(CP210x_SUCCESS != nStatus){
				 MessageBox::Show("Send Collect Random CMD Failed!");
				 return;
			 }

			 Start_RandomCollect();

		 }

	private: System::Void Start_RandomCollect(){

			bRet = ComPort->ComPort_Read(RET_FRAME_HEAD_LENGTH);
			if(!bRet){
				MessageBox::Show("Read Data Failed!");
				return;
			}

			strRetHeadType = Convert::ToString(ComPort->byRet[0], 16) + 
				Convert::ToString(ComPort->byRet[1], 16);

			Return_Data_Process(strRetHeadType);

		 }

	private: System::Void Return_Data_Process(String^ strRet){
			 
				 if(!strResault->Equals(RET_SUCESS)&&!strRetHeadType->Equals(RET_ERROR)){
					 MessageBox::Show("Collect Random Unknown Err!");
					 return;
				 }
				 if(strResault->Equals(RET_ERROR)){
					 bRet = ComPort->ComPort_Read(RET_ERR_SUB_CODE_LENGTH);
					 if(!bRet){
						 MessageBox::Show("Read Err Sub Code Failed!");
						 return;
					 }

					 if(TAG_ERR_RESPONSE_IS_CODE == ComPort->byRet[0]){				 
						 MessageBox::Show(TAG_ERR_RESPONSE_IS + Convert::ToString(ComPort->byRet[1], 16));
						 return
					 }

					 strErrSubCode = Convert::ToString(ComPort->byRet[0], 16) + 
						 Convert::ToString(ComPort->byRet[1], 16);
					 if(strResault->Equals(TAG_UNKNOWN_RESPONSE))
				 }else{

				 }
			 
			 }


};
}

