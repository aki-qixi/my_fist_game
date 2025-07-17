#pragma once
#include<graphics.h >
#include"load_anim.hpp"

class scene_help
{
public:
	int on_input(const ExMessage& msg, POINT& M_xy)
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			check_up = 1;
			M_xy = { msg.x,msg.y };
		}
		if (msg.message == WM_LBUTTONUP)
		{
		    if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 652 && msg.y <= 694 && check_up == 1)
		    {
		    	M_xy = { 0,0 };
			    check_up = 0;
			    return 1;
		    }
			else M_xy = { 0,0 };
		}
		return 0;
	}

	void on_update(POINT& M_xy, IMAGE& img_back)
	{
		static int sum = 30;//当sum==30时，下次按下必有音效
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 652 && M_xy.y <= 694))
			putimage_plus(1065, 647, &img_back);
		if ((M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 652 && M_xy.y <= 694))
		{
			if (sum >= 30)
			{
				mciSendString(_T("play anniu from 0"), NULL, 0, NULL);
				M_xy = { 0,0 };
				sum = 0;
				check_up = 0;
			}
		}
		if (sum <= 30)
		{
			sum++;
		}
	}
private:
	int check_up = 0;
};