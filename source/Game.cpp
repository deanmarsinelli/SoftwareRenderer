/*
	Game.cpp
	Author: Dean Marsinelli
*/

#include <WindowsX.h>

#include "Box.h"
#include "Game.h"

Game* g_pGame = nullptr;

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pGame->MsgProc(hWnd, msg, wParam, lParam);
}

Game::Game(HWND hWnd)
{
	g_pGame = this;
	this->hWnd = hWnd;

	graphics = new Graphics(hWnd, 800, 600);
	projectionMatrix = Graphics::PerspectiveMatrixLH(0.25 * _PI, 800.0f / 600.0f, 1.0f, 1000.0f);
	graphics->BindMatrix(&projectionMatrix, PROJECTION);

	timer = new Timer();

	camera = new Camera(Mat4x4::Identity);
	AddGameObject(camera);

	AddGameObject(new Box(Mat4x4::Identity));
}

void Game::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void Game::Update()
{
	float dt = timer->Tick();

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Update(dt);
	}
}

void Game::Draw()
{
	graphics->ClearBackBuffer(D3DCOLOR_XRGB(0, 0, 0));
	graphics->ClearDepthBuffer();

	Vector3F pos = camera->GetPosition();
	Vector3F dir = camera->GetDirection();

	Mat4x4 viewMatrix = Graphics::LookAtLH(pos, pos + dir, { 0.0f, 1.0f, 0.0f });
	graphics->BindMatrix(&viewMatrix, VIEW);

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Draw(graphics);
	}

	graphics->Present();
}

LRESULT Game::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		OnKeyDown((BYTE)wParam);
		return 0;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	lastMouseX = x;
	lastMouseY = y;
	SetCapture(hWnd);
}

void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	ReleaseCapture();
}

void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	if ((buttonState & MK_LBUTTON) != 0 && lastMouseX != x && lastMouseY != y)
	{
		float deltaX = (float)(lastMouseX - x);
		float deltaY = (float)(lastMouseY - y);

		lastMouseX = x;
		lastMouseY = y;

		FLOAT yaw = DegToRad(deltaX / 9.0f);
		FLOAT pitch = DegToRad(deltaY / 9.0f);

		camera->Rotate(yaw, pitch, 0.0f);
	}
}

void Game::OnKeyDown(BYTE key)
{
	Vector3F pos = camera->GetPosition();
	Vector3F dir = camera->GetDirection().Normalize();
	Vector3F right = camera->GetRight().Normalize();

	switch (key)
	{
		// vector math is faster than trig
	case 0x57: // W
		pos.x += dir.x;
		pos.y += dir.y;
		pos.z += dir.z;
		// pos.x -= sin(DegToRad(yaw)) * 0.5f;
		// pos.z += cos(DegToRad(yaw)) * 0.5f;
		// pos.y += sin(DegToRad(pitch)) * 0.5f;
		break;
	case 0x41: // A
		pos.x -= right.x;
		pos.y -= right.y;
		pos.z -= right.z;
		// pos.x -= cos(DegToRad(yaw + (_PI / 2.0f))) * 0.5f;
		// pos.z += sin(DegToRad(yaw - _PI / 2.0f)) * 0.5f;
		break;
	case 0x53: // S
		pos.x -= dir.x;
		pos.y -= dir.y;
		pos.z -= dir.z;
		// pos.x -= sin(DegToRad(yaw)) * -0.5f;
		// pos.z += cos(DegToRad(yaw)) * -0.5f;
		// pos.y += sin(DegToRad(pitch)) * -0.5f;
		break;
	case 0x44: // D
		pos.x += right.x;
		pos.y += right.y;
		pos.z += right.z;
		// pos.x += cos(DegToRad(yaw + _PI / 2.0f)) * 0.5f;
		// pos.z -= sin(DegToRad(yaw - _PI / 2.0f)) * 0.5f;
		break;
	}

	camera->SetPosition(pos);
}
