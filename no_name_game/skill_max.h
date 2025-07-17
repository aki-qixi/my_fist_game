#pragma once
#include<graphics.h >
#include"role_anim.h"
#include"load_anim.hpp"

class skill_max
{
public:
	skill_max(fast_load* f_max_anim);

	~skill_max() {};

	void draw(int xx,int yy,int delat);

private:
	POINT max_xy = { 0,0 };
	anim* max_anim;
};
