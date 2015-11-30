#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include"GameManager.h"
#include "bomb.h"

class player
{
private:
	GLubyte ***image, **die;
	int positionX, positionY;		//맵상에서의 좌표
	int drawPositionX, drawPositionY;	//그림이 그려질 좌표
	int speedCountMax, speedCount;	//객체의 속도
	int dyingcount;					//죽는중에 몇번지났는지 확인
	int temporaryValueX, temporaryValueY;	// Enemy 방향값
	int way;			//가려는 방향값  0우 1좌 2상 3하
	int maxbomb;		//최대가능 갯수
	int nowbomb;		//현재 설치한 갯수
	int power;			//폭탄의 화력
	bool moving;		//움직이는 중인지 확인
	bool movingmap;		//이동중에 맵상에서 옮겨졌는지 확인
	bool right, left, up, down;//현재 움직이는 상태
	bool isdying;		//true면 Die실행
//	bool Check();		//move()에서 받은 입력값이 갈수 있는곳인지 확인(갈수 있으면 TRUE)??필요없나??ㅋ
public:
	player(int x, int y, GLubyte ***image, GLubyte **die);
	void Move(int key);		//입력값을 받아서 움직임을 Moving()에 명령
	void Draw();		//객체의 이미지를 그려줌
	void Moving();		//move()에서 받은 명령을 시행(pixelx,y 설정)
	void Die();			//객체를 죽는 모션후에 죽임
	void Kill();		//isDying을 트루로 만들어줌
	void Putbomb(GLubyte * image,GLubyte **explosionimage);		//폭탄 설치(폭탄 클래스의 인스턴스 생성)
//	void Getbomb();		//폭탄이 터지면 nowbomb의 값을 재조정해준다
//	~player();
};

extern MapStruct map[15][20];

#endif
/*
specialFunc()에서 Move()가 값을 받아서 Check()로 갈수 있는지 확인하고 Moving()에 이동할 곳을 넘김
Moving()은 timerFunc()에서 프레임마다 실행된다
*/