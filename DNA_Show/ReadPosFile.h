#pragma once
#include <string>
#include <list>
#include <vector>
using namespace std;

struct BOXinfo
{
	int classtype;
	float xiangshidu;
	float box[4];

};
class CReadPosFile
{
public:
	CReadPosFile(string path);
	~CReadPosFile();

	void readfileInfo();
	list<BOXinfo> m_listBoxsInfo;
private:
	string m_path;

	
};

