#pragma once
#ifndef __FIRE_H__
#define __FIRE_H__

#include "GameManager.h"

class fire
{
private:
	GLubyte *image;							//�̹���
	int speedCountMax, speedCount;			//�ӵ�
	int positionX, positionY;				//�ʻ󿡼��� ��ġ
	int drawPositionX, drawPositionY;		//�׷������ȼ���
	int temporaryValueX, temporaryValueY;	//���Ⱚ�� ���� �װ�
	int movecount;							//�����ϼ� �ִ� Ƚ��
	int way;								//���Ⱚ 1���� 2�� 3�� 4�Ʒ�

public:
	fire(GLubyte *image, int x,int y,int way);
	~fire();
	void Draw();
	void Moving();
	void Destroyobject(int x, int y);
};


#endif