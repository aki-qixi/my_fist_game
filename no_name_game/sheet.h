#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"bullet.h"
#include"role_anim.h"
#include"magic.h"
#include"father_e.h"

class sheet :public efa
{
public:
	sheet(fast_load* f_sheet_anim_left, fast_load* f_sheet_anim_right);

	~sheet();

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
	const double e_speed = 3;//��ɫ�ٶ�
public:
	const int e_width = 100;//��ɫ���
	const int e_height = 100;//��ɫ��
private:
	const int shadow_width = 60;//Ӱ�ӿ��
	const int player_fra_num = 8;//����ͼƬ��

	bool alive = 1;//�Ƿ���
	int blood = 12;//����Ѫ��

	//ӰͼƬ
	IMAGE img_shadow;
	//���������������ƶ���ָ��
	anim* e_anim_left;
	anim* e_anim_right;
	//�жϽ�ɫ����
	bool facing_left = 0;
public:
	//��ɫλ��
	POINT e_xy = { 0,0 };
};