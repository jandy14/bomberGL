#include "player.h"

player::player(int x, int y)
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

	image[0][0] = LoadBmp("Image/player/Right_1.bmp");
	image[0][1] = LoadBmp("Image/player/Right_2.bmp");
	image[0][2] = LoadBmp("Image/player/Right_3.bmp");
	image[0][3] = LoadBmp("Image/player/Right_4.bmp");
	image[0][4] = LoadBmp("Image/player/Right_5.bmp");

	image[1][0] = LoadBmp("Image/player/Left_1.bmp");
	image[1][1] = LoadBmp("Image/player/Left_2.bmp");
	image[1][2] = LoadBmp("Image/player/Left_3.bmp");
	image[1][3] = LoadBmp("Image/player/Left_4.bmp");
	image[1][4] = LoadBmp("Image/player/Left_5.bmp");

	image[2][0] = LoadBmp("Image/player/Up_1.bmp");
	image[2][1] = LoadBmp("Image/player/Up_2.bmp");
	image[2][2] = LoadBmp("Image/player/Up_3.bmp");
	image[2][3] = LoadBmp("Image/player/Up_4.bmp");
	image[2][4] = LoadBmp("Image/player/Up_5.bmp");

	image[3][0] = LoadBmp("Image/player/Down_1.bmp");
	image[3][1] = LoadBmp("Image/player/Down_2.bmp");
	image[3][2] = LoadBmp("Image/player/Down_3.bmp");
	image[3][3] = LoadBmp("Image/player/Down_4.bmp");
	image[3][4] = LoadBmp("Image/player/Down_5.bmp");
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