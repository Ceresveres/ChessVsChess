#include "Bullet.h"
#include "Board.h"
#include "ui-tools.h"

void Bullet::setXY(int ix, int iy) {
	dx = ix;
	dy = iy;
	//(dx + (GRID_WIDTH/2) - 1, dy + GRID_HEIGHT / 2)
	//x = (dx + 1) * (GRID_WIDTH + 1) - (GRID_WIDTH/2);
	//y = (dy) * (GRID_HEIGHT + 1) + GRID_HEIGHT/2;
	x = dx * (GRID_WIDTH);
	y = dy * (GRID_HEIGHT);
}

void Bullet::print() {
	Goto_XY(x, y);
	DrawCircle(x + GRID_WIDTH / 2, y + GRID_HEIGHT / 2, GRID_WIDTH / 10, WHITE);
	PrintWithColor("*");
}

void Bullet::move(Board &board) {
	board.grid[dx][dy].setRefresh();
	if (x % (GRID_WIDTH + 1) == 0) {
		Goto_XY(x, y);
		PrintWithColor("#");
	}
	x += GRID_WIDTH/10;
	if (dx >= GRID_NUM_X) {
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
	dx = x / (GRID_WIDTH + 1);
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
	PrintWithColor("$", 4);
}

void FireBullet::hitInvader(vector<Invader*>& invader) {
	for (auto var : invader) {
		var->hit(attack);
		var->setBurn();
	}
}

void FireBullet::print() {
	Goto_XY(x, y);
	PrintWithColor(">", 4);
}