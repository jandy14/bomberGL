#include "fire.h"

fire::fire(GLubyte *image, int x, int y,int way, int power)
{
	speedCount = 0;
	speedCountMax = 5;
	movecount = power;

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
		Destroyobject(positionX, positionY);
		//ĭ�� �ִ°� ���� ����
		//�����̸� �ν�
	}

	/* Ÿ���� ������ �� �Ѿ�Դ��� üũ */
	if (speedCountMax - 1 == speedCount)
	{
		speedCount = 0;
		movecount--;
	}

	else speedCount++;

	if (movecount == 0)
	{
		PopNode(&(map[positionY][positionX].nextNode), this);
		delete this;
	}

	return;
}

void fire::Destroyobject(int x, int y)
{
	Node *currentNode = map[y][x].nextNode;
	Node *prevNode = NULL;
	player *p;
	enemy *e;
	block *b;
	bomb *bom;
	Item *i;

	while (currentNode != NULL)
	{
		switch (currentNode->type)
		{
		case 1:
			p = (player *)currentNode->object;
			p->Kill();
			break;
		case 2:
			e = (enemy *)currentNode->object;
			e->Kill();
			break;
		case 11:
			movecount = 0;
			break;
		case 12:
			b = (block *)currentNode->object;
			b->Break();
			movecount = 0;
			break;
		case 21:
			bom = (bomb *)currentNode->object;
			bom->Explode();
			break;
		case 41: case 42: case 43:
			i = (Item *)currentNode->object;
			i->Destroy();

			if (currentNode->object != i)
			{
				if (prevNode != NULL) currentNode = prevNode->nextNode;
				else if (prevNode == NULL) currentNode = map[y][x].nextNode;
				continue;
			}
			break;
		default:
			break;
		}
		prevNode = currentNode;
		currentNode = currentNode->nextNode;
	}
}