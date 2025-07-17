#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"

class snail:public efa
{
public:
	snail(fast_load* f_snail_anim_left,fast_load* f_snail_anim_right);

	~snail();

	//��ⷨ����ײ
	bool checkmagic(const magic& magic);

	//����ӵ���ײ
	bool checkbullet(const bullet& bullet);

	//��������ײ
	bool checkplayer(const player_anim& player);

	void move(const player_anim& player);

	void draw(int delat);

	void hurt(int attack);

	bool checkalive();


private:
	const double snail_speed = 1.5;//��ɫ�ٶ�
	const int snail_width = 80;//��ɫ���
	const int snail_height = 80;//��ɫ��
	const int shadow_width = 60;//Ӱ�ӿ��
	const int player_fra_num = 8;//����ͼƬ��

	bool alive = 1;//�Ƿ���
	int blood = 2;//����Ѫ��

	//ӰͼƬ
	IMAGE img_shadow;
	//���������������ƶ���ָ��
	anim* snail_anim_left;
	anim* snail_anim_right;	
	//�жϽ�ɫ����
	bool facing_left = 0;
public:
	//��ɫλ��
	POINT e_xy={ 0,0 };

};