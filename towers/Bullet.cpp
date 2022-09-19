#include "Bullet.h"
#include "Board.h"
#include "ui-tools.h"

void Bullet::setXY(int ix, int iy) {
	x = ix;
	y = iy;
	dx = x * BOX_WIDTH + BOX_WIDTH;
	dy = y * BOX_HEIGHT + BOX_HEIGHT/2;
}

void Bullet::updateXY() {
	x++;
	dx = x * BOX_WIDTH;
}

void Bullet::print(SDL_Renderer& rend) {
	SDL_Rect gridRect = { dx,  dy, 5, 5 };
	SDL_SetRenderDrawColor(&rend, 3, 252, 98, 255);
	SDL_RenderFillRect(&rend, &gridRect);
}

void Bullet::move(Board *board) {
	board->grid[x][y].setRefresh();
	dx += 45;
	if (dx >= (x+1) * BOX_WIDTH) {
		x++;
		board->grid[x][y].setRefresh();
	}
	
	if (x >= GRID_NUM_X) {
		hit = true;
		return;
	}
	if (board->grid[x][y].invaders.size() > 0) {
		hitInvader(board->grid[x][y].invaders);
		//board->grid[x][y].setRefresh();
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
		//var->setSlow();
		var->applyEffect(bulletElement);
	}
}

void SlowBullet::print() {
	Goto_XY(x, y);
	PrintWithColor("$", FOREGROUND_BLUE);
}

void FireBullet::hitInvader(vector<Invader*>& invader) {
	for (auto var : invader) {
		var->hit(attack);
		var->applyEffect(bulletElement);
	}
}

void FireBullet::print() {
	Goto_XY(x, y);
	PrintWithColor(">", FOREGROUND_RED | FOREGROUND_BLUE);
}