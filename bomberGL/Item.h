#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "GameManager.h"

class Item
{
private:
	GLubyte *item;
	int positionX, positionY;											// block �迭 ��ǥ��
	int drawPositionX, drawPositionY;									// Draw ���� ��ǥ��
	int drawCount;

public:
	Item(int x, int y, GLubyte *itemList);
	~Item();
	void Draw();
	void Moving();
	void Destroy();
};

#endif
