#pragma once
#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <windows.h>
#include <GL/glut.h>

#define SIZE 60
#define WIDTH 1200
#define HEIGHT 900

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
GLubyte *LoadBmp(const char *path);
void DrawFunc(GLubyte * image, int dx, int dy);
Node* CreateNode(int type, void *object);
void RemoveNode(Node* node);
void AddNode(Node** Head, Node* newNode);
void PopNode(Node** Head, void* object);
Node* SearchNode(Node* Head, void* object);


#endif