#include"prop.h"

prop::prop(int frm_num,POINT e_xy)
{
	//prop_frm = frm_num;
	//prop_xy = e_xy;
	//loadimage(&img_shadow, _T("img/shadow_player.png"), shadow_width);//加载阴影
	//if (prop_frm == 1)
	//{
	//	loadimage(&img_prop, _T("img/shadow_player.png"), prop_width);//加载单图片道具
	//}
	////else
}

void prop::draw(int delat)
{
	int shadow_x = prop_xy.x + (prop_width / 2 - prop_width / 2);
	int shadow_y = prop_xy.y + prop_height - 16;
	putimage_plus(shadow_x+shadow_xx, shadow_y+shadow_yy, &img_shadow);
	if (prop_frm == 1)
	{
		putimage_plus(prop_xy.x, prop_xy.y, &img_prop);
	}
	else
	{
		prop_anim->play(prop_xy.x, prop_xy.y, delat);
	}
}

bool prop::checkplayer(const player_anim& player)
{
	POINT check_prop_xy = { prop_xy.x + prop_width / 2,prop_xy.y + prop_height / 2 };
	bool is_in_x = check_prop_xy.x >= player.player_xy.x && check_prop_xy.x <= player.player_xy.x + 80;
	bool is_in_y = check_prop_xy.y >= player.player_xy.y && check_prop_xy.y <= player.player_xy.y + 80;
	return is_in_x && is_in_y;
}