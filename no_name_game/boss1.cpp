#include"boss1.h"

boss1::boss1(fast_load* f_boss1_anim_left, fast_load* f_boss1_anim_right, const player_anim& player)
{
	loadimage(&img_shadow, _T("img/shadow_player.png"), shadow_width);//加载阴影
	boss1_anim_left = new anim(f_boss1_anim_left, 45);
	boss1_anim_right = new anim(f_boss1_anim_right, 45);

	blood = 250;
	e_xy.x = 540;
	e_xy.y = -200;
}

bool boss1::checkbullet(const bullet& bullet)
{
	bool is_in_x = bullet.bullet_xy.x >= e_xy.x+20 && bullet.bullet_xy.x <= e_xy.x + boss1_width-20;
	bool is_in_y = bullet.bullet_xy.y >= e_xy.y+10 && bullet.bullet_xy.y <= e_xy.y + boss1_height-10;
	return is_in_x && is_in_y;
}

bool boss1::checkmagic(const magic& magic)
{
	bool is_in_x = magic.magic_xy.x >= e_xy.x+20 && magic.magic_xy.x <= e_xy.x + boss1_width-20;
	bool is_in_y = magic.magic_xy.y >= e_xy.y+10 && magic.magic_xy.y <= e_xy.y + boss1_height-10;
	return is_in_x && is_in_y;
}

bool boss1::checkplayer(const player_anim& player)
{
	POINT check_boss1_xy = { e_xy.x + boss1_width / 2,e_xy.y + boss1_height / 2 };
	bool is_in_x = check_boss1_xy.x >= player.player_xy.x && check_boss1_xy.x <= player.player_xy.x + 80;
	bool is_in_y = check_boss1_xy.y >= player.player_xy.y && check_boss1_xy.y <= player.player_xy.y + 80;
	return is_in_x && is_in_y;
}

bool boss1::checkalive()
{
	return alive;
}

void boss1::move(const player_anim& player)
{
	POINT is_xy = e_xy;
	int xx = player.player_xy.x - e_xy.x;
	int yy = player.player_xy.y - e_xy.y;
	double len = sqrt(xx * xx + yy * yy);
	if (len != 0 && stage == 0)
	{
		if (len != 0)
		{
			// 使用浮点数计算，避免整数除法丢失精度
			double dx = (double)xx / len;
			double dy = (double)yy / len;
			int move_x = (int)(boss1_speed * dx);
			int move_y = (int)(boss1_speed * dy);

			e_xy.x += move_x;
			e_xy.y += move_y;
		}
	}
	if (len <= set_x && e_xy.y > 0 && e_xy.y < 520 && e_xy.x>0 && e_xy.x < 1080 && stage == 0)
	{
		stage = 1;
	}
	if (stage == 1)
	{
		static int x = 0;
		if(x<=400)
		{
			x += boss1_speed / 2;
			e_xy.x += boss1_speed / 2;
		}
		else
		{
			x += boss1_speed / 2;
			e_xy.x -= boss1_speed / 2;
			if (x >= 800)
				x = 0;
		}
	}
	if (stage == 2)
	{
		e_xy.x += boss1_speed;
		if (e_xy.x >= 1600)
		{
			stage = 3;
			e_xy.x = 540;
			e_xy.y = -200;
		}
	}
	if (stage == 3)
	{
		e_xy.y += boss1_speed;
		if (e_xy.y >= 1000)
		{
			stage = 4;
			e_xy.x = -200;
			e_xy.y = 260;
		}
	}
	if (stage == 4)
	{
		e_xy.x += boss1_speed;
		if (e_xy.x >= 1600)
		{
			stage = 0;
			e_xy.x = 540;
			e_xy.y = 720;
		}
	}
	if (blood <= 100)
	{
		stage = 5;
		boss1_speed = 5;
	}
	if (stage == 5)
	{	
		if (e_xy.x > 1600 || e_xy.y > 1000 || e_xy.x < -320 || e_xy.y < -320)
		{
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
				e_xy.y = -boss1_height;
				break;
			case bianjie::down:
				e_xy.x = rand() % 1200;
				e_xy.y = 720;
				break;
			case bianjie::left:
				e_xy.x = -boss1_width;
				e_xy.y = rand() % 640;
				break;
			case bianjie::right:
				e_xy.x = 1280;
				e_xy.y = rand() % 640;
				break;
			default:
				break;
			}
			xxx = player.player_xy.x - e_xy.x;
			yyy = player.player_xy.y - e_xy.y;
			len1 = sqrt(xxx * xxx + yyy * yyy);
		}	
		e_xy.x += (double)(boss1_speed * xxx) / len1;
		e_xy.y += (double)(boss1_speed * yyy) / len1;
	}
	if (is_xy.x - e_xy.x > 0)
		facing_left = 1;
	else if (is_xy.x - e_xy.x < 0)
		facing_left = 0;
}

void boss1::draw(int delat)
{
	int shadow_x = e_xy.x + (e_width / 2 - shadow_width / 2) + 50;
	int shadow_y = e_xy.y + e_height + 110;
	putimage_plus(shadow_x, shadow_y, &img_shadow);

	if (facing_left)
		boss1_anim_left->play(e_xy.x, e_xy.y, delat);
	else
		boss1_anim_right->play(e_xy.x, e_xy.y, delat);
}

int boss1::attack()
{
	if (stage == 0)
		return 0;
	if (stage > 0 && stage < 5)
		return 1;
	if (stage == 5)
		return 2;
}

void boss1::hurt(int attack)
{
	blood -= attack;
	if (blood <= 0)
		alive = 0;
}