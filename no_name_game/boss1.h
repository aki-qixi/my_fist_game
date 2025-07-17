#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"

class boss1:public efa
{
public:
	boss1(fast_load* f_boss1_anim_left, fast_load* f_boss1_anim_right,const player_anim& player);

	~boss1() {};

	//��ⷨ����ײ
	bool checkmagic(const magic& magic);

	//����ӵ���ײ
	bool checkbullet(const bullet& bullet);

	//��������ײ
	bool checkplayer(const player_anim& player);

	void move(const player_anim& player);

	void draw(int delat);

	int attack();

	bool checkalive();

	void hurt(int attack);


private:
	double boss1_speed = 4;//��ɫ�ٶ�
public:
	const int boss1_width = 200;//��ɫ���
	const int boss1_height = 200;//��ɫ��
private:
	const int shadow_width = 150;//Ӱ�ӿ��
	const int player_fra_num = 4;//����ͼƬ��

	bool alive = 1;//�Ƿ���
public:
	int blood = 250;//����Ѫ��
private:

	//ӰͼƬ
	IMAGE img_shadow;
	//���������������ƶ���ָ��
	anim* boss1_anim_left;
	anim* boss1_anim_right;
	//�жϽ�ɫ����
	bool facing_left = 0;
	//׷����Χ
	int set_x = 180;

	//stage5
	int xxx=1;
	int yyy=1;
	int len1=1;

public:
	//�����׶�
	int stage = 0;
	//��ɫλ��
	POINT e_xy = { 0,0 };

};