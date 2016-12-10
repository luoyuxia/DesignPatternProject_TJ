#pragma once
#ifndef _COMMANDFACTORY
#define _COMMANDFACTORY
#include"FileCommand.h"


//���󹤳�����������һ����������
class CommandFactory
{
public:
	CommandFactory() {};
	~CommandFactory() {};
	//��������ļ�������
	Command* createAddFileCommand(Entry* root, string fileName,int size=0);
	
	//�������Ŀ¼������
	Command* createAddDirCommand(Entry* root, string dirName);
	
	//����ɾ���ļ���Ŀ¼������
	Command* createDeleteEntryCommand(Entry* root, string entryName);
	
	//�����ӵ�ǰĿ¼��ת��ĳһĿ¼������
	Command* createGotoDirCommand(Entry*& root,string& current, string dirName);
	
	//�����г���ǰĿ¼�������ļ���Ŀ¼������
	Command* createListAllCommand(Entry* root);
	
	//��������Ŀ¼��ת��ĳһĿ¼������
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

