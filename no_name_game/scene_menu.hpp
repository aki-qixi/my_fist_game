#pragma once
#include<graphics.h >
#include"load_anim.hpp"

class scene_menu
{
public:
	int on_input(const ExMessage &msg, POINT &M_xy)
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			check_up = 0;
			M_xy = { msg.x,msg.y };
		}
		if (msg.message == WM_LBUTTONUP)
		{
			check_up = 1;
			if (msg.x >= 565 && msg.x <= 717 && msg.y >= 316 && msg.y <= 364)
			{
				M_xy = { msg.x,msg.y };
				return 1;
			}
			else if (msg.x >= 565 && msg.x <= 717 && msg.y >= 383 && msg.y <= 431)
			{
				M_xy = { msg.x,msg.y };
				return 2;
			}
			else if (msg.x >= 565 && msg.x <= 717 && msg.y >= 452 && msg.y <= 500)
			{
				M_xy = { msg.x,msg.y };
				return 3;
			}
			else if (msg.x >= 565 && msg.x <= 717 && msg.y >= 521 && msg.y <= 569)
			{
				M_xy = { msg.x,msg.y };
				return 4;
			}
			else if (msg.x >= 565 && msg.x <= 717 && msg.y >= 590 && msg.y <= 638)
			{
				M_xy = { msg.x,msg.y };
				return 5;
			}
			else M_xy = { 0,0 };
		}
		return 0;
	}

	void on_update(POINT& M_xy, IMAGE& img_play,IMAGE &img_shop, IMAGE& img_help, IMAGE& img_setting, IMAGE& img_exit)
	{
		static int sum = 0;//当sum==0时，下次按下必有音效
		if (sum == 20 || check_up)
			sum = 0;
        if(!(M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 316 && M_xy.y <= 364))
			putimage_plus(565, 316, &img_play);
		if(!(M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 383 && M_xy.y <= 431))
			putimage_plus(565, 383, &img_shop);
		if(!(M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 452 && M_xy.y <= 500))
			putimage_plus(565, 452, &img_help);
		if(!(M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 521 && M_xy.y <= 569))
			putimage_plus(565, 521, &img_setting);
		if(!(M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 590 && M_xy.y <= 638))
			putimage_plus(565, 590, &img_exit);

		if ((M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 316 && M_xy.y <= 364) || (M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 383 && M_xy.y <= 431) ||
			(M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 452 && M_xy.y <= 500) || (M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 521 && M_xy.y <= 569) ||
			(M_xy.x >= 565 && M_xy.x <= 717 && M_xy.y >= 590 && M_xy.y <= 638))
			sum++;
		if (sum == 1)
		{
			mciSendString(_T("play anniu from 0"), NULL, 0, NULL);
			sum += 1;
		}
	}

private:
	bool check_up = 0;
};