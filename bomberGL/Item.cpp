#include "Item.h"

Item::Item(int x, int y, GLubyte *itemList)
{
	this->item = itemList;

	this->positionX = x;
	this->positionY = y;

	drawCount = 1;

	drawPositionX = 60 * positionX;
	drawPositionY = 60 * (positionY + 1);
}

Item::~Item()
{

}

void Item::Draw()
{
	DrawFunc(item, drawPositionX, drawPositionY);
}

void Item::Moving()
{
	if (drawCount < 6)
	{
		if (drawCount % 2 == 0)
			drawPositionY--;
	}

	else if (drawCount < 12)
	{
		if (drawCount % 2 == 0)
			drawPositionY++;
	}

	else if (drawCount == 12) drawCount = -1;

	drawCount++;
}

void Item::Destroy()
{
	PopNode(&(map[positionY][positionX].nextNode), this);
	delete this;
}
