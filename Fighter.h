#pragma once
#include "FlyingObject.h"
#include "MissileA.h"
#include "MissileB.h"
#include <vector>

class Fighter : public FlyingObject
{
	unsigned int dir;		// Œ»İ‚ÌˆÚ“®•ûŒü

public:
	std::vector<Missile*> missiles;
	enum DIRECTION {
		STOP = 0,
		FORE = 1,
		BACK = 2,
		LEFT = 4,
		RIGHT = 8
	};

	Fighter();
	~Fighter();

	void init();
	void cleanup();
	void update();
	void draw();
	void loadMissile(Missile* m);
	void shootA();
	void shootB();

	void move(DIRECTION dir);
	void stop(DIRECTION dir);
};
