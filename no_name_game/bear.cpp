#include"bear.h"
#include<ctime>

bear::bear(fast_load* f_bear_anim_left, fast_load* f_bear_anim_right)
{
	loadimage(&img_shadow, _T("img/shadow_player.png"), shadow_width);//加载阴影
	e_anim_left = new anim(f_bear_anim_left, 45);
	e_anim_right = new anim(f_bear_anim_right, 45);

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
		e_xy.y = -e_height;
		break;
	case bianjie::down:
		e_xy.x = rand() % 1280;
		e_xy.y = 720;
		break;
	case bianjie::left:
		e_xy.x = -e_width;
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

bear::~bear() {}


void bear::hurt(int attack)
{
	blood -= attack;
	if (blood <= 0)
		alive = 0;
}

bool bear::checkalive()
{
	return alive;
}

bool bear::checkmagic(const magic& magic)
{
	bool is_in_x = magic.magic_xy.x >= e_xy.x && magic.magic_xy.x <= e_xy.x + e_width;
	bool is_in_y = magic.magic_xy.y >= e_xy.y && magic.magic_xy.y <= e_xy.y + e_height;
	return is_in_x && is_in_y;
}

bool bear::checkbullet(const bullet& bullet)
{
	bool is_in_x = bullet.bullet_xy.x >= e_xy.x && bullet.bullet_xy.x <= e_xy.x + e_width;
	bool is_in_y = bullet.bullet_xy.y >= e_xy.y && bullet.bullet_xy.y <= e_xy.y + e_height;
	return is_in_x && is_in_y;
}

bool bear::checkplayer(const player_anim& player)
{
	POINT check_enemy_xy = { e_xy.x + e_width / 2,e_xy.y + e_height / 2 };
	bool is_in_x = check_enemy_xy.x >= player.player_xy.x && check_enemy_xy.x <= player.player_xy.x + 80;
	bool is_in_y = check_enemy_xy.y >= player.player_xy.y && check_enemy_xy.y <= player.player_xy.y + 80;
	return is_in_x && is_in_y;
}

void bear::draw(int delat)
{
	int shadow_x = e_xy.x + (e_width / 2 - shadow_width / 2)+5;
	int shadow_y = e_xy.y + e_height - 8;
	putimage_plus(shadow_x, shadow_y, &img_shadow);

	if (facing_left)
		e_anim_left->play(e_xy.x, e_xy.y, delat);
	else
		e_anim_right->play(e_xy.x, e_xy.y, delat);
}

void bear::move(const player_anim& player)
{
	int xx = player.player_xy.x - e_xy.x;
	int yy = player.player_xy.y - e_xy.y;
	double len = sqrt(xx * xx + yy * yy);
	if (len != 0)
	{
		double xxx = xx / len;
		double yyy = yy / len;
		e_xy.x += (double)(e_speed * xxx);
		e_xy.y += (double)(e_speed * yyy);
	}
	if (xx < 0)
		facing_left = 1;
	else if (xx > 0)
		facing_left = 0;
}