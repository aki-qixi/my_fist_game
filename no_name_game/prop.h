#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"load_anim.hpp"
#include"role_anim.h"
#include<ctime>

class prop
{
public:
	prop() {};

	prop(int frm_num,POINT e_xy);

	~prop() {};

	void draw(int delat);

	bool checkplayer(const player_anim& player);

	void virtual yaku() {};

public:
	POINT prop_xy = { 0,0 };//����λ��

	IMAGE img_prop;//����ͼ����
	IMAGE img_shadow;//��Ӱͼ

	anim* prop_anim;//���߶�������

	int prop_height=16;//����Ĭ�ϸ�
    int prop_width=16;//����Ĭ�Ͽ�
	const int shadow_width = 16;//Ĭ����Ӱ��

	int prop_frm = 1;//����ͼƬ��

	int shadow_xx = 0;//��Ӱƫ��ֵ���������ʼ��
	int shadow_yy = 0;

};
