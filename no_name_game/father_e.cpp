#include"father_e.h"

bool efa::checkmagic(const magic& magic)
{
	bool is_in_x = magic.magic_xy.x >= e_xy.x && magic.magic_xy.x <= e_xy.x + e_width;
	bool is_in_y = magic.magic_xy.y >= e_xy.y && magic.magic_xy.y <= e_xy.y + e_height;
	return is_in_x && is_in_y;
}

bool efa::checkbullet(const bullet& bullet)
{
	bool is_in_x = bullet.bullet_xy.x >= e_xy.x && bullet.bullet_xy.x <= e_xy.x + e_width;
	bool is_in_y = bullet.bullet_xy.y >= e_xy.y && bullet.bullet_xy.y <= e_xy.y + e_height;
	return is_in_x && is_in_y;
}

bool efa::checkplayer(const player_anim& player)
{
	POINT check_enemy_xy = { e_xy.x + e_width / 2,e_xy.y + e_height / 2 };
	bool is_in_x = check_enemy_xy.x >= player.player_xy.x && check_enemy_xy.x <= player.player_xy.x + 80;
	bool is_in_y = check_enemy_xy.y >= player.player_xy.y && check_enemy_xy.y <= player.player_xy.y + 80;
	return is_in_x && is_in_y;
}

void efa::move(const player_anim& player)
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

void efa::draw(int delat)
{
	int shadow_x = e_xy.x + (e_width / 2 - shadow_width / 2);
	int shadow_y = e_xy.y + e_height - 8;
	putimage_plus(shadow_x, shadow_y, &img_shadow);

	if (facing_left)
		e_anim_left->play(e_xy.x, e_xy.y, delat);
	else
		e_anim_right->play(e_xy.x, e_xy.y, delat);
}

void efa::hurt(int attack)
{
	blood -= attack;
	if (blood == 0)
		alive = 0;
}

bool efa::checkalive()
{
	return alive;
}