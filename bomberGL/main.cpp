//===================================================================��ó��
#pragma warning(disable:4996)
#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "MapManager.h"
#include "player.h"
#include "enemy.h"
#include "block.h"
#include "bomb.h"
//===================================================================����
#define WIDTH 1200
#define HEIGHT 900
#define SIZE 60
//===================================================================�Լ�����
void glutInit();
void Resize(int, int);
void Dodisplay();
void Dospecial(int, int, int);
void Dokeyboard(unsigned char, int, int);
void Update(int);
float ConversionX(float x)
{
	return (x - WIDTH / 2) / (WIDTH / 2);
}
float ConversionY(float y)
{
	return (HEIGHT / 2 - y) / (HEIGHT / 2);
}
//===================================================================��������
/*typedef struct
{
	short type;
	void *object;
}s_map;*/
//s_map map[15][20];
MapManager map;
player **p;
enemy **e;
block **b;
int enemymax;
int blockmax;
//===================================================================����
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInit();
	glutCreateWindow("OpenGL");
	glutReshapeFunc(Resize);
	glutDisplayFunc(Dodisplay);
	glutSpecialFunc(Dospecial);
	glutKeyboardFunc(Dokeyboard);
	glutTimerFunc(10, Update, 1);
	glutMainLoop();

	return 0;
}
//===================================================================�Լ�����
void glutInit()
{
	int a;
	int blockcount = 0;
	int enemycount = 0;
	std::ifstream f;
	f.open("Map/GameInfo.txt");
//===============================================count�� ���ֱ� ���� �ݺ�����
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			f >> a;
			if (a > 10)
				blockcount++;
			else if (a == 2)
				enemycount++;
		}
	}
//===============================================count�ȸ�ŭ �������Ҵ�
	p = (player **)malloc(sizeof(player *));	//������ �ϳ��� �ѵ� �����ߴ�;
	e = (enemy **)malloc(sizeof(enemy *)*enemycount);
	b = (block **)malloc(sizeof(block *)*blockcount);
//������ �ΰ�������߿��� ��� ���� �����Ѵ�
//�ϳ��� ���� ����� �����ϴ°�
//���ϳ��� �̱������Ϳ� new�� ���ִ°�
//new�� ���� �Ǹ� �����ڸ� ������ ��� ���� �ʱ�ȭ�Լ��� ���������Ѵ�.
//��� ���� ��뤻
//===============================================���������͸� �ٽ� ó������
	f.clear();		//��������
	f.seekg(0, std::ios::beg);		//���������͸� �Ǿ�����
//===============================================������
	blockmax = blockcount;
	enemymax = enemycount;
//===============================================��ü�����׹�ġ
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			f >> a;
			if (a < 10)
			{
				b[--blockcount] = new block(j, i);//�ʻ�xy��ǥ
				map.type[i][j] = 10;
				map.object[i][j] = b[blockcount];
			}
			else if (a == 2)
			{
				e[--enemycount] = new enemy(j, i);//�ʻ�xy��ǥ
				map.type[i][j] = 2;
				map.object[i][j] = e[enemycount];
			}
			else if (a == 1)
			{
				p[0] = new player(j, i);//�ʻ�xy��ǥ
				map.type[i][j] = 1;
				map.object[i][j] = p[0];
			}
		}
	}
	f.close();
}
void Resize(int width, int height)
{
	if (width == WIDTH && height == HEIGHT)
		return;

	glutReshapeWindow(WIDTH, HEIGHT);
}
void Dodisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	p[0]->Draw();
	for (int i = 0; i < enemymax && e[i] != NULL; i++)
		e[i]->Draw();
	for (int i = 0; i < blockmax && b[i] != NULL; i++)
		b[i]->Draw();
	glutSwapBuffers();
}
void Dospecial(int key, int x, int y)
{
	p[0]->Move(key);
//	player.move();������ key������ ���⸸ �޾��ش�
}
void Dokeyboard(unsigned char value, int x, int y)
{
	p[0]->Putbomb();
//Dospecial()�� �ٸ��� ���� ���⼱ �����̽����Է��� �޾� ��ź�� ��ġ�ϸ� �ȴ�.
//�� player.Putbomb()�� ���ָ� �ȴ�.
}
void Update(int value)
{
//�� ��ü���� ��������� �ϴ� ������ ����.
//s_map����ü���� �� �ѷ����鼭 ������������ �𸣰ڴ�.
	p[0]->Moving();
	for (int i = 0; i < enemymax && e[i] != NULL; i++)
		e[i]->Moving();
	for (int i = 0; i < blockmax && b[i] != NULL; i++)
		b[i]->Moving();

	glutPostRedisplay();
	glutTimerFunc(30, Update, 1);
}