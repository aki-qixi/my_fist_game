#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"

class boss1:public efa
{
public:
	boss1(fast_load* f_boss1_anim_left, fast_load* f_boss1_anim_right,const player_anim& player);

	~boss1() {};

	//检测法阵碰撞
	bool checkmagic(const magic& magic);

	//检测子弹碰撞
	bool checkbullet(const bullet& bullet);

	//检测玩家碰撞
	bool checkplayer(const player_anim& player);

	void move(const player_anim& player);

	void draw(int delat);

	int attack();

	bool checkalive();

	void hurt(int attack);


private:
	double boss1_speed = 4;//角色速度
public:
	const int boss1_width = 200;//角色宽度
	const int boss1_height = 200;//角色高
private:
	const int shadow_width = 150;//影子宽度
	const int player_fra_num = 4;//动画图片数

	bool alive = 1;//是否存活
public:
	int blood = 250;//敌人血量
private:

	//影图片
	IMAGE img_shadow;
	//加载向左还是向右移动的指针
	anim* boss1_anim_left;
	anim* boss1_anim_right;
	//判断角色方向
	bool facing_left = 0;
	//追击范围
	int set_x = 180;

	//stage5
	int xxx=1;
	int yyy=1;
	int len1=1;

public:
	//进攻阶段
	int stage = 0;
	//角色位置
	POINT e_xy = { 0,0 };

};