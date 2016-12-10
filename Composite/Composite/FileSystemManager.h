#pragma once
#ifndef _FILESYSTEMMANAGER
#define _FILESYSTEMMANGER
#include"File.h"
#include"CommandFactory.h"
#include"FileCommand.h"
#include"FileCommand.h"
using namespace std;

//ȥ���ַ����������ߵĿո�
void trim_first_last(string& str)
{
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos)
	{
		str = "";
		return;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
	{
		str = str.substr(pos, pos2 - pos + 1);
	}
	else
		str = str.substr(pos);
}


class FileSystemManager
{
public:
	FileSystemManager();
	~FileSystemManager();
	void doCommand(string commandLine);
	Command* getCommand(string commandLine);
	void addCommand(Command* cmd);
	const bool ignoreCaseEqual(const char* s1,const char* s2) const{ return _strcmpi(s1, s2) == 0; }
	void redoCommand();
	void undoCommand();
	void printHelpInfo();
	string getPath() { return currentPath; }
private:
	Entry* root;
	Entry* currentEntry;
	string currentPath;
	vector<Command*> commandList;
	int commandIndex;
	CommandFactory cmdFactory;
};

//��ʼ���ļ�ϵͳ
FileSystemManager::FileSystemManager()
{
	root = new Directory(ROOT);
	currentEntry = root;
	currentPath =  root->getName();
	commandIndex = -1;
}


FileSystemManager::~FileSystemManager()
{
	delete root;
}

//���������е����ݣ�ִ�ж�Ӧ�Ĳ���
void FileSystemManager::doCommand(string commandLine)
{
	if (ignoreCaseEqual(commandLine.c_str(), "undo"))
		undoCommand();//��������
	else if (ignoreCaseEqual(commandLine.c_str(), "redo"))
		redoCommand();//��������
	else if(ignoreCaseEqual(commandLine.c_str(),"help"))
	{
		printHelpInfo();
	}
	else //ִ�ж�Ӧ����
	{
		Command* cmd = getCommand(commandLine);
		if(cmd!=NULL)cmd->excute();
	}
} 

void FileSystemManager::printHelpInfo()
{
	cout << "********************help******************\n";
	cout << "cd     �ӵ�ǰĿ¼����ĳ��Ŀ¼             \n";
	cout << "ls     �г���ǰĿ¼�µ����������Ϣ       \n";
	cout << "home   ����ڸ�Ŀ¼����ĳ��Ŀ¼           \n";
	cout << "mkdir  �ڵ�ǰĿ¼�´���һ��Ŀ¼           \n";
	cout << "mkfile �ڵ�ǰĿ¼�´���һ���ļ�           \n";
	cout << "del	ɾ��ĳ���ļ���Ŀ¼				   \n";
	cout << "********************help******************\n\n\n";
}
//������������������
Command * FileSystemManager::getCommand(string commandLine)
{
	if (ignoreCaseEqual(commandLine.c_str(), "ls"))
	{
		return cmdFactory.createListAllCommand(currentEntry);
	}
	int index = commandLine.find_first_of(" ");//������������
	string realCommand = commandLine.substr(0, index);
	string parameters = index == string::npos ? "" : commandLine.substr(index + 1, commandLine.size());
	trim_first_last(parameters);
	if (ignoreCaseEqual(realCommand.c_str(), "home"))
	{  //�������Ŀ¼��ת��ĳ��Ŀ¼
		Command* cmd = cmdFactory.createFromRoot(currentEntry, root, currentPath, parameters);
		if (cmd->canbeExcuteSuccess() == false) throw EnTryException("�����ڶ�Ӧ��Ŀ¼��");
		addCommand(cmd);
		return cmd;
	}
	
	//��������Ŀ¼
	if (ignoreCaseEqual(realCommand.c_str(), "mkdir"))
	{
		if (parameters == "") throw EnTryException("����û�������ļ�������");
		Command* cmd = cmdFactory.createAddDirCommand(currentEntry, parameters);
		addCommand(cmd);
		return cmd;
	}

	//���������ļ�
	if (ignoreCaseEqual(realCommand.c_str(), "mkfile"))
	{
		int index = parameters.find_first_of(" ");
		if (index < 0)return cmdFactory.createAddFileCommand(currentEntry, parameters);
		string fileName = parameters.substr(0, index);
		string sizeString = parameters.substr(index + 1, parameters.size());
		int size = atol(sizeString.c_str());
		if (size == 0 && sizeString != "0")throw EnTryException("�ļ���СӦΪ������");
		Command* cmd = cmdFactory.createAddFileCommand(currentEntry, fileName, size);
		addCommand(cmd);
		return cmd;
	}

	//�������ת��ĳĿ¼
	if (ignoreCaseEqual(realCommand.c_str(), "cd"))
	{
		if (parameters == "")throw EnTryException("��Ч��ָ�");
		Command* cmd = cmdFactory.createGotoDirCommand(currentEntry, currentPath, parameters);
		if (cmd->canbeExcuteSuccess() == false) throw EnTryException("�����ڶ�Ӧ��Ŀ¼��");
		addCommand(cmd);
		return cmd;
	}

	//�����ɾ��ĳĿ¼���ļ�
	if (ignoreCaseEqual(realCommand.c_str(), "del"))
	{
		if (parameters == "")throw EnTryException("��Ч��ָ�");
		Command* cmd = cmdFactory.createDeleteEntryCommand(currentEntry, parameters);
		
		//��������ڶ�Ӧ���ļ���Ŀ¼
		if (cmd->canbeExcuteSuccess() == false) throw EnTryException("�����ڶ�Ӧ��Ŀ¼���ļ���");
		addCommand(cmd);
		return cmd;
	}
	//�����ڶ�Ӧ��Ŀ¼
	throw EnTryException("��Ч��ָ�");
	return NULL;
}

//�������б������һ������
void FileSystemManager::addCommand(Command * cmd)
{
	if(commandIndex!=commandList.size()-1)
	{
		vector<Command*>::iterator iter = commandList.begin();
		for (int i = 0; i <= commandIndex; iter++,i++);
		commandList.erase(iter, commandList.end());
	}//�������redo�������������п���redo��ָ��
	commandList.push_back(cmd);
	commandIndex++;
}


inline void FileSystemManager::redoCommand()
{
	if (commandIndex == commandList.size() - 1)
		throw EnTryException("�Ѿ������������ˣ�");
	Command* cmd = commandList[++commandIndex];
	cmd->excute();
}

inline void FileSystemManager::undoCommand()
{
	if (commandIndex < 0)
		throw EnTryException("�Ѿ������ٳ����ˣ�");
	Command* cmd = commandList[commandIndex--];
	cmd->unexcute();
}

#endif // !_FILESYSTEMMANAGER

