#pragma once
#include<string>
#include<vector>
#include<graphics.h >
#include"fast_load.hpp"

#pragma comment(lib,"MSIMG32.LIB")
//有透明度的放置图片
inline void putimage_plus(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

//加载动画类
class anim
{	
public:
	anim(fast_load* anims, int interval)
	{
		anim_load = anims;
		interval_ms = interval;
	}

	~anim() = default;

	//动画播放函数
	void play(int x, int y, int delta)
	{
		timer += delta;
		if (timer >= interval_ms)
		{
			idx_img = (idx_img + 1) % anim_load->img_obj.size();
			timer = 0;
		}
		putimage_plus(x, y, anim_load->img_obj[idx_img]);
	}

private:
	int interval_ms = 0;
	int timer = 0;
public:
	int idx_img = 0;
private:
	fast_load* anim_load;
};
