#include "ShootingApp.h"
#include "FlyingObject.h"

#define sqr(x) ((x)*(x))

FlyingObject::FlyingObject() : x(0), vx(0),y(0),vy(0),radius(0),status(0)
{
}


FlyingObject::~FlyingObject()
{
}

void FlyingObject::init()
{
	x = 0;
	vx = 0;
	y = 0;
	vy = 0;
	elapsed.reset();
	radius = 20;
	status = ACTIVE;
	mtimer.reset();
}

void FlyingObject::cleanup()
{
	status = 0;
}

void FlyingObject::update()
{
}

void FlyingObject::draw()
{
}

void FlyingObject::drawDebug() 
{
	HBRUSH hBrush, hBrush_old;
	HPEN hPen, hPen_old;
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	hBrush_old = (HBRUSH)SelectObject(App::hDC, hBrush);
	hPen_old = (HPEN)SelectObject(App::hDC, hPen);
	Ellipse(App::hDC, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(hPen);
	SelectObject(App::hDC, hBrush_old);
	SelectObject(App::hDC, hPen_old);
}

bool FlyingObject::checkCollision(FlyingObject* fo)
{
	if (!(fo->status & ACTIVE))
		return false;
	if ((sqr(x - fo->x) + sqr(y - fo->y)) > sqr(radius + fo->radius))
		return false;
	
	if (!(status & COLLISION)) {
		status |= COLLISION;
		etimer.reset();
	}

	if (!(status & ACTIVE))
		return false;
	if ((sqr(x - fo->x) + sqr(y - fo->y)) > sqr(radius + fo->radius))
		return false;

	if (!(fo->status & COLLISION)) {
		fo->status |= COLLISION;
		fo->etimer.reset();
	}

	return true;
}

void FlyingObject::drawExplosion()
{ 
	LPCWSTR c;
	double t = etimer.get(); // Õ“Ë‚µ‚Ä‚©‚ç‚ÌŒo‰ßŽžŠÔ
	if (t > 0.5) {
		c = TEXT("*       *");
		TextOut(App::hDC, (int)x - 25, (int)y - 25, c, lstrlen(c));
		c = TEXT("*       *");
		TextOut(App::hDC, (int)x - 25, (int)y + 15, c, lstrlen(c));
		c = TEXT("*     *");
		TextOut(App::hDC, (int)x - 20, (int)y - 20, c, lstrlen(c));
		c = TEXT("*     *");
	}
	else if (t > 0.4) {
		c = TEXT("*     *");
		TextOut(App::hDC, (int)x - 20, (int)y - 20, c, lstrlen(c));
		c = TEXT("*     *");
		TextOut(App::hDC, (int)x - 20, (int)y + 10, c, lstrlen(c));
		c = TEXT("*   *");
		TextOut(App::hDC, (int)x - 15, (int)y - 15, c, lstrlen(c));
		c = TEXT("*   *");
		TextOut(App::hDC, (int)x - 15, (int)y + 5, c, lstrlen(c));
	}
	else if (t > 0.3) {
		c = TEXT("*   *");
		TextOut(App::hDC, (int)x - 15, (int)y - 15, c, lstrlen(c));
		c = TEXT("*   *");
		TextOut(App::hDC, (int)x - 15, (int)y + 5, c, lstrlen(c));
		c = TEXT("* *");
		TextOut(App::hDC, (int)x - 10, (int)y - 10, c, lstrlen(c));
		c = TEXT("* *");
		TextOut(App::hDC, (int)x - 10, (int)y, c, lstrlen(c));
	}
	else if (t > 0.1) {
		c = TEXT("* *");
		TextOut(App::hDC, (int)x - 10, (int)y - 10, c, lstrlen(c));
		c = TEXT("* *");
		TextOut(App::hDC, (int)x - 10, (int)y, c, lstrlen(c));
		c = TEXT("*");
		TextOut(App::hDC, (int)x - 5, (int)y - 5, c, lstrlen(c));
	}
	else {
		Sound::getInstance()->request(TEXT("explosion"));
		c = TEXT("*");
		TextOut(App::hDC, (int)x - 5, (int)y - 5, c, lstrlen(c));
	}
}
