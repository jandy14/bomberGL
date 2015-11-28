//===================================================================전처리
#pragma warning(disable:4996)
#include "GameManager.h"
#include "player.h"
#include "enemy.h"
#include "block.h"
#include "bomb.h"
//===================================================================함수선언
void glutInit();
void Resize(int, int);
void Dodisplay();
void Dospecial(int, int, int);
void Dokeyboard(unsigned char, int, int);
void Update(int);
GLubyte *LoadBmp(const char *path);
//===================================================================변수선언
player *p;
enemy *e;
block *b;
bomb *bom;
GLubyte *playerImage[4][5], *enemyImage[4][2], *blockImage[2], *bombImage, *bombexplosionimage[7];
GLubyte *playerDie[3], *enemyDie[3];
Node* current;
Node* prev = NULL;
extern MapStruct map[15][20];
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
	int objectType;
	int blockcount = 0;
	int enemycount = 0;
	std::ifstream f;

	/* 맵 배열 초기화 */
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 20; j++)
			map[i][j].nextNode = NULL;

	/* Player 이미지 로드 */
	playerImage[0][0] = LoadBmp("Image/player/Right_1.bmp");
	playerImage[0][1] = LoadBmp("Image/player/Right_2.bmp");
	playerImage[0][2] = LoadBmp("Image/player/Right_3.bmp");
	playerImage[0][3] = LoadBmp("Image/player/Right_4.bmp");
	playerImage[0][4] = LoadBmp("Image/player/Right_5.bmp");

	playerImage[1][0] = LoadBmp("Image/player/Left_1.bmp");
	playerImage[1][1] = LoadBmp("Image/player/Left_2.bmp");
	playerImage[1][2] = LoadBmp("Image/player/Left_3.bmp");
	playerImage[1][3] = LoadBmp("Image/player/Left_4.bmp");
	playerImage[1][4] = LoadBmp("Image/player/Left_5.bmp");

	playerImage[2][0] = LoadBmp("Image/player/Up_1.bmp");
	playerImage[2][1] = LoadBmp("Image/player/Up_2.bmp");
	playerImage[2][2] = LoadBmp("Image/player/Up_3.bmp");
	playerImage[2][3] = LoadBmp("Image/player/Up_4.bmp");
	playerImage[2][4] = LoadBmp("Image/player/Up_5.bmp");

	playerImage[3][0] = LoadBmp("Image/player/Down_1.bmp");
	playerImage[3][1] = LoadBmp("Image/player/Down_2.bmp");
	playerImage[3][2] = LoadBmp("Image/player/Down_3.bmp");
	playerImage[3][3] = LoadBmp("Image/player/Down_4.bmp");
	playerImage[3][4] = LoadBmp("Image/player/Down_5.bmp");

	/* Enemy 이미지 로드 */
	enemyImage[0][0] = LoadBmp("Image/Enemy/Right_1.bmp");
	enemyImage[0][1] = LoadBmp("Image/Enemy/Right_2.bmp");

	enemyImage[1][0] = LoadBmp("Image/Enemy/Up_1.bmp");
	enemyImage[1][1] = LoadBmp("Image/Enemy/Up_2.bmp");

	enemyImage[2][0] = LoadBmp("Image/Enemy/Left_1.bmp");
	enemyImage[2][1] = LoadBmp("Image/Enemy/Left_2.bmp");

	enemyImage[3][0] = LoadBmp("Image/Enemy/Down_1.bmp");
	enemyImage[3][1] = LoadBmp("Image/Enemy/Down_2.bmp");

	/* Enemy Die 이미지 로드 */
	enemyDie[0] = LoadBmp("Image/Enemy/Die_1.bmp");
	enemyDie[1] = LoadBmp("Image/Enemy/Die_2.bmp");
	enemyDie[2] = LoadBmp("Image/Enemy/Die_3.bmp");

	/* Block 이미지 로드 */
	blockImage[0] = LoadBmp("Image/Block/Brick1.bmp");
	blockImage[1] = LoadBmp("Image/Block/Brick2.bmp");

	/* Bomb 이미지 로드*/
	bombImage = LoadBmp("Image/Bomb/Bomb.bmp");
	bombexplosionimage[0] = LoadBmp("Image/Bomb/Explosion0.bmp");
	bombexplosionimage[1] = LoadBmp("Image/Bomb/Explosion1.bmp");
	bombexplosionimage[2] = LoadBmp("Image/Bomb/Explosion2.bmp");
	bombexplosionimage[3] = LoadBmp("Image/Bomb/Explosion3.bmp");
	bombexplosionimage[4] = LoadBmp("Image/Bomb/Explosion4.bmp");
	bombexplosionimage[5] = LoadBmp("Image/Bomb/Explosion5.bmp");
	bombexplosionimage[6] = LoadBmp("Image/Bomb/Explosion6.bmp");

	/* 객체 생성 및 배치 */
	f.open("Info/mapinfo.txt");

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			f >> objectType;

			switch (objectType)
			{
			case 0:
				AddNode(&(map[i][j].nextNode), CreateNode(objectType, NULL));
				break;
			case 1:
				p = new player(j, i, playerImage, playerDie);//맵상xy좌표
				AddNode(&(map[i][j].nextNode), CreateNode(objectType, p));
				break;
			case 2:
				e = new enemy(j, i, enemyImage, enemyDie);
				AddNode(&(map[i][j].nextNode), CreateNode(objectType, e));
				break;
			case 11: case 12:
				b = new block(j, i, blockImage[objectType % 11]);
				AddNode(&(map[i][j].nextNode), CreateNode(objectType, b));
				break;
			default:
				break;
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

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			current = map[i][j].nextNode;
			while (current != NULL)
			{
				switch (current->type)
				{
				case 1:
					p = (player *)current->object;
					p->Draw();
					break;
				case 2:
					e = (enemy *)current->object;
					e->Draw();
					break;
				case 11: case 12:
					b = (block *)current->object;
					b->Draw();
					break;
				case 21:
					bom = (bomb *)current->object;
					bom->Draw();
					break;
				default:
					break;
				}

				prev = current;
				current = current->nextNode;
			}
		}
	}
	glutSwapBuffers();
}

void Dospecial(int key, int x, int y)
{
	p->Move(key);
//	player.move();식으로 key값으로 방향만 받아준다
}

void Dokeyboard(unsigned char value, int x, int y)
{
	if (value == 32)
		p->Putbomb(bombImage, bombexplosionimage);
}

void Update(int value)
{
	glutTimerFunc(30, Update, 1);
	//각 객체마다 갱신해줘야 하는 내용이 들어간다.
	//s_map구조체안을 다 둘러보면서 갱신해줄지도 모르겠다.	
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			current = map[i][j].nextNode;
			while (current != NULL)
			{
				switch (current->type)
				{
				case 1:
					p = (player *)current->object;
					p->Moving();

					if (current->object != p)
					{
						current = prev->nextNode;
						continue;
					}
					break;
				case 2:
					e = (enemy *)current->object;
					e->Die();
					e->Move();
					e->Moving();

					if (current->object != e)
					{
						current = prev->nextNode;
						continue;
					}
					break;
				case 11: case 12:
					break;
				case 21:
					bom = (bomb *)current->object;
					bom->Countdown();
					bom->Explosion();
					if (current->object != bom)
					{
						current = prev->nextNode;
						continue;
					}
					break;
				default:
					break;
				}

				prev = current;
				current = current->nextNode;
			}
		}
	}

	glutPostRedisplay();
}
