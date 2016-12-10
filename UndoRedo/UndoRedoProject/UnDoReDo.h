#pragma once
#include"MyException.h"
#include"UndoableEditEvent.h"
#include"UndoRedoComponent.h"
#include"UndoableEditSupport.h"
#include"MyPoint.h"
#include"DrawLineEdit.h"
namespace UndoRedoProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Runtime::InteropServices;
	/// <summary>
	/// UnDoReDo ժҪ
	/// </summary>
	public ref class UnDoReDo : public System::Windows::Forms::Form
	{
	public:
		UnDoReDo(void)
		{
			InitializeComponent();
			//
			//TODO:  �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~UnDoReDo()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  drawMap;

	//���ߵ�׼����������ʼ������������
	private:Point orignalPoint;
	private:Point aimPoint;
	private:Point processPoint;
	private:Bitmap^ bitmap;
	private:Pen^ pen;
	private:Graphics^ g;
	private:bool mouseIsDown = false;
	private:Pen^ earsePen;
	private:UndoRedoEditSupport* editSupport;
	private:UndoManager* undoManager;
	//�洢��ǰ�������е���
	private:vector<MyLine*>*lines;
	private: System::Windows::Forms::Button^  undoButton;
	private: System::Windows::Forms::Button^  redoButton;
			 //	private:vector<pair<Point, Point>*>*lines;


	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  undoStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  redoStrip;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  �༭ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  undoItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redoItem;
	private: System::ComponentModel::IContainer^  components;
	protected:

	protected:

	private:

		/// <summary>
		/// ����������������
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->drawMap = (gcnew System::Windows::Forms::PictureBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->undoStrip = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoStrip = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoButton = (gcnew System::Windows::Forms::Button());
			this->redoButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->�༭ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawMap))->BeginInit();
			this->contextMenuStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// drawMap
			// 
			this->drawMap->ContextMenuStrip = this->contextMenuStrip1;
			this->drawMap->Location = System::Drawing::Point(0, 31);
			this->drawMap->Name = L"drawMap";
			this->drawMap->Size = System::Drawing::Size(1278, 445);
			this->drawMap->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->drawMap->TabIndex = 0;
			this->drawMap->TabStop = false;
			this->drawMap->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UnDoReDo::drawMap_MouseDown);
			this->drawMap->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &UnDoReDo::drawMap_MouseMove);
			this->drawMap->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UnDoReDo::drawMap_MouseUp);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->undoStrip,
					this->redoStrip
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(214, 56);
			// 
			// undoStrip
			// 
			this->undoStrip->Name = L"undoStrip";
			this->undoStrip->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::Z));
			this->undoStrip->Size = System::Drawing::Size(213, 26);
			this->undoStrip->Text = L"����";
			this->undoStrip->Click += gcnew System::EventHandler(this, &UnDoReDo::undoStrip_Click);
			// 
			// redoStrip
			// 
			this->redoStrip->Name = L"redoStrip";
			this->redoStrip->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::Y));
			this->redoStrip->Size = System::Drawing::Size(213, 26);
			this->redoStrip->Text = L"����";
			this->redoStrip->Click += gcnew System::EventHandler(this, &UnDoReDo::redoStrip_Click);
			// 
			// undoButton
			// 
			this->undoButton->Location = System::Drawing::Point(12, 482);
			this->undoButton->Name = L"undoButton";
			this->undoButton->Size = System::Drawing::Size(95, 38);
			this->undoButton->TabIndex = 2;
			this->undoButton->Text = L"����";
			this->undoButton->UseVisualStyleBackColor = true;
			this->undoButton->Click += gcnew System::EventHandler(this, &UnDoReDo::undo_Click);
			// 
			// redoButton
			// 
			this->redoButton->Location = System::Drawing::Point(125, 484);
			this->redoButton->Name = L"redoButton";
			this->redoButton->Size = System::Drawing::Size(107, 35);
			this->redoButton->TabIndex = 3;
			this->redoButton->Text = L"����";
			this->redoButton->UseVisualStyleBackColor = true;
			this->redoButton->Click += gcnew System::EventHandler(this, &UnDoReDo::redo_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->�༭ToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1281, 28);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// �༭ToolStripMenuItem
			// 
			this->�༭ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->undoItem,
					this->redoItem
			});
			this->�༭ToolStripMenuItem->Name = L"�༭ToolStripMenuItem";
			this->�༭ToolStripMenuItem->Size = System::Drawing::Size(51, 24);
			this->�༭ToolStripMenuItem->Text = L"�༭";
			// 
			// undoItem
			// 
			this->undoItem->Name = L"undoItem";
			this->undoItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
			this->undoItem->Size = System::Drawing::Size(169, 26);
			this->undoItem->Text = L"����";
			this->undoItem->Click += gcnew System::EventHandler(this, &UnDoReDo::undoItem_Click);
			// 
			// redoItem
			// 
			this->redoItem->Name = L"redoItem";
			this->redoItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Y));
			this->redoItem->Size = System::Drawing::Size(169, 26);
			this->redoItem->Text = L"����";
			this->redoItem->Click += gcnew System::EventHandler(this, &UnDoReDo::redoItem_Click);
			// 
			// UnDoReDo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1281, 529);
			this->Controls->Add(this->redoButton);
			this->Controls->Add(this->undoButton);
			this->Controls->Add(this->drawMap);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"UnDoReDo";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UnDoReDo";
			this->Load += gcnew System::EventHandler(this, &UnDoReDo::UnDoReDo_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->drawMap))->EndInit();
			this->contextMenuStrip1->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void UnDoReDo_Load(System::Object^  sender, System::EventArgs^  e) {
		editSupport = new UndoRedoEditSupport();
		undoManager = new UndoManager();
		//��Ӽ�����
		editSupport->addUndoableEditListener(undoManager);
		lines = new vector<MyLine*>();


		//��ʼ���������ʣ���ť��Ϣ
		pen = gcnew Pen(Color::Black , 0.5);
		earsePen = gcnew Pen(drawMap->BackColor,1);
		bitmap = gcnew Bitmap(drawMap->Width, drawMap->Height);
		drawMap->Image = bitmap;
		g = Graphics::FromImage(bitmap);
		setCanRedo();
		setCanUndo();
		
	}


	//�жϵ�ǰ��״̬���Ƿ����Redo
	private: void setCanRedo()
	{
		redoButton->Enabled = undoManager->canRedo();
		redoItem->Enabled = undoManager->canRedo();
		redoStrip->Enabled = undoManager->canRedo();
	}

	//�жϵ�ǰ��״̬���Ƿ����Undo
	private:void setCanUndo()
	{
		undoButton->Enabled = undoManager->canUndo();
		undoItem->Enabled = undoManager->canUndo();
		undoStrip->Enabled = undoManager->canUndo();
	}

	//����ڻ����ϵ���󴥷����¼�
	private: System::Void drawMap_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		orignalPoint = e->Location;
		processPoint = e->Location;
		mouseIsDown = true;
	}
    
	//����ڻ������ƶ��󴥷����¼�
	private: System::Void drawMap_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (mouseIsDown == false) return;
		Graphics^ g = getGraphics();
		g->DrawLine(earsePen, orignalPoint, processPoint);
		g->DrawLine(pen, orignalPoint, e->Location);
		processPoint = e->Location;
	}
			 //����ڻ������ɿ���ť�������¼�
	private: System::Void drawMap_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			mouseIsDown = false;
			MyLine* line = new MyLine(new MyPoint(orignalPoint.X, orignalPoint.Y),new MyPoint(e->Location.X,e->Location.Y));
			
			//��һ�����ߵı༭�������͸�������
			editSupport->postEdit(new DrawLineEdit(lines, line));
			setCanUndo();
			setCanRedo();
	
	}

	private:Graphics^ getGraphics()
	{
		bitmap = gcnew Bitmap(bitmap);
		drawMap->Image = bitmap;
		return Graphics::FromImage(bitmap);
	}
	private:void clearDrawMap()
	{
		Graphics^ g = getGraphics();
		g->Clear(drawMap->BackColor);
	}

	private:void redraw()
	{
		clearDrawMap();
		Graphics^ g = getGraphics();
		vector<MyLine*>::iterator iter = lines->begin();
		for (; iter != lines->end(); iter++)
		{
			g->DrawLine(pen, Point((*iter)->getStartPoint()->getX(), (*iter)->getStartPoint()->getY()),
				Point((*iter)->getEndPoint()->getX(),(*iter)->getEndPoint()->getY()));
		}
	}
			//��������
	private:void myUndo()
	{
		try
		{
			undoManager->undo();
			redraw();
			setCanRedo();
			setCanUndo();
		}
		catch (MyException* e)
		{
			String^ s = gcnew String(e->printException().c_str());

			MessageBox::Show(s);
		}
	}
			//��������
	private:void myRedo()
	{
		try
		{
			undoManager->redo();
			redraw();
			setCanRedo();
			setCanUndo();
		}
		catch (MyException* e)
		{
			String^ s = gcnew String(e->printException().c_str());

			MessageBox::Show(s);
		}
	}



//����redo��undo�ĵ������
private: System::Void undo_Click(System::Object^  sender, System::EventArgs^  e) {
	myUndo();
}

private: System::Void redo_Click(System::Object^  sender, System::EventArgs^  e) {
	myRedo();
}
private: System::Void undoItem_Click(System::Object^  sender, System::EventArgs^  e) {
	myUndo();
}
private: System::Void redoItem_Click(System::Object^  sender, System::EventArgs^  e) {
	myRedo();
}
private: System::Void undoStrip_Click(System::Object^  sender, System::EventArgs^  e) {
	myUndo();
}
private: System::Void redoStrip_Click(System::Object^  sender, System::EventArgs^  e) {
	myRedo();
}
};
}
