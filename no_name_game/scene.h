#pragma once
#include<graphics.h >
class scene
{
public:
	scene() = default;

	virtual ~scene() = default;

	void on_enter() {};

	void update(POINT M_xy) {};

	void on_draw() {};

	int on_input(const ExMessage &msg, POINT M_xy) {};

	void on_exit() {};
};
