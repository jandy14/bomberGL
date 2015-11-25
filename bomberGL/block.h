#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "MapManager.h"

class block
{
private:
	GLubyte *image;
	int speedCountMax, speedCount;			// block �ӵ�
	int positionX, positionY;				// block �迭 ��ǥ��
	int drawPositionX, drawPositionY;		// Draw ���� ��ǥ��
	int temporaryValueX, temporaryValueY;	// block ���Ⱚ
	bool moving;							// ������ ����
	bool right, left, up, down;				// �����̴� ����
	bool breakable;							// �ı������� �������� �Ǵ�

	bool Check();							// movable üũ
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