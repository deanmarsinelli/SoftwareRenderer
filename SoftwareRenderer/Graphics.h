/*
	Graphics.h
	Author: Dean Marsinelli

	Interface into the graphics system. This class is supposed
	to resemble a hardware rendering system where the user
	binds resources and draws.
*/

#pragma once

#include <d3d9.h>

#include "Matrix.h"
#include "Texture.h"
#include "Triangle.h"
#include "Vertex.h"

#define _PI			3.141592654f
#define _2PI		6.283185307f
#define DegToRad(x) x * (_PI / 180)

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
	
	static Texture LoadTexture(const WCHAR* fileName);
	static Mat4x4 PerspectiveMatrixLH(FLOAT verticalFov, FLOAT aspectRatio, FLOAT nearZ, FLOAT farZ);
	static Mat4x4 LookAtLH(const Vector3F& position, const Vector3F& target, const Vector3F& upDirection);

	// input setup
	void BindVertexBuffer(VertexBuffer* buffer);
	void BindIndexBuffer(IndexBuffer* buffer);
	void BindTexture(Texture texture, int width, int height);
	void BindMatrix(Mat4x4* mat, Matrix type);
	void BindMatrices(Mat4x4* world, Mat4x4* view, Mat4x4* projection);

	// "pipeline"
	void ClearBackBuffer(D3DCOLOR clearColor);
	void ClearDepthBuffer();
	void DrawIndexed();
	void Present();

private:
	Triangle TransformTriangle(const Triangle& triangle);
	bool ClipTriangle(const Triangle& triangle);
	Triangle PerspectiveDivide(const Triangle& triangle);
	Triangle GetWindowCoordinates(const Triangle& triangle);
	void DrawWireFrame(const Triangle& triangle);
	void DrawTriangleColored(const Triangle& triangle);
	void DrawTriangleTextured(const Triangle& triangle);
	void DrawLine(float x0, float y0, const Vector4F& color0, float x1, float y1, const Vector4F& color1);
	void DrawSpansColor(const EdgeColor& e0, const EdgeColor& e1);
	void DrawSpanColor(const SpanColor& span, int y);
	void DrawSpansTexture(const EdgeTexture& e0, const EdgeTexture& e1);
	void DrawSpanTexture(const SpanTexture& span, int y);
	D3DCOLOR SampleTexture(TexCoord& texcoord);
	void DrawPixel(int x, int y, const Vector4F& color);
	void DrawPixel(int x, int y, const D3DCOLOR& color);

public:
	bool wireFrame;

private:
	int screenWidth;
	int screenHeight;
	
	D3DCOLOR* frameBuffer;
	FLOAT* depthBuffer;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	Texture texture;
	int texWidth;
	int texHeight;

	Mat4x4* worldMatrix;
	Mat4x4* viewMatrix;
	Mat4x4* projMatrix;
	Mat4x4 worldViewProj;

	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
	D3DLOCKED_RECT		backRect;
	IDirect3DSurface9*	pBackBuffer;
};
