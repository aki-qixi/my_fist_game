#include"snail.h"

snail::snail(fast_load* f_snail_anim_left, fast_load* f_snail_anim_right)
{
	loadimage(&img_shadow, _T("img/shadow_player.png"), shadow_width);//加载阴影
	snail_anim_left = new anim(f_snail_anim_left, 45);
	snail_anim_right = new anim(f_snail_anim_right, 45);

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
		e_xy.y = -snail_height;
		break;
	case bianjie::down:
		e_xy.x = rand() % 1280;
		e_xy.y = 720;
		break;
	case bianjie::left:
		e_xy.x = -snail_width;
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

snail::~snail(){}

bool snail::checkbullet(const bullet&bullet)
{
	bool is_in_x = bullet.bullet_xy.x >= e_xy.x && bullet.bullet_xy.x <= e_xy.x + snail_width;
	bool is_in_y = bullet.bullet_xy.y >= e_xy.y && bullet.bullet_xy.y <= e_xy.y + snail_height;
	return is_in_x && is_in_y;
}

bool snail::checkmagic(const magic& magic)
{
	bool is_in_x = magic.magic_xy.x >= e_xy.x && magic.magic_xy.x <= e_xy.x + snail_width;
	bool is_in_y = magic.magic_xy.y >= e_xy.y && magic.magic_xy.y <= e_xy.y + snail_height;
	return is_in_x && is_in_y;
}

bool snail::checkplayer(const player_anim& player)
{
	POINT check_snail_xy = { e_xy.x + snail_width / 2,e_xy.y + snail_height / 2 };
	bool is_in_x = check_snail_xy.x >= player.player_xy.x && check_snail_xy.x <= player.player_xy.x + 80;
	bool is_in_y = check_snail_xy.y >= player.player_xy.y && check_snail_xy.y <= player.player_xy.y + 80;
	return is_in_x && is_in_y;
}

bool snail::checkalive()
{
	return alive;
}

void snail::move(const player_anim& player)
{
	int xx = player.player_xy.x - e_xy.x;
	int yy = player.player_xy.y - e_xy.y;
	double len = sqrt(xx * xx + yy * yy);
	if (len != 0)
	{
		if (len != 0)
		{
			// 使用浮点数计算，避免整数除法丢失精度
			double dx = (double)xx / len;
			double dy = (double)yy / len;
			int move_x = (int)(snail_speed * dx);
			int move_y = (int)(snail_speed * dy);

			e_xy.x += move_x;
			e_xy.y += move_y;
		}
	}
	if (xx < 0)
		facing_left = 1;
	else if (xx > 0)
		facing_left = 0;
}

void snail::draw(int delat)
{
	int shadow_x = e_xy.x + (snail_width / 2 - shadow_width / 2);
	int shadow_y = e_xy.y + snail_height - 16;
	putimage_plus(shadow_x, shadow_y, &img_shadow);

	if (facing_left)
		snail_anim_left->play(e_xy.x, e_xy.y, delat);
	else
		snail_anim_right->play(e_xy.x, e_xy.y, delat);
}

void snail::hurt(int attack)
{
	blood-=attack;
	if (blood <= 0)
		alive = 0;
}