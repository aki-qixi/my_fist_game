#include"e_bullet.h"

ebullet::ebullet(const POINT e_xy,const player_anim &player)
{
	ebullet_xy.x = e_xy.x + 40;
	ebullet_xy.y = e_xy.y + 40;
	xx = player.player_xy.x - ebullet_xy.x;
    yy = player.player_xy.y - ebullet_xy.y;
	rr= sqrt(xx * xx + yy * yy);
}

void ebullet::draw()
{
	setlinecolor(RGB(255, 155, 50));
	setfillcolor(RGB(150, 0, 0));
	fillcircle(ebullet_xy.x, ebullet_xy.y, ebullet_size);
}

void ebullet::move()
{
	if(rr>0)
	{
		ebullet_xy.x += (double)(ebullet_speed * xx) / rr;
		ebullet_xy.y += (double)(ebullet_speed * yy) / rr;
	}
}

bool ebullet::checkplayer(const player_anim& player)
{
	bool is_in_x = ebullet_xy.x >= player.player_xy.x+20 && ebullet_xy.x <= player.player_xy.x + 60;
	bool is_in_y = ebullet_xy.y >= player.player_xy.y+20 && ebullet_xy.y <= player.player_xy.y + 60;
	return is_in_x && is_in_y;
}