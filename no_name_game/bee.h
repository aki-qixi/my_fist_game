#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"

class bee:public efa
{
public:
	bee(fast_load* f_bee_anim_left,fast_load* f_bee_anim_right);

	~bee();

	//检测法阵碰撞
	bool checkmagic(const magic& magic);

	//检测子弹碰撞
	bool checkbullet(const bullet& bullet);

	//检测玩家碰撞
	bool checkplayer(const player_anim& player);

	void move(const player_anim& player);

	void draw(int delat);

	void hurt(int attack);

	bool checkalive();

	int go_count = 0;//来回计数器


private:
	const double bee_speed = 1.5;//角色速度
	const int bee_width = 80;//角色宽度
	const int bee_height = 80;//角色高
	const int shadow_width = 60;//影子宽度
	const int player_fra_num = 4;//动画图片数

	bool alive = 1;//是否存活
	int blood = 2;//敌人血量

	int up_left = 0;

	//影图片
	IMAGE img_shadow;
	//加载向左还是向右移动的指针
	anim* bee_anim_left;
	anim* bee_anim_right;
	//判断角色方向
	bool facing_left = 0;
public:
	//角色位置
	POINT e_xy={ 0,0 };
};