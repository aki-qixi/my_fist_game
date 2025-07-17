#include"role_anim.h"

void player_anim::player_msg(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case 'W':
			is_move_up = 1;
			break;
		case 'S':
			is_move_down = 1;
			break;
		case 'A':
			is_move_left = 1;
			break;
		case 'D':
			is_move_right = 1;
			break;
		case VK_SPACE:
			is_stop = 1;
			break;
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		switch (msg.vkcode)
		{
		case 'W':
			is_move_up = 0;
			break;
		case 'S':
			is_move_down = 0;
			break;
		case 'A':
			is_move_left = 0;
			break;
		case 'D':
			is_move_right = 0;
			break;
		}
	}
}

void player_anim::move()
{
	//利用向量使八个方向等速率移动
	int xx = is_move_right - is_move_left;
	int yy = is_move_down - is_move_up;
	double len = sqrt(xx * xx + yy * yy);
	if (len != 0)
	{
		double xxx = xx / len;
		double yyy = yy / len;
		player_xy.x += (int)(player_speed * xxx);
		player_xy.y += (int)(player_speed * yyy);
	}
	////边界判定1
	//if (player_xy.x < -80)
	//	player_xy.x = 1280;
	//if (player_xy.y < -80)
	//	player_xy.y = 720;
	//if (player_xy.x > 1280)
	//	player_xy.x = -80;
	//if (player_xy.y > 720)
	//	player_xy.y = -80;

	//边界判定2
	if (player_xy.x <= 0 && is_move_left)
		player_xy.x = 0;
	if (player_xy.y <= 0 && is_move_up)
		player_xy.y = 0;
	if (player_xy.x >= 1200 && is_move_right)
		player_xy.x = 1200;
	if (player_xy.y >= 640 && is_move_down)
		player_xy.y = 640;

		
}

void player_anim::draw(int delat)
{
	int shadow_x = player_xy.x + (player_width / 2 - shadow_width / 2);//+0
	int shadow_y = player_xy.y + player_height - 8;//-8
	putimage_plus(shadow_x, shadow_y, &img_shadow);

	static bool is_left = 0;
	int x = is_move_right - is_move_left;
	if (x < 0)
		is_left = 1;
	else if (x > 0)
		is_left = 0;
	if (is_left)
	{
		left_or_right = -1;
		player_anim_left->play(player_xy.x, player_xy.y, delat);
	}
	else
	{
		left_or_right = 1;
		player_anim_right->play(player_xy.x, player_xy.y, delat);
	}
}

void player_anim::hurt(int attack)
{
	player_hp-=attack;
	srand((unsigned int)time(NULL));
	int temp = rand() % 4;
	switch (temp)
	{
	case 0:
		mciSendString(_T("play hurt1 from 0"), NULL, 0, NULL);
		break;
	case 1:
		mciSendString(_T("play hurt2 from 0"), NULL, 0, NULL);
		break;
	case 2:
		mciSendString(_T("play hurt3 from 0"), NULL, 0, NULL);
		break;
	case 3:
		mciSendString(_T("play hurt4 from 0"), NULL, 0, NULL);
		break;
	default:
		break;
	}
	if (player_hp <= 0)
	{
		alive = 0;
	}
}

bool player_anim::checkalive()
{
	return alive;
}

void player_anim::draw_hp(IMAGE& img)
{
	int x = 1240;
	int y = 8;
	int num = 0;
	int t = 0;
	for (int i = 0; i < player_hp; i++)
	{
		t++;
		if (t >= 6)
		{
			y = 56;
			num++;
			t = 1;
			if (num == 2)
				break;
		}
		putimage_plus(x - t * 48, y, &img);
	}
}

void player_anim::cure()
{
	if (player_hp < max_hp)
		player_hp++;
}

void player_anim::coinup(int coin_type)
{
	if (coin_type == 1)
		player_coin += 3;
	else if (coin_type == 2)
		player_coin += 15;
	else if (coin_type == 3)
		player_coin += 75;
}

int player_anim::getcoin()
{
	return player_coin;
}

void player_anim::save_coin()
{
	ofstream ofs;
	ofs.open(filename, ios::out);
	ofs << player_coin;
	ofs.close();
}

void player_anim::save_skill()
{
	ofstream ofs;
	ofs.open(skill_file, ios::out);
	ofs << max_power << endl;
	ofs << is_magic << endl;
	ofs << magic_num << endl;
	ofs << is_ball_skill << endl;
	ofs << speed_up << endl;
	ofs << max_hp << endl;
	ofs << player_attack << endl;
	ofs << is_the_world << endl;
	ofs << is_coin_fly << endl;
	ofs << is_max << endl;
	ofs.close();
}

void player_anim::chushicoin()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	ifs >> player_coin;
	ifs.close();
}

void player_anim::chushi_all()
{
	ifstream ifs(skill_file, ios::in);
	if (ifs.is_open())
	{
		if (!(ifs >> max_power >> is_magic >> magic_num >> is_ball_skill
			>> speed_up >> max_hp >> player_attack >> is_the_world
			>> is_coin_fly >> is_max))
		{
			// 读取失败，恢复默认值
			max_power = 180;
			is_magic = 0;
			magic_num = 5;
			is_ball_skill = 0;
			speed_up = 0;
			max_hp = 3;
			player_attack = 1;
			is_the_world = 0;
			is_coin_fly = 1;
			is_max = 0;
			save_skill(); // 保存默认值
		}
		ifs.close();
	}
	else
	{
		// 文件不存在，恢复默认值
		max_power = 180;
		is_magic = 0;
		magic_num = 5;
		is_ball_skill = 0;
		speed_up = 0;
		max_hp = 3;
		player_attack = 1;
		is_the_world = 0;
		is_coin_fly = 1;
		is_max = 0;
		save_skill(); // 保存默认值
	}

	player_speed = 3 + speed_up;
	player_hp = max_hp;
	power = max_power;
	alive = 1;

	is_move_up = is_move_down = is_move_left = is_move_right = 0;
	player_xy = { 560, 320 };
}

void player_anim::stop(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE)
	{
		is_stop = 0;
		is_move_up = 0;
		is_move_down = 0;
		is_move_left = 0;
		is_move_right = 0;
	}
}

void player_anim::power_up(int up_num)
{
	if(power<max_power)
	{
		power += up_num;
		if(power>=max_power)
			mciSendString(_T("play power_full from 0"), NULL, 0, NULL);
	}
	if (power > max_power)
		power = max_power;
}
