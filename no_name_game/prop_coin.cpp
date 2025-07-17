#include"prop_coin.h"

coin::coin(int frm_num,POINT e_xy,fast_load *f_coin_anim,int type)
{
	srand((unsigned int)time(NULL));
	int add_x = (rand() % 100);
	int add_y = (rand() % 75);
	prop_frm = frm_num;//图数
	prop_xy = e_xy;
	prop_xy.x += add_x;
	prop_xy.y += add_y;
	coin_type = type;//硬币类型
	prop_height = 32;//初始化宽高
	prop_width = 32;
	shadow_xx = 8;
	shadow_yy = 5;
	loadimage(&img_shadow, _T("img/shadow_player.png"), shadow_width);//加载阴影
	prop_anim = new anim(f_coin_anim, 45);
}

void coin::move(const player_anim& player)
{
	int xx = player.player_xy.x - prop_xy.x;
	int yy = player.player_xy.y - prop_xy.y;
	double len = sqrt(xx * xx + yy * yy);
	if (len != 0)
	{
			// 使用浮点数计算，避免整数除法丢失精度
			double dx = (double)xx / len;
			double dy = (double)yy / len;
			int move_x = (int)(coin_speed * dx);
			int move_y = (int)(coin_speed * dy);

			prop_xy.x += move_x;
			prop_xy.y += move_y;
	}
}

