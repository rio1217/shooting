#pragma once
#include "Missile.h"
class MissileB : public Missile
{
private:
	double ay;
public:
	void init();
	void update();
	void draw();
	void fire(double x, double y, double vx, double vy);
};

