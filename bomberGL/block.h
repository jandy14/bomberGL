#pragma once
#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "GameManager.h"

class block
{
private:
	GLubyte *image, **destroy, **itemList;											// �̹��� ���� ����
	int speedCountMax, speedCount;													// block �ӵ�
	int breakCount;																	// Break ī��Ʈ
	int attackCount;																// Attack ī��Ʈ
	int positionX, positionY;														// block �迭 ��ǥ��
	int drawPositionX, drawPositionY;												// Draw ���� ��ǥ��
	int temporaryValueX, temporaryValueY;											// block ���Ⱚ
	bool moving;																	// ������ ����
	bool right, left, up, down;														// �����̴� ����
	bool isBreaking;																// Break ���°�
	bool isShooting;																// �� �߻� ���� ���°�
	bool attack;																	// ���� ���°�

	bool Check();																	// movable üũ
public:
	block(int x, int y, GLubyte *image, GLubyte **destroy, GLubyte **itemList);		// ���� ����
	~block();																		// ���� �ı�
	void Move();
	void Draw();
	void Moving();
	void Destroy();																	// ������ �μ���
	void Break();																	// ������ Break ���¸� True�� ����
	void setShooting();																// isShooting ����
	void Attack(GLubyte **explosionimage);
};

extern MapStruct map[15][20];

#endif