#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"boss1.h"

class b1_bullet
{
public:
	b1_bullet(const boss1& boss, fast_load* f_b1_bullet_anim, const player_anim& player);

	~b1_bullet() {};

	void move(const player_anim& player, const boss1& boss,int move_type, int b_type);

	bool checkplayer(const player_anim& player);

	void draw(int delta);

private:
	POINT b1_xy;
	anim* b1_bullet_anim;
	int b1_speed = 5;
	int bullet_type;//上1 右2 下3 左4 左上5 右上6 右下7 左下8

	int xx;
	int yy;
};