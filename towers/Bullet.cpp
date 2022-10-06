#include "Bullet.h"
#include "ui-tools.h"

Bullet::Bullet(int x, int y) : Object(new LoaderParams(5, 5)), pos(x, y), move(x, y, speed) {}

void Bullet::draw(SDL_Renderer& rend) {
	SDL_Rect gridRect = { pos.x,  pos.y, 5, 5 };
	SDL_SetRenderDrawColor(&rend, 3, 252, 98, 255);
	SDL_RenderFillRect(&rend, &gridRect);
}

void Bullet::update(Uint32 delta) {
	move.UpdatePosition(delta, pos);
	if (pos.x >= SCREEN_WIDTH) { hit = true; }
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