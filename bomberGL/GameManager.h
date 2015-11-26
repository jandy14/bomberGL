#pragma once
#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <windows.h>
#include <GL/glut.h>

#define SIZE 60
#define WIDTH 1200
#define HEIGHT 900

float ConversionX(float x);
float ConversionY(float y);
GLubyte *LoadBmp(const char *path);
void DrawFunc(GLubyte * image, int dx, int dy);


#endif