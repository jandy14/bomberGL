#include "player.h"
#include"MapManager.h"

player::player(int x, int y)
{
	positionX = x;
	positionY = y;
	drawPositionX = x * 60;
	drawPositionY = (y * 60) + 60;
	maxbomb = 1;
	nowbomb = 1;
	power = 1;
	speedCountMax = 20;
	speedCount = 0;
	moving = false;
	right = left = up = down = false;
}

void player::Move(int key)
{
	if (!moving)
	{
		switch (key)
		{
		case GLUT_KEY_RIGHT:
			if (type[positionY][positionX + 1] <= 10)
			{
				right = true;
				temporaryValueX = 1;
			}
			left = up = down = false;
			break;
		case GLUT_KEY_LEFT:
			if (type[positionY][positionX - 1] <= 10)
			{
				left = true;
				temporaryValueX = -1;
			}
			right = up = down = false;
			break;
		case GLUT_KEY_UP:
			if (type[positionY - 1][positionX] <= 10)
			{
				up = true;
				temporaryValueY = -1;
			}
			left = right = down = false;
			break;
		case GLUT_KEY_DOWN:
			if (type[positionY + 1][positionX] <= 10)
			{
				down = true;
				temporaryValueY = 1;
			}
			left = up = right = false;
			break;
		}
		moving = true;
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
				type[positionY][positionX++] = 0;
				type[positionY][positionX] = 1;
				object[positionY][positionX] = object[positionY][positionX - 1];
				object[positionY][positionX - 1] = NULL;
			}

			else if (left)
			{
				type[positionY][positionX--] = 0;
				type[positionY][positionX] = 1;
				object[positionY][positionX] = object[positionY][positionX + 1];
				object[positionY][positionX + 1] = NULL;
			}

			else if (up)
			{
				type[positionY--][positionX] = 0;
				type[positionY][positionX] = 1;
				object[positionY][positionX] = object[positionY + 1][positionX];
				object[positionY + 1][positionX] = NULL;
			}

			else if (down)
			{
				type[positionY++][positionX] = 0;
				type[positionY][positionX] = 1;
				object[positionY][positionX] = object[positionY - 1][positionX];
				object[positionY - 1][positionX] = NULL;
			}
		}

		/* 타일을 완전히 다 넘어왔는지 체크 */
		if (speedCountMax == speedCount)
		{
			moving = false;
			right = left = up = down = false;
			speedCount = 0;
			temporaryValueX = temporaryValueY = 0;
		}

		else speedCount++;
	}

	return;
	//speed가 기존 speedcount의 역할을 하고 60/speed를 한 스텝으로 잡고 움직이면서
	//speedcount가 speed와 같아지면 그좌표로 정확히 꽂아주는 방식
	//그리고 speedcount가 speed의 반을 넘으면 그때 맵상의 좌표도 옮겨 주는걸로
}
void player :: Draw()
{

}