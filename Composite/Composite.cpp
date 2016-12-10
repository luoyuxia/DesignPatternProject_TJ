#include"FileSystemManager.h"

int main()
{
	FileSystemManager manager;
	string commandLine;
	string commands[6];
	commands[0] = "mkdir luoyuxia";
	commands[1] = "mkfile luoyuxia1997 20";
	commands[2] = "mkdir user";
	commands[3] = "mkdir temp";
	commands[4] = "mkdir bin";
	commands[5] = "cd user";
	for (int  i = 0; i < 6; i++)
	{
		manager.doCommand(commands[i]);
	}
	while (true)
	{
		
		cout << "/" + manager.getPath() + "$$ ";
		getline(cin, commandLine);
		trim_first_last(commandLine);
		if (commandLine== "")
			continue;
		if (_strcmpi(commandLine.c_str(), "exit")==0)
			break;
		try
		{
			manager.doCommand(commandLine);
		}
		catch (EnTryException& e)
		{
			e.printException();
		}
	}
	system("pause");
	
}
