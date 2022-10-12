//#include "Bullet.h"
//#include "ui-tools.h"
//
//Bullet::Bullet(int x, int y) :pos(x, y), 
//							  move(speed), 
//							  size(50, 5) {}
//
//void Bullet::draw() {
//	int tmpColor[4] = { 3, 3, 3, 255 };
//	SDL_Rect gridRect = { pos.x,  pos.y, size.mWidth, size.mHeight };
//	TextureManager::GetSingletonInstance()->drawTemp(gridRect, tmpColor);
//}
//
//void Bullet::update(Uint32 delta) {
//	move.UpdatePosition(delta, pos);
//	if (pos.x >= SCREEN_WIDTH) { hit = true; }
//}
//
////void Bullet::hitInvader(vector<Invader*> invaders) {
////	for (auto var : invaders) {
////		var->hit(attack);
////	}
////}
////
////void SlowBullet::hitInvader(vector<Invader*> invader) {
////	for (auto var : invader) {
////		var->hit(attack);
////		//var->setSlow();
////		var->applyEffect(bulletElement);
////	}
////}
////
////void SlowBullet::print() {
////	Goto_XY(mX, mY);
////	PrintWithColor("$", FOREGROUND_BLUE);
////}
////
////void FireBullet::hitInvader(vector<Invader*> invader) {
////	for (auto var : invader) {
////		var->hit(attack);
////		var->applyEffect(bulletElement);
////	}
////}
////
////void FireBullet::print() {
////	Goto_XY(mX, mY);
////	PrintWithColor(">", FOREGROUND_RED | FOREGROUND_BLUE);
////}