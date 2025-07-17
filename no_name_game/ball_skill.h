#pragma once
#include<graphics.h >
#include<string>
#include<cmath>
#include<vector>
#include"load_anim.hpp"
#include"role_anim.h"

class ball
{
public:
	ball(fast_load* f_ball_anim,const player_anim& player);

	~ball();

	void draw(int delta);

	void move();

	bool check_e(POINT e_xy,int e_width,int e_height);


private:
	POINT ball_xy = { 0,0 };
	double ball_speed = 4;
	anim* ball_anim;
	int xx = 0;
	int yy = 0;
	int left_or_right;
	int ball_width = 100;
	int ball_height = 100;
};
