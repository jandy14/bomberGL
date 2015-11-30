#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "GameManager.h"

class Item
{
private:
	GLubyte *item;
	int positionX, positionY;											// block 배열 좌표값
	int drawPositionX, drawPositionY;									// Draw 시작 좌표값
	int drawCount;

public:
	Item(int x, int y, GLubyte *itemList);
	~Item();
	void Draw();
	void Moving();
	void Destroy();
};

#endif
