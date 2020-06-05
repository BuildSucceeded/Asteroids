#pragma once

#include "resource.h"
#include "Point2D.h"

#define ASTEROID_SPEED 50
#define ASTEROID_MAX_ROTATION 90
#define ASTEROID_SIZE_MULTIPLIER 10
#define ASTEROID_SIZE_VARIATION 20
#define ASTEROID_CORNERS 9

class Asteroid
{
public:
	Asteroid();
	Asteroid(Point2D newPosition, int newSize, Point2D newSpeed);
	~Asteroid();

	void InitializeD2D(ID2D1HwndRenderTarget* m_pRenderTarget);
	void Advance(double elapsedTime);
	void Explode();

	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	Point2D GetPosition();
	Point2D GetSpeed();
	int GetSize();
	double GetExplosionTime();

private:
	Point2D position;
	Point2D speed;

	int size;
	double explosionTime;
	double rotation;
	double rotationSpeed;

	int sizeVariation[ASTEROID_CORNERS];

	ID2D1SolidColorBrush* m_pBlueBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
};

