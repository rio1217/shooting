#pragma once
#include "Timer.h"

class FlyingObject
{
protected:
	double x;		// ���݂̈ʒu (pixel)
	double vx;		// ���݂̈ړ����x (pixel/s)
	double y;
	double vy;
	double radius; //���a
	Timer mtimer; //�ړ��o�H�v�Z�p
	Timer etimer;
	Timer elapsed;	// �O���update����̌o�ߎ��Ԍv���p
public:
	enum STATUS {
		ACTIVE = 1,
		COLLISION = 2
	};
	FlyingObject();
	virtual ~FlyingObject();

    virtual void init();
	virtual void cleanup();
	virtual void update();
	virtual void draw();
	virtual void drawDebug();
	virtual bool checkCollision(FlyingObject* fo);
	virtual void drawExplosion();
	
	unsigned int status = 0;
};
