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

class bear :public efa
{
public:
	bear(fast_load* f_bear_anim_left, fast_load* f_bear_anim_right);

	~bear();

	void hurt(int attack);

	bool checkmagic(const magic& magic);

    bool checkbullet(const bullet& bullet);

	bool checkplayer(const player_anim& player);

	void draw(int delat);

	void move(const player_anim& player);

	bool checkalive();

private:
	const double e_speed = 2;//��ɫ�ٶ�
public:
	const int e_width = 99;//��ɫ���
	const int e_height = 116;//��ɫ��
private:
	const int shadow_width = 80;//Ӱ�ӿ��
	const int player_fra_num = 4;//����ͼƬ��

	bool alive = 1;//�Ƿ���
	int blood = 7;//����Ѫ��

	//�жϽ�ɫ����
	bool facing_left = 0;

};
