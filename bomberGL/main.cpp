//===================================================================전처리
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
//===================================================================정의
#define WIDTH 1200
#define HEIGHT 900
#define SIZE 60
//===================================================================함수선언
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
//===================================================================변수선언
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
//===================================================================메인
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
//===================================================================함수정의
void glutInit()
{
	int a;
	int blockcount = 0;
	int enemycount = 0;
	std::ifstream f;
	f.open("Map/GameInfo.txt");
//===============================================count를 세주기 위한 반복구문
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
//===============================================count된만큼 데이터할당
	p = (player **)malloc(sizeof(player *));	//어차피 하나긴 한데 통일했다;
	e = (enemy **)malloc(sizeof(enemy *)*enemycount);
	b = (block **)malloc(sizeof(block *)*blockcount);
//생성에 두가지방법중에서 어떤걸 할지 골라야한다
//하나는 원래 방식을 유지하는것
//또하나는 싱글포인터에 new를 써주는것
//new를 쓰게 되면 생성자를 쓸수가 없어서 따로 초기화함수를 만들어줘야한다.
//어떤게 맘에 드노ㅋ
//===============================================파일포인터를 다시 처음으로
	f.clear();		//버퍼정리
	f.seekg(0, std::ios::beg);		//파일포인터를 맨앞으로
//===============================================값저장
	blockmax = blockcount;
	enemymax = enemycount;
//===============================================객체생성및배치
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			f >> a;
			if (a < 10)
			{
				b[--blockcount] = new block(j, i);//맵상xy좌표
				map.type[i][j] = 10;
				map.object[i][j] = b[blockcount];
			}
			else if (a == 2)
			{
				e[--enemycount] = new enemy(j, i);//맵상xy좌표
				map.type[i][j] = 2;
				map.object[i][j] = e[enemycount];
			}
			else if (a == 1)
			{
				p[0] = new player(j, i);//맵상xy좌표
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
//	player.move();식으로 key값으로 방향만 받아준다
}
void Dokeyboard(unsigned char value, int x, int y)
{
	p[0]->Putbomb();
//Dospecial()과 다를건 없다 여기선 스페이스바입력을 받아 폭탄만 설치하면 된다.
//즉 player.Putbomb()만 써주면 된다.
}
void Update(int value)
{
//각 객체마다 갱신해줘야 하는 내용이 들어간다.
//s_map구조체안을 다 둘러보면서 갱신해줄지도 모르겠다.
	p[0]->Moving();
	for (int i = 0; i < enemymax && e[i] != NULL; i++)
		e[i]->Moving();
	for (int i = 0; i < blockmax && b[i] != NULL; i++)
		b[i]->Moving();

	glutPostRedisplay();
	glutTimerFunc(30, Update, 1);
}