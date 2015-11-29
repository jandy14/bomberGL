#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "GameManager.h"

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

	bool Check();							// movable 체크
public:
	block(int x,int y, GLubyte *i);
	void Move();
	void Draw();
	void Moving();
	~block();
};

extern MapStruct map[15][20];

#endif