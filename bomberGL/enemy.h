#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameManager.h"
#include <random>

class enemy 
{
private:
	GLubyte ***image, **die;													// 이미지 저장 변수
	int speedCountMax, speedCount;												// Enemy 속도
	int dyingCount;																// dying 카운트
	int positionX, positionY;													// Enemy 배열 좌표값
	int drawPositionX, drawPositionY;											// Draw 시작 좌표값
	int temporaryValueX, temporaryValueY;										// Enemy 이동방향 계산값
	int way;																	// Enemy 방향 저장값
	bool moving;																// 움직임 상태
	bool right, left, up, down;													// 움직이는 방향
	bool isDying;																// Die 상태값

	bool Check();																// movable 체크

public:
	enemy(int positionX, int positionY, GLubyte ***image, GLubyte **die);		// Enemy 소환
	~enemy();																	// Enemy 소멸
	void Move();																// 입력값을 받아서 움직임을 Moving()에 명령
	void Draw();																// 객체의 이미지를 그려줌
	void Moving();																// Move()에서 받은 명령을 시행(pixelx,y 설정)
	void Die();																	// 경단이 죽는 함수
	void Kill();																// Enemy의 Die상태를 True로 만듦
};

extern MapStruct map[15][20];


#endif