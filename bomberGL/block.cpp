#include "block.h"

block::block(int x, int y, GLubyte *image)
{
	this->image = image;
	speedCount = 0;
	speedCountMax = 12;
	temporaryValueX = temporaryValueY = 0;
	right = left = up = down = false;
	moving = false;
	this->positionX = x;
	this->positionY = y;
	drawPositionX = x * 60;
	drawPositionY = (y * 60) + 60;
}

block::~block()
{

}

void block::Draw()
{
	DrawFunc(image, drawPositionX, drawPositionY);
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