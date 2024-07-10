#pragma once
#include "Missile.h"
class MissileA : public Missile
{
public:
	void init();
	void update();
	void draw();
	void fire(double x, double y, double vx, double vy);
};

