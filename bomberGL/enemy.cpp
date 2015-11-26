#include "enemy.h"

enemy::enemy(int positionX, int positionY)
{
	way = 1;

	speedCount = 0;
	speedCountMax = 12;

	drawPositionX = 60 * positionX;
	drawPositionY = 60 * (positionY + 1);

	temporaryValueX = temporaryValueY = 0;
	right = left = up = down = false;
	moving = false;

	this->positionX = positionX;
	this->positionY = positionY;

	/* Enemy �̹��� �ε� */
	this->image[0][0] = LoadBmp("Image/Enemy/Right_1.bmp");
	this->image[0][1] = LoadBmp("Image/Enemy/Right_2.bmp");

	this->image[1][0] = LoadBmp("Image/Enemy/Up_1.bmp");
	this->image[1][1] = LoadBmp("Image/Enemy/Up_2.bmp");

	this->image[2][0] = LoadBmp("Image/Enemy/Left_1.bmp");
	this->image[2][1] = LoadBmp("Image/Enemy/Left_2.bmp");

	this->image[3][0] = LoadBmp("Image/Enemy/Down_1.bmp");
	this->image[3][1] = LoadBmp("Image/Enemy/Down_2.bmp");
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
		if (positionY + 1 < 15)
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
	int randomNumber;
	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<__int64> range(1, 10);

	if (!moving)
	{
		while (!Check())
		{
			/* ���� ���� */
			randomNumber = range(rng);
			right = left = up = down = false;

			/* 1 : ������, 2 : ��, 3 : ����, 4 : �Ʒ�, 5~ : ���� */
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
			default:
				return;
			}

			way = randomNumber;
		}
	}

	//Sleep((range(rng)) * 50);
	moving = true;
	return;
}

void enemy::Draw()
{
	DrawFunc(image[way - 1][(speedCount / 4) % 2], drawPositionX, drawPositionY);
}

void enemy::Moving()
{
	if (moving)
	{
		/* �����¿� ������ ��� */
		drawPositionX += (60 / speedCountMax) * temporaryValueX;
		drawPositionY += (60 / speedCountMax) * temporaryValueY;

		/* Ÿ���� �����̻� �Ѿ���� üũ */
		if (speedCountMax / 2 == speedCount)
		{
			if (right)
			{
				type[positionY][positionX++] = 0;
				type[positionY][positionX] = 2;
				object[positionY][positionX] = object[positionY][positionX - 1];
				object[positionY][positionX - 1] = NULL;
			}

			else if (left)
			{
				type[positionY][positionX--] = 0;
				type[positionY][positionX] = 2;
				object[positionY][positionX] = object[positionY][positionX + 1];
				object[positionY][positionX + 1] = NULL;
			}

			else if (up)
			{
				type[positionY--][positionX] = 0;
				type[positionY][positionX] = 2;
				object[positionY][positionX] = object[positionY + 1][positionX];
				object[positionY + 1][positionX] = NULL;
			}

			else if (down)
			{
				type[positionY++][positionX] = 0;
				type[positionY][positionX] = 2;
				object[positionY][positionX] = object[positionY - 1][positionX];
				object[positionY - 1][positionX] = NULL;
			}
		}

		/* Ÿ���� ������ �� �Ѿ�Դ��� üũ */
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
