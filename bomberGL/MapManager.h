#pragma once
#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

#include <windows.h>
#include <GL/glut.h>

#define SIZE 60
#define WIDTH 1200
#define HEIGHT 900

float ConversionX(float x);
float ConversionY(float y);
GLubyte *LoadBmp(const char *path);


#endif