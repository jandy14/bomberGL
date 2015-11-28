#include "enemy.h"

enemy::enemy(int positionX, int positionY, GLubyte *image[4][2], GLubyte *die[3])
{
	way = 1;

	speedCount = 0;
	speedCountMax = 12;

	drawPositionX = 60 * positionX;
	drawPositionY = 60 * (positionY + 1);

	temporaryValueX = temporaryValueY = 0;
	right = left = up = down = false;
	isDying = moving = false;

	this->positionX = positionX;
	this->positionY = positionY;

	/* Enemy �̹��� �ε� */
	for (int i = 0; i < 4; i++)
	{
		this->image[i][0] = image[i][0];
		this->image[i][1] = image[i][1];
	}

	for (int i = 0; i < 3; i++) this->die[i] = die[i];
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
			if (map[positionY][positionX + 1].nextNode->type <= 10)
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
			if (map[positionY][positionX - 1].nextNode->type <= 10)
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
			if (map[positionY - 1][positionX].nextNode->type <= 10)
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
			if (map[positionY + 1][positionX].nextNode->type <= 10)
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

	if (!moving && !isDying)
	{
		while (!Check())
		{
			/* ���� ���� */
			randomNumber = range(rng);
			right = left = up = down = false;

			/* 1 : ������, 2 : ��, 3 : ����, 4 : �Ʒ�, 5~ : ���� */
			switch (randomNumber)
			{
			case RIGHT:
				right = true;
				break;
			case UP:
				up = true;
				break;
			case LEFT:
				left = true;
				break;
			case DOWN:
				down = true;
				break;
			case 7:
				isDying = true;
				return;
			default:
				return;
			}

			way = randomNumber;
		}
	}

	moving = true;
	return;
}

void enemy::Draw()
{
	if (isDying) DrawFunc(die[speedCount % 3], drawPositionX, drawPositionY);
	else DrawFunc(image[way - 1][(speedCount / 2) % 2], drawPositionX, drawPositionY);
}

void enemy::Moving()
{
	if (moving && !isDying)
	{
		/* �����¿� ������ ��� */
		drawPositionX += (60 / speedCountMax) * temporaryValueX;
		drawPositionY += (60 / speedCountMax) * temporaryValueY;

		/* Ÿ���� �����̻� �Ѿ���� üũ */
		if (speedCountMax / 2 == speedCount)
			FourWayMoving(right + (up * 2) + (left * 3) + (down * 4), this, &positionX, &positionY, 2);

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

void enemy::Die()
{
	if (isDying)
	{
		if (speedCount == 2)
		{
			PopNode(&(map[positionY][positionX].nextNode), this);
			free(this);
		}

		speedCount++;
	}
}