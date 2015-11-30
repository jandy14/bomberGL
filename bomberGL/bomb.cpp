#include "bomb.h"

bomb::bomb(int x, int y,GLubyte *image ,GLubyte **explosionimage)
{
	positionX = x;
	positionY = y;
	drawPositionX = x * 60;
	drawPositionY = (y * 60) + 60;
	count = 60;
	exploding = false;
	explosioncount = 0;

	this->image = image;
	this->explosionimage = explosionimage;
}


bomb::~bomb()
{
}

void bomb::Draw()
{
	if (!exploding)
		DrawFunc(image, drawPositionX, drawPositionY);
	else
		DrawFunc(explosionimage[explosioncount], drawPositionX, drawPositionY);
}

void bomb::Countdown()
{
	if (count > 0)
		count--;
	else
		explosioncount++;
		
}

void bomb::Explosion()
{
	if (count == 0 && !exploding)
	{
		exploding = true;
		for (int i = 1; i <= 4; i++)
		{
			fire * f;
			f = new fire(explosionimage[0], positionX, positionY, i);
			AddNode(&(map[positionY][positionX].nextNode), CreateNode(31, f));
		}
	}
	else if (explosioncount ==  7)
	{
		PopNode(&(map[positionY][positionX].nextNode), this);
		delete this;
	}
}

void bomb::Explode()
{
	count = 1;
}