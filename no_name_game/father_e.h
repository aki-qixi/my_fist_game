#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"prop.h"

class efa
{
public:
	efa() {};

	virtual ~efa() {};

	//检测法阵碰撞
	bool checkmagic(const magic& magic);

	//检测子弹碰撞
	bool checkbullet(const bullet& bullet);

	//检测玩家碰撞
	bool checkplayer(const player_anim& player);
	//敌人默认移动方式
	void move(const player_anim& player);
	//默认绘图
	void draw(int delat);
	//默认一点伤害
	void hurt(int attack);

	bool checkalive();

public:
	const double e_speed = 1.8;//默认角色速度
	const int e_width = 80;//默认角色宽度
	const int e_height = 80;//默认角色高
	const int shadow_width = 60;//默认影子宽度

	bool alive = 1;//是否存活
	int blood = 1;//敌人血量
	//影图片
    IMAGE img_shadow;
	//向左和向右的动画指针(在子类初始化)
	anim* e_anim_left;
	anim* e_anim_right;

	//角色位置
	POINT e_xy = { 0, 0 };
	//判断角色方向
	bool facing_left = 0;
};