#pragma once

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
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
			this->comboBoxComList->Size = System::Drawing::Size(121, 20);
			this->comboBoxComList->TabIndex = 1;
			// 
			// btnOpenCom
			// 
			this->btnOpenCom->Location = System::Drawing::Point(214, 8);
			this->btnOpenCom->Name = L"btnOpenCom";
			this->btnOpenCom->Size = System::Drawing::Size(75, 23);
			this->btnOpenCom->TabIndex = 2;
			this->btnOpenCom->Text = L"打开端口";
			this->btnOpenCom->UseVisualStyleBackColor = true;
			// 
			// btnCloseCom
			// 
			this->btnCloseCom->Location = System::Drawing::Point(309, 8);
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
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(371, 255);
			this->textBox1->TabIndex = 4;
			// 
			// btnStartCollect
			// 
			this->btnStartCollect->Location = System::Drawing::Point(139, 48);
			this->btnStartCollect->Name = L"btnStartCollect";
			this->btnStartCollect->Size = System::Drawing::Size(114, 30);
			this->btnStartCollect->TabIndex = 5;
			this->btnStartCollect->Text = L"开始采集";
			this->btnStartCollect->UseVisualStyleBackColor = true;
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
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(397, 393);
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
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}

