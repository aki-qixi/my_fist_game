#include"skill.h"

void skill::max_hp_up(player_anim& player)
{
	if (player.max_hp < 10 && player.player_coin >= 100)
	{
		player.max_hp++;
		player.player_coin -= 100;
		player.save_coin();
	}
}

void skill::magic_up(player_anim& player)
{
	if (player.is_magic < 3 && player.player_coin >= 75)
	{
		player.is_magic++;
		player.player_coin -= 75;
		player.save_coin();
	}
}

void skill::magic_kill_num(player_anim& player)
{
	if (player.magic_num > 3 && player.player_coin >= 100)
	{
		player.magic_num--;
		player.player_coin -= 100;
		player.save_coin();
	}
}

void skill::speed_up(player_anim& player)
{
	if (player.speed_up < 1 && player.player_coin >= 75)
	{
		player.speed_up += 1;
		player.player_coin -= 75;
		player.save_coin();
	}
}

void skill::player_attack_up(player_anim& player)
{
	if (player.player_attack < 5 && player.player_coin >= 100)
	{
		player.player_attack += 1;
		player.player_coin -= 100;
		player.save_coin();
	}
}

void skill::ball_skill_up(player_anim& player)
{
	if (player.is_ball_skill < 3 && player.player_coin >= 125)
	{
		player.is_ball_skill += 1;
		player.player_coin -= 125;
		player.save_coin();
	}
}

void skill::the_world_up(player_anim& player)
{
	if (player.is_the_world == 0 && player.player_coin >= 150)
	{
		player.is_the_world = 1;
		player.player_coin -= 150;
		player.save_coin();
	}
}

void skill::max_power_up(player_anim& player)
{
	if (player.max_power < 200)
	{
		player.max_power += 15;
	}
}

void skill::skill_max_up(player_anim& player)
{
	if (player.is_max < 5 && player.player_coin >= 150)
	{
		player.is_max += 1;
		player.player_coin -= 150;
		player.save_coin();
	}
}