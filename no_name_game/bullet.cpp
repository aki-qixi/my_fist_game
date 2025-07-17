#include"bullet.h"

bullet::bullet(const player_anim &player)
{
	bullet_xy.x = player.player_xy.x + 40;
	bullet_xy.y = player.player_xy.y + 40;
	xx = player.is_move_right - player.is_move_left;
	yy = player.is_move_down - player.is_move_up;
	left_or_right = player.left_or_right;
}


void bullet::draw(const player_anim &player)
{
	setfillcolor(WHITE);
	fillcircle(bullet_xy.x, bullet_xy.y, bullet_size);

	setfillcolor(RGB(255, 215, 0));  // ÁÁ½ðÉ«
	fillcircle(bullet_xy.x, bullet_xy.y, bullet_size / 2);


}

void bullet::move(const player_anim &player)
{
	double len = sqrt(xx * xx + yy * yy);

	if (len != 0)
	{
		double xxx = xx / len;
		double yyy = yy / len;
		bullet_xy.x += (int)(bullet_speed * xxx);
		bullet_xy.y += (int)(bullet_speed * yyy);
	}
	else
	{
		bullet_xy.x += (int)(bullet_speed *left_or_right);
	}
}
