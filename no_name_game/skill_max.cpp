#include"skill_max.h"

skill_max::skill_max(fast_load* f_max_anim)
{
	max_anim = new anim(f_max_anim, 45);
}

void skill_max::draw(int xx,int yy,int delat)
{
	max_anim->play(xx,yy,delat);
}