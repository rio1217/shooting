#define _USE_MATH_DEFINES	// Visual C++でM_PIを使えるように
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

	phase = App::rand() * M_PI;	// M_PIはπ

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

	// updateの間隔が長すぎるときは、強制的にdtを設定
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
	c = TEXT("＼(^o^)／");
	TextOut(App::hDC, (int)x-32, (int)y-15, c, lstrlen(c));
	c = TEXT("」 L");
	TextOut(App::hDC, (int)x-13, (int)y +1, c, lstrlen(c));
}