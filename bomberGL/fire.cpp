#include "fire.h"

fire::fire(GLubyte *image, int x, int y,int way)
{
	speedCount = 0;
	speedCountMax = 5;
	movecount = 1;

	this->positionX = x;
	this->positionY = y;

	drawPositionX = 60 * positionX;
	drawPositionY = 60 * (positionY + 1);

	this->way = way;

	switch (way)
	{
	case 1://����
		temporaryValueX = 1;
		temporaryValueY = 0;
		break;
	case 2://��
		temporaryValueY = -1;
		temporaryValueX = 0;
		break;
	case 3://��
		temporaryValueX = -1;
		temporaryValueY = 0;
		break;
	case 4://�Ʒ�
		temporaryValueY = 1;
		temporaryValueX = 0;
		break;
	default:
		break;
	}
	/* Fire �̹��� �ε� */
	this->image = image;
}


fire::~fire()
{
}

void fire::Draw()
{
	DrawFunc(image, drawPositionX, drawPositionY);
}

void fire::Moving()
{
		/* �����¿� ������ ��� */
		drawPositionX += (60 / speedCountMax) * temporaryValueX;
		drawPositionY += (60 / speedCountMax) * temporaryValueY;

		/* Ÿ���� �����̻� �Ѿ���� üũ */
		if (speedCountMax / 2 == speedCount)
		{
			FourWayMoving(way, this, &positionX, &positionY, 31);
			//ĭ�� �ִ°� ���� ����
			//�����̸� �ν�
		}

		/* Ÿ���� ������ �� �Ѿ�Դ��� üũ */
		if (speedCountMax - 1 == speedCount)
		{
			speedCount = 0;
			movecount--;
			if (movecount == 0)
			{
				PopNode(&(map[positionY][positionX].nextNode), this);
				delete this;
			}
		}

		else speedCount++;

	return;
}