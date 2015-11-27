#include "GameManager.h"

//short type[15][20];
//void *object[15][20];
MapStruct map[15][20];


float ConversionX(float x)
{
	return (x - WIDTH / 2) / (WIDTH / 2);
}

float ConversionY(float y)
{
	return (HEIGHT / 2 - y) / (HEIGHT / 2);
}

GLubyte *LoadBmp(const char *path)
{
	HANDLE hFile;
	DWORD fileSize, dwRead;
	BITMAPFILEHEADER *fh = NULL;
	BYTE *pRaster;

	hFile = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return NULL;
	fileSize = GetFileSize(hFile, NULL);
	fh = new BITMAPFILEHEADER[fileSize];
	ReadFile(hFile, fh, fileSize, &dwRead, NULL);
	CloseHandle(hFile);

	int len = fileSize - fh->bfOffBits;
	pRaster = new GLubyte[len];
	memcpy(pRaster, (BYTE *)fh + fh->bfOffBits, len);

	free(fh);
	return pRaster;
}

void DrawFunc(GLubyte * image, int dx, int dy)
{
	int x, y;
	int count = 0;
	x = dx;
	y = dy;

	for (int pixelindex = 0; pixelindex < 10800; pixelindex += 3)
	{
		count++;
		if (image[pixelindex] + image[pixelindex + 1] + image[pixelindex + 2] != 765)
		{
			glBegin(GL_POINTS);
			{
				glColor3ub(image[pixelindex + 2], image[pixelindex + 1], image[pixelindex]);
				glVertex2f(ConversionX(x), ConversionY(y));
			}
			glEnd();
		}

		if (count == 60)
		{
			y--;
			x = dx;
			count = 0;
		}

		x++;
	}
}

///* 리스트 관련 함수 *///

/* 노드 생성 */
Node* CreateNode(int type, void *object)
{
	Node *newNode = new Node;

	newNode->type = type;
	newNode->object = object;
	newNode->nextNode = NULL;

	return newNode;
}

/* 노드 추가 */
void AddNode(Node** head, Node* newNode)
{
	if ((*head) == NULL)
		*head = newNode;

	else
	{
		Node* tail = (*head);
		while (tail->nextNode != NULL)
			tail = tail->nextNode;

		tail->nextNode = newNode;
	}
}

/* 노드 삭제 */
void PopNode(Node** head, int index)
{
	Node* prev = (*head);
	int i = 1;

	while (i != index - 1)
	{
		prev = prev->nextNode;
		i++;
	}

	Node* currentNode = prev->nextNode;

	if (currentNode->nextNode != NULL)
	{
		prev->nextNode = currentNode->nextNode;
		currentNode->nextNode = NULL;
	}

	else prev->nextNode = NULL;

	RemoveNode(currentNode);
	return;
}

/* 노드 소멸 */
void RemoveNode(Node* node)
{
	free(node);
}