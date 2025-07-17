#include"magic.h"

magic::magic(fast_load* f_magic_anim)
{
	magic_anim = new anim(f_magic_anim, 45);
}

void magic::draw(int delat)
{
	magic_anim->play(magic_xy.x - 50, magic_xy.y - 50, delat);
}

bool magic::checkplayer(const player_anim& player)
{
	bool is_in_x = magic_xy.x - 20 >= player.player_xy.x + 20 && magic_xy.x - 20 <= player.player_xy.x + 60;
	bool is_in_y = magic_xy.y - 20 >= player.player_xy.y + 20 && magic_xy.y - 20 <= player.player_xy.y + 60;
	return is_in_x && is_in_y;
}