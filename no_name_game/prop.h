#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"role_anim.h"
#include<ctime>

class prop
{
public:
	prop() {};

	prop(int frm_num,POINT e_xy);

	~prop() {};

	void draw(int delat);

	bool checkplayer(const player_anim& player);

	void virtual yaku() {};

public:
	POINT prop_xy = { 0,0 };//道具位置

	IMAGE img_prop;//道具图对象
	IMAGE img_shadow;//阴影图

	anim* prop_anim;//道具动画对象

	int prop_height=16;//道具默认高
    int prop_width=16;//道具默认宽
	const int shadow_width = 16;//默认阴影宽

	int prop_frm = 1;//道具图片数

	int shadow_xx = 0;//阴影偏差值，在子类初始化
	int shadow_yy = 0;

};
