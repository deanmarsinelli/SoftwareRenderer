#include <assert.h>
#include "Graphics.h"

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

	worldViewProj = (*worldMatrix) * (*viewMatrix);

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