#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"prop.h"

class efa
{
public:
	efa() {};

	virtual ~efa() {};

	//��ⷨ����ײ
	bool checkmagic(const magic& magic);

	//����ӵ���ײ
	bool checkbullet(const bullet& bullet);

	//��������ײ
	bool checkplayer(const player_anim& player);
	//����Ĭ���ƶ���ʽ
	void move(const player_anim& player);
	//Ĭ�ϻ�ͼ
	void draw(int delat);
	//Ĭ��һ���˺�
	void hurt(int attack);

	bool checkalive();

public:
	const double e_speed = 1.8;//Ĭ�Ͻ�ɫ�ٶ�
	const int e_width = 80;//Ĭ�Ͻ�ɫ���
	const int e_height = 80;//Ĭ�Ͻ�ɫ��
	const int shadow_width = 60;//Ĭ��Ӱ�ӿ��

	bool alive = 1;//�Ƿ���
	int blood = 1;//����Ѫ��
	//ӰͼƬ
    IMAGE img_shadow;
	//��������ҵĶ���ָ��(�������ʼ��)
	anim* e_anim_left;
	anim* e_anim_right;

	//��ɫλ��
	POINT e_xy = { 0, 0 };
	//�жϽ�ɫ����
	bool facing_left = 0;
};