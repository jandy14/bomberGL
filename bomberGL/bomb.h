 #pragma once
#ifndef __BOMB_H__
#define __BOMB_H__

#include "GameManager.h"

class bomb
{
	GLubyte *image, *explosionimage[7];				// 이미지 저장 변수
	int positionX, positionY;						// Bomb의 맵상 좌표값
	int drawPositionX, drawPositionY;				// Draw 시작 좌표값
	int count;										// 폭탄이 터지기까지 남은 프레임
	bool explosing;									// 폭탄이 터지기 시작하는지 확인
public:
	bomb(int x,int y,GLubyte * image,GLubyte ** explosionimage);
	void Draw();
	void Countdown();
	void Explosion();
	~bomb();
};

extern MapStruct map[15][20];


#endif