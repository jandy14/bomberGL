 #pragma once
#ifndef __BOMB_H__
#define __BOMB_H__

#include "GameManager.h"

class bomb
{
public:
	bomb(int x,int y);
	void Move();
	void Draw();
	void Moving();
	~bomb();
};


#endif