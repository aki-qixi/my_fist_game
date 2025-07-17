#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"role_anim.h"
#include <ctime>
using namespace std;

class bullet
{
public:
	bullet(const player_anim &player);

	~bullet(){}

	//»æÖÆ×Óµ¯
	void draw(const player_anim &player);

	void move(const player_anim &player);



private:
	const int bullet_size = 10;
	const int bullet_speed = 12;
	int left_or_right;

public:
	POINT bullet_xy = { 0,0 };
	int xx = 0;
	int yy = 0;
};
