#pragma once
#include<graphics.h >
#include"role_anim.h"

class skill
{
public:
	skill() {};

	~skill() {};

	//�����������ֵ����
	void max_hp_up(player_anim& player);

	//����������
	void magic_up(player_anim& player);

	void magic_kill_num(player_anim& player);

	//�����ٶȺ���
	void speed_up(player_anim& player);

	//������ͨ��������
	void player_attack_up(player_anim& player);

	//����ball����
	void ball_skill_up(player_anim& player);

	//����ʱͣ����
	void the_world_up(player_anim& player);

	//��������������޵ļ���
	void max_power_up(player_anim& player);

	//����max����
	void skill_max_up(player_anim& player);


private:


};
