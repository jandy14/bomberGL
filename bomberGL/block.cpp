#include "block.h"

block::block(int x, int y, GLubyte *image, GLubyte **destroy, GLubyte **itemList)
{
	speedCount = 0;
	speedCountMax = 12;

	breakCount = 0;

	temporaryValueX = temporaryValueY = 0;
	right = left = up = down = false;
	isBreaking = moving = false;

	this->positionX = x;
	this->positionY = y;

	drawPositionX = x * 60;
	drawPositionY = (y * 60) + 60;

	this->image = image;
	this->destroy = destroy;
	this->itemList = itemList;
}

block::~block()
{

}

void block::Draw()
{
	if (isBreaking) DrawFunc(destroy[breakCount], drawPositionX, drawPositionY);
	else DrawFunc(image, drawPositionX, drawPositionY);
}

bool block::Check()
{
	return false;
}

void block::Moving()
{

}

void block::Move()
{

}

void block::Destroy()
{
	if (isBreaking)
	{
		if (breakCount == 4)
		{
			Item *i;
			i = new Item(positionX, positionY, itemList[0]);
			PopNode(&(map[positionY][positionX].nextNode), this);
			AddNode(&(map[positionY][positionX].nextNode), CreateNode(41, i));
			
			delete this;
		}

		breakCount++;
	}
}

void block::Break()
{
	isBreaking = true;
}