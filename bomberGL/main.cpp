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
GLubyte *breakableBlock;
GLubyte *unbreakableBlock;
GLubyte *blockimage[2];
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
//===============================================�̹��� �� ���� �ε�
	unbreakableBlock = LoadBmp("Image/Block/Brick1.bmp");
	breakableBlock = LoadBmp("Image/Block/Brick2.bmp");
	blockimage[0] = LoadBmp("Image/Block/Brick1.bmp");
	blockimage[1] = LoadBmp("Image/Block/Brick2.bmp");
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
				b[--blockcount] = new block(j, i, blockimage[1]);//�ʻ�xy��ǥ
				type[i][j] = 10;
				object[i][j] = b[blockcount];
			}
			else if (a == 11)
			{
				b[--blockcount] = new block(j, i, blockimage[0]);//�ʻ�xy��ǥ
				type[i][j] = 10;
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
//	p[0]->Draw();
	for (int i = 0; i < enemymax && e[i] != NULL; i++)
		e[i]->Draw(blockimage[0]);
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
GLubyte *LoadBmp(const char *path)
{
	HANDLE hFile;
	DWORD FileSize, dwRead;
	BITMAPFILEHEADER *fh = NULL;
	BYTE *pRaster;

	hFile = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return NULL;
	FileSize = GetFileSize(hFile, NULL);
	fh = new BITMAPFILEHEADER[FileSize];
	ReadFile(hFile, fh, FileSize, &dwRead, NULL);
	CloseHandle(hFile);

	int len = FileSize - fh->bfOffBits;
	pRaster = new GLubyte[len];
	memcpy(pRaster, (BYTE *)fh + fh->bfOffBits, len);

	free(fh);
	return pRaster;
}