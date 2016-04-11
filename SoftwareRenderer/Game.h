/*
	Game.h
	Author: Dean Marsinelli

	Game class controls the main loop for updating
	the scene and drawing every frame.
*/

#pragma once

#include <vector>
#include <Windows.h>

#include "Camera.h"
#include "Graphics.h"
#include "GameObject.h"
#include "Timer.h"

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Game
{
public:
	Game(HWND hWnd);

	void Update();
	void Draw();
	void AddGameObject(GameObject* gameObject);

	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnMouseDown(WPARAM buttonState, int x, int y);
	void OnMouseUp(WPARAM buttonState, int x, int y);
	void OnMouseMove(WPARAM buttonState, int x, int y);
	void OnKeyDown(BYTE key);
	
private:
	HWND hWnd;
	Graphics* graphics;
	Timer* timer;

	Mat4x4 projectionMatrix;
	Camera* camera;
	std::vector<GameObject*> gameObjects;

	int lastMouseX;
	int lastMouseY;
};
