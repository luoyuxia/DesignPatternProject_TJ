#pragma once
#ifndef _FILECOMMAND
#define _FILECOMMAND
#include"Entry.h"
#include"Directory.h"
class Command
{
public:
	Command() {};
	~Command() {};
	virtual void excute() {};
	virtual void unexcute(){};
	virtual void addCommand(Command* command) { throw EnTryException("不能添加命令！"); }
	virtual bool canbeExcuteSuccess() { return true; }
private:

};

//添加文件后目录的命令
class AddEntryCommand :public Command
{
public:
	AddEntryCommand(Entry* root, Entry* added) :_root_entry(root), _added_entry(added) {}
	~AddEntryCommand() {};
	virtual void excute() { _root_entry->add(_added_entry); }
	virtual void unexcute() { _root_entry->deleteEntry(_added_entry->getName()); }
private:
	Entry* _root_entry;
	Entry* _added_entry;
};

class DeleteEntryCommand :public Command
{
public:
	DeleteEntryCommand(Entry* root, string deletename) :_root_entry(root), _deleteEntryname(deletename) {};
	~DeleteEntryCommand() {};
	virtual void excute() {_delete_entry = _root_entry->deleteEntry(_deleteEntryname); }
	virtual void unexcute() { _root_entry->add(_delete_entry); }
private:
	Entry* _root_entry;
	Entry* _delete_entry;
	string _deleteEntryname;
};

//根据相对路径进行跳转
class GoToDirectoryCommand:public Command
{
public:
	GoToDirectoryCommand(Directory*& dir,string& currentPath, string path):_current_path(currentPath), _old(dir),_changed(dir),_path(path),_oldPath(currentPath){}
	~GoToDirectoryCommand() {}
	//跳转至相对路径对应的目录，更改当前路径
	virtual void excute() { _changed = _old->findDirByPath(_path); _current_path = _current_path + "/" + _path; }

	//将当前路径改成之前记录下来的路径，更改当前目录
	virtual void unexcute() { _changed = _old; _current_path = _oldPath; };
	virtual bool canbeExcuteSuccess() { return _old->findDirByPath(_path) != NULL; }
	//如果存在对应目录，则该指令可以成功执行
private:
	Directory*& _changed;
	Directory* _old;
	string& _current_path;
	string _oldPath;
	string _path;
};

//根据主目录进行跳转
class GoFromRootCommand:public Command
{
public:
	GoFromRootCommand(Directory*& current, Directory* root, string& currentPath, string path)
		:_current(current), _currentPath(currentPath) {
		oldEntry = current; _root = root;
		_oldPath = currentPath; _path = path;
	};
	~GoFromRootCommand() {};
	virtual void excute();
	virtual void unexcute();
	virtual bool canbeExcuteSuccess();
private:
	Directory*& _current;
	Directory* oldEntry;
	Directory* _root;
	string& _currentPath;
	string _oldPath;
	string _path;
};
void  GoFromRootCommand::excute()
{
	if (canbeExcuteSuccess() == false) return;
	if (_path == "")
	{
		_current = _root;
		_currentPath = ROOT;
		return;
	}
	_current = _root->findDirByPath(_path);
	_currentPath = ROOT + string("/")+_path;

}

void  GoFromRootCommand::unexcute()
{
	_current = oldEntry;
	_currentPath = _oldPath;
}

bool  GoFromRootCommand::canbeExcuteSuccess()
{
	if (_path == "" || _root->findDirByPath(_path))
		return true;
	return false;
}

//宏命令，可以将多条命令进行组合
class MacroCommand:Command
{
public:
	MacroCommand() {};
	~MacroCommand() {};
	virtual void excute() {
		for each (Command* cmd in commands)
		{
			cmd->excute();
		}
	};
	virtual void unexcute() {
		vector<Command*>::reverse_iterator re_iter = commands.rbegin();
		for (;re_iter!=commands.rend();re_iter++)
		{
			(*re_iter)->unexcute();
		}
	};
	virtual void addCommand(Command* command) { commands.push_back(command); };
private:
	vector<Command*> commands;
};



class ListAllEntryCommand:public Command
{
public:
	ListAllEntryCommand(Entry* entry) :_entry(entry) {};
	~ListAllEntryCommand() {};
	virtual void excute() { _entry->print();}
private:
	Entry* _entry;

};



#endif // !_FILECOMMAND

