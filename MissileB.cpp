#include "MissileB.h"
#include "ShootingApp.h"
#define sqr(x) ((x)*(x))

void MissileB::init() 
{
	FlyingObject::init();
	vx = vy = 0;
	ay = 4;
	radius = 5;
}

void MissileB::update()
{
	if (status & COLLISION) {
		if (etimer.get() > 0.5)
			cleanup();
		return;
	}
	if (x < 0 || x > 799 || y < 0 || y > 599) // 画面からはみ出たら、ミサイルはなくなる。
		cleanup();
	double dt = elapsed.get();
	x += vx * dt;
	y += vy * dt;
	vy = vy + sqr(ay);
	radius = radius + 1.5;
	elapsed.reset();
}

void MissileB::draw()
{
	if (status & COLLISION) {
		drawExplosion();
		return;
	}
	if (vy < 0) {
		Ellipse(App::hDC, x - radius, y - radius, x + radius, y + radius);
	}
}

void MissileB::fire(double x, double y, double vx, double vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
}