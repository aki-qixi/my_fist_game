#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"

class bee:public efa
{
public:
	bee(fast_load* f_bee_anim_left,fast_load* f_bee_anim_right);

	~bee();

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

	int go_count = 0;//���ؼ�����


private:
	const double bee_speed = 1.5;//��ɫ�ٶ�
	const int bee_width = 80;//��ɫ���
	const int bee_height = 80;//��ɫ��
	const int shadow_width = 60;//Ӱ�ӿ��
	const int player_fra_num = 4;//����ͼƬ��

	bool alive = 1;//�Ƿ���
	int blood = 2;//����Ѫ��

	int up_left = 0;

	//ӰͼƬ
	IMAGE img_shadow;
	//���������������ƶ���ָ��
	anim* bee_anim_left;
	anim* bee_anim_right;
	//�жϽ�ɫ����
	bool facing_left = 0;
public:
	//��ɫλ��
	POINT e_xy={ 0,0 };
};