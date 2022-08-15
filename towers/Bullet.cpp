#include "Bullet.h"
#include "Board.h"
#include "ui-tools.h"


Bullet::Bullet()
{
	attack = 10;
	hit = false;
}

void Bullet::setXY(int ix, int iy) {
	dx = ix;
	dy = iy;
	x = (dx +1) * (GRID_WIDTH + 1) - (GRID_WIDTH/2);
	y = (dy + 1) * (GRID_HEIGHT);
}

void Bullet::move(Board &board) {
	//if (board.grid[dx][dy].invaders.size() > 0) {
	//	board.grid[dx][dy].setRefresh();

	//}
	board.grid[dx][dy].setRefresh();
	if (x % (GRID_WIDTH + 1) == 0) {
		Goto_XY(x, y);
		PrintWithColor("#");
	}
	x += 2;
	dx = x / (GRID_WIDTH+1);
	if (dx > GRID_NUM_X) {
		hit = true;
		return;
	}
	if (board.grid[dx][dy].invaders.size() > 0) {
		hitInvader(board.grid[dx][dy].invaders);
		board.grid[dx][dy].setRefresh();
		if (x % (GRID_WIDTH + 1) == 0) {
			Goto_XY(x, y);
			PrintWithColor("#");
		}
		hit = true;
		return;
	}
}

void Bullet::hitInvader(vector<Invader*>& invader) {
	for (auto var : invader) {
		var->hit(attack);
	}
}

void SlowBullet::hitInvader(vector<Invader*>& invader) {
	for (auto var : invader) {
		var->hit(attack);
		var->setSlow();
	}
}

void SlowBullet::print() {
	Goto_XY(x, y);
	PrintWithColor("$", FOREGROUND_BLUE);
}

void Bullet::print() {
	Goto_XY(x, y);
	PrintWithColor("*");
}