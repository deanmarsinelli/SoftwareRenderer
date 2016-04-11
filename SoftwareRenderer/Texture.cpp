/*
	Texture.cpp
	Author: Dean Marsinelli

	Inspired by Chili @ http://www.planetchili.net/ with bitmap info
	from https://en.wikipedia.org/wiki/BMP_file_format
*/

#include <assert.h>
#include <stdio.h>

#include "Texture.h"

void LoadTexture(const char* fileName, Texture texture)
{
	FILE* bmpFile = fopen(fileName, "rb");

	char signature[2];
	fread(signature, sizeof(char), 2, bmpFile);
	assert(signature[0] == 'B' && signature[1] == 'M');

	BitmapFileHeader fileHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);

	BitmapInfoHeader infoHeader;
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);

	fseek(bmpFile, fileHeader.offsetToPixelData, SEEK_SET);

	int nPaddingBytesPerRow = (4 - ((infoHeader.width * 3) % 4)) % 4;
	for (int y = infoHeader.height - 1; y >= 0; y--)
	{
		for (int x = 0; x < infoHeader.width; x++)
		{
			Pixel24 pixel;
			fread(&pixel, sizeof(pixel), 1, bmpFile);
			texture[x + y * infoHeader.width] = D3DCOLOR_XRGB(pixel.red, pixel.green, pixel.blue);
		}
		fseek(bmpFile, nPaddingBytesPerRow, SEEK_CUR);
	}

	fclose(bmpFile);
}
