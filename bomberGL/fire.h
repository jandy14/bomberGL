#pragma once
#ifndef __FIRE_H__
#define __FIRE_H__

#include "GameManager.h"

class fire
{
private:
	GLubyte *image;							//이미지
	int speedCountMax, speedCount;			//속도
	int positionX, positionY;				//맵상에서의 위치
	int drawPositionX, drawPositionY;		//그려지는픽셀값
	int temporaryValueX, temporaryValueY;	//방향값에 따른 그거
	int movecount;							//움직일수 있는 횟수
	int way;								//방향값 1오른 2위 3왼 4아래

public:
	fire(GLubyte *image, int x,int y,int way);
	~fire();
	void Draw();
	void Moving();
	void Destroyobject(int x, int y);
};


#endif