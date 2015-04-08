#include "util.h"

//读取配置文件
/********************************* 
* Function Name:
* Function description:
* Author: jensonhjt 
* Input parameter: 
*
* Return value: 
*
**********************************/
extern string readconfig(const string filepath, const string section, const string key, string value)
{
	ifstream infile(filepath.c_str(), ifstream::in);
	if(!infile)
	{
		cout << __FILE__ << __LINE__<< "file not exit\n";
	}
	string s, sword;
	bool flag = false;
	while(getline(infile, s))
	{
		sword = "";
		switch(s[0])
			{
			case '#'|'/'|' ':
				break;
			case '[':
				if(s.find(section))
				{
					getline(infile, s);
					if(s.find(key) != string::npos)
					{
						int pos = s.find("=");
						sword = s.substr(pos+1);
						flag = true;
					}
				}
				break;
			}
		if(flag)
		{
			break;
		}
		else
		{
			sword = value;
		}
	}
	// infile.clear();
	infile.close();
	return sword;
}
/********************************* 
* Function Name:
* Function description:
* Author: jensonhjt 
* Input parameter: 
*
* Return value: 在min max获取随机数
*
**********************************/
extern int genrandom(int min, int max)
{
	if(min >= max)
		return -1;
	int t = (rand()%(max-min) + 1) +min;
	return t;
}

extern double random(double start, double end)
{
    return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
