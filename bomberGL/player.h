#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"GameManager.h"
#include "bomb.h"

class player
{
private:
	GLubyte ***image, **die;
	int positionX, positionY;		//�ʻ󿡼��� ��ǥ
	int drawPositionX, drawPositionY;	//�׸��� �׷��� ��ǥ
	int speedCountMax, speedCount;	//��ü�� �ӵ�
	int dyingcount;					//�״��߿� ����������� Ȯ��
	int temporaryValueX, temporaryValueY;	// Enemy ���Ⱚ
	int way;			//������ ���Ⱚ  0�� 1�� 2�� 3��
	int maxbomb;		//�ִ밡�� ����
	int nowbomb;		//���� ��ġ�� ����
	int power;			//��ź�� ȭ��
	bool moving;		//�����̴� ������ Ȯ��
	bool movingmap;		//�̵��߿� �ʻ󿡼� �Ű������� Ȯ��
	bool right, left, up, down;//���� �����̴� ����
	bool isdying;		//true�� Die����
//	bool Check();		//move()���� ���� �Է°��� ���� �ִ°����� Ȯ��(���� ������ TRUE)??�ʿ����??��
public:
	player(int x, int y, GLubyte ***image, GLubyte **die);
	void Move(int key);		//�Է°��� �޾Ƽ� �������� Moving()�� ���
	void Draw();		//��ü�� �̹����� �׷���
	void Moving();		//move()���� ���� ����� ����(pixelx,y ����)
	void Die();			//��ü�� �״� ����Ŀ� ����
	void Kill();		//isDying�� Ʈ��� �������
	void Putbomb(GLubyte * image,GLubyte **explosionimage);		//��ź ��ġ(��ź Ŭ������ �ν��Ͻ� ����)
//	void Getbomb();		//��ź�� ������ nowbomb�� ���� ���������ش�
//	~player();
};

extern MapStruct map[15][20];

#endif
/*
specialFunc()���� Move()�� ���� �޾Ƽ� Check()�� ���� �ִ��� Ȯ���ϰ� Moving()�� �̵��� ���� �ѱ�
Moving()�� timerFunc()���� �����Ӹ��� ����ȴ�
*/