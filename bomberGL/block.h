#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "GameManager.h"

class block
{
private:
	GLubyte *image, **destroy, **itemList;											// 이미지 저장 변수
	int speedCountMax, speedCount;													// block 속도
	int breakCount;																	// Break 카운트
	int attackCount;																// Attack 카운트
	int positionX, positionY;														// block 배열 좌표값
	int drawPositionX, drawPositionY;												// Draw 시작 좌표값
	int temporaryValueX, temporaryValueY;											// block 방향값
	bool moving;																	// 움직임 상태
	bool right, left, up, down;														// 움직이는 방향
	bool isBreaking;																// Break 상태값
	bool isShooting;																// 불 발사 가능 상태값
	bool attack;																	// 공격 상태값

	bool Check();																	// movable 체크
public:
	block(int x, int y, GLubyte *image, GLubyte **destroy, GLubyte **itemList);		// 벽돌 생성
	~block();																		// 벽돌 파괴
	void Move();
	void Draw();
	void Moving();
	void Destroy();																	// 벽돌을 부순다
	void Break();																	// 벽돌의 Break 상태를 True로 만듦
	void setShooting();																// isShooting 세팅
	void Attack(GLubyte **explosionimage);
};

extern MapStruct map[15][20];

#endif