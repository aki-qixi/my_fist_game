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
		loadimage(&img_shadow, _T("img/shadow_player.png"));//加载阴影
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
			is_magic = 0;//法球伤害升级
			magic_num = 5;    //法球击杀数限制
			is_ball_skill = 0;//火球法术及其伤害
			speed_up = 0;//加速
			max_hp = 3;//玩家血量上限
			player_attack = 1;  //player普通攻击伤害  
			is_the_world = 0; //时停技能升级
			is_coin_fly = 1;  //自动拾取硬币技能实现
			is_max = 0;//max技能升级
			ifs.close();
			save_skill();
		}
		ifs >> ch;
		if (ifs.eof())
		{
			max_power = 180;
			is_magic = 0;//法球伤害升级
			magic_num = 5;    //法球击杀数限制
			is_ball_skill = 0;//火球法术及其伤害
			speed_up = 0;//加速
			max_hp = 3;//玩家血量上限
			player_attack = 1;  //player普通攻击伤害  
			is_the_world = 0; //时停技能升级
			is_coin_fly = 1;  //自动拾取硬币技能实现
			is_max = 0;//max技能升级
			ifs.close();
			save_skill();
		}
		chushi_all();
	}

	~player_anim(){}
	//处理玩家按键信息
	void player_msg(const ExMessage& msg);

	//处理玩家移动
	void move();

	//绘制玩家
	void draw(int delat);

	//玩家受击
	void hurt(int attack = 1);

	//绘制hp
	void draw_hp(IMAGE& img);

	bool checkalive();

	void cure();//玩家受治疗

	void coinup(int coin_type);//玩家获得的金钱数（局内碰撞）

	int getcoin();//获取玩家钱数

	void save_coin();//保存coin

	void chushicoin();//初始硬币

	void chushi_all();//初始除硬币以外的

	void stop(const ExMessage& msg);//处理玩家局内暂停

	void power_up(int up_num);//玩家局内法力值升高

	void save_skill();//保存技能等级


private:
	double player_speed = 3 + speed_up;//角色速度
	const int player_width = 80;//角色宽度
	const int player_height = 80;//角色高
	const int shadow_width = 32;//影子宽度
	const int player_fra_num = 6;//玩家动画图片数

	const int hp_x = 1040;//hp的显示位置信息
	const int hp_y = 96;

	int player_hp = 3;//玩家当前血量

public:
	//********************************************技  能  区************
	int max_power;//玩家最大法术值
	int power; //玩家当前法术值
	int is_magic;//法球伤害升级
	int magic_num;    //法球击杀数限制
	int is_ball_skill;//火球法术及其伤害
	int speed_up;//加速
	int player_coin;//玩家钱数
	int max_hp;//玩家血量上限
	int player_attack;  //player普通攻击伤害  
	bool is_the_world; //时停技能升级
	bool is_coin_fly;  //自动拾取硬币技能实现
	int is_max;//max技能升级
	//*******************************************************************
private:
	//影图片
	IMAGE img_shadow;
	//加载玩家向左还是向右移动的指针
	anim *player_anim_left;
	anim *player_anim_right;

	bool alive = 1;

public:
	//移动方向
	bool is_move_up = 0;
	bool is_move_down = 0;
	bool is_move_left = 0;
	bool is_move_right = 0;	

	int left_or_right;

	//角色位置
	POINT player_xy{ 560,320 };

	bool is_stop = 0;
};