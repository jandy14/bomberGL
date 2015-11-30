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
	fire * f;
	if (count == 0)
	{
		explosing = true;
		for (int i = 1; i <= 4; i++)
		{
			f = new fire(explosionimage[0], positionX, positionY, i);
			AddNode(&(map[positionY][positionX].nextNode), CreateNode(31, f));
		}
	}
	else if (count <=  -7)
	{
		PopNode(&(map[positionY][positionX].nextNode), this);
		delete this;
	}
}