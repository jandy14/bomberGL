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
	case 1://오른
		temporaryValueX = 1;
		temporaryValueY = 0;
		break;
	case 2://위
		temporaryValueY = -1;
		temporaryValueX = 0;
		break;
	case 3://왼
		temporaryValueX = -1;
		temporaryValueY = 0;
		break;
	case 4://아래
		temporaryValueY = 1;
		temporaryValueX = 0;
		break;
	default:
		break;
	}
	/* Fire 이미지 로드 */
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
		/* 상하좌우 움직임 명령 */
		drawPositionX += (60 / speedCountMax) * temporaryValueX;
		drawPositionY += (60 / speedCountMax) * temporaryValueY;

		/* 타일의 절반이상 넘어갔는지 체크 */
		if (speedCountMax / 2 == speedCount)
		{
			FourWayMoving(way, this, &positionX, &positionY, 31);
			Destroyobject(positionX, positionY);
			//칸에 있는거 전부 죽임
			//벽돌이면 부쉼
		}

		/* 타일을 완전히 다 넘어왔는지 체크 */
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
	Node * currentNode = map[y][x].nextNode;
	player * p;
	enemy * e;
	bomb * bom;
		while (currentNode != NULL)
		{
			switch (currentNode->type)
			{
			case 1:
				p = (player *)currentNode->object;
				p->Killplayer();
				break;
			case 2:
				e = (enemy *)currentNode->object;
				e->Kill();
				break;
			case 11:
				movecount = 0;
				break;
			case 12:
				movecount = 0;
				break;
			case 21:
				bom = (bomb *)currentNode->object;
				bom->Explode();
				break;
			default:
				break;
			}
			currentNode = currentNode->nextNode;
		}
}