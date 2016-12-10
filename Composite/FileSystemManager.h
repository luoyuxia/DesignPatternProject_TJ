#pragma once
#ifndef _FILESYSTEMMANAGER
#define _FILESYSTEMMANGER
#include"File.h"
#include"CommandFactory.h"
#include"FileCommand.h"
#include"FileCommand.h"
using namespace std;

//去除字符串左右两边的空格
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

//初始化文件系统
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

//根据命令行的内容，执行对应的操作
void FileSystemManager::doCommand(string commandLine)
{
	if (ignoreCaseEqual(commandLine.c_str(), "undo"))
		undoCommand();//撤销操作
	else if (ignoreCaseEqual(commandLine.c_str(), "redo"))
		redoCommand();//重做操作
	else if(ignoreCaseEqual(commandLine.c_str(),"help"))
	{
		printHelpInfo();
	}
	else //执行对应命令
	{
		Command* cmd = getCommand(commandLine);
		if(cmd!=NULL)cmd->excute();
	}
} 

void FileSystemManager::printHelpInfo()
{
	cout << "********************help******************\n";
	cout << "cd     从当前目录进入某个目录             \n";
	cout << "ls     列出当前目录下的所有项的信息       \n";
	cout << "home   相对于根目录进入某个目录           \n";
	cout << "mkdir  在当前目录下创建一个目录           \n";
	cout << "mkfile 在当前目录下创建一个文件           \n";
	cout << "del	删除某个文件或目录				   \n";
	cout << "********************help******************\n\n\n";
}
//根据命令行生成命令
Command * FileSystemManager::getCommand(string commandLine)
{
	if (ignoreCaseEqual(commandLine.c_str(), "ls"))
	{
		return cmdFactory.createListAllCommand(currentEntry);
	}
	int index = commandLine.find_first_of(" ");//获得命令的种类
	string realCommand = commandLine.substr(0, index);
	string parameters = index == string::npos ? "" : commandLine.substr(index + 1, commandLine.size());
	trim_first_last(parameters);
	if (ignoreCaseEqual(realCommand.c_str(), "home"))
	{  //如果从主目录跳转到某个目录
		Command* cmd = cmdFactory.createFromRoot(currentEntry, root, currentPath, parameters);
		if (cmd->canbeExcuteSuccess() == false) throw EnTryException("不存在对应的目录！");
		addCommand(cmd);
		return cmd;
	}
	
	//如果是添加目录
	if (ignoreCaseEqual(realCommand.c_str(), "mkdir"))
	{
		if (parameters == "") throw EnTryException("错误！没有输入文件夹名！");
		Command* cmd = cmdFactory.createAddDirCommand(currentEntry, parameters);
		addCommand(cmd);
		return cmd;
	}

	//如果是添加文件
	if (ignoreCaseEqual(realCommand.c_str(), "mkfile"))
	{
		int index = parameters.find_first_of(" ");
		if (index < 0)return cmdFactory.createAddFileCommand(currentEntry, parameters);
		string fileName = parameters.substr(0, index);
		string sizeString = parameters.substr(index + 1, parameters.size());
		int size = atol(sizeString.c_str());
		if (size == 0 && sizeString != "0")throw EnTryException("文件大小应为整数！");
		Command* cmd = cmdFactory.createAddFileCommand(currentEntry, fileName, size);
		addCommand(cmd);
		return cmd;
	}

	//如果是跳转到某目录
	if (ignoreCaseEqual(realCommand.c_str(), "cd"))
	{
		if (parameters == "")throw EnTryException("无效的指令！");
		Command* cmd = cmdFactory.createGotoDirCommand(currentEntry, currentPath, parameters);
		if (cmd->canbeExcuteSuccess() == false) throw EnTryException("不存在对应的目录！");
		addCommand(cmd);
		return cmd;
	}

	//如果是删除某目录或文件
	if (ignoreCaseEqual(realCommand.c_str(), "del"))
	{
		if (parameters == "")throw EnTryException("无效的指令！");
		Command* cmd = cmdFactory.createDeleteEntryCommand(currentEntry, parameters);
		
		//如果不存在对应的文件或目录
		if (cmd->canbeExcuteSuccess() == false) throw EnTryException("不存在对应的目录或文件！");
		addCommand(cmd);
		return cmd;
	}
	//不存在对应的目录
	throw EnTryException("无效的指令！");
	return NULL;
}

//在命令列表中添加一个命令
void FileSystemManager::addCommand(Command * cmd)
{
	if(commandIndex!=commandList.size()-1)
	{
		vector<Command*>::iterator iter = commandList.begin();
		for (int i = 0; i <= commandIndex; iter++,i++);
		commandList.erase(iter, commandList.end());
	}//如果可以redo，擦除后面所有可以redo的指令
	commandList.push_back(cmd);
	commandIndex++;
}


inline void FileSystemManager::redoCommand()
{
	if (commandIndex == commandList.size() - 1)
		throw EnTryException("已经不能再重做了！");
	Command* cmd = commandList[++commandIndex];
	cmd->excute();
}

inline void FileSystemManager::undoCommand()
{
	if (commandIndex < 0)
		throw EnTryException("已经不能再撤销了！");
	Command* cmd = commandList[commandIndex--];
	cmd->unexcute();
}

#endif // !_FILESYSTEMMANAGER

