#pragma once
#include<graphics.h >
#include<string>
#include<vector>
#include"role_anim.h"
#include"load_anim.hpp"

//∑® ı’Û
class magic
{
public:
	magic(fast_load* f_magic_anim);

	~magic() {};

	void draw(int delat);

	bool checkplayer(const player_anim& player);


public:
	POINT magic_xy = { 0,0 };
private:
	const int magic_size = 10;
	anim* magic_anim;

};
