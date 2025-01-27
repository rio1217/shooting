#include "App.h"

App::App()
{
}

App::~App()
{
}

void App::init()
{
	std::random_device rd;
	mt.seed(rd());
}

void App::cleanup()
{
}

void App::update()
{
}

void App::draw()
{
}

void App::keyDown(WPARAM key)
{
}

void App::keyUp(WPARAM key)
{
}

double App::rand()
{
	static std::uniform_real_distribution<> dist(0.0, 1.0);
	return dist(mt);
}

std::mt19937 App::mt;
HWND App::hWnd = 0;
HDC App::hDC = 0;
