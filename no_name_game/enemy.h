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

class enemy :public efa
{
public:
	enemy(fast_load* f_enemy_anim_left, fast_load* f_enemy_anim_right);

	~enemy();

	void hurt(int attack);

	bool checkalive();

private:
	const double enemy_speed = 1.8;//角色速度
	const int enemy_width = 80;//角色宽度
	const int enemy_height = 80;//角色高
	const int shadow_width = 60;//影子宽度
	const int player_fra_num = 6;//动画图片数

	bool alive = 1;//是否存活
	int blood = 1;//敌人血量

	//判断角色方向
	bool facing_left = 0;

};