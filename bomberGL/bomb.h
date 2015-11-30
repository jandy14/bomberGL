 #pragma once
#ifndef __BOMB_H__
#define __BOMB_H__

#include "GameManager.h"

class bomb
{
	GLubyte *image, **explosionimage;				// �̹��� ���� ����
	int positionX, positionY;						// Bomb�� �ʻ� ��ǥ��
	int drawPositionX, drawPositionY;				// Draw ���� ��ǥ��
	int count;										// ��ź�� ��������� ���� ������
	int explosioncount;								// ��ź�� ������ ���� Ƚ��
	bool exploding;									// ��ź�� ������ �����ϴ��� Ȯ��
public:
	bomb(int x,int y,GLubyte *image,GLubyte **explosionimage);
	void Draw();
	void Countdown();
	void Explosion();								//���������� �����ϸ� ���ư��� �Լ�
	void Explode();									//������ ���߽�Ű�� �Լ�
	~bomb();
};

extern MapStruct map[15][20];


#endif