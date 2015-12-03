//===================================================================전처리
#pragma warning(disable:4996)
#include "GameManager.h"
//===================================================================함수선언
void glutInit();
void Resize(int, int);
void Dodisplay();
void Dospecial(int, int, int);
void Dokeyboard(unsigned char, int, int);
void Update(int);
void reStart();
//===================================================================변수선언
player *p;
enemy *e;
block *b;
bomb *bom;
fire *f;
Item *i;
GLubyte **gameIntro, **mainScene;
GLubyte ***playerImage, ***enemyImage, **blockImage, *bombImage, **bombexplosionimage, **bulletImage, **blockExplosionImage;;
GLubyte **playerDie, **enemyDie, **blockDestroy;
GLubyte **itemImage;
Node* current;
Node* prev = NULL;
int gameStart = 0, playerDyingCount = 0;;
bool isPlaying = false, gameOver = false;;
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
	//int blockcount = 0;
	//int enemycount = 0;
	std::ifstream f;

	/* 맵 배열 초기화 */
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 20; j++)
			map[i][j].nextNode = NULL;

	/* 할당 */
	playerImage = new GLubyte**[4];
	for (int i = 0; i < 4; i++)
		playerImage[i] = new GLubyte*[5];

	enemyImage = new GLubyte**[4];
	for (int i = 0; i < 4; i++)
		enemyImage[i] = new GLubyte*[2];

	blockImage = new GLubyte*[2];
	bombexplosionimage = new GLubyte*[7];
	playerDie = new GLubyte*[3];
	enemyDie = new GLubyte*[3];
	blockDestroy = new GLubyte*[5];
	itemImage = new GLubyte*[5];
	bulletImage = new GLubyte*[4];
	blockExplosionImage = new GLubyte*[2];
	gameIntro = new GLubyte*[29];
	mainScene = new GLubyte*[2];

	/* Intro 이미지 로드 */
	gameIntro[0] = LoadBmp("Image/Intro/Frame0.bmp");
	gameIntro[1] = LoadBmp("Image/Intro/Frame1.bmp");
	gameIntro[2] = LoadBmp("Image/Intro/Frame2.bmp");
	gameIntro[3] = LoadBmp("Image/Intro/Frame3.bmp");
	gameIntro[4] = LoadBmp("Image/Intro/Frame4.bmp");
	gameIntro[5] = LoadBmp("Image/Intro/Frame5.bmp");
	gameIntro[6] = LoadBmp("Image/Intro/Frame6.bmp");
	gameIntro[7] = LoadBmp("Image/Intro/Frame7.bmp");
	gameIntro[8] = LoadBmp("Image/Intro/Frame8.bmp");
	gameIntro[9] = LoadBmp("Image/Intro/Frame9.bmp");
	gameIntro[10] = LoadBmp("Image/Intro/Frame10.bmp");
	gameIntro[11] = LoadBmp("Image/Intro/Frame11.bmp");
	gameIntro[12] = LoadBmp("Image/Intro/Frame12.bmp");
	gameIntro[13] = LoadBmp("Image/Intro/Frame13.bmp");
	gameIntro[14] = LoadBmp("Image/Intro/Frame14.bmp");
	gameIntro[15] = LoadBmp("Image/Intro/Frame15.bmp");
	gameIntro[16] = LoadBmp("Image/Intro/Frame16.bmp");
	gameIntro[17] = LoadBmp("Image/Intro/Frame17.bmp");
	gameIntro[18] = LoadBmp("Image/Intro/Frame18.bmp");
	gameIntro[19] = LoadBmp("Image/Intro/Frame19.bmp");
	gameIntro[20] = LoadBmp("Image/Intro/Frame20.bmp");
	gameIntro[21] = LoadBmp("Image/Intro/Frame21.bmp");
	gameIntro[22] = LoadBmp("Image/Intro/Frame22.bmp");
	gameIntro[23] = LoadBmp("Image/Intro/Frame23.bmp");
	gameIntro[24] = LoadBmp("Image/Intro/Frame24.bmp");
	gameIntro[25] = LoadBmp("Image/Intro/Frame25.bmp");
	gameIntro[26] = LoadBmp("Image/Intro/Frame26.bmp");
	gameIntro[27] = LoadBmp("Image/Intro/Frame27.bmp");
	gameIntro[28] = LoadBmp("Image/Intro/Frame28.bmp");

	/* 메인화면 로드 */
	mainScene[0] = LoadBmp("Image/Main/Main1.bmp");
	mainScene[1] = LoadBmp("Image/Main/Main2.bmp");

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

	playerDie[0] = LoadBmp("Image/player/Left_1.bmp");
	playerDie[1] = LoadBmp("Image/player/Right_1.bmp");
	playerDie[2] = LoadBmp("Image/player/Up_1.bmp");

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

	/* Block Explosion 이미지 로드 */
	blockExplosionImage[0] = LoadBmp("Image/Block/Block_Fire_1.bmp");

	/* Block Break 이미지 로드 */
	blockDestroy[0] = LoadBmp("Image/Block/Break_1.bmp");
	blockDestroy[1] = LoadBmp("Image/Block/Break_2.bmp");
	blockDestroy[2] = LoadBmp("Image/Block/Break_3.bmp");
	blockDestroy[3] = LoadBmp("Image/Block/Break_4.bmp");
	blockDestroy[4] = LoadBmp("Image/Block/Break_5.bmp");

	/* Bomb 이미지 로드*/
	bombImage = LoadBmp("Image/Bomb/Bomb.bmp");
	bombexplosionimage[0] = LoadBmp("Image/Bomb/Explosion0.bmp");
	bombexplosionimage[1] = LoadBmp("Image/Bomb/Explosion1.bmp");
	bombexplosionimage[2] = LoadBmp("Image/Bomb/Explosion2.bmp");
	bombexplosionimage[3] = LoadBmp("Image/Bomb/Explosion3.bmp");
	bombexplosionimage[4] = LoadBmp("Image/Bomb/Explosion4.bmp");
	bombexplosionimage[5] = LoadBmp("Image/Bomb/Explosion5.bmp");
	bombexplosionimage[6] = LoadBmp("Image/Bomb/Explosion6.bmp");

	/* Item 이미지 로드 */
	itemImage[0] = LoadBmp("Image/Item/Item_IncreaseBombCount.bmp");
	itemImage[1] = LoadBmp("Image/Item/Item_IncreaseFireRange.bmp");
	itemImage[2] = LoadBmp("Image/Item/Item_RandomFireRange.bmp");

	/* Bullet 이미지 로드*/
	bulletImage[0] = LoadBmp("Image/Fire/BulletRight.bmp");//오른
	bulletImage[1] = LoadBmp("Image/Fire/BulletUp.bmp");//위
	bulletImage[2] = LoadBmp("Image/Fire/BulletLeft.bmp");//왼
	bulletImage[3] = LoadBmp("Image/Fire/BulletDown.bmp");//아래

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
				b = new block(j, i, blockImage[objectType % 11], blockDestroy, itemImage);
				AddNode(&(map[i][j].nextNode), CreateNode(objectType, b));
				break;
			case 13:
				b = new block(j, i, blockImage[0], blockDestroy, itemImage);
				b->setShooting();
				AddNode(&(map[i][j].nextNode), CreateNode(objectType, b));
				break;
			default:
				break;
			}
		}
	}

	f.close();
}

void reStart()
{
	/* 동적 객체 해제 */
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			prev = NULL;
			current = map[x][y].nextNode;
			while (current != NULL)
			{
				switch (current->type)
				{
				case 1:
					p = (player *)current->object;
					delete p;

					if (current->object != p)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 2:
					e = (enemy *)current->object;
					delete e;

					if (current->object != e)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 11: case 12: case 13:
					b = (block *)current->object;
					delete b;

					if (current->object != b)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 21:
					bom = (bomb *)current->object;
					delete bom;

					if (current->object != bom)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 31: case 32: case 33:
					f = (fire *)current->object;
					delete f;
					if (current->object != f)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 41: case 42: case 43:
					i = (Item *)current->object;
					delete i;

					if (current->object != i)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
				default:
					break;
				}

				prev = current;
				current = current->nextNode;
			}
		}
	}

	/* 맵 배열 초기화 */
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 20; j++)
			map[i][j].nextNode = NULL;
	gameOver = false;

	/* 객체 생성 및 배치 */
	int objectType;
	std::ifstream f;

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
				b = new block(j, i, blockImage[objectType % 11], blockDestroy, itemImage);
				AddNode(&(map[i][j].nextNode), CreateNode(objectType, b));
				break;
			case 13:
				b = new block(j, i, blockImage[0], blockDestroy, itemImage);
				b->setShooting();
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

	if (gameStart < 29)
	{
		glRasterPos2f(-1, -1);
		glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, gameIntro[gameStart]);
		Sleep(80);

		gameStart++;
	}

	else if (gameStart >= 29 && !isPlaying)
	{
		glRasterPos2f(-1, -1);
		glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, mainScene[(gameStart - 1) % 2]);
		Sleep(500);

		gameStart++;
	}

	else
	{
		for (int x = 0; x < 15; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				current = map[x][y].nextNode;
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
					case 11: case 12: case 13:
						b = (block *)current->object;
						b->Draw();
						break;
					case 21:
						bom = (bomb *)current->object;
						bom->Draw();
						break;
					case 31: case 32: case 33:
						f = (fire *)current->object;
						f->Draw();
						break;
					case 41: case 42: case 43:
						i = (Item *)current->object;
						i->Draw();
					default:
						break;
					}

					prev = current;
					current = current->nextNode;
				}
			}
		}
	}

	glutSwapBuffers();
}

void Dospecial(int key, int x, int y)
{
	if (isPlaying) p->Move(key);
	else if (!isPlaying && gameStart >= 29) isPlaying = true;
	//	player.move();식으로 key값으로 방향만 받아준다
}

void Dokeyboard(unsigned char value, int x, int y)
{
	if (isPlaying)
	{
		if (value == 32)
			p->Putbomb(bombImage, bombexplosionimage);
		else if (value == 'd')
			p->shootbullet(bulletImage[0], 1);
		else if (value == 'w')
			p->shootbullet(bulletImage[1], 2);
		else if (value == 'a')
			p->shootbullet(bulletImage[2], 3);
		else if (value == 's')
			p->shootbullet(bulletImage[3], 4);
	}

	else if (!isPlaying && gameStart >= 29) isPlaying = true;
}

void Update(int value)
{
	glutTimerFunc(30, Update, 1);
	//각 객체마다 갱신해줘야 하는 내용이 들어간다.
	//s_map구조체안을 다 둘러보면서 갱신해줄지도 모르겠다.	
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			prev = NULL;
			current = map[x][y].nextNode;
			while (current != NULL)
			{
				switch (current->type)
				{
				case 1:
					p = (player *)current->object;
					p->Die();
					p->Moving();
					playerDyingCount = p->getDyingCount();

					if (current->object != p)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
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
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 11:
					break;
				case 12:
					b = (block *)current->object;
					b->Destroy();

					if (current->object != b)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 13:
					b = (block *)current->object;
					b->Attack(blockExplosionImage);
					break;
				case 21:
					bom = (bomb *)current->object;
					bom->Countdown();
					bom->Explosion();
					if (current->object != bom)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 31: case 32: case 33:
					f = (fire *)current->object;
					f->Moving();
					if (current->object != f)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
					break;
				case 41: case 42: case 43:
					i = (Item *)current->object;
					i->Moving();

					if (current->object != i)
					{
						if (prev != NULL) current = prev->nextNode;
						else if (prev == NULL) current = map[x][y].nextNode;
						continue;
					}
				default:
					break;
				}

				prev = current;
				current = current->nextNode;
			}
		}
	}

	if (playerDyingCount == 8) gameOver = true;

	else if (gameOver)
	{
		gameStart++;
		if (gameStart >= 60)
		{
			gameStart = 29;
			isPlaying = false;
			reStart();
		}
	}

	glutPostRedisplay();
}
