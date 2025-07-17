#include"enemy.h"
#include<ctime>

enemy::enemy(fast_load* f_enemy_anim_left,fast_load* f_enemy_anim_right)
{
	loadimage(&img_shadow, _T("img/shadow_player.png"),shadow_width);//加载阴影
	e_anim_left = new anim(f_enemy_anim_left, 45);
    e_anim_right = new anim(f_enemy_anim_right, 45);

	//敌人生成边界
	enum class bianjie
	{
		up = 0, down, left, right
	};
	//随机边界
	srand((unsigned int)time(NULL));
	bianjie edge = (bianjie)(rand() % 4);
	switch (edge)
	{
	case bianjie::up:
		e_xy.x = rand() % 1280;
		e_xy.y = -enemy_height;
		break;
	case bianjie::down:
		e_xy.x = rand() % 1280;
		e_xy.y = 720;
		break;
	case bianjie::left:
		e_xy.x = -enemy_width;
		e_xy.y = rand() % 720;
		break;
	case bianjie::right:
		e_xy.x = 1280;
		e_xy.y = rand() % 720;
		break;
	default:
		break;
	}

}

enemy::~enemy(){}


void enemy::hurt(int attack)
{
	blood -= attack;
	if (blood <= 0)
	alive = 0;
}

bool enemy::checkalive()
{
	return alive;
}
