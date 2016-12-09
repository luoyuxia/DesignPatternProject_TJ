#include "UnDoReDo.h"
using namespace UndoRedoProject;
ref class UnDoReDo;
[STAThread]

int main()
{
	Application::EnableVisualStyles();
	Application::Run(gcnew UndoRedoProject::UnDoReDo());
	return 0;
}