#include "stdafx.h"
#include "ReadPosFile.h"
#include<iostream>
#include<fstream>
#include <stdlib.h>

void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}




CReadPosFile::CReadPosFile(string path)
{
	m_path = path;
}


CReadPosFile::~CReadPosFile()
{
}

void CReadPosFile::readfileInfo()
{

	const char *filename = m_path.c_str();
	std::ifstream inf(filename);
	if (!inf.is_open())
	{
		std::cout << "Error opening file";
		return;
	}
	while (!inf.eof())
	{
		char d[256];
		inf.getline(d, 256);
		string lineinfo = d;
		if (lineinfo == "")
		{
			continue;
		}
		vector<string> v;
		SplitString(lineinfo, v, " "); //可按多个字符来分隔;
		BOXinfo box;
		box.classtype = atoi(v[0].c_str());
		box.xiangshidu = atof(v[1].c_str());
		box.box[0] = atof(v[2].c_str());
		box.box[1] = atof(v[3].c_str());
		box.box[2] = atof(v[4].c_str());
		box.box[3] = atof(v[5].c_str());
		m_listBoxsInfo.push_back(box); 
	}

}