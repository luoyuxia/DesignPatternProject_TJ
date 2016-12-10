#pragma once
#ifndef _DIRECTORY
#define _DIRECTORY
#include"Entry.h"
#include"File.h"
#include<vector>
class Directory :public Entry
{
public:
	Directory();
	Directory(string name);
	~Directory();
	virtual int getSize();
	virtual string getName();
	virtual void add(Entry* entry);
	virtual Entry* deleteEntry(string entryname);
	virtual void printList(string prefix);
	virtual string getType();
	virtual bool isDir() { return true; };
	File* findFileByPath(string path,string separator="/");
	Directory* findDirByPath(string path, string separator = "/");
	vector<string> splitString(string s, string separator);
	virtual Entry* clone();
private:
	string _name;
	vector<Entry*> entries;
	Entry* searchByPath(vector<string>vecPath,vector<Entry*>& entries,int index=0);
};

Directory::Directory()
{
	Directory("null");
}
Directory::Directory(string name) :_name(name)
{
	
}
Directory::~Directory()
{
}

Entry* Directory::clone()
{
	Directory* dir = new Directory(_name);
	for (int i = 0; i < entries.size(); i++)
	{
		dir->add(entries[i]->clone());
	}
	return dir;
}
inline int Directory::getSize()
{
	int size = 0;
	for each (Entry* entry in entries)
	{
		size += entry->getSize();
	}
	return size;
}

inline string Directory::getName()
{
	return _name;
}

//添加目录或文件
inline void Directory::add(Entry * entry)
{
	for each (Entry* _entry  in entries)
	{
		if (_entry->getName() == entry->getName())
		{
			throw EnTryException("存在同名文件或文件夹！");
			return;
		}
	}
	entries.push_back(entry);
}

//删除目录或文件
inline Entry* Directory::deleteEntry(string entryname)
{
	vector<Entry*>::iterator iter = entries.begin();
	for (; iter != entries.end(); iter++)
	{
		if ((*iter)->getName() == entryname)
		{
			break;
		}
	}
	Entry* entry = NULL;
	if (iter != entries.end())
	{
		entry = (*iter)->clone();
		entries.erase(iter, iter + 1);
	}
	return entry;
}

//输出文件或目录信息
inline void Directory::printList(string prefix)
{
	cout << prefix + "/" + tostring() + "\n";
	for each (Entry* entry in entries)
	{
		entry->printList(prefix+"/"+getName());
	}
}
inline string Directory::getType()
{
	return string("@目录@");
}

//根据相对该目录的路径找到文件
 File * Directory::findFileByPath(string path, string separator)
{
	vector<string> paths = splitString(path, separator);
	Entry* entry = searchByPath(paths,entries, 0);
	if (entry == NULL)return NULL;
	if (entry->isDir()) return NULL;
	return (File*)entry;
}

 //根据相对该目录的路径找到目录
inline Directory * Directory::findDirByPath(string path, string separator)
{
	vector<string> paths = splitString(path, separator);
	Entry* entry = searchByPath(paths, entries, 0);
	if (entry == NULL)return NULL;
	if (entry->isDir()==false) return NULL;
	return (Directory*)entry;
}

//分割字符串
inline vector<string> Directory::splitString(string s, string splitor)
{
	vector<string> vecs;
	int index = 0;
	while ((index = s.find_first_of(splitor))>=0)
	{
		string path = s.substr(0, index);
		vecs.push_back(path);
		s = s.substr(index + 1, s.length());
	}
	vecs.push_back(s);
	return vecs;
}

//根据路径查找文件或目录
inline Entry * Directory::searchByPath(vector<string> vecPath, vector<Entry*>&entries,int index)
{
	if(vecPath.size() <= index)
		return NULL;
	string aimEntryName = vecPath[index];
	for each (Entry* entry in entries)
	{
		if (entry->getName() == aimEntryName)
		{
			if (index == vecPath.size() - 1)
				return entry;
			else
			{
				if (entry->isDir() == false) return  NULL;
				Directory* dir = (Directory*)entry;
				
				return searchByPath(vecPath, dir->entries,++index);
			}
		}
	}
	return NULL;
}
#endif // !_DIRECTORY
