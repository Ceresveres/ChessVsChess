#include "Bullet.h"
#include "ui-tools.h"

void Bullet::setXY(int dx, int dy) {
	x = dx * (GRID_WIDTH);
	y = dy * (GRID_HEIGHT);
}

void Bullet::print() {
	Goto_XY(x, y);
	PrintWithColor("*");
}