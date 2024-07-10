#include "ShootingApp.h"
#include "Fighter.h"

Fighter::Fighter() : FlyingObject(), dir(STOP)
{
}

Fighter::~Fighter()
{
}

void Fighter::init()
{
	FlyingObject::init();

	x = 400;
	vx = 200;
	y = 500;
	vy = 200;
}

void Fighter::cleanup()
{
	FlyingObject::cleanup();
	missiles.clear();
}

void Fighter::update()
{
	if (status & COLLISION) {
		if (etimer.get() > 0.5)
			cleanup();
		return;
	}
	FlyingObject::update();

	double dx = 0;
	double dy = 0;
	double dt = elapsed.get();

	if (dir & LEFT)
		dx -= vx * dt;
	if (dir & RIGHT)
		dx += vx * dt;
	if (dir & FORE)
		dy -= vy * dt;
	if (dir & BACK)
		dy += vy * dt;

	x += dx;
	y += dy;
	elapsed.reset();
}

void Fighter::draw()
{
	if (status & COLLISION) {
		drawExplosion();
		return;
	}
	LPCWSTR c;

	c = TEXT("^");
	TextOut(App::hDC, (int)x-3, (int)y-18, c, lstrlen(c));
	c = TEXT("^^");
	TextOut(App::hDC, (int)x-5, (int)y-12, c, lstrlen(c));
	c = TEXT("<'|~|'>");
	TextOut(App::hDC, (int)x-18, (int)y-5, c, lstrlen(c));
	c = TEXT("^^^^");
	TextOut(App::hDC, (int)x - 10, (int)y + 8, c, lstrlen(c));


}

void Fighter::loadMissile(Missile* m)
{
	missiles.push_back(m);
}

void Fighter::shootA()
{
	for (size_t i=0;i<missiles.size()-N_MISSILE_B;i++)
		if (!(missiles[i]->status & ACTIVE)) {
			missiles[i]->init();
			missiles[i]->fire(x, y - radius, 0, -400);
			Sound::getInstance()->request(TEXT("shoot"));
			return;
		}
}

void Fighter::shootB()
{
	for (size_t i = N_MISSILE_A; i < missiles.size(); i++)
		if (!(missiles[i]->status & ACTIVE)) {
			missiles[i]->init();
			missiles[i]->fire(x, y - radius, 0, -400);
			Sound::getInstance()->request(TEXT("shoot"));
			return;
		}
}



void Fighter::move(DIRECTION dir)
{
	this->dir |= dir;
}

void Fighter::stop(DIRECTION dir)
{
	this->dir &= ~dir;
}