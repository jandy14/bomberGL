#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameManager.h"
#include <random>

class enemy 
{
private:
	GLubyte ***image, **die;													// �̹��� ���� ����
	int speedCountMax, speedCount;												// Enemy �ӵ�
	int dyingCount;																// dying ī��Ʈ
	int positionX, positionY;													// Enemy �迭 ��ǥ��
	int drawPositionX, drawPositionY;											// Draw ���� ��ǥ��
	int temporaryValueX, temporaryValueY;										// Enemy �̵����� ��갪
	int way;																	// Enemy ���� ���尪
	bool moving;																// ������ ����
	bool right, left, up, down;													// �����̴� ����
	bool isDying;																// Die ���°�

	bool Check();																// movable üũ

public:
	enemy(int positionX, int positionY, GLubyte ***image, GLubyte **die);		// Enemy ��ȯ
	~enemy();																	// Enemy �Ҹ�
	void Move();																// �Է°��� �޾Ƽ� �������� Moving()�� ���
	void Draw();																// ��ü�� �̹����� �׷���
	void Moving();																// Move()���� ���� ����� ����(pixelx,y ����)
	void Die();																	// ����� �״� �Լ�
	void Kill();																// Enemy�� Die���¸� True�� ����
};

extern MapStruct map[15][20];


#endif