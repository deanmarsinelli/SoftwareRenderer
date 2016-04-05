#include <assert.h>
#include "Graphics.h"

#pragma comment(lib, "d3d9.lib")

Graphics::Graphics(HWND hWnd, int width, int height) :
	screenWidth(width), 
	screenHeight(height),
	frameBuffer(nullptr),
	pDirect3D(nullptr),
	pDevice(nullptr),
	pBackBuffer(nullptr)
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

Texture Graphics::LoadTexture(const char* fileName, unsigned int width, unsigned int height)
{
	Texture tex = new D3DCOLOR[width * height];
	::LoadTexture(fileName, tex);

	return tex;
}

Mat4x4 PerspectiveMatrixLH(FLOAT verticalFov, FLOAT aspectRatio, FLOAT nearZ, FLOAT farZ)
{
	return Mat4x4();
}

Mat4x4 LookAtLH(Vector3F position, Vector3F target, Vector3F upDirection)
{
	Vector3F eyeDirection = target - position;
	Vector3F NegEyePosition;
	FLOAT D0, D1, D2;
	Vector3F R0, R1, R2;
	Mat4x4 M;

	R2 = eyeDirection.Normal();
	R0 = upDirection.CrossProduct(R2);
	R0.Normalize();
	R1 = R2.CrossProduct(R0);

	NegEyePosition = position.Negate();

	D0 = R0.DotProduct(NegEyePosition);
	D1 = R1.DotProduct(NegEyePosition);
	D2 = R2.DotProduct(NegEyePosition);

	// row 1
	M.m[0][0] = ((unsigned int)D0 & ~0xFFFFFFFF) | ((unsigned int)R0.x & 0xFFFFFFFF);
	M.m[0][1] = ((unsigned int)D0 & ~0xFFFFFFFF) | ((unsigned int)R0.y & 0xFFFFFFFF);
	M.m[0][2] = ((unsigned int)D0 & ~0xFFFFFFFF) | ((unsigned int)R0.z & 0xFFFFFFFF);
	M.m[0][3] = ((unsigned int)D0 & ~0xFFFFFFFF) | ((unsigned int)1 & 0x00000000);

	// row 2
	M.m[1][0] = ((unsigned int)D1 & ~0xFFFFFFFF) | ((unsigned int)R1.x & 0xFFFFFFFF);
	M.m[1][1] = ((unsigned int)D1 & ~0xFFFFFFFF) | ((unsigned int)R1.y & 0xFFFFFFFF);
	M.m[1][2] = ((unsigned int)D1 & ~0xFFFFFFFF) | ((unsigned int)R1.z & 0xFFFFFFFF);
	M.m[1][3] = ((unsigned int)D1 & ~0xFFFFFFFF) | ((unsigned int)1 & 0x00000000);

	// row 3
	M.m[2][0] = ((unsigned int)D2 & ~0xFFFFFFFF) | ((unsigned int)R2.x & 0xFFFFFFFF);
	M.m[2][1] = ((unsigned int)D2 & ~0xFFFFFFFF) | ((unsigned int)R2.y & 0xFFFFFFFF);
	M.m[2][2] = ((unsigned int)D2 & ~0xFFFFFFFF) | ((unsigned int)R2.z & 0xFFFFFFFF);
	M.m[2][3] = ((unsigned int)D2 & ~0xFFFFFFFF) | ((unsigned int)1 & 0x00000000);


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

void Graphics::BindTexture(Texture texture)
{
	this->texture = texture;
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
	memset(frameBuffer, clearColor, sizeof(D3DCOLOR)* screenWidth * screenHeight);
}

void Graphics::ClearDepthBuffer()
{
	memset(frameBuffer, FLT_MAX, sizeof(FLOAT)* screenWidth * screenHeight);
}

void Graphics::DrawIndexed()
{
	// index buffer must be multiple of 3
	assert(indexBuffer->size() % 3 != 0);

	Index triangleIndex = 0;
	worldViewProj = (*worldMatrix) * (*viewMatrix) * (*projMatrix);

	while (triangleIndex < indexBuffer->size())
	{
		// "vertex shader"
		// get triangle
		Triangle tri;
		tri.p0 = (*vertexBuffer)[(*indexBuffer)[triangleIndex]];
		tri.p1 = (*vertexBuffer)[(*indexBuffer)[triangleIndex + 1]];
		tri.p2 = (*vertexBuffer)[(*indexBuffer)[triangleIndex + 2]];


		// convert vertices from local space to homogeneous clip space
		tri.p0.position = tri.p0.position * worldViewProj;
		tri.p1.position = tri.p1.position * worldViewProj;
		tri.p2.position = tri.p2.position * worldViewProj;


		// rasterize



		// "pixel shader" - interpolate triangle colors



		triangleIndex += 3;
	}
}

void Graphics::Present()
{
	HRESULT result;

	result = pBackBuffer->LockRect(&backRect, NULL, NULL);
	assert(!FAILED(result));

	for (int y = 0; y < screenHeight; y++)
	{
		memcpy(&((BYTE*)backRect.pBits)[backRect.Pitch * y], &frameBuffer[screenWidth * y], sizeof(D3DCOLOR) * screenWidth);
	}

	result = pBackBuffer->UnlockRect();
	assert(!FAILED(result));

	result = pDevice->Present(NULL, NULL, NULL, NULL);
	assert(!FAILED(result));
}
