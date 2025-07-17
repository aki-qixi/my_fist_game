#include"prop_heart.h"

prop_heart::prop_heart(int frm_num, POINT e_xy,IMAGE &img)
{
	srand((unsigned int)time(NULL));
	int add_x = (rand() % 100);
	int add_y = (rand() % 75);
	img_prop = img;
	prop_frm = frm_num;
	prop_xy = e_xy;
	prop_xy.x += add_x;
	prop_xy.y += add_y;
	shadow_yy = 10;
	loadimage(&img_shadow, _T("img/shadow_player.png"), shadow_width);//加载阴影
	if (prop_frm == 1)
	{
		loadimage(&img_prop, _T("img/heart_prop.png"), prop_width,prop_height);//加载单图片道具
	}
}