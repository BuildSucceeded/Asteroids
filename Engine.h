#pragma once

#include "resource.h"
#include "Ship.h"
#include "Projectile.h"
#include "Asteroid.h"

#define RESOLUTION_X 800
#define RESOLUTION_Y 600
#define PI 3.14159265

class Engine
{
public:
	Engine();
	~Engine();

	HRESULT InitializeD2D(HWND m_hwnd);
	void KeyUp(WPARAM wParam);
	void KeyDown(WPARAM wParam);
	void Logic(double elapsedTime);
	HRESULT Draw();

private:
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pWhiteBrush;

	Ship* ship;
	Projectile* projectiles[20];
	int noProjectiles;
	Asteroid* asteroids[32];
	int noAsteroids;
	int lives;
	Ship* lifeShips[3];

	bool leftPressed;
	bool rightPressed;
	bool accelerationPressed;
	int firePressed;

	bool gameOver;
	bool gameWon;
};

