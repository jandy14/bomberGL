#pragma once									// 해결 해야할 문제들
#ifndef __GAMEMANAGER_H__						// Image 포인터값을 객체에 전달
#define __GAMEMANAGER_H__						// 오른쪽, 아래로 갈때 순풍으로 인한 텔레포트
												// 노드 Pop시 main.cpp의 current값이 0xdddddddd로 되는 현상
#include <windows.h>							// PopNode AddNode등 노드 함수들에 인자값이 **Head 인거
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>

#define SIZE 60
#define WIDTH 1200
#define HEIGHT 900

/* 방향값 정의 */
#define RIGHT 1
#define UP 2
#define LEFT 3
#define DOWN 4

typedef struct node
{
	int type;
	void *object;
	struct node* nextNode;
} Node;

typedef struct Map
{
	struct node* nextNode;
} MapStruct;

float ConversionX(float x);
float ConversionY(float y);
GLubyte *LoadBmp(const char *path);				//비트맵이미지정보를 읽어줌
void DrawFunc(GLubyte *image, int dx, int dy);	//비트맵이미지 그려줌
void FourWayMoving(int wayValue, void *object, int *x, int *y, int type);				// 맵 배열상의 오브젝트 이동 처리 함수
Node* CreateNode(int type, void *object);		//node구조체 생성그리고 node주소 리턴
void RemoveNode(Node* node);					//node주소 해제
void AddNode(Node** Head, Node* newNode);		//노드추가
void PopNode(Node** Head, void* object);		//object값이 들어있는 노드삭제
void * SearchNode(Node* Head, int type);		//object값이 들어있는 노드의 주소값리턴

#include "player.h"
#include "enemy.h"
#include "block.h"
#include "bomb.h"
#include "fire.h"
#include "Item.h"

#endif