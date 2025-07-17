#pragma once
#include<string>
#include<vector>
#include<graphics.h >
#include<fstream>
#include"load_anim.hpp"
#define filename "coin_file.txt"
#define skill_file "skill_file.txt"
using namespace std;

class player_anim
{
public:
	player_anim(fast_load* f_player_anim_left, fast_load* f_player_anim_right)
	{
		loadimage(&img_shadow, _T("img/shadow_player.png"));//������Ӱ
		player_anim_left = new anim(f_player_anim_left, 45);
		player_anim_right = new anim(f_player_anim_right, 45);

		ifstream ifs;
		ifs.open(filename, ios::in);
		if (!ifs.is_open())
		{
			player_coin = 0;
			ifs.close();
		}
		char ch;
		ifs >> ch;
		if (ifs.eof())
		{
			player_coin = 0;
			ifs.close();
		}
		chushicoin();
		ifs.open(skill_file, ios::in);
		
		if (!ifs.is_open())
		{
			max_power = 180;
			is_magic = 0;//�����˺�����
			magic_num = 5;    //�����ɱ������
			is_ball_skill = 0;//�����������˺�
			speed_up = 0;//����
			max_hp = 3;//���Ѫ������
			player_attack = 1;  //player��ͨ�����˺�  
			is_the_world = 0; //ʱͣ��������
			is_coin_fly = 1;  //�Զ�ʰȡӲ�Ҽ���ʵ��
			is_max = 0;//max��������
			ifs.close();
			save_skill();
		}
		ifs >> ch;
		if (ifs.eof())
		{
			max_power = 180;
			is_magic = 0;//�����˺�����
			magic_num = 5;    //�����ɱ������
			is_ball_skill = 0;//�����������˺�
			speed_up = 0;//����
			max_hp = 3;//���Ѫ������
			player_attack = 1;  //player��ͨ�����˺�  
			is_the_world = 0; //ʱͣ��������
			is_coin_fly = 1;  //�Զ�ʰȡӲ�Ҽ���ʵ��
			is_max = 0;//max��������
			ifs.close();
			save_skill();
		}
		chushi_all();
	}

	~player_anim(){}
	//������Ұ�����Ϣ
	void player_msg(const ExMessage& msg);

	//��������ƶ�
	void move();

	//�������
	void draw(int delat);

	//����ܻ�
	void hurt(int attack = 1);

	//����hp
	void draw_hp(IMAGE& img);

	bool checkalive();

	void cure();//���������

	void coinup(int coin_type);//��һ�õĽ�Ǯ����������ײ��

	int getcoin();//��ȡ���Ǯ��

	void save_coin();//����coin

	void chushicoin();//��ʼӲ��

	void chushi_all();//��ʼ��Ӳ�������

	void stop(const ExMessage& msg);//������Ҿ�����ͣ

	void power_up(int up_num);//��Ҿ��ڷ���ֵ����

	void save_skill();//���漼�ܵȼ�


private:
	double player_speed = 3 + speed_up;//��ɫ�ٶ�
	const int player_width = 80;//��ɫ���
	const int player_height = 80;//��ɫ��
	const int shadow_width = 32;//Ӱ�ӿ��
	const int player_fra_num = 6;//��Ҷ���ͼƬ��

	const int hp_x = 1040;//hp����ʾλ����Ϣ
	const int hp_y = 96;

	int player_hp = 3;//��ҵ�ǰѪ��

public:
	//********************************************��  ��  ��************
	int max_power;//��������ֵ
	int power; //��ҵ�ǰ����ֵ
	int is_magic;//�����˺�����
	int magic_num;    //�����ɱ������
	int is_ball_skill;//�����������˺�
	int speed_up;//����
	int player_coin;//���Ǯ��
	int max_hp;//���Ѫ������
	int player_attack;  //player��ͨ�����˺�  
	bool is_the_world; //ʱͣ��������
	bool is_coin_fly;  //�Զ�ʰȡӲ�Ҽ���ʵ��
	int is_max;//max��������
	//*******************************************************************
private:
	//ӰͼƬ
	IMAGE img_shadow;
	//������������������ƶ���ָ��
	anim *player_anim_left;
	anim *player_anim_right;

	bool alive = 1;

public:
	//�ƶ�����
	bool is_move_up = 0;
	bool is_move_down = 0;
	bool is_move_left = 0;
	bool is_move_right = 0;	

	int left_or_right;

	//��ɫλ��
	POINT player_xy{ 560,320 };

	bool is_stop = 0;
};