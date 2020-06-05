#pragma once

#include "resource.h"
#include "Point2D.h"

class Ship
{
public:
	Ship();
	Ship(int lifeNo);
	~Ship();

	void InitializeD2D(ID2D1HwndRenderTarget* m_pRenderTarget);
	void Advance(double elapsedTime);
	void ApplyLeftRotation(double elapsedTime);
	void ApplyRightRotation(double elapsedTime);
	void ApplyAcceleration(double elapsedTime);
	void Explode();
	void Reset();

	void Draw(ID2D1HwndRenderTarget* m_pRenderTarget);

	Point2D GetPosition();
	double GetRotation();
	bool IsExploded();
	double GetExplosionTime();

private:
	Point2D position;
	Point2D speed;

	double rotation;
	bool exploded;
	double explosionTime;

	ID2D1SolidColorBrush* m_pGreenBrush;
	ID2D1SolidColorBrush* m_pYellowBrush;
};

