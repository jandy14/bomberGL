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

///* ����Ʈ ���� �Լ� *///

/* ��� ���� */
Node* CreateNode(int type, void *object)
{
	Node *newNode = new Node;

	newNode->type = type;
	newNode->object = object;
	newNode->nextNode = NULL;

	return newNode;
}

/* ��� �߰� */
void AddNode(Node** Head, Node* newNode)
{
	if ((*Head) == NULL)
		*Head = newNode;

	else
	{
		Node* tail = (*Head);

		if (tail->type == 0)
		{
			tail->type = newNode->type;
			tail->object = newNode->object;
			tail->nextNode = NULL;

			return;
		}

		while (tail->nextNode != NULL)
			tail = tail->nextNode;

		tail->nextNode = newNode;

		return;
	}
}

/* ��� ���� */
void PopNode(Node** Head, void* object)
{
	Node* prev = (*Head);
	int i = 0;

	while (prev->nextNode != NULL)
	{
		i++;
		if (prev->object == object) break;
		prev = prev->nextNode;
	}

	Node* currentNode = prev->nextNode;

	/* ���� ��尡 ���� �ƴҰ�� */
	if (prev->nextNode != NULL && currentNode->nextNode != NULL)
	{
		prev->nextNode = currentNode->nextNode;	
		prev->nextNode->nextNode = NULL;
	}

	/* ��尡 �Ѱ����� ���*/
	else if (i == 0 && prev->nextNode == NULL)
	{
		prev->type = 0;
		prev->object = NULL;

		return;	
	}
	/* ���� ��尡 ���� ���� ��� */
	else prev->nextNode = NULL;

	RemoveNode(currentNode);
	return;
}

/* ��� Ž�� */
Node* SearchNode(Node* head, void* object)
{
	Node* current = head;

	while (current != NULL)
	{
		if (current->object == object) return current;
		current = current->nextNode;
	}
}


/* ��� �Ҹ� */
void RemoveNode(Node* node)
{
	free(node);
}