#pragma once									// �ذ� �ؾ��� ������
#ifndef __GAMEMANAGER_H__						// Image �����Ͱ��� ��ü�� ����
#define __GAMEMANAGER_H__						// ������, �Ʒ��� ���� ��ǳ���� ���� �ڷ���Ʈ
												// ��� Pop�� main.cpp�� current���� 0xdddddddd�� �Ǵ� ����
#include <windows.h>							// PopNode AddNode�� ��� �Լ��鿡 ���ڰ��� **Head �ΰ�
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>

#define SIZE 60
#define WIDTH 1200
#define HEIGHT 900

/* ���Ⱚ ���� */
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
GLubyte *LoadBmp(const char *path);				//��Ʈ���̹��������� �о���
void DrawFunc(GLubyte *image, int dx, int dy);	//��Ʈ���̹��� �׷���
void FourWayMoving(int wayValue, void *object, int *x, int *y, int type);				// �� �迭���� ������Ʈ �̵� ó�� �Լ�
Node* CreateNode(int type, void *object);		//node����ü �����׸��� node�ּ� ����
void RemoveNode(Node* node);					//node�ּ� ����
void AddNode(Node** Head, Node* newNode);		//����߰�
void PopNode(Node** Head, void* object);		//object���� ����ִ� ������
void * SearchNode(Node* Head, int type);		//object���� ����ִ� ����� �ּҰ�����

#include "player.h"
#include "enemy.h"
#include "block.h"
#include "bomb.h"
#include "fire.h"
#include "Item.h"

#endif