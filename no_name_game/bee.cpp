#include"bee.h"

bee::bee(fast_load* f_bee_anim_left,fast_load* f_bee_anim_right)
{
	loadimage(&img_shadow, _T("img/shadow_player.png"), shadow_width);//加载阴影
	bee_anim_left = new anim(f_bee_anim_left,45);
	bee_anim_right = new anim(f_bee_anim_right, 45);

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
		e_xy.x = rand() % 1200;
		e_xy.y = -bee_height;
		break;
	case bianjie::down:
		e_xy.x = rand() % 1200;
		e_xy.y = 720;
		break;
	case bianjie::left:
		e_xy.x = -bee_width;
		e_xy.y = rand() % 640;
		break;
	case bianjie::right:
		e_xy.x = 1280;
		e_xy.y = rand() % 640;
		break;
	default:
		break;
	}
}

bee::~bee()
{

}

bool bee::checkbullet(const bullet& bullet)
{
	bool is_in_x = bullet.bullet_xy.x >= e_xy.x && bullet.bullet_xy.x <= e_xy.x + bee_width;
	bool is_in_y = bullet.bullet_xy.y >= e_xy.y && bullet.bullet_xy.y <= e_xy.y + bee_height;
	return is_in_x && is_in_y;
}

bool bee::checkmagic(const magic& magic)
{
	bool is_in_x = magic.magic_xy.x >= e_xy.x && magic.magic_xy.x <= e_xy.x + bee_width;
	bool is_in_y = magic.magic_xy.y >= e_xy.y && magic.magic_xy.y <= e_xy.y + bee_height;
	return is_in_x && is_in_y;
}

bool bee::checkplayer(const player_anim& player)
{
	POINT check_bee_xy = { e_xy.x + bee_width / 2,e_xy.y + bee_height / 2 };
	bool is_in_x = check_bee_xy.x >= player.player_xy.x && check_bee_xy.x <= player.player_xy.x + 80;
	bool is_in_y = check_bee_xy.y >= player.player_xy.y && check_bee_xy.y <= player.player_xy.y + 80;
	return is_in_x && is_in_y;
}

bool bee::checkalive()
{
	return alive;
}

void bee::move(const player_anim& player)
{
	//朝向玩家
	int xx = player.player_xy.x - e_xy.x;
	int yy = player.player_xy.y - e_xy.y;
	if (xx < 0)
		facing_left = 1;
	else if (xx > 0)
		facing_left = 0;

	//判断是否到达边界
	if (e_xy.y == -80)
	{
		up_left = 1;
		go_count++;
	}
	else if (e_xy.y == 720)
	{
		up_left = 2;
		go_count++;
	}
	if (e_xy.x == -80)
	{
		up_left = 3;
		go_count++;
	}
	else if (e_xy.x == 1280)
	{
		up_left = 4;
		go_count++;
	}
	//循环直线逻辑
	if (e_xy.x >= 0 && e_xy.x <= 1200 && up_left == 1)
	{
		e_xy.y += bee_speed;
	}
	else if (e_xy.x >= 0 && e_xy.x <= 1200 && up_left == 2)
	{
		e_xy.y -= bee_speed;
	}
	else if (e_xy.y >= 0 && e_xy.y <= 640 && up_left == 3)
	{
	    e_xy.x += bee_speed;
	}
	else if (e_xy.y >= 0 && e_xy.y <= 640 && up_left == 4)
	{
		e_xy.x -= bee_speed;
	}

}

void bee::draw(int delat)
{
	int shadow_x = e_xy.x + (bee_width / 4);
	int shadow_y = e_xy.y + bee_height;
	putimage_plus(shadow_x, shadow_y, &img_shadow);

	if (facing_left)
		bee_anim_left->play(e_xy.x, e_xy.y, delat);
	else
		bee_anim_right->play(e_xy.x, e_xy.y, delat);
}

void bee::hurt(int attack)
{
	blood-=attack;
	if (blood <= 0)
		alive = 0;
}