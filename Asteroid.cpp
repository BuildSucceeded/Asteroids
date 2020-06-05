#include "framework.h"
#include "Point2D.h"
#include "Engine.h"
#include "Asteroid.h"

Asteroid::Asteroid() : m_pBlueBrush(NULL), m_pYellowBrush(NULL)
{
	// Initialize position randomly on the screen
	position.x = rand() % RESOLUTION_X;
	position.y = rand() % RESOLUTION_Y;

	// Initialize fixed speed in a random direction
	double rotationAngle = rand() % 360;
	speed.x = sin(rotationAngle * PI / 180) * ASTEROID_SPEED;
	speed.y = -cos(rotationAngle * PI / 180) * ASTEROID_SPEED;

	// Initial size : 4
	size = 4;

	// Initializes a random rotation speed
	rotation = 0;
	rotationSpeed = rand() % ASTEROID_MAX_ROTATION - (ASTEROID_MAX_ROTATION / 2);

	// Generates random shape of the asteroid
	int variation = ASTEROID_SIZE_VARIATION * size / 4;
	for (int i = 0; i < ASTEROID_CORNERS; i++)
	{
		sizeVariation[i] = rand() % variation - (variation / 2.0);
	}
}

Asteroid::Asteroid(Point2D newPosition, int newSize, Point2D newSpeed) : m_pBlueBrush(NULL), m_pYellowBrush(NULL)
{
	// Initializes position, speed and size from received parameters
	position = newPosition;
	speed = newSpeed;
	size = newSize;

	// Initializes a random rotation speed
	rotation = 0;
	rotationSpeed = rand() % ASTEROID_MAX_ROTATION - (ASTEROID_MAX_ROTATION / 2);

	// Generates random shape of the asteroid
	int variation = ASTEROID_SIZE_VARIATION * size / 4;
	for (int i = 0; i < ASTEROID_CORNERS; i++)
	{
		sizeVariation[i] = rand() % variation - (variation / 2.0);
	}
}

Asteroid::~Asteroid()
{
	SafeRelease(&m_pBlueBrush);
	SafeRelease(&m_pYellowBrush);
}

void Asteroid::InitializeD2D(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Creates a blue brush for drawing asteroid
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&m_pBlueBrush
	);
	// Creates a yellow brush for drawing explosions
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Yellow),
		&m_pYellowBrush
	);
}

void Asteroid::Advance(double elapsedTime)
{
	// If size > 0, we have an asteroid moving around
	// If size == 0, our asteroid is exploded
	if (size > 0)
	{
		// We move it around, and if it goes outside the screen, we make it pop up on the other side
		position.x += elapsedTime * speed.x;
		if (position.x < -10)
		{
			position.x = RESOLUTION_X + 10;
		}
		if (position.x > RESOLUTION_X + 10)
		{
			position.x = -10;
		}
		position.y += elapsedTime * speed.y;
		if (position.y < -10)
		{
			position.y = RESOLUTION_Y + 10;
		}
		if (position.y > RESOLUTION_Y + 10)
		{
			position.y = -10;
		}
		// We also rotate it
		rotation += rotationSpeed * elapsedTime;
	}
	else
	{
		// We use explosionTime to generate a visual explosion and remove it after 0.5 seconds
		explosionTime += elapsedTime;
	}
}

void Asteroid::Explode()
{
	// Asteroids goes into explosion mode
	size = 0;
	explosionTime = 0;
}

void Asteroid::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	if (size > 0)
	{
		// If it's not exploded, we draw the asteroid's shape
		ID2D1PathGeometry* clPath;
		ID2D1Factory* factory;
		m_pRenderTarget->GetFactory(&factory);
		factory->CreatePathGeometry(&clPath);

		ID2D1GeometrySink* pclSink;
		clPath->Open(&pclSink);
		pclSink->SetFillMode(D2D1_FILL_MODE_WINDING);
		D2D1_POINT_2F point0 = D2D1::Point2F(position.x + (size * ASTEROID_SIZE_MULTIPLIER + sizeVariation[0]) * sin(rotation * PI / 180), position.y - (size * ASTEROID_SIZE_MULTIPLIER + sizeVariation[0]) * cos(rotation * PI / 180));
		pclSink->BeginFigure(point0, D2D1_FIGURE_BEGIN_FILLED);
		int angleStep = 360 / ASTEROID_CORNERS;
		for (int i = 1; i < ASTEROID_CORNERS; i++)
		{
			D2D1_POINT_2F point = D2D1::Point2F(position.x + (size * ASTEROID_SIZE_MULTIPLIER + sizeVariation[i]) * sin((rotation + i * angleStep) * PI / 180), position.y - (size * ASTEROID_SIZE_MULTIPLIER + sizeVariation[i]) * cos((rotation + i * angleStep) * PI / 180));
			pclSink->AddLine(point);
		}
		pclSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pclSink->Close();
		m_pRenderTarget->DrawGeometry(clPath, m_pBlueBrush, 4);

		SafeRelease(&pclSink);
		SafeRelease(&clPath);

	}
	else
	{
		// In case of an explosion, we draw 9 points moving away from the center
		int angleStep = 360 / ASTEROID_CORNERS;
		for (int i = 0; i < ASTEROID_CORNERS; i++)
		{
			D2D1_ELLIPSE ellipseBall = D2D1::Ellipse(
				D2D1::Point2F(position.x + (explosionTime * (100 + 20 * sizeVariation[i])) * sin(i * angleStep * PI / 180), position.y - (explosionTime * (100 + 20 * sizeVariation[i])) * cos(i * angleStep * PI / 180)),
				4, 4
			);
			m_pRenderTarget->FillEllipse(&ellipseBall, m_pYellowBrush);
		}
	}
}

Point2D Asteroid::GetPosition()
{
	return position;
}

Point2D Asteroid::GetSpeed()
{
	return speed;
}

int Asteroid::GetSize()
{
	return size;
}

double Asteroid::GetExplosionTime()
{
	return explosionTime;
}