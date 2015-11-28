#include "GameManager.h"

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

void FourWayMoving(int wayValue, void *object, int *x, int *y, int type)
{
	switch (wayValue)
	{
	case RIGHT:
		AddNode(&(map[*y][++(*x)].nextNode), CreateNode(type, object));
		PopNode(&(map[*y][(*x) - 1].nextNode), object);
		break;
	case UP:
		AddNode(&(map[--(*y)][*x].nextNode), CreateNode(type, object));
		PopNode(&(map[(*y) + 1][*x].nextNode), object);
		break;
	case LEFT:
		AddNode(&(map[*y][--(*x)].nextNode), CreateNode(type, object));
		PopNode(&(map[*y][(*x) + 1].nextNode), object);
		break;
	case DOWN:
		AddNode(&(map[++(*y)][*x].nextNode), CreateNode(type, object));
		PopNode(&(map[(*y) - 1][*x].nextNode), object);
		break;
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
	Node* prevNode = (*Head);
	Node* currentNode = (*Head)->nextNode;
	int i = 0;

	while (currentNode != NULL)
	{
		if (i == 0 && prevNode->object == object)
		{
			i--;
			break;
		}
		if (currentNode->object == object) break;

		prevNode = currentNode;
		currentNode = currentNode->nextNode;
		i++;
	}

	/* ��尡 �������� ��� */
	if (currentNode != NULL)
	{
		/* ���� ���� ��带 ������ ��� */
		if (i == -1)
		{
			(*Head) = currentNode;
			prevNode->nextNode = NULL;
			RemoveNode(prevNode);

			return;
		}
		/* ���� ��尡 ���� �ƴҰ�� */
		if (currentNode->nextNode != NULL)
		{
			prevNode->nextNode = currentNode->nextNode;
			currentNode->nextNode = NULL;
		}

		/* ���� ��尡 ���ϰ�� */
		else prevNode->nextNode = NULL;
	}

	/* ��尡 �Ѱ����� ���*/
	else if (i == 0 && currentNode == NULL)
	{
		prevNode->type = 0;
		prevNode->object = NULL;
		prevNode->nextNode = NULL;

		return;	
	}

	RemoveNode(currentNode);
	return;
}

/* ��� Ž�� */
bool SearchNode(Node* head, int type)
{
	Node* current = head;

	while (current != NULL)
	{
		if (current->type == type) return true;
		current = current->nextNode;
	}

	return false;
}


/* ��� �Ҹ� */
void RemoveNode(Node* node)
{
	free(node);
}