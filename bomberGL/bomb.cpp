#include "bomb.h"



bomb::bomb(int x, int y,GLubyte* image ,GLubyte ** explosionimage)
{
	positionX = x;
	positionY = y;
	drawPositionX = x * 60;
	drawPositionY = (y * 60) + 60;
	count = 60;
	this->image = image;
	for (int i = 0; i < 7; i++)
		this->explosionimage[i] = explosionimage[i];
}


bomb::~bomb()
{
}

void bomb::Draw()
{
	if (!explosing)
		DrawFunc(image, drawPositionX, drawPositionY);
	else
		DrawFunc(explosionimage[count*(-1)], drawPositionX, drawPositionY);
}

void bomb::Countdown()
{
	count--;
}

void bomb::Explosion()
{
	if (count == 0)
		explosing = true;
	else if (count <=  -7)
	{
		PopNode(&(map[positionY][positionX].nextNode), this);
		delete this;
	}
}