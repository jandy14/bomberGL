 #pragma once
#ifndef __BOMB_H__
#define __BOMB_H__

#include "GameManager.h"

class bomb
{
	GLubyte *image, *explosionimage[7];				// �̹��� ���� ����
	int positionX, positionY;						// Bomb�� �ʻ� ��ǥ��
	int drawPositionX, drawPositionY;				// Draw ���� ��ǥ��
	int count;										// ��ź�� ��������� ���� ������
	bool explosing;									// ��ź�� ������ �����ϴ��� Ȯ��
public:
	bomb(int x,int y,GLubyte * image,GLubyte ** explosionimage);
	void Draw();
	void Countdown();
	void Explosion();
	~bomb();
};

extern MapStruct map[15][20];


#endif