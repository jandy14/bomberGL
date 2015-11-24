#include "enemy.h"

enemy::enemy(int positionX, int positionY)
{
	speedCount = 0;
	temporaryValueX = temporaryValueY = 0;
	right = left = up = down = false;
	moving = false;
	this->positionX = positionX;
	this->positionY = positionY;

	//InitMap(2, , positionX, positionY);
}

enemy::~enemy()
{

}

bool enemy::Check()
{
	if (right)
	{
		if (positionX + 1 < 20)
		{
			if (type[positionY][positionX + 1] == 0)
			{
				temporaryValueX = 1;
				return true;
			}
		}
	}

	else if (left)
	{
		if (positionX - 1 >= 0)
		{
			if (type[positionY][positionX - 1] == 0)
			{
				temporaryValueX = -1;
				return true;
			}
		}
	}

	else if (up)
	{
		if (positionY - 1 >= 0)
		{
			if (type[positionY - 1][positionX] == 0)
			{
				temporaryValueY = -1;
				return true;
			}
		}
	}

	else if (down)
	{
		if (positionY + 1 < 20)
		{
			if (type[positionY + 1][positionX] == 0)
			{
				temporaryValueY = 1;
				return true;
			}
		}
	}

	return false;
}

void enemy::Move()
{
	if (!moving)
	{
		/* 난수 생성 */
		std::random_device rd;
		std::mt19937_64 rng(rd());
		std::uniform_int_distribution<__int64> range(1, 4);

		int randomNumber = range(rng);

		while (!Check())
		{
			/* 1 : 오른쪽, 2 : 위, 3 : 왼쪽, 4 : 아래 */
			switch (randomNumber)
			{
			case 1:
				right = true;
				break;
			case 2:
				up = true;
				break;
			case 3:
				left = true;
				break;
			case 4:
				down = true;
				break;
			}
		}

		drawPositionX = 60 * positionX;
		drawPositionY = 60 * (positionY + 1);
		moving = true;
	}

	return;
}

void enemy::Draw()
{

}

void enemy::Moving()
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
				type[positionY][positionX] = 2;
			}

			else if (left)
			{
				type[positionY][positionX--] = 0;
				type[positionY][positionX] = 2;
			}

			else if (up)
			{
				type[positionY--][positionX] = 0;
				type[positionY][positionX] = 2;
			}

			else if (down)
			{
				type[positionY++][positionX] = 0;
				type[positionY][positionX] = 2;
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
}
