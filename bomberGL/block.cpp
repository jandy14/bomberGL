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
	int x, y;
	int count = 0;
	x = this->drawPositionX;
	y = this->drawPositionY;

	for (int pixelindex = 0; pixelindex < 10800; pixelindex += 3)
	{
		count++;
		if (image[pixelindex] + image[pixelindex + 1] + image[pixelindex + 2] != 765)
		{
			glBegin(GL_POINTS);
			{
				glColor3ub(image[pixelindex + 2], image[pixelindex + 1], image[pixelindex]);
				glVertex2f(ConversionX(x), ConversionY(y));
			}
			glEnd();
		}

		if (count == 60)
		{
			y--;
			x = this->drawPositionX;
			count = 0;
		}

		x++;
	}
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