#pragma once
#include "Timer.h"

class FlyingObject
{
protected:
	double x;		// 現在の位置 (pixel)
	double vx;		// 現在の移動速度 (pixel/s)
	double y;
	double vy;
	double radius; //半径
	Timer mtimer; //移動経路計算用
	Timer etimer;
	Timer elapsed;	// 前回のupdateからの経過時間計測用
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

