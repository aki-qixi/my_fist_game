#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"

class eagle :public efa
{
public:
	eagle(fast_load* f_eagle_anim_left, fast_load* f_eagle_anim_right);

	~eagle() {};

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
	const double bee_speed = 4;//��ɫ�ٶ�
	const int bee_width = 80;//��ɫ���
	const int bee_height = 80;//��ɫ��
	const int shadow_width = 60;//Ӱ�ӿ��
	const int player_fra_num = 4;//����ͼƬ��

	bool alive = 1;//�Ƿ���
	int blood = 7;//����Ѫ��

	int up_left = 0;

	//ӰͼƬ
	IMAGE img_shadow;
	//���������������ƶ���ָ��
	anim* e_anim_left;
	anim* e_anim_right;
	//�жϽ�ɫ����
	bool facing_left = 0;
	int set_x = 200;
public:
	int stage = 0;
	//��ɫλ��
	POINT e_xy = { 0,0 };

};
