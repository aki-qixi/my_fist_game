#pragma once
#include<string>
#include<vector>
#include<graphics.h >

class fast_load
{
public:
	fast_load(LPCTSTR path, int num,int wd=0,int ht=0)
	{
		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);
			IMAGE* frame = new IMAGE();
			loadimage(frame, path_file,wd,ht);
			img_obj.push_back(frame);
		}
	}

	~fast_load()
	{
		for (int i = 0; i < img_obj.size(); i++)
		{
			delete img_obj[i];
		}
	}

	std::vector<IMAGE*> img_obj;

};
