#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"role_anim.h"
#include"prop.h"

class coin:public prop
{
public:
	coin(int frm_num,POINT e_xy,fast_load* prop_coin1_anim,int type );

	~coin() {};

	void move(const player_anim& player);

public:
	int coin_type;
	int coin_speed = 8;

};
