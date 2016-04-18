/*
	Graphics.cpp
	Author: Dean Marsinelli

	View and Projection matrix methods inspired by Microsoft's non-sse
	implementations for view and project matrices in xnamath.

	Triangle Rasterization influenced by the implementation at:
	http://joshbeam.com/articles/triangle_rasterization/
*/

#include <assert.h>

#include "Graphics.h"

#pragma comment(lib, "d3d9.lib")

static void ScalarSinCos(FLOAT& sin, FLOAT& cos, FLOAT value)
{
	FLOAT		ValueMod;
	FLOAT		ValueSq;
	Vector4F	V0123, V0246, V1357, V8101214, V9111315, V16182022, V17192123;
	Vector4F	V1, V2, V6, V8;
	FLOAT		S0, S1, S2, C0, C1, C2;

	float angle = value;
	angle = angle + _PI;
	ValueMod = fabsf(angle);
	ValueMod = ValueMod - (_2PI * (FLOAT)((INT)(ValueMod / _2PI)));
	ValueMod = ValueMod - _PI;
	if (angle < 0.0f)
	{
		ValueMod = -ValueMod;
	}

	ValueSq = ValueMod * ValueMod;

	V0123 = { 1.0f, ValueMod, ValueSq, ValueSq * ValueMod };
	V1 = { V0123.y, V0123.y, V0123.y, V0123.y };
	V2 = { V0123.z, V0123.z, V0123.z, V0123.z };

	V0246 = V0123 * V0123;
	V1357 = V0246 * V1;

	V6 = { V0246.w, V0246.w, V0246.w, V0246.w };
	V8 = V6 * V2;

	V8101214 = V0246 * V8;
	V9111315 = V1357 * V8;
	V16182022 = V8101214 * V8;
	V17192123 = V9111315 * V8;

	C0 = V0246.DotProduct({ 1.0f, -0.5f, 4.166666667e-2f, -1.388888889e-3f });
	S0 = V1357.DotProduct({ 1.0f, -0.166666667f, 8.333333333e-3f, -1.984126984e-4f });
	C1 = V8101214.DotProduct({ 2.480158730e-5f, -2.755731922e-7f, 2.087675699e-9f, -1.147074560e-11f });
	S1 = V9111315.DotProduct({ 2.755731922e-6f, -2.505210839e-8f, 1.605904384e-10f, -7.647163732e-13f });
	C2 = V16182022.DotProduct({ 4.779477332e-14f, -1.561920697e-16f, 4.110317623e-19f, -8.896791392e-22f });
	S2 = V17192123.DotProduct({ 2.811457254e-15f, -8.220635247e-18f, 1.957294106e-20f, -3.868170171e-23f });

	cos = C0 + C1 + C2;
	sin = S0 + S1 + S2;
}

Graphics::Graphics(HWND hWnd, int width, int height) :
	screenWidth(width), 
	screenHeight(height),
	frameBuffer(nullptr),
	depthBuffer(nullptr),
	texture(nullptr),
	pDirect3D(nullptr),
	pDevice(nullptr),
	pBackBuffer(nullptr),
	wireFrame(false)
{
	HRESULT result;

	backRect.pBits = NULL;

	pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	assert(pDirect3D != NULL);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	result = pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &pDevice);
	assert(!FAILED(result));

	result = pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	assert(!FAILED(result));

	frameBuffer = new D3DCOLOR[screenWidth * screenHeight];
	depthBuffer = new FLOAT[screenWidth * screenHeight];
}

Graphics::~Graphics()
{
	if (pDevice)
	{
		pDevice->Release();
		pDevice = nullptr;
	}

	if (pDirect3D)
	{
		pDirect3D->Release();
		pDirect3D = nullptr;
	}

	if (pBackBuffer)
	{
		pBackBuffer->Release();
		pBackBuffer = nullptr;
	}

	if (frameBuffer)
	{
		delete frameBuffer;
		frameBuffer = nullptr;
	}

	if (depthBuffer)
	{
		delete depthBuffer;
		depthBuffer = nullptr;
	}
}

Texture Graphics::LoadTexture(const WCHAR* fileName)
{
	Texture tex = nullptr;
	::LoadTexture(fileName, &tex);

	return tex;
}

Mat4x4 Graphics::PerspectiveMatrixLH(FLOAT verticalFov, FLOAT aspectRatio, FLOAT nearZ, FLOAT farZ)
{
	FLOAT sinFov;
	FLOAT cosFov;
	FLOAT height;
	FLOAT width;

	ScalarSinCos(sinFov, cosFov, 0.5f * verticalFov);

	height = cosFov / sinFov;
	width = height / aspectRatio;

	Mat4x4 output;
	output.m[0][0] = width;
	output.m[0][1] = 0.0f;
	output.m[0][2] = 0.0f;
	output.m[0][3] = 0.0f;

	output.m[1][0] = 0.0f;
	output.m[1][1] = height;
	output.m[1][2] = 0.0f;
	output.m[1][3] = 0.0f;
	
	output.m[2][0] = 0.0f;
	output.m[2][1] = 0.0f;
	output.m[2][2] = farZ / (farZ - nearZ);
	output.m[2][3] = 1.0f;

	output.m[3][0] = 0.0f;
	output.m[3][1] = 0.0f;
	output.m[3][2] = -output.m[2][2] * nearZ;
	output.m[3][3] = 0.0f;

	return output;
}

Mat4x4 Graphics::LookAtLH(const Vector3F& position, const Vector3F& target, const Vector3F& upDirection)
{
	Vector3F eyeDirection = target - position;
	Vector3F NegEyePosition;
	FLOAT D0, D1, D2;
	Vector3F R0, R1, R2;
	Mat4x4 M;

	R2 = eyeDirection.Normalize();
	R0 = upDirection.CrossProduct(R2);
	R0 = R0.Normalize();
	R1 = R2.CrossProduct(R0);

	NegEyePosition = position.Negate();

	D0 = R0.DotProduct(NegEyePosition);
	D1 = R1.DotProduct(NegEyePosition);
	D2 = R2.DotProduct(NegEyePosition);

	unsigned int temp;

	// The following code was inspired by Microsoft's XMVectorSelect() function in xnamathvector.inl
	// using their non-sse version
	// row 1
	temp = (reinterpret_cast<unsigned int&>(D0) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R0.x) & 0xFFFFFFFF);
	M.m[0][0] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D0) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R0.y) & 0xFFFFFFFF);
	M.m[0][1] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D0) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R0.z) & 0xFFFFFFFF);
	M.m[0][2] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D0) & ~0x00000000) | (0U & 0x00000000);
	M.m[0][3] = reinterpret_cast<float&>(temp);

	// row 2
	temp = (reinterpret_cast<unsigned int&>(D1) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R1.x) & 0xFFFFFFFF);
	M.m[1][0] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D1) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R1.y) & 0xFFFFFFFF);
	M.m[1][1] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D1) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R1.z) & 0xFFFFFFFF);
	M.m[1][2] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D1) & ~0x00000000) | (0U & 0x00000000);
	M.m[1][3] = reinterpret_cast<float&>(temp);

	// row 3
	temp = (reinterpret_cast<unsigned int&>(D2) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R2.x) & 0xFFFFFFFF);
	M.m[2][0] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D2) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R2.y) & 0xFFFFFFFF);
	M.m[2][1] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D2) & ~0xFFFFFFFF) | (reinterpret_cast<unsigned int&>(R2.z) & 0xFFFFFFFF);
	M.m[2][2] = reinterpret_cast<float&>(temp);
	temp = (reinterpret_cast<unsigned int&>(D2) & ~0x00000000) | (0U & 0x00000000);
	M.m[2][3] = reinterpret_cast<float&>(temp);

	// row 4
	M.m[3][0] = 0.0f;
	M.m[3][1] = 0.0f;
	M.m[3][2] = 0.0f;
	M.m[3][3] = 1.0f;

	M = M.Transpose();

	return M;
}

void Graphics::BindVertexBuffer(VertexBuffer* buffer)
{
	vertexBuffer = buffer;
}

void Graphics::BindIndexBuffer(IndexBuffer* buffer)
{
	indexBuffer = buffer;
}

void Graphics::BindTexture(Texture _texture, int width, int height)
{
	texture = _texture;
	texWidth = width;
	texHeight = height;
}

void Graphics::BindMatrix(Mat4x4* mat, Matrix type)
{
	switch (type)
	{
	case WORLD:
		worldMatrix = mat;
		break;
	case VIEW:
		viewMatrix = mat;
		break;

	case PROJECTION:
		projMatrix = mat;
		break;
	}
}

void Graphics::BindMatrices(Mat4x4* world, Mat4x4* view, Mat4x4* projection)
{
	worldMatrix = world;
	viewMatrix = view;
	projMatrix = projection;
}

void Graphics::ClearBackBuffer(D3DCOLOR clearColor)
{
	for (int i = 0; i < screenWidth * screenHeight; i++)
	{
		frameBuffer[i] = clearColor;
	}
}

void Graphics::ClearDepthBuffer()
{
	for (int i = 0; i < screenWidth * screenHeight; i++)
	{
		depthBuffer[i] = FLT_MAX;
	}
}

void Graphics::DrawIndexed()
{
	// index buffer must be multiple of 3
	assert(indexBuffer->size() % 3 == 0);

	Index triangleIndex = 0;
	worldViewProj = (*worldMatrix) * (*viewMatrix) * (*projMatrix);

	while (triangleIndex < indexBuffer->size())
	{
		Vector2F point;

		// "vertex shader"
		// get triangle
		Triangle tri;
		tri.p0 = (*vertexBuffer)[(*indexBuffer)[triangleIndex]];
		tri.p1 = (*vertexBuffer)[(*indexBuffer)[triangleIndex + 1]];
		tri.p2 = (*vertexBuffer)[(*indexBuffer)[triangleIndex + 2]];

		// convert vertices from local space to homogeneous clip space
		tri = TransformTriangle(tri);

		// clipping
		if (ClipTriangle(tri))
		{
			triangleIndex += 3;
			continue;
		}

		// perspective divide to NDC with 0,0 at the center of the screen
		tri = PerspectiveDivide(tri);

		// convert to window coordinates
		tri = GetWindowCoordinates(tri);

		// if wireframe mode is on
		if (wireFrame)
		{
			DrawWireFrame(tri);
			triangleIndex += 3;
			continue;
		}

		// if no texture, draw the triangle with color
		if (texture == nullptr)
		{
			DrawTriangleColored(tri);
			triangleIndex += 3;
			continue;
		}
		else
		{
			DrawTriangleTextured(tri);
			triangleIndex += 3;
			continue;
		}
	}
}

void Graphics::Present()
{
	HRESULT result;

	result = pBackBuffer->LockRect(&backRect, NULL, NULL);
	assert(!FAILED(result));

	for (int y = 0; y < screenHeight; y++)
	{
		memcpy(&((BYTE*)backRect.pBits)[backRect.Pitch * y], &frameBuffer[screenWidth * y], sizeof(D3DCOLOR)* screenWidth);
	}

	result = pBackBuffer->UnlockRect();
	assert(!FAILED(result));

	result = pDevice->Present(NULL, NULL, NULL, NULL);
	assert(!FAILED(result));
}

Triangle Graphics::TransformTriangle(const Triangle& triangle)
{
	Triangle tri;
	tri.p0.position = triangle.p0.position * worldViewProj;
	tri.p1.position = triangle.p1.position * worldViewProj;
	tri.p2.position = triangle.p2.position * worldViewProj;

	tri.p0.color = triangle.p0.color;
	tri.p1.color = triangle.p1.color;
	tri.p2.color = triangle.p2.color;
	tri.p0.texCoord = triangle.p0.texCoord;
	tri.p1.texCoord = triangle.p1.texCoord;
	tri.p2.texCoord = triangle.p2.texCoord;

	return tri;
}

bool Graphics::ClipTriangle(const Triangle& triangle)
{
	if ((abs(triangle.p0.position.x) > abs(triangle.p0.position.w) ||
		abs(triangle.p0.position.y) > abs(triangle.p0.position.w) ||
		abs(triangle.p0.position.z) > abs(triangle.p0.position.w)) &&
		(abs(triangle.p1.position.x) > abs(triangle.p1.position.w) ||
		abs(triangle.p1.position.y) > abs(triangle.p1.position.w) ||
		abs(triangle.p1.position.z) > abs(triangle.p1.position.w)) &&
		(abs(triangle.p2.position.x) > abs(triangle.p2.position.w) ||
		abs(triangle.p2.position.y) > abs(triangle.p2.position.w) ||
		abs(triangle.p2.position.z) > abs(triangle.p2.position.w)))
	{
		return true;
	}

	return false;
}

Triangle Graphics::PerspectiveDivide(const Triangle& triangle)
{
	Triangle tri;
	tri.p0.position.x = triangle.p0.position.x / triangle.p0.position.w;
	tri.p0.position.y = triangle.p0.position.y / triangle.p0.position.w;
	tri.p0.position.z = triangle.p0.position.z / triangle.p0.position.w;
	tri.p1.position.x = triangle.p1.position.x / triangle.p1.position.w;
	tri.p1.position.y = triangle.p1.position.y / triangle.p1.position.w;
	tri.p1.position.z = triangle.p1.position.z / triangle.p1.position.w;
	tri.p2.position.x = triangle.p2.position.x / triangle.p2.position.w;
	tri.p2.position.y = triangle.p2.position.y / triangle.p2.position.w;
	tri.p2.position.z = triangle.p2.position.z / triangle.p2.position.w;

	tri.p0.color = triangle.p0.color;
	tri.p1.color = triangle.p1.color;
	tri.p2.color = triangle.p2.color;
	tri.p0.texCoord = triangle.p0.texCoord;
	tri.p1.texCoord = triangle.p1.texCoord;
	tri.p2.texCoord = triangle.p2.texCoord;

	return tri;
}

Triangle Graphics::GetWindowCoordinates(const Triangle& triangle)
{
	Triangle tri;
	tri.p0.position.x = ((screenWidth / 2) * triangle.p0.position.x) + (0 + (screenWidth / 2));
	tri.p0.position.y = screenHeight - (((screenHeight / 2) * triangle.p0.position.y) + (0 + (screenHeight / 2)));
	tri.p0.position.z = triangle.p0.position.z;
	tri.p1.position.x = ((screenWidth / 2) * triangle.p1.position.x) + (0 + (screenWidth / 2));
	tri.p1.position.y = screenHeight - (((screenHeight / 2) * triangle.p1.position.y) + (0 + (screenHeight / 2)));
	tri.p1.position.z = triangle.p1.position.z;
	tri.p2.position.x = ((screenWidth / 2) * triangle.p2.position.x) + (0 + (screenWidth / 2));
	tri.p2.position.y = screenHeight - (((screenHeight / 2) * triangle.p2.position.y) + (0 + (screenHeight / 2)));
	tri.p2.position.z = triangle.p2.position.z;

	tri.p0.color = triangle.p0.color;
	tri.p1.color = triangle.p1.color;
	tri.p2.color = triangle.p2.color;
	tri.p0.texCoord = triangle.p0.texCoord;
	tri.p1.texCoord = triangle.p1.texCoord;
	tri.p2.texCoord = triangle.p2.texCoord;

	return tri;
}

void Graphics::DrawWireFrame(const Triangle& triangle)
{
	DrawLine(triangle.p0.position.x, triangle.p0.position.y, triangle.p0.color, triangle.p1.position.x, triangle.p1.position.y, triangle.p1.color);
	DrawLine(triangle.p1.position.x, triangle.p1.position.y, triangle.p1.color, triangle.p2.position.x, triangle.p2.position.y, triangle.p2.color);
	DrawLine(triangle.p2.position.x, triangle.p2.position.y, triangle.p2.color, triangle.p0.position.x, triangle.p0.position.y, triangle.p0.color);
}

void Graphics::DrawTriangleColored(const Triangle& triangle)
{
	EdgeColor edges[3] =
	{
		EdgeColor((int)triangle.p0.position.x, (int)triangle.p0.position.y, triangle.p0.position.z, triangle.p0.color, (int)triangle.p1.position.x, (int)triangle.p1.position.y, triangle.p1.position.z, triangle.p1.color),
		EdgeColor((int)triangle.p1.position.x, (int)triangle.p1.position.y, triangle.p1.position.z, triangle.p1.color, (int)triangle.p2.position.x, (int)triangle.p2.position.y, triangle.p2.position.z, triangle.p2.color),
		EdgeColor((int)triangle.p2.position.x, (int)triangle.p2.position.y, triangle.p2.position.z, triangle.p2.color, (int)triangle.p0.position.x, (int)triangle.p0.position.y, triangle.p0.position.z, triangle.p0.color)
	};

	int maxLength = 0;
	int longEdge = 0;

	// find edge with the greatest length in the y axis
	for (int i = 0; i < 3; i++)
	{
		int length = edges[i].y1 - edges[i].y0;
		if (length > maxLength)
		{
			maxLength = length;
			longEdge = i;
		}
	}

	int shortEdge0 = (longEdge + 1) % 3;
	int shortEdge1 = (longEdge + 2) % 3;

	DrawSpansColor(edges[longEdge], edges[shortEdge0]);
	DrawSpansColor(edges[longEdge], edges[shortEdge1]);
}

void Graphics::DrawTriangleTextured(const Triangle& triangle)
{
	EdgeTexture edges[3] =
	{
		EdgeTexture((int)triangle.p0.position.x, (int)triangle.p0.position.y, triangle.p0.position.z, triangle.p0.texCoord, (int)triangle.p1.position.x, (int)triangle.p1.position.y, triangle.p1.position.z, triangle.p1.texCoord),
		EdgeTexture((int)triangle.p1.position.x, (int)triangle.p1.position.y, triangle.p1.position.z, triangle.p1.texCoord, (int)triangle.p2.position.x, (int)triangle.p2.position.y, triangle.p2.position.z, triangle.p2.texCoord),
		EdgeTexture((int)triangle.p2.position.x, (int)triangle.p2.position.y, triangle.p2.position.z, triangle.p2.texCoord, (int)triangle.p0.position.x, (int)triangle.p0.position.y, triangle.p0.position.z, triangle.p0.texCoord)
	};

	int maxLength = 0;
	int longEdge = 0;

	// find edge with the greatest length in the y axis
	for (int i = 0; i < 3; i++)
	{
		int length = edges[i].y1 - edges[i].y0;
		if (length > maxLength)
		{
			maxLength = length;
			longEdge = i;
		}
	}

	int shortEdge0 = (longEdge + 1) % 3;
	int shortEdge1 = (longEdge + 2) % 3;

	DrawSpansTexture(edges[longEdge], edges[shortEdge0]);
	DrawSpansTexture(edges[longEdge], edges[shortEdge1]);
}

void Graphics::DrawLine(float x0, float y0, const Vector4F& color0, float x1, float y1, const Vector4F& color1)
{
	float dx = (x1 - x0);
	float dy = (y1 - y0);

	if (dx == 0.0f && dy == 0.0f) 
	{
		DrawPixel((int)x0, (int)y0, color0);
		return;
	}

	if (fabs(dx) > fabs(dy))
	{
		float xmin, xmax;

		if (x0 < x1) 
		{
			xmin = x0;
			xmax = x1;
		}
		else 
		{
			xmin = x1;
			xmax = x0;
		}

		float slope = dy / dx;
		for (float x = xmin; x <= xmax; x += 1.0f) 
		{
			float y = y0 + ((x - x0) * slope);
			Vector4F color = color0 + ((color1 - color0) * ((x - x0) / dx));
			DrawPixel((int)x, (int)y, color);
		}
	}
	else 
	{
		float ymin, ymax;

		if (y0 < y1) 
		{
			ymin = y0;
			ymax = y1;
		}
		else 
		{
			ymin = y1;
			ymax = y0;
		}

		float slope = dx / dy;
		for (float y = ymin; y <= ymax; y += 1.0f) 
		{
			float x = x0 + ((y - y0) * slope);
			Vector4F color = color0 + ((color1 - color0) * ((y - y0) / dy));
			DrawPixel((int)x, (int)y, color);
		}
	}
}

void Graphics::DrawSpansColor(const EdgeColor& e0, const EdgeColor& e1)
{
	// if the y difference of either edge is 0, there are no spans to draw
	float e0_dy = (float)(e0.y1 - e0.y0);
	if (e0_dy == 0.0f)
		return;

	float e1_dy = (float)(e1.y1 - e1.y0);
	if (e1_dy == 0.0f)
		return;

	// calculate differences of x position and colors
	float e0_dx = (float)(e0.x1 - e0.x0);
	float e1_dx = (float)(e1.x1 - e1.x0);
	float e0_dz = (float)(e0.z1 - e0.z0);
	float e1_dz = (float)(e1.z1 - e1.z0);
	Vector4F e0_dcolor = (e0.color1 - e0.color0);
	Vector4F e1_dcolor = (e1.color1 - e1.color0);

	// calculate interpolation and step factors
	float factor0 = (float)(e1.y0 - e0.y0) / e0_dy;
	float factorStep0 = 1.0f / e0_dy;
	float factor1 = 0.0f;
	float factorStep1 = 1.0f / e1_dy;

	// loop through each row between edges and draw
	for (int y = e1.y0; y < e1.y1; y++)
	{
		// create and draw span
		SpanColor span(e0.x0 + (int)(e0_dx * factor0), e0.z0 + (e0_dz * factor0), e0.color0 + (e0_dcolor * factor0),
			e1.x0 + (int)(e1_dx * factor1), e1.z0 + (e1_dz * factor1), e1.color0 + (e1_dcolor * factor1));

		DrawSpanColor(span, y);

		// increase factors
		factor0 += factorStep0;
		factor1 += factorStep1;
	}
}

void Graphics::DrawSpanColor(const SpanColor& span, int y)
{
	int dx = span.x1 - span.x0;
	float dz = span.z1 - span.z0;
	if (dx == 0)
		return;

	Vector4F dcolor = span.color1 - span.color0;
	float factor = 0.0f;
	float factorStep = 1.0f / (float)dx;

	float depth = span.z0;
	float depthStep;
	if (dz != 0.0f)
		depthStep = dz / dx;
	else
		depthStep = 0.0f;

	// draw each pixel in the row
	for (int x = span.x0; x < span.x1; x++)
	{
		if (x >= 0 && y >= 0 && x < screenWidth && y < screenHeight)
		{
			float currentDepth = depthBuffer[x + screenWidth * y];
			if (depth < currentDepth)
			{
				depthBuffer[x + screenWidth * y] = depth;
				DrawPixel(x, y, span.color0 + (dcolor * factor));
			}
		}

		depth += depthStep;
		factor += factorStep;
	}
}

void Graphics::DrawSpansTexture(const EdgeTexture& e0, const EdgeTexture& e1)
{
		// if the y difference of either edge is 0, there are no spans to draw
	float e0_dy = (float)(e0.y1 - e0.y0);
	if (e0_dy == 0.0f)
		return;

	float e1_dy = (float)(e1.y1 - e1.y0);
	if (e1_dy == 0.0f)
		return;

	// calculate differences of x position and colors
	float e0_dx = (float)(e0.x1 - e0.x0);
	float e1_dx = (float)(e1.x1 - e1.x0);
	float e0_dz = (float)(e0.z1 - e0.z0);
	float e1_dz = (float)(e1.z1 - e1.z0);
	TexCoord e0_dtexcoord = (e0.texCoord1 - e0.texCoord0);
	TexCoord e1_dtexcoord = (e1.texCoord1 - e1.texCoord0);

	// calculate interpolation and step factors
	float factor0 = (float)(e1.y0 - e0.y0) / e0_dy;
	float factorStep0 = 1.0f / e0_dy;
	float factor1 = 0.0f;
	float factorStep1 = 1.0f / e1_dy;

	// loop through each row between edges and draw
	for (int y = e1.y0; y < e1.y1; y++)
	{
		// create and draw span
		SpanTexture span(e0.x0 + (int)(e0_dx * factor0), e0.z0 + (e0_dz * factor0), e0.texCoord0 + (e0_dtexcoord * factor0),
			e1.x0 + (int)(e1_dx * factor1), e1.z0 + (e1_dz * factor1), e1.texCoord0 + (e1_dtexcoord * factor1));

		DrawSpanTexture(span, y);

		// increase factors
		factor0 += factorStep0;
		factor1 += factorStep1;
	}
}

void Graphics::DrawSpanTexture(const SpanTexture& span, int y)
{
	int dx = span.x1 - span.x0;
	float dz = span.z1 - span.z0;
	if (dx == 0)
		return;

	TexCoord dtexcord = span.texCoord1 - span.texCoord0;
	float factor = 0.0f;
	float factorStep = 1.0f / (float)dx;

	float depth = span.z0;
	float depthStep;
	if (dz != 0.0f)
		depthStep = dz / dx;
	else
		depthStep = 0.0f;

	// draw each pixel in the row
	for (int x = span.x0; x < span.x1; x++)
	{
		if (x >= 0 && y >= 0 && x < screenWidth && y < screenHeight)
		{
			float currentDepth = depthBuffer[x + screenWidth * y];
			if (depth < currentDepth)
			{
				depthBuffer[x + screenWidth * y] = depth;
				TexCoord texcoord = span.texCoord0 + (dtexcord * factor);
				D3DCOLOR color = SampleTexture(texcoord);
				DrawPixel(x, y, color);
			}
		}

		depth += depthStep;
		factor += factorStep;
	}
}

D3DCOLOR Graphics::SampleTexture(TexCoord& texcoord)
{
	while (texcoord.x > 1.0f)
	{
		texcoord.x -= 1.0f;
	}
	while (texcoord.y > 1.0f)
	{
		texcoord.y -= 1.0f;
	}

	int x = (int)(texcoord.x * (float)(texWidth));
	int y = (int)(texcoord.y * (float)(texHeight));
	D3DCOLOR color = texture[x + texWidth * y];

	return color;
}

void Graphics::DrawPixel(int x, int y, const Vector4F& color)
{
	if (!(x >= 0 && y >= 0 && x < screenWidth && y < screenHeight))
	{
		return;
	}
	
	int r = (int)(color.x * 255);
	int g = (int)(color.y * 255);
	int b = (int)(color.z * 255);

	D3DCOLOR col = D3DCOLOR_XRGB(r, g, b);
	frameBuffer[x + screenWidth * y] = col;
}

void Graphics::DrawPixel(int x, int y, const D3DCOLOR& color)
{
	if (!(x >= 0 && y >= 0 && x < screenWidth && y < screenHeight))
	{
		return;
	}

	frameBuffer[x + screenWidth * y] = color;
}
