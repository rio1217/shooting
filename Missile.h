#pragma once
#include "FlyingObject.h"

class Missile : public FlyingObject
{
public:
	virtual void fire(double x, double y, double vx, double vy);
};

