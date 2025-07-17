#pragma once
#include<graphics.h >
#include"role_anim.h"

class skill
{
public:
	skill() {};

	~skill() {};

	//升级最大生命值函数
	void max_hp_up(player_anim& player);

	//升级法球函数
	void magic_up(player_anim& player);

	void magic_kill_num(player_anim& player);

	//升级速度函数
	void speed_up(player_anim& player);

	//升级普通攻击函数
	void player_attack_up(player_anim& player);

	//升级ball函数
	void ball_skill_up(player_anim& player);

	//升级时停函数
	void the_world_up(player_anim& player);

	//升级最大能量上限的技能
	void max_power_up(player_anim& player);

	//升级max技能
	void skill_max_up(player_anim& player);


private:


};
