#define _USE_MATH_DEFINES	// Visual C++Ç≈M_PIÇégÇ¶ÇÈÇÊÇ§Ç…
#include <cmath>
#include "ShootingApp.h"
#include "EnemyA.h"

EnemyA::EnemyA() : Enemy()
{
}


EnemyA::~EnemyA()
{
}

void EnemyA::init()
{
	FlyingObject::init();

	phase = App::rand() * M_PI;	// M_PIÇÕÉŒ

	x = 100 + 500 * App::rand();
	y = 100 + 200 * App::rand();

	vx = 100 + 200 * App::rand();
	vy = 100 + 200 * App::rand();

	radius = 30;
	point = 20;
}

void EnemyA::update()
{
	if (status & COLLISION) {
		if (etimer.get() > 0.5)
			cleanup();
		return;
	}
	double dt = elapsed.get();
	double mt = mtimer.get();
	double dx, dy;

	// updateÇÃä‘äuÇ™í∑Ç∑Ç¨ÇÈÇ∆Ç´ÇÕÅAã≠êßìIÇ…dtÇê›íË
	if (dt > 1.0 / 30)
		dt = 1.0 / 30;

	dx = vx * sin(2 * mt + phase) * dt;
	dy = vy * cos(5 * mt + phase) * dt;

	x += dx;
	y += dy;

	elapsed.reset();
}

void EnemyA::draw()
{
	if (status & COLLISION) {
		drawExplosion();
		return;
	}
	LPCWSTR c;
	c = TEXT("Å_(^o^)Å^");
	TextOut(App::hDC, (int)x-32, (int)y-15, c, lstrlen(c));
	c = TEXT("Åv L");
	TextOut(App::hDC, (int)x-13, (int)y +1, c, lstrlen(c));
}