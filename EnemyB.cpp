#define _USE_MATH_DEFINES	// Visual C++でM_PIを使えるように
#include <cmath>
#include "ShootingApp.h"
#include "EnemyB.h"

EnemyB::EnemyB(): Enemy()
{
}


EnemyB::~EnemyB()
{
}

void EnemyB::init()
{
	FlyingObject::init();

	phase = App::rand() * M_PI;	// M_PIはπ

	x = 300 + 200 * App::rand();
	y = 100 + 100 * App::rand();

	vx = 100 + 200 * App::rand();
	vy = 100 + 200 * App::rand();

	radius = 60;
	point = 15;
}

void EnemyB::update()
{
	if (status & COLLISION) {
		if (etimer.get() > 0.5) {
		    cleanup();
		}
		return;
	}
	double dt = elapsed.get();
	double mt = mtimer.get();
	double dx, dy;

	// updateの間隔が長すぎるときは、強制的にdtを設定
	if (dt > 1.0 / 30)
		dt = 1.0 / 30;

	dx = vx * sin(2* mt + phase)* dt;
	dy = vy * cos(20 * mt + phase) * dt;

	x += dx;
	y += dy;

	elapsed.reset();
}

void EnemyB::draw()
{
	if (status & COLLISION) {
		drawExplosion();
		return;
	}
	LPCWSTR c;
	c = TEXT("／⌒ヽ");
	TextOut(App::hDC, (int)x-14 , (int)y - 37, c, lstrlen(c));
	c = TEXT("⊂二二( ^ω^)二⊃");
	TextOut(App::hDC, (int)x - 59 , (int)y - 22, c, lstrlen(c));
	c = TEXT("|    ノ");
	TextOut(App::hDC, (int)x-7, (int)y - 7, c, lstrlen(c));
	c = TEXT("(   ノ");
	TextOut(App::hDC, (int)x-9, (int)y + 6, c, lstrlen(c));
	c = TEXT("ノ>ノ");
	TextOut(App::hDC, (int)x-17 , (int)y + 19, c, lstrlen(c));
	c = TEXT("レレ");
	TextOut(App::hDC, (int)x-18, (int)y + 32, c, lstrlen(c));
}