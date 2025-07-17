#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"bee.h"

class ebullet
{
public:
	ebullet(const POINT e_xy, const player_anim& player);

	~ebullet() {};

	void draw();

	void move();

	bool checkplayer(const player_anim &player);

private:
	POINT ebullet_xy = { 0,0 };

	const int ebullet_size = 8;
	const double ebullet_speed = 5;

	double xx = 0;
	double yy = 0;
	double rr = 0;

};
