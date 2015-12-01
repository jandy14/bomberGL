 #pragma once
#ifndef __BOMB_H__
#define __BOMB_H__

#include "GameManager.h"

class bomb
{
	GLubyte *image, **explosionimage;				// �̹��� ���� ����
	void * master;									// ��ź�� ���� �ּҰ�
	int positionX, positionY;						// Bomb�� �ʻ� ��ǥ��
	int drawPositionX, drawPositionY;				// Draw ���� ��ǥ��
	int count;										// ��ź�� ��������� ���� ������
	int explosioncount;								// ��ź�� ������ ���� Ƚ��
	int power;										// ��ź�� ����
	bool exploding;									// ��ź�� ������ �����ϴ��� Ȯ��
public:
	bomb(void * master,int x,int y,GLubyte *image,GLubyte **explosionimage, int power);
	void Draw();
	void Countdown();
	void Explosion();								//���������� �����ϸ� ���ư��� �Լ�
	void Explode();									//������ ���߽�Ű�� �Լ�
	~bomb();
};

extern MapStruct map[15][20];


#endif