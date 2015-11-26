#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameManager.h"
#include <random>

class enemy 
{
private:
	GLubyte *image[4][2];
	int speedCountMax, speedCount;			// Enemy �ӵ�
	int positionX, positionY;				// Enemy �迭 ��ǥ��
	int drawPositionX, drawPositionY;		// Draw ���� ��ǥ��
	int temporaryValueX, temporaryValueY;	// Enemy ���� ��갪
	int way;								// Enemy ���Ⱚ
	bool moving;							// ������ ����
	bool right, left, up, down;				// �����̴� ����

	bool Check();							// movable üũ

public:
	enemy(int positionX, int positionY);	// Enemy ��ȯ
	~enemy();								// Enemy �Ҹ�
	void Move();							// �Է°��� �޾Ƽ� �������� Moving()�� ���
	void Draw();				// ��ü�� �̹����� �׷���
	void Moving();							// move()���� ���� ����� ����(pixelx,y ����)                                  
};



extern short type[15][20];
extern void *object[15][20];

#endif