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

	/* Enemy 이미지 로드 */
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
			/* 난수 생성 */
			randomNumber = range(rng);
			right = left = up = down = false;

			/* 1 : 오른쪽, 2 : 위, 3 : 왼쪽, 4 : 아래, 5~ : 정지 */
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
		/* 상하좌우 움직임 명령 */
		drawPositionX += (60 / speedCountMax) * temporaryValueX;
		drawPositionY += (60 / speedCountMax) * temporaryValueY;

		/* 타일의 절반이상 넘어갔는지 체크 */
		if (speedCountMax / 2 == speedCount)
			FourWayMoving(right + (up * 2) + (left * 3) + (down * 4), this, &positionX, &positionY, 2);

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