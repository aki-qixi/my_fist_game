#pragma once
#include<graphics.h >
#include"load_anim.hpp"

class scene_shop
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
			//check_up = 2;
			if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 112 && msg.y <= 154 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 1;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 166 && msg.y <= 208 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 2;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 218 && msg.y <= 260 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 3;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 282 && msg.y <= 322 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 4;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 340 && msg.y <= 382 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 5;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 428 && msg.y <= 470 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 6;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 512 && msg.y <= 554 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 7;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 574 && msg.y <= 616 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 8;
			}
			else if (msg.x >= 1070 && msg.x <= 1210 && msg.y >= 652 && msg.y <= 694 && check_up == 1)
			{
				M_xy = { 0,0 };
				check_up = 0;
				return 9;
			}
			else M_xy = { 0,0 };
		}
		return 0;
	}
	void on_update(POINT& M_xy, IMAGE& img_back, IMAGE& img_up)
	{
		static int sum = 30;//当sum==30时，下次按下必有音效
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 112 && M_xy.y <= 154))
			putimage_plus(1065, 107, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 166 && M_xy.y <= 208))
			putimage_plus(1065, 161, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 218 && M_xy.y <= 260))
			putimage_plus(1065, 213, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 282 && M_xy.y <= 322))
			putimage_plus(1065, 277, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 340 && M_xy.y <= 382))
			putimage_plus(1065, 335, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 428 && M_xy.y <= 470))
			putimage_plus(1065, 423, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 512 && M_xy.y <= 554))
			putimage_plus(1065, 507, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 574 && M_xy.y <= 616))
			putimage_plus(1065, 569, &img_up);
		if (!(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 652 && M_xy.y <= 694))
			putimage_plus(1065, 647, &img_back);

		if ((M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 112 && M_xy.y <= 154) || (M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 166 && M_xy.y <= 208) ||
			(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 218 && M_xy.y <= 260) || (M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 282 && M_xy.y <= 322) ||
			(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 340 && M_xy.y <= 382) || (M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 428 && M_xy.y <= 470) || 
			(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 512 && M_xy.y <= 554) || (M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 574 && M_xy.y <= 616) || 
			(M_xy.x >= 1070 && M_xy.x <= 1210 && M_xy.y >= 652 && M_xy.y <= 694))
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
	bool check_up = 0;
};