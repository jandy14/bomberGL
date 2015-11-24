#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "MapManager.h"

class block
{
public:
	block(int x,int y);
	void Move();
	void Draw();
	void Moving();
	~block();
};


extern short type[15][20];
extern void *object[15][20];


#endif