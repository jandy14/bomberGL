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
//#include "bomb.h"
//===================================================================�Լ�����
void glutInit();
void Resize(int, int);
void Dodisplay();
void Dospecial(int, int, int);
void Dokeyboard(unsigned char, int, int);
void Update(int);
GLubyte *LoadBmp(const char *path);
//===================================================================��������
player **p;
enemy **e;
block **b;
int enemymax;
int blockmax;
extern short type[15][20];
extern void * object[15][20];
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

	f.open("Info/mapinfo.txt");
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
			if (a == 12)
			{
				b[--blockcount] = new block(j, i, LoadBmp("Image/Block/Brick2.bmp"));//�ʻ�xy��ǥ
				type[i][j] = 12;
				object[i][j] = b[blockcount];
			}
			else if (a == 11)
			{
				b[--blockcount] = new block(j, i, LoadBmp("Image/Block/Brick1.bmp"));//�ʻ�xy��ǥ
				type[i][j] = 11;
				object[i][j] = b[blockcount];
			}
			else if (a == 2)
			{
				e[--enemycount] = new enemy(j, i);//�ʻ�xy��ǥ
				type[i][j] = 2;
				object[i][j] = e[enemycount];
			}
			else if (a == 1)
			{
				p[0] = new player(j, i);//�ʻ�xy��ǥ
				type[i][j] = 1;
				object[i][j] = p[0];
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
		//e[i]->Draw(blockimage[0]);
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
//	p[0]->Putbomb();
//Dospecial()�� �ٸ��� ���� ���⼱ �����̽����Է��� �޾� ��ź�� ��ġ�ϸ� �ȴ�.
//�� player.Putbomb()�� ���ָ� �ȴ�.
}
void Update(int value)
{
	glutTimerFunc(30, Update, 1);
//�� ��ü���� ��������� �ϴ� ������ ����.
//s_map����ü���� �� �ѷ����鼭 ������������ �𸣰ڴ�.
	for (int i = 0; i < enemymax && e[i] != NULL; i++)
		e[i]->Move();
	p[0]->Moving();
	for (int i = 0; i < enemymax && e[i] != NULL; i++)
		e[i]->Moving();
	for (int i = 0; i < blockmax && b[i] != NULL; i++)
		b[i]->Moving();

	glutPostRedisplay();
}
