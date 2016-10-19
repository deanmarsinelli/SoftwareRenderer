/*
	Texture.cpp
	Author: Dean Marsinelli
*/

#include <assert.h>
#include <Windows.h>
#include <gdiplus.h>

#include "Texture.h"

#pragma comment( lib,"gdiplus.lib" )

void LoadTexture(const WCHAR* fileName, Texture* texture)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int pitch = 0;
	D3DCOLOR* buffer = nullptr;

	{
		Gdiplus::Bitmap bitmap(fileName);
		pitch = width = bitmap.GetWidth();
		height = bitmap.GetHeight();
		buffer = new D3DCOLOR[pitch * height];

		for (unsigned int y = 0; y < height; y++)
		{
			for (unsigned int x = 0; x < width; x++)
			{
				Gdiplus::Color c;
				bitmap.GetPixel(x, y, &c);
				int r = c.GetR();
				int g = c.GetG();
				int b = c.GetB();
				D3DCOLOR color = D3DCOLOR_XRGB(r, g, b);
				buffer[x + pitch * y] = color;
			}
		}
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	*texture = buffer;
}
