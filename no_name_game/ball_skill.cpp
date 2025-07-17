#include"ball_skill.h"

ball::ball(fast_load* f_ball_anim, const player_anim& player)
{
	ball_anim = new anim(f_ball_anim, 45);
	ball_xy = player.player_xy;
	xx = player.is_move_right - player.is_move_left;
	yy = player.is_move_down - player.is_move_up;
	left_or_right = player.left_or_right;
}

ball::~ball()
{
	delete ball_anim;
}

void ball::draw(int delta)
{
	ball_anim->play(ball_xy.x, ball_xy.y, delta);
}

void ball::move()
{
	double len = sqrt(xx * xx + yy * yy);

	if (len != 0)
	{
		double xxx = xx / len;
		double yyy = yy / len;
		ball_xy.x += (int)(ball_speed * xxx);
		ball_xy.y += (int)(ball_speed * yyy);
	}
	else
	{
		ball_xy.x += (int)(ball_speed * left_or_right);
	}
}

bool ball::check_e(POINT e_xy, int e_width, int e_height)
{
	int ball_x1 = ball_xy.x + ball_width / 4;
	int ball_y1 = ball_xy.y + ball_height / 4;
	int ball_x2 = ball_xy.x + 75;
	int ball_y2 = ball_xy.y + 75;
	if (((ball_x1<e_xy.x + e_width && ball_x1>e_xy.x) || (ball_x2 > e_xy.x && ball_x2 < e_xy.x + e_width)) && 
		((ball_y1<e_xy.y + e_height && ball_y1>e_xy.y) || (ball_y2 > e_xy.y && ball_y2 < e_xy.y + e_height)))
		return 1;
	else
		return 0;
	
}