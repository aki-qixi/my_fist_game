#pragma once
#include<graphics.h >

class scene_begin
{
public:
	void on_update(POINT M_xy ,player_anim &player)
	{
		player.chushi_all();
	}
};