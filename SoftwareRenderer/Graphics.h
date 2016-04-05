#pragma once

#include <d3d9.h>

#include "Matrix.h"
#include "Texture.h"
#include "Triangle.h"
#include "Vertex.h"

enum Matrix
{
	WORLD,
	VIEW,
	PROJECTION
};

class Graphics
{
public:
	Graphics(HWND hWnd, int width, int height);
	~Graphics();
	
	Texture LoadTexture(const char* fileName, unsigned int width, unsigned int height);

	// input setup
	void BindVertexBuffer(VertexBuffer* buffer);
	void BindIndexBuffer(IndexBuffer* buffer);
	void BindTexture(Texture texture);
	void BindMatrix(Mat4x4* mat, Matrix type);
	void BindMatrices(Mat4x4* world, Mat4x4* view, Mat4x4* projection);

	// "pipeline"
	void ClearBackBuffer(D3DCOLOR clearColor);
	void ClearDepthBuffer();
	void DrawIndexed();
	void Present();

private:
	void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
	void DrawCircle(int cx, int cy, int radius, int r, int g, int b);

private:
	int screenWidth;
	int screenHeight;
	
	D3DCOLOR* frameBuffer;
	FLOAT* depthBuffer;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	Texture texture;
	
	Mat4x4* worldMatrix;
	Mat4x4* viewMatrix;
	Mat4x4* projMatrix;
	Mat4x4 worldViewProj;

	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
	D3DLOCKED_RECT		backRect;
	IDirect3DSurface9*	pBackBuffer;
};
