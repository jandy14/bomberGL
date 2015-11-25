#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "MapManager.h"

class block
{
private:
	GLubyte *image;
	int speedCountMax, speedCount;			// block 속도
	int positionX, positionY;				// block 배열 좌표값
	int drawPositionX, drawPositionY;		// Draw 시작 좌표값
	int temporaryValueX, temporaryValueY;	// block 방향값
	bool moving;							// 움직임 상태
	bool right, left, up, down;				// 움직이는 방향
	bool breakable;							// 파괴가능한 벽돌인지 판단

	bool Check();							// movable 체크
public:
	block(int x,int y, GLubyte *i);
	void Move();
	void Draw();
	void Moving();
	~block();
};


extern short type[15][20];
extern void *object[15][20];


#endif