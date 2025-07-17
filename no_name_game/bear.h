#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"
#include"prop.h"

class bear :public efa
{
public:
	bear(fast_load* f_bear_anim_left, fast_load* f_bear_anim_right);

	~bear();

	void hurt(int attack);

	bool checkmagic(const magic& magic);

    bool checkbullet(const bullet& bullet);

	bool checkplayer(const player_anim& player);

	void draw(int delat);

	void move(const player_anim& player);

	bool checkalive();

private:
	const double e_speed = 2;//角色速度
public:
	const int e_width = 99;//角色宽度
	const int e_height = 116;//角色高
private:
	const int shadow_width = 80;//影子宽度
	const int player_fra_num = 4;//动画图片数

	bool alive = 1;//是否存活
	int blood = 7;//敌人血量

	//判断角色方向
	bool facing_left = 0;

};
