#include "player.h"

player::player(int x, int y, GLubyte ***image, GLubyte **die)
{
	positionX = x;
	positionY = y;
	drawPositionX = x * 60;
	drawPositionY = (y * 60) + 60;
	temporaryValueX = temporaryValueY = 0;
	way = 0;
	maxbomb = 1;
	nowbomb = 1;
	power = 1;
	speedCountMax = 12;
	speedCount = 0;
	moving = false;
	right = left = up = down = false;
	isdying = false;
	dyingcount = 0;

	this->image = image;
	this->die = die;
}

void player::Move(int key)
{
	if (!moving && !isdying)
	{
		switch (key)
		{
		case GLUT_KEY_RIGHT:
			way = 0;
			if (map[positionY][positionX + 1].nextNode->type <= 10)
			{
				right = true;
				temporaryValueX = 1;
				moving = true;
			}
			left = up = down = false;
			break;
		case GLUT_KEY_LEFT:
			way = 1;
			if (map[positionY][positionX - 1].nextNode->type <= 10)
			{
				left = true;
				temporaryValueX = -1;
				moving = true;
			}
			right = up = down = false;
			break;
		case GLUT_KEY_UP:
			way = 2;
			if (map[positionY - 1][positionX].nextNode->type <= 10)
			{
				up = true;
				temporaryValueY = -1;
				moving = true;
			}
			left = right = down = false;
			break;
		case GLUT_KEY_DOWN:
			way = 3;
			if (map[positionY + 1][positionX].nextNode->type <= 10)
			{
				down = true;
				temporaryValueY = 1;
				moving = true;
			}
			left = up = right = false;
			break;
		}
	}
}
void player::Moving()
{
	if (moving && !isdying)
	{
		/* 상하좌우 움직임 명령 */
		drawPositionX += (60 / speedCountMax) * temporaryValueX;
		drawPositionY += (60 / speedCountMax) * temporaryValueY;

		/* 타일의 절반이상 넘어갔는지 체크 */
		if (speedCountMax / 2 == speedCount)
		{
			FourWayMoving(right + (up * 2) + (left * 3) + (down * 4), this, &positionX, &positionY, 1);
			if (SearchNode(map[positionY][positionX].nextNode, 2))//이동한 위치에 적이 있는지 확인 없으면 true
				Kill();
		}

		/* 타일을 완전히 다 넘어왔는지 체크 */
		if (speedCountMax - 1 == speedCount)
		{
			moving = false;
			right = left = up = down = false;
			speedCount = 0;
			temporaryValueX = temporaryValueY = 0;
		}

		else speedCount++;
	}

	return;
}
void player :: Draw()
{
	if (isdying)
		DrawFunc(die[dyingcount%3], drawPositionX, drawPositionY);
	else
	{
		if (moving)
		{
			if (speedCount * 5 / 4 > speedCountMax) DrawFunc(image[way][4], drawPositionX, drawPositionY);
			else if (speedCount * 5 / 3 > speedCountMax) DrawFunc(image[way][3], drawPositionX, drawPositionY);
			else if (speedCount * 5 / 2 > speedCountMax) DrawFunc(image[way][2], drawPositionX, drawPositionY);
			else if (speedCount * 5 > speedCountMax) DrawFunc(image[way][1], drawPositionX, drawPositionY);
			else DrawFunc(image[way][0], drawPositionX, drawPositionY);

		}
		else DrawFunc(image[way][0], drawPositionX, drawPositionY);
	}
}

void player::Putbomb(GLubyte * image, GLubyte **explosionimage)
{
	if (!SearchNode(map[positionY][positionX].nextNode, 21) && !isdying)//그자리에 폭탄이 있는지 확인 없으면 true
	{
		bomb *bom = new bomb(positionX, positionY, image, explosionimage);
		AddNode(&(map[positionY][positionX].nextNode), CreateNode(21, bom));
	}
}

void player::Die()
{
	if (isdying)
	{
		if (dyingcount == 8)
		{
			PopNode(&(map[positionY][positionX].nextNode), this);
			delete this;
		}

		dyingcount++;
	}
}

void player::Kill()
{
	isdying = true;
}