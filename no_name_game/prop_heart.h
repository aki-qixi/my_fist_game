#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"role_anim.h"
#include"prop.h"

class prop_heart :public prop
{
public:
	prop_heart(int frm_num, POINT e_xy, IMAGE& img);

	~prop_heart() {};

};