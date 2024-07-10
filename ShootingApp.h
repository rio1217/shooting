#pragma once
#include "App.h"
#include "Fighter.h"
#include "Missile.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "Score.h"
#include "Sound.h"
#include <vector>

#define N_ENEMY_A 2
#define N_MISSILE_A 10
#define N_ENEMY_B 3
#define N_MISSILE_B 5

class ShootingApp : public App
{
private:
	Fighter fighter;
	EnemyA enemyA[N_ENEMY_A];
	EnemyB enemyB[N_ENEMY_B];
	MissileA missileA[N_MISSILE_A];
	MissileB missileB[N_MISSILE_B];
	std::vector<FlyingObject*> fos;
	std::vector<Enemy*> enemies;
	std::vector<Missile*> missiles;
	Score score;
public:
	static HWND hWnd;
	static HDC hDC;

	 void init();
	 void cleanup();
     void update();
     void draw();
	 void keyDown(WPARAM key);
	 void keyUp(WPARAM key);
};

