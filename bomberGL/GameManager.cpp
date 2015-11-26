#include "GameManager.h"

short type[15][20];
void *object[15][20];

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