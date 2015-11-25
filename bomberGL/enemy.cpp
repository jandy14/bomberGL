#include "enemy.h"

enemy::enemy(int positionX, int positionY)
{
	speedCount = 0;
	speedCountMax = 12;
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
	int randomNumber;

	right = left = up = down = false;
	if (!moving)
	{
		std::random_device rd;
		std::mt19937_64 rng(rd());
		std::uniform_int_distribution<__int64> range(1, 10);
		while (!Check())
		{
			/* 난수 생성 */
			randomNumber = range(rng);

			/* 1 : 오른쪽, 2 : 위, 3 : 왼쪽, 4 : 아래, 5 : x */
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
				goto Here;
				//break;
			}
		}

		Here:
		drawPositionX = 60 * positionX;
		drawPositionY = 60 * (positionY + 1);
		moving = true;
	}

	return;
}

void enemy::Draw(GLubyte *image)
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
