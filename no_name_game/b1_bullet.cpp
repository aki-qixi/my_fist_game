#include"b1_bullet.h"

b1_bullet::b1_bullet(const boss1& boss,fast_load* f_b1_bullet_anim, const player_anim& player)
{
	b1_xy = boss.e_xy;
	b1_xy.x += boss.e_width / 2;
	b1_xy.y += boss.e_height / 2;
	b1_bullet_anim = new anim(f_b1_bullet_anim, 45);

	xx = player.player_xy.x - b1_xy.x;
	yy = player.player_xy.y - b1_xy.y;
}

void b1_bullet::move(const player_anim& player, const boss1& boss,int move_type, int b_type)
{
	double len = sqrt(xx * xx + yy * yy);
	double xy = sqrt(2) / 2;
	if (move_type == 0 && len > 0)
	{
		b1_xy.x += (double)(b1_speed * xx) / len;
		b1_xy.y += (double)(b1_speed * yy) / len;
	}
	if (move_type == 1)
	{
		if (b_type == 1)
			b1_xy.y += b1_speed;
		if (b_type == 2)
			b1_xy.x += b1_speed;
		if (b_type == 3)
			b1_xy.y -= b1_speed;
		if (b_type == 4)
			b1_xy.x -= b1_speed;
		if (b_type == 5)
		{
			b1_xy.x -= b1_speed * xy;
			b1_xy.y -= b1_speed * xy;
		}
		if (b_type == 6)
		{
			b1_xy.x += b1_speed * xy;
			b1_xy.y -= b1_speed * xy;
		}
		if (b_type == 7)
		{
			b1_xy.x += b1_speed * xy;
			b1_xy.y += b1_speed * xy;
		}
		if (b_type == 8)
		{
			b1_xy.x -= b1_speed * xy;
			b1_xy.y += b1_speed * xy;
		}
	}
	if (move_type == 2)
	{
		if (b_type >= 1 && b_type <= 3)
		b1_xy.x += (double)(b1_speed * xx) / len;
		b1_xy.y += (double)(b1_speed * yy) / len;
		if (b_type >= 4 && b_type <= 6)
		{
			const double speed2 = 0.0055;//切向速度
			double radin_interval = 2 * 3.14159 / 5;//弧度间隔
			double radius = 100 + 25 * sin(GetTickCount());
			for (int i = 0; i < 5; i++)
			{
				double radian = GetTickCount() * speed2 + radin_interval*i;
				b1_xy.x = boss.e_xy.x + 40 + (int)(radius * sin(radian));
				b1_xy.y = boss.e_xy.y + 40 + (int)(radius * cos(radian));
			}
		}
	}
}

bool b1_bullet::checkplayer(const player_anim& player)
{
	bool is_in_x = b1_xy.x+30 >= player.player_xy.x + 20 && b1_xy.x+30 <= player.player_xy.x + 60;
	bool is_in_y = b1_xy.y+30 >= player.player_xy.y + 20 && b1_xy.y+30 <= player.player_xy.y + 60;
	return is_in_x && is_in_y;
}

void b1_bullet::draw(int delta)
{
	b1_bullet_anim->play(b1_xy.x, b1_xy.y, delta);
}