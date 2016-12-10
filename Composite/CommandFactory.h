#pragma once
#ifndef _COMMANDFACTORY
#define _COMMANDFACTORY
#include"FileCommand.h"


//抽象工厂，用来产生一个个的命令
class CommandFactory
{
public:
	CommandFactory() {};
	~CommandFactory() {};
	//创建添加文件的命令
	Command* createAddFileCommand(Entry* root, string fileName,int size=0);
	
	//创建添加目录的命令
	Command* createAddDirCommand(Entry* root, string dirName);
	
	//创建删除文件或目录的命令
	Command* createDeleteEntryCommand(Entry* root, string entryName);
	
	//创建从当前目录跳转到某一目录的命令
	Command* createGotoDirCommand(Entry*& root,string& current, string dirName);
	
	//创建列出当前目录下所有文件或目录的命令
	Command* createListAllCommand(Entry* root);
	
	//创建从主目录跳转到某一目录的命令
	Command* createFromRoot(Entry*& current, Entry* root, string& currentPath, string path);
private:
	
};
Command * CommandFactory::createAddFileCommand(Entry * root, string fileName,int size)
{
return new AddEntryCommand(root, new File(fileName, size));
}

Command * CommandFactory::createAddDirCommand(Entry * root, string dirName)
{
return new AddEntryCommand(root, new Directory(dirName));
}

Command * CommandFactory::createDeleteEntryCommand(Entry * root, string entryName)
{
return new DeleteEntryCommand(root, entryName);
}

Command * CommandFactory::createGotoDirCommand(Entry *& root,string& current, string path)
{
	return new GoToDirectoryCommand((Directory*&)root,current,path);
}



Command * CommandFactory::createListAllCommand(Entry * root)
{
return new ListAllEntryCommand(root);
}
inline Command * CommandFactory::createFromRoot(Entry *& current, Entry* root, string & currentPath, string path)
{
	return new GoFromRootCommand((Directory*&)current, (Directory*&)root, currentPath, path);
}
#endif // !_COMMANDFACTORY

