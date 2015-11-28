#include "player.h"

player::player(int x, int y, GLubyte *image[4][5], GLubyte *die[3])
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

	for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) this->image[i][j] = image[i][j];
}

void player::Move(int key)
{
	if (!moving)
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
	if (moving)
	{
		/* 상하좌우 움직임 명령 */
		drawPositionX += (60 / speedCountMax) * temporaryValueX;
		drawPositionY += (60 / speedCountMax) * temporaryValueY;

		/* 타일의 절반이상 넘어갔는지 체크 */
		if (speedCountMax / 2 == speedCount)
		{
			if (right)
			{
				AddNode(&(map[positionY][++positionX].nextNode), CreateNode(1, this));
				PopNode(&(map[positionY][positionX - 1].nextNode), this);
			}

			else if (left)
			{
				AddNode(&(map[positionY][--positionX].nextNode), CreateNode(1, this));
				PopNode(&(map[positionY][positionX + 1].nextNode), this);
			}

			else if (up)
			{
				AddNode(&(map[--positionY][positionX].nextNode), CreateNode(1, this));
				PopNode(&(map[positionY + 1][positionX].nextNode), this);
			}

			else if (down)
			{
				AddNode(&(map[++positionY][positionX].nextNode), CreateNode(1, this));
				PopNode(&(map[positionY - 1][positionX].nextNode), this);
			}
		}

		/* 타일을 완전히 다 넘어왔는지 체크 */
		if (speedCountMax-1 == speedCount)
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