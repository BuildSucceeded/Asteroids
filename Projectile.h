#pragma once

#include "resource.h"
#include "Point2D.h"

#define PROJECTILE_SPEED 400;

class Projectile
{
public:
	Projectile(Point2D startPosition, double rotationAngle);
	~Projectile();

	void InitializeD2D(ID2D1HwndRenderTarget* m_pRenderTarget);
	void Advance(double elapsedTime);
	bool IsOut();

	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	Point2D GetPosition();

private:
	Point2D position;
	Point2D speed;

	ID2D1SolidColorBrush* m_pRedBrush;
};

