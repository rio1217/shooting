#include "ShootingApp.h"

void ShootingApp::init()
{
	App::init();
	fighter.init();
	fos.push_back(&fighter);
	Sound::getInstance()->registerFile(TEXT("c:/windows/Media/chimes.wav"), TEXT("explosion"));
	Sound::getInstance()->registerFile(TEXT("c:/windows/Media/ir_begin.wav"), TEXT("shoot"));
	Sound::getInstance()->registerFile(TEXT("c:/windows/Media/flourish.mid"), TEXT("bgm"));
	for (size_t i = 0; i < N_ENEMY_A; i++) {
		enemyA[i].init();
		enemies.push_back(&enemyA[i]);
		fos.push_back(&enemyA[i]);
	}
	for (size_t i = 0; i < N_ENEMY_B; i++) {
		enemyB[i].init();
		enemies.push_back(&enemyB[i]);
		fos.push_back(&enemyB[i]);
	}
	for (size_t i = 0; i < N_MISSILE_A; i++) {
		fighter.loadMissile(&missileA[i]);
		missiles.push_back(&missileA[i]);
		fos.push_back(&missileA[i]);
	}
	for (size_t i = 0; i < N_MISSILE_B; i++) {
		fighter.loadMissile(&missileB[i]);
		missiles.push_back(&missileB[i]);
		fos.push_back(&missileB[i]);
	}
	score.init();
	Sound::getInstance()->request(TEXT("bgm"));
}

void ShootingApp::cleanup()
{
	App::cleanup();
	Sound::getInstance()->cleanup();
	for (size_t i = 0; i < fos.size(); i++)
		fos[i]->cleanup();
	fos.clear();
	enemies.clear();
	missiles.clear();
}

void ShootingApp::update()
{
	App::update();
	for (size_t i = 0; i < fos.size(); i++)
		if (fos[i]->status & FlyingObject::ACTIVE)
			fos[i]->update();

	for (size_t i = 0; i < enemies.size(); i++) {
		if (!(enemies[i]->status & FlyingObject::ACTIVE))
			continue;
		for (size_t j = 0; j < missiles.size(); j++)
			if (enemies[i]->checkCollision(missiles[j]))
				score.add(enemies[i]->point);
		enemies[i]->checkCollision(&fighter);
	}

	for (size_t i = 0; i < enemies.size(); i++)
		if (!enemies[i]->status)
			enemies[i]->init();

	if (!fighter.status) {
		cleanup();
		init();
	}
}

void ShootingApp::draw()
{
	App::draw();
	Sound::getInstance()->play();
	for (size_t i = 0; i < fos.size(); i++)
		if (fos[i]->status & FlyingObject::ACTIVE)
			fos[i]->draw();
	score.draw(10, 10);
}

void ShootingApp::keyDown(WPARAM key)
{
	switch (key) {
	case VK_LEFT:
		fighter.move(Fighter::LEFT);
		break;
	case VK_RIGHT:
		fighter.move(Fighter::RIGHT);
		break;
	case VK_UP:
		fighter.move(Fighter::FORE);
		break;
	case VK_DOWN:
		fighter.move(Fighter::BACK);
		break;
	case VK_SPACE:
		fighter.shootA();
		break;
	case VK_SHIFT:
		fighter.shootB();
		break;
	}
	
}

void ShootingApp::keyUp(WPARAM key)
{
	switch (key) {
	case VK_LEFT:
		fighter.stop(Fighter::LEFT);
		break;
	case VK_RIGHT:
		fighter.stop(Fighter::RIGHT);
		break;
	case VK_UP:
		fighter.stop(Fighter::FORE);
		break;
	case VK_DOWN:
		fighter.stop(Fighter::BACK);
		break;
	case VK_SPACE:
		fighter.stop(Fighter::STOP);
		break;
	case VK_SHIFT:
		fighter.stop(Fighter::STOP);
		break;
	}
}