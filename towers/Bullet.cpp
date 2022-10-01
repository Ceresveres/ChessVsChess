#include "Bullet.h"
#include "Board.h"
#include "ui-tools.h"

Bullet::Bullet(const LoaderParams* pParams, int x, int y) : Object(pParams)
{
}

void Bullet::setXY(int ix, int iy) {
	mX = ix;
	mY = iy;
	dx = mX * GRID_HEIGHT + GRID_HEIGHT;
	dy = mY * GRID_WIDTH + GRID_WIDTH/2;
}

void Bullet::draw(SDL_Renderer& rend) {
	SDL_Rect gridRect = { mX,  mY, 5, 5 };
	SDL_SetRenderDrawColor(&rend, 3, 252, 98, 255);
	SDL_RenderFillRect(&rend, &gridRect);
}

void Bullet::update() {
	Board* board{ Board::GetSingleton() };
	mX += 5;
	if (dx >= (mX +1) * GRID_HEIGHT) {
		board->grid[mX][mY].setRefresh();
	}
	
	if (mX >= SCREEN_WIDTH) {
		hit = true;
		return;
	}
}

//void Bullet::hitInvader(vector<Invader*> invaders) {
//	for (auto var : invaders) {
//		var->hit(attack);
//	}
//}
//
//void SlowBullet::hitInvader(vector<Invader*> invader) {
//	for (auto var : invader) {
//		var->hit(attack);
//		//var->setSlow();
//		var->applyEffect(bulletElement);
//	}
//}
//
//void SlowBullet::print() {
//	Goto_XY(mX, mY);
//	PrintWithColor("$", FOREGROUND_BLUE);
//}
//
//void FireBullet::hitInvader(vector<Invader*> invader) {
//	for (auto var : invader) {
//		var->hit(attack);
//		var->applyEffect(bulletElement);
//	}
//}
//
//void FireBullet::print() {
//	Goto_XY(mX, mY);
//	PrintWithColor(">", FOREGROUND_RED | FOREGROUND_BLUE);
//}