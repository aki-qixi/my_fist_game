#include<graphics.h >
#include <tchar.h>
#include <Windows.h>
#include<string>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<graphics.h >
#include"bullet.h"
#include"enemy.h"
#include"snail.h"
#include"bee.h"
#include"bear.h"
#include"eagle.h"
#include"sheet.h"
#include"magic.h"
#include"e_bullet.h"
#include"fast_load.hpp"
#include"prop_heart.h"
#include"prop_coin.h"
#include"scene.h"
#include"scene_menu.hpp"
#include"scene_begin.hpp"
#include"scene_shop.hpp"
#include"scene_help.hpp"
#include"scene_setting.hpp"
#include"skill.h"
#include"ball_skill.h"
#include"boss1.h"
#include"b1_bullet.h"
#include"skill_max.h"
#pragma comment(lib,"Winmm.lib")
using namespace std;

//*********************************************************************************ȫ  ��  ��  ��  ��********************************************************************************
int player_attack_interval = 50;   //��ɫ����Ƶ��
int enemy_coin1_p = 2;             //Ұ�����coin1�ĸ���
int enemy_heart_p = 50;            //�����heart�ĸ���
int bear_heart_p = 3;              //�ܵ����ĵĸ���
int eagle_heart_p = 4;
int bee_heart_p = 5;
int sheet_coin3_p = 5;
int bee_coin2_p = 2;               //bee����coin2�ĸ���
int magic_on_interval = 150;       //�������֡��������
int bee_attack_interval = 300;     //bee�����ӵ���֡���
int player_ball_interval = 200;    //ball�ĳ���ʱ����CD
int ball_attack_interval = 10;      //ball�Ĺ���Ƶ��
int the_world_interval = 250;      //ʱͣ������֡��
int ball_power_cost = 15;          //ball���ܷ�������
int the_world_power_cost = 15;     //ʱͣ���ܷ�������
int skill_max_cost = 45;           //max���ܷ�������
int is_max_hurt = 0;               //��¼max�˺��Ĵ���
int temp = 0;                      //����death�������һ��ͼ���ŵ�֡��
int player_hurt_interval = 30;     //��ɫ�ܻ�cd
int boss1_hurt_interval = 0;         //boss1�ܻ�cd  
int b1_move_type = 0;                //b1 move_type
int eagle_attack1_interval = 250;    //eagle��stage==1ʱ�Ĺ������
int eagle_attack2_interval = 100;    //eagle��stage==1ʱ�Ĺ������

//***************************************************��  ��  ��  ��  ��  ��  ָ  ��***************************************************
fast_load* f_player_anim_left;
fast_load* f_player_anim_right;

fast_load* f_enemy_anim_left;
fast_load* f_enemy_anim_right;

fast_load* f_bee_anim_left;
fast_load* f_bee_anim_right;

fast_load* f_snail_anim_left;
fast_load* f_snail_anim_right;

fast_load* f_bear_anim_left;
fast_load* f_bear_anim_right;

fast_load* f_eagle_anim_left;
fast_load* f_eagle_anim_right;

fast_load* f_sheet_anim_left;
fast_load* f_sheet_anim_right;

fast_load* f_boss1_anim_left;
fast_load* f_boss1_anim_right;
fast_load* f_b1_bullet_anim;

fast_load* f_coin1_anim;
fast_load* f_coin2_anim;
fast_load* f_coin3_anim;

fast_load* f_magic_anim;

fast_load* f_ball_anim;

fast_load* f_death_anim;
anim* death_anim;

fast_load* f_max_anim;

//************************************************************************************************************************************

//���ʺ���
bool check_prop(int p)//1/p��ʾ����
{
	srand((unsigned int)time(NULL));
	int temp = rand() % p;
	if (temp == 0)
		return 1;
	else
		return 0;
}
//************************************************************************ȫ  ��  ��  ��  ��  ��*******************************************************************************
//���heart����
void addheart(vector<prop_heart*>& heart_list,POINT e_xy,IMAGE &img_prop_heart)
{
	heart_list.push_back(new prop_heart(1, e_xy ,img_prop_heart));
}

//���coin����
void addcoin1(vector<coin*>& coin1_list, POINT e_xy,int coin_type)
{
	if(coin_type==1)
	    coin1_list.push_back(new coin(14, e_xy, f_coin1_anim,coin_type));
	else if(coin_type==2)
		coin1_list.push_back(new coin(14, e_xy, f_coin2_anim, coin_type));
	else if (coin_type == 3)
		coin1_list.push_back(new coin(14, e_xy, f_coin3_anim, coin_type));
}

//���boss1
void addboss1(boss1*& boss,const player_anim& player)
{
	boss = new boss1(f_boss1_anim_left,f_boss1_anim_right,player);
	boss1_hurt_interval = 30;
}

//���b1�ӵ�
void addb1_bullet(vector<b1_bullet*> &b1_bullet_list, vector<int> &b1_bullet_type_list, vector<int> &b1_bullet_interval ,boss1 &boss, const player_anim& player)
{
	static int i = 0;
	static int j = 0;
	if (boss.stage == 1)
	{
		j++;
		b1_move_type = 1;
	}
	if (boss.stage == 2)
	{
		j = 0;
		temp = 0;
	}
	if ( j<=64 )
	{
		b1_bullet_list.push_back(new b1_bullet(boss, f_b1_bullet_anim,player));
		b1_bullet_type_list.push_back(i++ % 8 + 1);
		b1_bullet_interval.push_back(0);
	}
}

//���sheet
void addsheet(vector<sheet*>& sheet_list, vector<int>& sheet_interval, vector<int>& sheet_hurt_interval,vector<magic*>& e_magic_list, int score)
{
	int interval = 800;
	if (score >= 225)
		interval = 600;
	if (score >= 400)
		interval = 450;
	static int counter = 0;
	if (++counter % interval == 0)
	{
		sheet_list.push_back(new sheet(f_sheet_anim_left, f_sheet_anim_right));
		e_magic_list.push_back(new magic(f_b1_bullet_anim));
		sheet_interval.push_back(0);
		sheet_hurt_interval.push_back(0);
	}
}

//���eagle����
void addeagle(vector<eagle*> &eagle_list,vector<int> &eagle_interval,vector<int>&eagle_hurt_interval ,int score)
{
	int interval = 500;
	if (score >= 180)
		interval = 800;
	if (score >= 400)
		interval = 600;
	static int counter = 0;
	if (++counter % interval == 0)
	{
		eagle_list.push_back(new eagle(f_eagle_anim_left, f_eagle_anim_right));
		eagle_interval.push_back(0);
		eagle_hurt_interval.push_back(0);
	}
}

//���bee����
void addbee(vector<bee*>& bee_list, vector<int>&bee_interval, int score)
{
	int interval = 300;
	if (score >= 90)
		interval = 300;
	if (score >= 135)
		interval = 300;
	if (score >= 135)
		interval = 500;
	static int counter = 0;
	if ((++counter) % interval == 0)
	{
		bee_list.push_back(new bee(f_bee_anim_left, f_bee_anim_right));
		bee_interval.push_back(0);
	}
}

//�����ţ����
void addsnail(vector<snail*>& snail_list, vector<int>& snail_hurt_interval,int score)
{
	int interval = 200;
	if (score >= 45)
		interval = 200;
	if (score >= 90)
		interval = 250;
	if (score >= 135)
		interval = 250;
	if (score >= 180)
		interval = 250;
	static int counter = 0;
	if ((++counter) % interval == 0)
	{
		snail_hurt_interval.push_back(0);
		snail_list.push_back(new snail(f_snail_anim_left, f_snail_anim_right));
	}
}

//����ܵ���
void addbear(vector<bear*>& bear_list, vector<int>& bear_hurt_interval, int score)
{
	int interval=800;
	if (score >= 135)
		interval = 1200;
	if (score >= 180)
		interval = 1300;
	static int counter = 0;
	if ((++counter) % interval == 0)
	{
		bear_hurt_interval.push_back(0);
		bear_list.push_back(new bear(f_bear_anim_left, f_bear_anim_right));
	}
}

//���Ұ�����
void addenemy(vector<enemy*>& enemy_list,const int score)
{
	int interval = 150;
	if (score >= 15)
		interval = 200;
	if (score >= 45)
		interval = 200;
	if (score >= 90)
		interval = 200;
	if (score >= 135)
		interval = 200;
	if (score >= 180)
		interval = 150;
	static int counter = 0;
	if ((++counter) % interval == 0)
	{
		enemy_list.push_back(new enemy(f_enemy_anim_left, f_enemy_anim_right));
	}
}

void add_death(POINT xy,vector<POINT>&death_point)
{
	death_point.push_back(xy);
}
//���·���λ��
void update_magic(vector<magic*>& magic_list, const player_anim& player)
{
	const double speed1 = 0.0045;//�����ٶ�
	const double speed2 = 0.0055;//�����ٶ�
	double radin_interval = 2 * 3.14159 / 3;//���ȼ��
	double radius = 100 + 25 * sin(GetTickCount() * speed1);
		for (int i = 0; i < 3; i++)
		{
			double radian = GetTickCount() * speed2 + radin_interval * i;
			magic_list[i]->magic_xy.x = player.player_xy.x + 40 + (int)(radius * sin(radian));
			magic_list[i]->magic_xy.y = player.player_xy.y + 40 + (int)(radius * cos(radian));
		}
}

//����e_magicλ��
void update_e_magic(magic& e_magic, const sheet& Sheet)
{
	const double speed1 = 0.0045;//�����ٶ�
	const double speed2 = 0.0055;//�����ٶ�
	double radius = 100 + 25 * sin(GetTickCount() * speed1);
    double radian = GetTickCount() * speed2;
	e_magic.magic_xy.x = Sheet.e_xy.x + 40 + (int)(radius * sin(radian));
	e_magic.magic_xy.y = Sheet.e_xy.y + 40 + (int)(radius * cos(radian));
}

//��������
void draw_score(int score)
{
	AddFontResourceEx(_T("FZMWFont.ttf"), FR_PRIVATE, 0);
	static TCHAR text[64];
	_stprintf_s(text, _T("��ǰ�÷֣�%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 248, 220));
	settextstyle(32, 0, _T("����������"));
	outtextxy(10, 10, text);
}

//���ڽ��������
void draw_money(player_anim& player, int x = 250, int y = 10)
{
	AddFontResourceEx(_T("FZMWFont.ttf"), FR_PRIVATE, 0);
	static TCHAR text[64];
	_stprintf_s(text, _T("��ң�%d"), player.getcoin());

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 215, 0));
	settextstyle(32, 0, _T("����������"));
	outtextxy(x, y, text);
}

//���ڷ���ֵ����
void draw_power(player_anim& player)
{
	AddFontResourceEx(_T("FZMWFont.ttf"), FR_PRIVATE, 0);
	static TCHAR text[64];
	_stprintf_s(text, _T("����ֵ��%d / %d"), player.power,player.max_power);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(176, 213, 230));
	settextstyle(32, 0, _T("����������"));
	outtextxy(500, 10, text);
}

//shop�ڵȼ�����
void draw_skill_lev(int skill_lev, int max_lev, int x, int y)
{
	AddFontResourceEx(_T("FZMWFont.ttf"), FR_PRIVATE, 0);
	static TCHAR text[64];
	_stprintf_s(text, _T(" % d/% d"),skill_lev , max_lev);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(176, 213, 230));
	settextstyle(32, 0, _T("����������"));
	outtextxy(x, y, text);
}

//********************************************************************************�� �� ��*********************************************************************************
int main()
{
	initgraph(1280, 720);//���ƴ���
	//***********************************************************************��  Դ  ��  ��  ��****************************************************************************
	//���ؽ�ɫͼƬ
	f_player_anim_left = new fast_load(_T("img/cat_left_%d.png"), 6,80,80);
    f_player_anim_right = new fast_load(_T("img/cat_right_%d.png"), 6,80,80);
	f_bee_anim_left = new fast_load(_T("img/bee_left_%d.png"), 4);
    f_bee_anim_right = new fast_load(_T("img/bee_right_%d.png"), 4);
    f_enemy_anim_left = new fast_load(_T("img/boar_left_%d.png"), 6);
	f_enemy_anim_right = new fast_load(_T("img/boar_right_%d.png"), 6);
    f_snail_anim_left = new fast_load(_T("img/snail_left_%d.png"), 8);
	f_snail_anim_right = new fast_load(_T("img/snail_right_%d.png"), 8);
	f_bear_anim_left = new fast_load(_T("img/bear_left_%d.png"), 4, 99, 116);
	f_bear_anim_right = new fast_load(_T("img/bear_right_%d.png"), 4, 99, 116);
	f_sheet_anim_left = new fast_load(_T("img/Sheet_left_%d.png"), 8, 100, 100);
	f_sheet_anim_right = new fast_load(_T("img/Sheet_right_%d.png"), 8, 100, 100);
	f_eagle_anim_left = new fast_load(_T("img/eagle_left_%d.png"), 4, 80, 80);
	f_eagle_anim_right = new fast_load(_T("img/eagle_right_%d.png"), 4, 80, 80);
	f_boss1_anim_right = new fast_load(_T("img/MOVE_right_%d.png"), 4, 200, 200);
	f_boss1_anim_left = new fast_load(_T("img/MOVE_left_%d.png"), 4, 200, 200);
	f_b1_bullet_anim = new fast_load(_T("img/magic_%d.png"), 15, 80, 80);

	f_coin1_anim = new fast_load(_T("img/copper_%d.png"), 14, 32, 32);
	f_coin2_anim = new fast_load(_T("img/silver_%d.png"), 14, 32, 32);
	f_coin3_anim = new fast_load(_T("img/golden_%d.png"), 14, 32, 32);

	f_magic_anim = new fast_load(_T("img/2_%d.png"), 15, 100, 100);
	f_ball_anim = new fast_load(_T("img/1_%d.png"), 60, 100, 100);

	f_death_anim = new fast_load(_T("img/death_%d.png"), 4, 80, 80);
	death_anim = new anim(f_death_anim, 40);

	f_max_anim = new fast_load(_T("img/max_%d.png"), 9, 128, 96);

	//��������Ͳ���ͼƬ��Դ����
	IMAGE img_background;
	IMAGE img_menu;
	IMAGE img_scene_shop;
	IMAGE img_scene_help;
	IMAGE img_scene_setting;
	IMAGE img_play;
	IMAGE img_shop;
	IMAGE img_help;
	IMAGE img_setting;
	IMAGE img_exit;
	IMAGE img_back;
	IMAGE img_up;

	//���ر�����ͼƬ
	loadimage(&img_background, _T("img\\background.png"));
	loadimage(&img_menu, _T("img\\1280_menu2.png"));
	loadimage(&img_scene_shop, _T("img\\1280_menu_shop.png"));
	loadimage(&img_scene_help, _T("img\\1280_menu_help.png"));
	loadimage(&img_scene_setting, _T("img\\1280_menu_setting.png"));
	loadimage(&img_play, _T("img\\ui_play.png"),152,48);
	loadimage(&img_shop, _T("img\\ui_shop.png"), 152, 48);
	loadimage(&img_help, _T("img\\ui_help.png"), 152, 48);
	loadimage(&img_setting, _T("img\\ui_setting.png"), 152, 48);
	loadimage(&img_exit, _T("img\\ui_exit.png"), 152, 48);
	loadimage(&img_back, _T("img\\ui_back_new.png"), 152, 48);
	loadimage(&img_up, _T("img\\ui_up_new.png"), 152, 48);

	//heart_hp����
	IMAGE img_heart;
	loadimage(&img_heart, _T("img\\heart1.png"));

	//���ĵ���
	IMAGE img_prop_heart;

	//��������
	mciSendString(_T("open mus/panda.mp3 alias bgm_sound"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);
	mciSendString(_T("open mus/hurt1.wav alias hurt1"), NULL, 0, NULL);
	mciSendString(_T("open mus/hurt2.wav alias hurt2"), NULL, 0, NULL);
	mciSendString(_T("open mus/hurt3.wav alias hurt3"), NULL, 0, NULL);
	mciSendString(_T("open mus/hurt4.wav alias hurt4"), NULL, 0, NULL);
	mciSendString(_T("open mus/coin.wav alias coin"), NULL, 0, NULL);
	mciSendString(_T("open mus/anniu.wav alias anniu"), NULL, 0, NULL);
	mciSendString(_T("open mus/the_world.wav alias the_world"), NULL, 0, NULL);
	mciSendString(_T("open mus/ill_do_my_best.mp3 alias begin"), NULL, 0, NULL);
	mciSendString(_T("open mus/we_lost.mp3 alias lost"), NULL, 0, NULL);
	mciSendString(_T("open mus/power_full.mp3 alias power_full"), NULL, 0, NULL);
	mciSendString(_T("open mus/use_ball.mp3 alias use_ball"), NULL, 0, NULL);
	mciSendString(_T("open mus/jbs.mp3 alias jbs"), NULL, 0, NULL);
	mciSendString(_T("open mus/max.mp3 alias max"), NULL, 0, NULL);
	mciSendString(_T("open mus/name.mp3 alias name"), NULL, 0, NULL);
	mciSendString(_T("open mus/congratulations.wav alias win"), NULL, 0, NULL);

//*****************************************************************************��  ��  ��***********************************************************************************
	bool running = true;

	int score = 0;//��ҵ÷�

	int kill_num = 0;//��ɱ�Ƿ񳬹���������

	bool levup = 0;//�Ƿ�������״̬

	int lev_count = 0;//������֡������

	int player_hurt_counter = 0;//��ɫ�ܻ���֡������

	int add_bullet_const = 0;

	ExMessage msg;

	scene_menu* menu = new scene_menu;
	scene_begin* begin = new scene_begin;
	scene_shop* shop = new scene_shop;
	scene_help* help = new scene_help;
	scene_setting* setting = new scene_setting;
	
	//bee����ʱ��֡�������б�
	vector<int> bee_interval;
	//bee�ӵ�����ʱ��֡�����б�
	vector<int>ebullet_interval;
	//��ţ�ķ����ܻ����
	vector<int> snail_hurt_interval;
	//�ܵķ����ܻ����
	vector<int> bear_hurt_interval;
	//bee����ָ���
	vector<bee*>bee_list;
	//bee���ӵ�ebullet����ָ���
	vector<ebullet*>ebullet_list;
	//eagle���˶���ָ���
	vector<eagle*>eagle_list;
	//eagle����ʱ��֡��������
	vector<int>eagle_interval;
	//eagle�ķ����ܻ����
	vector<int>eagle_hurt_interval;
	//sheet���˶���ָ���
	vector<sheet*>sheet_list;
	//sheet����ʱ��֡��������
	vector<int>sheet_interval;
	//sheet�ķ����ܻ����
	vector<int>sheet_hurt_interval;
	//sheet�ķ���ָ���
	vector<magic*>e_magic_list;
	//����˶���ָ���
	vector<enemy*>enemy_list;
	//��ţ����ָ��
	vector<snail*>snail_list;
	//�ܶ���ָ���
	vector<bear*>bear_list;
	//�ӵ�����ָ��
	bullet* bullet1 = NULL;
	//ball����ָ��
	ball* ballx = NULL;
	//�������ָ���
	vector<magic*> magic_list(3);
	//���ĵ��߶���ָ���
	vector<prop_heart*>heart_list;
	//coin1���߶���ָ���
	vector<coin*>coin1_list;
	//coin���ߴ���ʱ��֡�����б�
	vector<int>coin_interval;
	//�����������б�
	vector<POINT>death_point;
	//boss1����
	boss1* boss1 = NULL;
	//b1�ӵ�����ָ���
	vector<b1_bullet*> b1_bullet_list;
	//b1�ӵ�����ָ���
	vector<int> b1_bullet_type_list;
	//boss�ӵ�����ʱ��֡�����б�
	vector<int>b1_bullet_interval;
	//max����ָ��
	skill_max* skill_m=new skill_max(f_max_anim);
	for (int i = 0; i < 3; i++)
	{
		magic_list[i] = NULL;
	}
	
	player_anim player(f_player_anim_left, f_player_anim_right);//��ɫ����
	skill player_skill;//��ɫ���ܶ���

	int bullet_counter = player_attack_interval;//�ϴ��ӵ�����֡������
	int ball_counter = player_ball_interval;//�ϴ�ball����֡������
	int ball_attack_counter = 0;//�ϴ�ball�����˺���֡������
	int the_world_counter = the_world_interval;//�ϴν���������֡��
	int max_interval = 0;//�ϴ�ʹ��max���ܹ���֡��

	bool game_start = 1;//��Ϸ�ܿ���

	bool is_menu = 1;//���˵�����

    BeginBatchDraw();
	//******************************************************************************�� Ϸ ѭ ��**********************************************************************************
	while(game_start)
	{
		POINT M_xy = { 0,0 };//��갴������
		int menu_temp = 0;//���˵���������
		int shop_temp = 0;//shop��������
		int help_temp = 0;//help��������
		int setting_temp = 0;//setting��������
		if(is_menu)
		    mciSendString(_T("play name repeat from 0"), NULL, 0, NULL);
		while (is_menu)
		{
			DWORD start_time = GetTickCount();
			//���˵��¼�����ѭ��
			while (peekmessage(&msg))
			{
				switch(menu_temp)
				{
				case 0:
					menu_temp = menu->on_input(msg, M_xy);
					if (msg.message == WM_KEYDOWN)
					{
						if (msg.vkcode == 'O')
						{
							player.coinup(3);
							mciSendString(_T("play coin from 0"), NULL, 0, NULL);
							player.save_coin();
						}
					}
					break;
				case 1:
					running = 1;
					is_menu = 0;
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				default:
					break;
				}
			}
			cleardevice();
			switch (menu_temp)
			{
			case 0:
				putimage(0, 0, &img_menu);
				menu->on_update(M_xy,img_play,img_shop,img_help,img_setting,img_exit);//����ť
				break;
			case 1://ȫ��ʼ��
				mciSendString(_T("stop name"), NULL, 0, NULL);
				mciSendString(_T("play begin from 0"), NULL, 0, NULL);
				begin->on_update(M_xy,player);//��ʼ��player
				score = 0;
				bullet_counter = player_attack_interval;
				ball_counter = player_ball_interval;
				the_world_counter = the_world_interval;
				kill_num = 0;
				levup = 0;
				lev_count = 0;
				player_hurt_counter = 0;
				add_bullet_const = 0;
				break;
			case 2:
				putimage(0, 0, &img_scene_shop);
				draw_skill_lev(player.max_hp, 10, 950, 112);
				draw_skill_lev(player.player_attack, 5, 950, 166);
				draw_skill_lev(player.speed_up, 1, 950, 213);
				draw_skill_lev(player.is_magic, 3, 950, 287);
				draw_skill_lev(player.magic_num, 3, 950, 340);
				draw_skill_lev(player.is_ball_skill, 3, 950, 428);
				draw_skill_lev(player.is_the_world, 1, 950, 512);
				draw_skill_lev(player.is_max, 5, 950, 579);
				draw_money(player,800,10);
				shop->on_update(M_xy, img_back, img_up);
				{
					switch (shop_temp)
					{
					case 0:
						shop_temp = shop->on_input(msg, M_xy);
						break;
					case 1:
						player_skill.max_hp_up(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 2:
						player_skill.player_attack_up(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 3:
						player_skill.speed_up(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 4:
						player_skill.magic_up(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 5:
						player_skill.magic_kill_num(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 6:
						player_skill.ball_skill_up(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 7:
						player_skill.the_world_up(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 8:
						player_skill.skill_max_up(player);
						player.save_skill();
						shop_temp = 0;
						break;
					case 9:
						shop_temp = 0;
						menu_temp = 0;
						break;
					}
				}
				break;

			case 3:
				putimage(0, 0, &img_scene_help);
				help->on_update(M_xy, img_back);
				help_temp = help->on_input(msg, M_xy);
				if (help_temp == 1)
				{
					help_temp = 0;
					menu_temp = 0;
				}
				break;
			case 4:
				putimage(0, 0, &img_scene_setting);
				setting->on_update(M_xy, img_back);
				setting_temp = setting->on_input(msg, M_xy);
				if (setting_temp == 1)
				{
					setting_temp = 0;
					menu_temp = 0;
				}
				break;
			case 5:
				player.save_skill();
				game_start = 0;
				is_menu = 0;
				running = 0;
				break;

			default:
				break;
			}
			FlushBatchDraw();

			DWORD end_time = GetTickCount();
			DWORD delta_time = end_time - start_time;
			if (delta_time < 1000 / 60)
			{
				Sleep(1000 / 60 - delta_time);
			}
		}

        //**********************************************************************�� �� �� Ϸ ѭ ��****************************************************************************
		if(running)
		mciSendString(_T("play jbs repeat from 0"), NULL, 0, NULL);//���ű�������
		while (running)
		{
			DWORD start_time = GetTickCount();
			bullet_counter++;
			ball_counter++;
			ball_attack_counter++;
			lev_count++;
			the_world_counter++;
			player_hurt_counter++;
			add_bullet_const++;
			max_interval++;

			//***�¼�����ѭ��***
			while (peekmessage(&msg))
			{
				//����ƶ���Ϣ����
				player.player_msg(msg);

				//�����ӵ�
				const int bullet_interval = player_attack_interval;//������ͨ��������
				const int ball_interval = player_ball_interval;//����ball����
				if (msg.message == WM_KEYDOWN)
				{
					if (msg.vkcode == 'J')
					{
						if (bullet_counter > bullet_interval)
						{
							if (bullet1 != NULL)
							{
								delete bullet1;
								bullet1 = NULL;
							}
							bullet1 = new bullet(player);
							bullet_counter = 0;
						}
					}
					if (msg.vkcode == 'K' && player.is_ball_skill)
					{
						if (ball_counter > ball_interval && player.power >= ball_power_cost)
						{
							if (ballx != NULL)
							{
								delete ballx;
								ballx = NULL;
							}
							mciSendString(_T("play use_ball from 0"), NULL, 0, NULL);
							ballx = new ball(f_ball_anim, player);
							player.power -= ball_power_cost;
							ball_counter = 0;
						}
					}
					if (msg.vkcode == 'L' && player.is_the_world)
					{
						if (the_world_counter > the_world_interval && player.power >= the_world_power_cost)
						{
							the_world_counter = 0;
							mciSendString(_T("play the_world from 0"), NULL, 0, NULL);
							player.power-=the_world_power_cost;
						}
					}
					if (msg.vkcode == 'U' && player.is_max&& player.power>=skill_max_cost)
					{
						mciSendString(_T("play max from 0"), NULL, 0, NULL);
						max_interval = 0;
						player.power -= skill_max_cost;
					}
				}
			}

			//while (player.is_stop)//������Ұ���ͣ���߼�
			//{
			//	Sleep(15);
			//	while (peekmessage(&msg))
			//		player.stop(msg);
			//}

			//��ɫ�ƶ�
			player.move();

			//����ɱ�ﵽ����
			if (kill_num == player.magic_num&&player.is_magic)
			{
				kill_num++;
				levup = 1;
				lev_count = 0;
				for (int i = 0; i < 3; i++)
				{
					if (magic_list[i] == NULL)
					{
						magic_list[i] = new magic(f_magic_anim);  // �����������aa
					}
				}
			}
			//************************************************************************�� �� Ϊ �� �� �� ײ �� ��***************************************************************************
			// ��������heart���ߵ���ײ
			for (int i = 0; i < heart_list.size(); i++)
			{
				if (heart_list[i]->checkplayer(player))
				{
					player.cure();
					prop_heart* heart = heart_list[i];
					swap(heart_list[i], heart_list.back());
					heart_list.pop_back();
					delete heart;
				}
			}

			//�����Һ�coin1���ߵ���ײ
			for (int i = 0; i < coin1_list.size(); i++)
			{
				if (coin1_list[i]->checkplayer(player))
				{
					mciSendString(_T("play coin from 0"), NULL, 0, NULL);
					player.coinup(coin1_list[i]->coin_type);
					coin* coin1 = coin1_list[i];
					swap(coin1_list[i], coin1_list.back());
					coin1_list.pop_back();
					delete coin1;
					i--;
				}
			}

			//���boss1�������ײ
			if (boss1 != NULL)
			{
				if (max_interval <= 70)
				{
					if (max_interval ==60)
					{
						boss1->hurt(player.is_max);
					}
				}
				if (boss1->checkplayer(player) && player_hurt_counter > player_hurt_interval )
				{
					player.hurt(2);
					player_hurt_counter = 0;
				}
			}

			//���eagle�������ײ
			for (eagle* eagle : eagle_list)
			{
				if (max_interval <= 70)
				{
					if (max_interval  == 60)
					{
						eagle->hurt(player.is_max);
					}
				}
				if (eagle->checkplayer(player))
				{
					player.hurt();
					while (eagle->checkalive())
						eagle->hurt(1);
				}
			}

			//���sheet�������ײ
			for (size_t i=0;i<sheet_list.size();i++)
			{
				if (max_interval <= 70)
				{
					if (max_interval == 60)
					{
						sheet_list[i]->hurt(player.is_max);
					}
				}
				if (sheet_list[i]->checkplayer(player))
				{
					player.hurt(2);
					while (sheet_list[i]->checkalive())
						sheet_list[i]->hurt(1);
				}
				if (e_magic_list[i]->checkplayer(player)&& player_hurt_counter > player_hurt_interval)
				{
					player.hurt(2);
					player_hurt_counter = 0;
				}
			}

			//���Ұ����˺������ײ
			for (enemy* enemy : enemy_list)
			{
				if (max_interval <= 70)
				{
					if (max_interval == 60)
					{
						enemy->hurt(player.is_max);
					}
				}
				if (enemy->checkplayer(player))
				{
					player.hurt();
					while (enemy->checkalive())//������ʧ
					{
						enemy->hurt(1);
					}
				}
			}

			//���bee���˺������ײ
			for (bee* bee : bee_list)
			{
				if (max_interval <= 70)
				{
					if (max_interval == 60)
					{
						bee->hurt(player.is_max);
					}
				}
				if (bee->checkplayer(player))
				{
					player.hurt();
					while (bee->checkalive())//������ʧ
					{
						bee->hurt(1);
					}
				}
			}

			//�����ţ���˺������ײ
			for (snail* snail : snail_list)
			{
				if (max_interval <= 70)
				{
					if (max_interval == 60)
					{
						snail->hurt(player.is_max);
					}
				}
				if (snail->checkplayer(player))
				{
					player.hurt();
					while (snail->checkalive())
					{
						snail->hurt(1);
					}
				}
			}

			//����ܵ��˺������ײ
			for (bear* bear : bear_list)
			{
				if (max_interval <= 70)
				{
					if (max_interval == 60)
					{
						bear->hurt(player.is_max);
					}
				}
				if (bear->checkplayer(player))
				{
					player.hurt();
					while (bear->checkalive())
					{
						bear->hurt(1);
					}
				}
			}

			//����ӵ���ball��boss1����ײ
			if (bullet1 != NULL || ballx != NULL)
				if (boss1 != NULL)
				{
					if (bullet1 != NULL)
					{
						bullet& bullet = *bullet1;
						if (boss1->checkbullet(bullet))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							player.power += 3;
							boss1->hurt(player.player_attack);
							delete bullet1;
							bullet1 = NULL;
						}
					}
					if (ballx != NULL && ball_attack_counter > ball_attack_interval)
					{
						if (ballx->check_e(boss1->e_xy, boss1->boss1_width, boss1->boss1_height))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							boss1->hurt(player.is_ball_skill);
							ball_attack_counter = 0;
						}
					}
				}

			//����ӵ���Ұ����˵���ײ
			if (bullet1 != NULL || ballx != NULL)
				for (enemy* enemy : enemy_list)
				{
					if(bullet1!=NULL)
					{
						bullet& bullet = *bullet1;
						if (enemy->checkbullet(bullet))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							enemy->hurt(player.player_attack);
							delete bullet1;
							bullet1 = NULL;
							break;
						}
					}
					if (ballx != NULL && ball_attack_counter > ball_attack_interval)
					{
						if (ballx->check_e(enemy->e_xy,enemy->e_width,enemy->e_height))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							enemy->hurt(player.is_ball_skill);
							ball_attack_counter = 0;
						}
					}
				}

			//����ӵ���ball����ţ���˵���ײ
			if (bullet1 != NULL || ballx != NULL)
				for (snail* snail : snail_list)
				{
					if (bullet1 != NULL)
					{
						bullet& bullet = *bullet1;
						if (snail->checkbullet(bullet))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							snail->hurt(player.player_attack);
							delete bullet1;
							bullet1 = NULL;
							break;
						}
					}
					if (ballx != NULL && ball_attack_counter > ball_attack_interval)
					{
						if (ballx->check_e(snail->e_xy, snail->e_width, snail->e_height))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							snail->hurt(player.is_ball_skill);
							ball_attack_counter = 0;
						}
					}
				}

			//����ӵ���ball���ܵ��˵���ײ
			if (bullet1 != NULL || ballx != NULL)
				for (bear* bear : bear_list)
				{
					if (bullet1 != NULL)
					{
						bullet& bullet = *bullet1;
						if (bear->checkbullet(bullet))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							bear->hurt(player.player_attack);
							delete bullet1;
							bullet1 = NULL;
							break;
						}
					}
					if (ballx != NULL && ball_attack_counter > ball_attack_interval)
					{
						if (ballx->check_e(bear->e_xy, bear->e_width, bear->e_height))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							bear->hurt(player.is_ball_skill);
							ball_attack_counter = 0;
						}
					}
				}

			//����ӵ���ball��eagle���˵���ײ
			if (bullet1 != NULL || ballx != NULL)
				for (eagle* eagle : eagle_list)
				{
					if (bullet1 != NULL)
					{
						bullet& bullet = *bullet1;
						if (eagle->checkbullet(bullet))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							eagle->hurt(player.player_attack);
							delete bullet1;
							bullet1 = NULL;
							break;
						}
					}
					if (ballx != NULL && ball_attack_counter > ball_attack_interval)
					{
						if (ballx->check_e(eagle->e_xy, eagle->e_width, eagle->e_height))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							eagle->hurt(player.is_ball_skill);
							ball_attack_counter = 0;
						}
					}
				}

			//����ӵ���ball��sheet���˵���ײ
			if (bullet1 != NULL || ballx != NULL)
				for (sheet*sheet : sheet_list)
				{
					if (bullet1 != NULL)
					{
						bullet& bullet = *bullet1;
						if (sheet->checkbullet(bullet))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							sheet->hurt(player.player_attack);
							delete bullet1;
							bullet1 = NULL;
							break;
						}
					}
					if (ballx != NULL && ball_attack_counter > ball_attack_interval)
					{
						if (ballx->check_e(sheet->e_xy, sheet->e_width, sheet->e_height))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							sheet->hurt(player.is_ball_skill);
							ball_attack_counter = 0;
						}
					}
				}

			//����ӵ���ball��bee���˵���ײ
			if (bullet1 != NULL || ballx != NULL)
				for (bee* bee : bee_list)
				{
					if (bullet1 != NULL)
					{
						bullet& bullet = *bullet1;
						if (bee->checkbullet(bullet))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							bee->hurt(player.player_attack);
							delete bullet1;
							bullet1 = NULL;
							break;
						}
					}
					if (ballx != NULL && ball_attack_counter > ball_attack_interval)
					{
						if (ballx->check_e(bee->e_xy, bee->e_width, bee->e_height))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							bee->hurt(player.is_ball_skill);
							ball_attack_counter = 0;
						}
					}
				}

			//��ⷨ����boss1������ײ
			if (magic_list[1] != NULL)
			{
				if (boss1 != NULL)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (boss1->checkmagic(magic1) && boss1_hurt_interval >= 15)
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							boss1->hurt(player.is_magic);
							boss1_hurt_interval= 0;
							break;
						}
					}
				}
			}

			//��ⷨ����Ұ�������ײ
			if (magic_list[1] != NULL)
			{
				for (enemy* enemy : enemy_list)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (enemy->checkmagic(magic1))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							enemy->hurt(player.is_magic);
							break;
						}
					}
				}
			}

			//��ⷨ������ţ������ײ
			if (magic_list[1] != NULL)
			{
				for (int i = 0; i < snail_list.size(); i++)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (snail_list[i]->checkmagic(magic1) && snail_hurt_interval[i] >= 10)
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							snail_list[i]->hurt(player.is_magic);
							snail_hurt_interval[i] = 0;
							break;
						}
					}
				}
			}

			//��ⷨ����eagle������ײ
			if (magic_list[1] != NULL)
			{
				for (int i = 0; i < eagle_list.size(); i++)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (eagle_list[i]->checkmagic(magic1) && eagle_hurt_interval[i] >= 10)
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							eagle_list[i]->hurt(player.is_magic);
							eagle_hurt_interval[i] = 0;
							break;
						}
					}
				}
			}

			//��ⷨ����sheet������ײ
			if (magic_list[1] != NULL)
			{
				for (int i = 0; i < sheet_list.size(); i++)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (sheet_list[i]->checkmagic(magic1) && sheet_hurt_interval[i] >= 10)
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							sheet_list[i]->hurt(player.is_magic);
							sheet_hurt_interval[i] = 0;
							break;
						}
					}
				}
			}

			//��ⷨ�����ܵ�����ײ
			if (magic_list[1] != NULL)
			{
				for (int i = 0; i < bear_list.size(); i++)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (bear_list[i]->checkmagic(magic1) && bear_hurt_interval[i] >= 10)
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							bear_list[i]->hurt(player.is_magic);
							bear_hurt_interval[i] = 0;
							break;
						}
					}
				}
			}

			//��ⷨ�����ܵ�����ײ
			if (magic_list[1] != NULL)
			{
				for (int i = 0; i < eagle_list.size(); i++)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (eagle_list[i]->checkmagic(magic1) && eagle_hurt_interval[i] >= 10)
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							eagle_list[i]->hurt(player.is_magic);
							eagle_hurt_interval[i] = 0;
							break;
						}
					}
				}
			}

			//��ⷨ����Ұ�������ײ
			if (magic_list[1] != NULL)
			{
				for (bee* bee : bee_list)
				{
					for (magic* magic2 : magic_list)
					{
						magic& magic1 = *magic2;
						if (bee->checkmagic(magic1))
						{
							mciSendString(_T("play hit from 0"), NULL, 0, NULL);
							bee->hurt(player.is_magic);
							break;
						}
					}
				}
			}
			//���bee�����ӵ�����ҵ���ײ
			for (int i = 0; i < ebullet_list.size(); i++)
			{
				if (ebullet_list[i]->checkplayer(player))
				{
					player.hurt();
					ebullet* ebullet = ebullet_list[i];
					swap(ebullet_list[i], ebullet_list.back());
					ebullet_list.pop_back();
					swap(ebullet_interval[i], ebullet_interval.back());
					ebullet_interval.pop_back();
					delete ebullet;
					i--;
				}
			}

			//���boss1�ӵ�����ҵ���ײ
			for (size_t i = 0; i < b1_bullet_list.size(); i++)
			{
				b1_bullet_interval[i]++;
				if (b1_bullet_list[i]->checkplayer(player))
				{
					player.hurt();
					b1_bullet* bullet = b1_bullet_list[i];
					swap(b1_bullet_list[i], b1_bullet_list.back());
					b1_bullet_list.pop_back();
					swap(b1_bullet_type_list[i], b1_bullet_type_list.back());
					b1_bullet_type_list.pop_back();
					swap(b1_bullet_interval[i], b1_bullet_interval.back());
					b1_bullet_interval.pop_back();
					delete bullet;
					i--;
				}
			}

			//*************************************************************************��  ��  ��  ��  ��  ��  ��  ֵ*************************************************************************
			//���boss1����ֵ
			if (boss1 != NULL && !boss1->checkalive())
			{
				mciSendString(_T("play win from 0"), NULL, 0, NULL);
				for (auto& b1_bullet : b1_bullet_list)
					delete b1_bullet;
				b1_bullet_list.clear();
				score += 200;
				kill_num++;
				player.power_up(30);
				for (int i = 0; i < 3; i++)
				{
					addcoin1(coin1_list, boss1->e_xy, 3);
					if (i > 0)
						addheart(heart_list, boss1->e_xy, img_prop_heart);
				}
				add_death(boss1->e_xy, death_point);
				delete boss1;
				boss1 = NULL;
			}
			 
			//������������ֵ
			for (size_t i = 0; i < enemy_list.size(); i++)
			{
				enemy* enemy = enemy_list[i];
				if (!enemy->checkalive())
				{
					score++;
					kill_num++;
					player.power_up(2);
					if (check_prop(enemy_coin1_p))
						addcoin1(coin1_list, enemy->e_xy, 1);
					if (check_prop(enemy_heart_p))
					{
						addheart(heart_list, enemy->e_xy, img_prop_heart);
					}
					swap(enemy_list[i], enemy_list.back());
					enemy_list.pop_back();
					add_death(enemy->e_xy, death_point);
					delete enemy;
					i--;
				}
			}

			//�����ţ��������ֵ
			for (int i = 0; i < snail_list.size(); i++)
			{
				snail* snail = snail_list[i];
				int hurt_interval = snail_hurt_interval[i];
				if (!snail->checkalive())
				{
					score += 2;
					kill_num++;
					player.power_up(2);
					addcoin1(coin1_list, snail->e_xy, 1);
					if (check_prop(enemy_heart_p))
					{
						addheart(heart_list, snail->e_xy, img_prop_heart);
					}
					swap(snail_list[i], snail_list.back());
					snail_list.pop_back();
					swap(snail_hurt_interval[i], snail_hurt_interval.back());
					snail_hurt_interval.pop_back();
					add_death(snail->e_xy, death_point);
					delete snail;
					i--;  // ��Ϊ������Ԫ�أ���Ҫ��������
				}
			}

			//����ܵ�������ֵ
			for (int i = 0; i < bear_list.size(); i++)
			{
				bear* bear = bear_list[i];
				int hurt_interval = bear_hurt_interval[i];
				if (!bear->checkalive())
				{
					score += 5;
					kill_num++;
					player.power_up(3);
					addcoin1(coin1_list, bear->e_xy, 2);
					if (check_prop(bear_heart_p))
					{
						addheart(heart_list, bear->e_xy, img_prop_heart);
					}
					swap(bear_list[i], bear_list.back());
					bear_list.pop_back();
					swap(bear_hurt_interval[i], bear_hurt_interval.back());
					bear_hurt_interval.pop_back();
					add_death(bear->e_xy, death_point);
					delete bear;
					i--;  // ��Ϊ������Ԫ�أ���Ҫ��������
				}
			}

			//���eagle����ֵ
			for (int i = 0; i < eagle_list.size(); i++)
			{
				eagle* eagle = eagle_list[i];
				int hurt_interval = eagle_hurt_interval[i];
				if (!eagle->checkalive())
				{
					score += 5;
					kill_num++;
					player.power_up(3);
					addcoin1(coin1_list, eagle->e_xy, 2);
					if (check_prop(eagle_heart_p))
					{
						addheart(heart_list, eagle->e_xy, img_prop_heart);
					}
					swap(eagle_list[i], eagle_list.back());
					eagle_list.pop_back();
					swap(eagle_hurt_interval[i], eagle_hurt_interval.back());
					eagle_hurt_interval.pop_back();
					add_death(eagle->e_xy, death_point);
					delete eagle;
					i--;  // ��Ϊ������Ԫ�أ���Ҫ��������
				}
			}

			//���sheet����ֵ
			for (int i = 0; i < sheet_list.size(); i++)
			{
				sheet* sheet = sheet_list[i];
				int hurt_interval = sheet_hurt_interval[i];
				if (!sheet->checkalive())
				{
					score += 10;
					kill_num++;
					player.power_up(5);
					if (check_prop(sheet_coin3_p))
						addcoin1(coin1_list, sheet->e_xy, 3);
					else
					    addcoin1(coin1_list, sheet->e_xy, 2);
					if (check_prop(eagle_heart_p))
					{
						addheart(heart_list, sheet->e_xy, img_prop_heart);
					}
					swap(sheet_list[i], sheet_list.back());
					sheet_list.pop_back();
					swap(sheet_hurt_interval[i], sheet_hurt_interval.back());
					sheet_hurt_interval.pop_back();
					add_death(sheet->e_xy, death_point);
					delete sheet;
					i--;  // ��Ϊ������Ԫ�أ���Ҫ��������
				}
			}

			//���bee��������ֵ
			for (size_t i = 0; i < bee_list.size(); i++)
			{
				bee* bee = bee_list[i];
				if (!bee->checkalive())
				{
					score += 3;
					kill_num++;
					player.power_up(2);
					if (check_prop(bee_coin2_p))
					{
						addcoin1(coin1_list, bee->e_xy, 2);
					}
					else
						addcoin1(coin1_list, bee->e_xy, 1);
					if (check_prop(bee_heart_p))
					{
						addheart(heart_list, bee->e_xy, img_prop_heart);
					}
					swap(bee_list[i], bee_list.back());
					bee_list.pop_back();
					add_death(bee->e_xy, death_point);
					delete bee;
					i--;
				}
			}

			//����������ֵ
			if (!player.checkalive())
			{
				mciSendString(_T("stop jbs"), NULL, 0, NULL);
				player.save_coin();
				static TCHAR text[128];
				_stprintf_s(text, _T("���յ÷֣�%d ��!"), score);
				MessageBox(GetHWnd(), text, _T("�˾Ͷ���!"), MB_OK);
				is_menu = 1;
				running = 0;
			  //�ͷ�������Դ
				for (auto& bee : bee_list) delete bee;
				bee_list.clear();
				bee_interval.clear();

				for (auto& snail : snail_list) 
					delete snail;
				snail_list.clear();
				snail_hurt_interval.clear();

				for (auto& eagle : eagle_list)
					delete eagle;
				eagle_list.clear();
				eagle_hurt_interval.clear();
				eagle_interval.clear();

				for (auto& sheet : sheet_list)
					delete sheet;
				for (auto& magic : e_magic_list)
					delete magic;
				sheet_list.clear();
				magic_list.clear();
				sheet_hurt_interval.clear();
				sheet_interval.clear();

				for (auto& bear : bear_list)
					delete bear;
				bear_list.clear();
				bear_hurt_interval.clear();

				for (auto& enemy : enemy_list) 
					delete enemy;
				enemy_list.clear();

				for (auto& magic : magic_list) 
					delete magic;
				magic_list.clear();  // ע�⣺magic_list �ǹ̶���С 3 �� vector����Ҫ���⴦��

				for (auto& bullet : ebullet_list) 
					delete bullet;
				ebullet_list.clear();
				ebullet_interval.clear();

				for (auto& coin : coin1_list) 
					delete coin;
				coin1_list.clear();

				for (auto& heart : heart_list) 
					delete heart;
				heart_list.clear();

				for (auto& b1_bullet : b1_bullet_list)
					delete b1_bullet;
				b1_bullet_list.clear();

				if (bullet1) 
				{
					delete bullet1;
					bullet1 = nullptr;
				}

				if (boss1)
				{
					delete boss1;
					boss1 = NULL;
				}
				//����magic
				magic_list.resize(3);  // ȷ����СΪ 3
				for (auto& magic : magic_list) {
					if (magic) 
					{
						delete magic;
						magic = nullptr;
					}
				}
				mciSendString(_T("play lost from 0"), NULL, 0, NULL);
				break;
			}
			//****************************************************************************��            ��****************************************************************************
			//�ӵ��ƶ�
			if (bullet1 != NULL)
				bullet1->move(player);

			//ball�ƶ�
			if (ballx != NULL)
				ballx->move();

			//�������ʱ��ﵽ��ɾ������
			if (lev_count == magic_on_interval)
			{
				if (magic_list[1] != NULL)
				{
					levup = 0;
					kill_num = 0;
					for (int i = 0; i < 3; i++)
					{
						delete magic_list[i];
						magic_list[i] = NULL;
					}
				}
			}

			//��ʼ��¼bee�����ӵ����ڵ�֡��  bee�ӵ�����һ��ʱ���ɾ��
			for (int i = 0; i < ebullet_interval.size(); i++)
			{
				ebullet_interval[i]++;
				ebullet_list[i]->move();
				if (ebullet_interval[i] >= 400)
				{
					ebullet* ebullet = ebullet_list[i];
					swap(ebullet_list[i], ebullet_list.back());
					ebullet_list.pop_back();
					swap(ebullet_interval[i], ebullet_interval.back());
					ebullet_interval.pop_back();
					delete ebullet;
					i--;  // ��Ϊ������Ԫ�أ���Ҫ��������
				}
			}

			//*******************************************************************�� �� �� �� �� �� ��*****************************************************************************
			// ���boss1
			if (score >= 250 && boss1 == NULL && score <= 450)
			{
				addboss1(boss1,player);
			}
			if (boss1 != NULL)
			{
				boss1->move(player);
			}

			if (b1_move_type == 1 && b1_bullet_list.size() == 0)
			{
					b1_move_type = 0;
					boss1->stage = 2;
			}

			if (boss1 != NULL && boss1->blood <= 50)
			{
				b1_move_type = 2;
			}

			//���b1_bullet
			if (boss1 != NULL)
			{
				if (boss1->stage == 0 && add_bullet_const > 25)
				{
					addb1_bullet(b1_bullet_list, b1_bullet_type_list, b1_bullet_interval, *boss1, player);
					add_bullet_const = 0;
				}
				if (boss1->stage == 1 && add_bullet_const > 10)
				{
					addb1_bullet(b1_bullet_list, b1_bullet_type_list, b1_bullet_interval,*boss1,player);
					add_bullet_const = 0;
				}
				if (boss1->stage > 1 && boss1->stage < 5 && add_bullet_const>30)
				{
					addb1_bullet(b1_bullet_list, b1_bullet_type_list, b1_bullet_interval,*boss1,player);
					add_bullet_const = 0;
				}
				if (boss1->stage == 5 && add_bullet_const > 30)
				{
					addb1_bullet(b1_bullet_list, b1_bullet_type_list,b1_bullet_interval ,*boss1,player);
					add_bullet_const = 0;
				}
				for (size_t i = 0; i < b1_bullet_list.size(); i++)
				{
					b1_bullet_list[i]->move(player, *boss1, b1_move_type, b1_bullet_type_list[i]);
					if (b1_bullet_interval[i] >= 400)
					{
						b1_bullet* bullet = b1_bullet_list[i];
						swap(b1_bullet_list[i], b1_bullet_list.back());
						b1_bullet_list.pop_back();
						swap(b1_bullet_type_list[i], b1_bullet_type_list.back());
						b1_bullet_type_list.pop_back();
						swap(b1_bullet_interval[i], b1_bullet_interval.back());
						b1_bullet_interval.pop_back();
						delete bullet;
						i--;
					}
				}
			}

			//��������
			if (the_world_counter > the_world_interval && boss1 == NULL && (score < 250 || score>450))//��ʱͣ
			{
				addenemy(enemy_list, score);
				for (enemy* enemy : enemy_list)
				{
					enemy->move(player);
				}
			}

			//�������ﵽ20ʱ��ʼ�����ţ����
			if (score >= 15 && (the_world_counter > the_world_interval) && boss1 == NULL && (score < 250 || score>450))
			{
				addsnail(snail_list, snail_hurt_interval, score);
				for (int i = 0; i < snail_list.size(); i++)
				{
					snail_hurt_interval[i]++;
					snail_list[i]->move(player);
				}
			}

			//�������ﵽ60ʱ��ʼ���bee
			if (score >= 45 && (the_world_counter > the_world_interval) && boss1 == NULL && (score < 250 || score>450))
			{
				addbee(bee_list, bee_interval, score);
				for (int i = 0; i < bee_list.size(); i++)
				{
					bee_list[i]->move(player);
					bee_interval[i]++;
					if (bee_interval[i] >= bee_attack_interval) //bee�ӵ�����
					{
						bee_interval[i] = 0;
						ebullet_list.push_back(new ebullet(bee_list[i]->e_xy, player));
						ebullet_interval.push_back(0);
					}
				}
			}

			//�������ﵽ120ʱ��ʼ����ܵ���
			if (score >= 90 && (the_world_counter > the_world_interval) && boss1 == NULL && (score < 250 || score>450))
			{
				addbear(bear_list, bear_hurt_interval, score);
				for (int i = 0; i < bear_list.size(); i++)
				{
					bear_hurt_interval[i]++;
					bear_list[i]->move(player);
				}
			}

			//�������ﵽ150ʱ��ʼ���eagle
			if (score >= 135 && (the_world_counter > the_world_interval) && boss1 == NULL && (score < 250||score>450))
			{
				addeagle(eagle_list, eagle_interval, eagle_hurt_interval, score);
				for (int i = 0; i < eagle_list.size(); i++)
				{
					eagle_hurt_interval[i]++;
					eagle_interval[i]++;
					eagle_list[i]->move(player);
					if (eagle_interval[i] >= eagle_attack1_interval && eagle_list[i]->stage == 0)
					{
						eagle_interval[i] = 0;
						ebullet_list.push_back(new ebullet(eagle_list[i]->e_xy, player));
						ebullet_interval.push_back(0);
					}
					if (eagle_list[i]->stage == 1&& eagle_interval[i] >= eagle_attack2_interval)
					{
						static int temp = 0;
						temp++;
						eagle_interval[i] = 0;
						ebullet_list.push_back(new ebullet(eagle_list[i]->e_xy, player));
						ebullet_interval.push_back(0);
						if (temp % 3 == 0)
							eagle_list[i]->stage = 0;
					}
				}
			}

			//�������ﵽ200ʱ��ʼ���sheet
			if (score >= 180 && (the_world_counter > the_world_interval) && boss1 == NULL && (score < 250 || score>450) ||(boss1!=NULL&&boss1->blood<75&& (the_world_counter > the_world_interval)))
			{
				addsheet(sheet_list, sheet_interval, sheet_hurt_interval,e_magic_list, score);
				for (int i = 0; i < sheet_list.size(); i++)
				{
					update_e_magic(*e_magic_list[i], *sheet_list[i]);
					sheet_hurt_interval[i]++;
					sheet_interval[i]++;
					sheet_list[i]->move(player);
					if (sheet_interval[i] >= eagle_attack2_interval)
					{
					    sheet_interval[i] = 0;
					}
				}
			}

			if (boss1 != NULL)//boss1�����ܻ�֡�Ѽ�
			    boss1_hurt_interval++;
			//***************************************************************�� �� �� �� ��*****************************************************************************
			cleardevice();

			//���ñ���
			putimage(0, 0, &img_background);

			//�����ĵ���
			for (int i = 0; i < heart_list.size(); i++)
				heart_list[i]->draw(1000 / 144);

			//����coin1
			for (int i = 0; i < coin1_list.size(); i++)
			{
				coin1_list[i]->draw(1000 / 144);
				if (player.is_coin_fly)
					coin1_list[i]->move(player);
			}

			//���Ʒ���
			if (levup)
			{
				if (magic_list[1] != NULL)
				{
					update_magic(magic_list, player);
					for (int i = 0; i < 3; i++)
					{
						magic_list[i]->draw(1000 / 144);
					}
				}
			}

			//����bee�ӵ�
			for (ebullet* ebullet : ebullet_list)
			{
				ebullet->draw();
			}

			//����b1�ӵ�
			for (b1_bullet* bullet : b1_bullet_list)
			{
				bullet->draw(1000 / 144);
			}

			//���ƽ�ɫ
			player.draw(1000 / 144);

			//����boss1
			if (boss1 != NULL)
			{
				boss1->draw(1000 / 144);
				if (max_interval <= 70 && player.is_max)
				{
					skill_m->draw(boss1->e_xy.x, boss1->e_xy.y+60, 1000 / 144);
				}
			}

			//�����ӵ�
			if (bullet1 != NULL)
			{
				bullet1->draw(player);
			}
			//���������
			for (enemy* enemy : enemy_list)
			{
				enemy->draw(1000 / 144);
				if (max_interval <= 70 && player.is_max)
				{
					skill_m->draw(enemy->e_xy.x-10, enemy->e_xy.y+10, 1000 / 144);
				}
			}
			//������ţ
			for (snail* snail : snail_list)
			{
				snail->draw(1000 / 144);
				if (max_interval <= 70 && player.is_max)
				{
					skill_m->draw(snail->e_xy.x-10, snail->e_xy.y+10, 1000 / 144);
				}
			}

			//������
			for (bear* bear : bear_list)
			{
				bear->draw(1000 / 144);
				if (max_interval <= 70 && player.is_max)
				{
					skill_m->draw(bear->e_xy.x, bear->e_xy.y+50, 1000 / 144);
				}
			}

			//����sheet
			for (size_t i=0;i<sheet_list.size();i++)
			{
				sheet_list[i]->draw(1000 / 144);
				e_magic_list[i]->draw(1000 / 144);
				if (max_interval <= 70 && player.is_max)
				{
					skill_m->draw(sheet_list[i]->e_xy.x-10, sheet_list[i]->e_xy.y+10, 1000 / 144);
				}
			}

			//����bee
			for (bee* bee : bee_list)
			{
				bee->draw(1000 / 144);
				if (max_interval <= 70 && player.is_max)
				{
					skill_m->draw(bee->e_xy.x-10, bee->e_xy.y+10, 1000 / 144);
				}
			}

			//����eagle
			for (eagle* eagle : eagle_list)
			{
				eagle->draw(1000 / 144);
				if (max_interval <= 70 && player.is_max)
				{
					skill_m->draw(eagle->e_xy.x, eagle->e_xy.y+20, 1000 / 144);
				}
			}

			//����ball
			if (ballx != NULL)
			{
				ballx->draw(1000 / 30);
			}

			//����ﵽָ��֡����ɾ������ӵ�
			if (bullet_counter > 200 && bullet1 != NULL)
			{
				delete bullet1;
				bullet1 = NULL;
			}
			//����ﵽָ��֡����ɾ�����ball
			if (ball_counter > 200 && ballx != NULL)
			{
				delete ballx;
				ballx = NULL;
			}

			for (int i = 0; i < death_point.size(); i++)
			{
				death_anim->play(death_point[i].x, death_point[i].y, 5);
				if (death_anim->idx_img==3)
				{
					temp++;
					if(temp>=8)
					{
						swap(death_point[i], death_point.back());
						death_point.pop_back();
						i--;
						temp = 0;
					}
				}
			}

			//����hp
			player.draw_hp(img_heart);
			//���Ʒ���
			draw_score(score);
			//���ƾ����ܽ�Ǯ
			draw_money(player);
			//���Ʒ���ֵ
			draw_power(player);

		    FlushBatchDraw();

			//֡�ʿ���
			DWORD end_time = GetTickCount();
			DWORD delta_time = end_time - start_time;
			if (delta_time < 1000 / 60)
			{
				Sleep(1000 / 60 - delta_time);
			}
		}
	}

	delete f_player_anim_left;
	delete f_player_anim_right;

	delete f_enemy_anim_left;
	delete f_enemy_anim_right;

	delete f_bee_anim_left;
	delete f_bee_anim_right;

	delete f_snail_anim_left;
	delete f_snail_anim_right;

	delete f_bear_anim_left;
	delete f_bear_anim_right;

	delete f_sheet_anim_left;
	delete f_sheet_anim_right;

	delete f_boss1_anim_left;
	delete f_boss1_anim_right;
	delete f_b1_bullet_anim;

	delete f_coin1_anim;
	delete f_coin2_anim;
	delete f_coin3_anim;

	delete f_magic_anim;
	delete f_ball_anim;

	delete menu;
	delete begin;
	delete shop;
	delete help;

	delete f_death_anim;
	delete death_anim;

	delete f_max_anim;

	EndBatchDraw();

	return 0;
}