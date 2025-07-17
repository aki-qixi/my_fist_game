#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"
#include"prop.h"

class enemy :public efa
{
public:
	enemy(fast_load* f_enemy_anim_left, fast_load* f_enemy_anim_right);

	~enemy();

	void hurt(int attack);

	bool checkalive();

private:
	const double enemy_speed = 1.8;//��ɫ�ٶ�
	const int enemy_width = 80;//��ɫ���
	const int enemy_height = 80;//��ɫ��
	const int shadow_width = 60;//Ӱ�ӿ��
	const int player_fra_num = 6;//����ͼƬ��

	bool alive = 1;//�Ƿ���
	int blood = 1;//����Ѫ��

	//�жϽ�ɫ����
	bool facing_left = 0;

};