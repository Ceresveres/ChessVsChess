#pragma once

#include <vector>
#include "Object.h"
#include <SDL_render.h>

class Bullet : public Object {
protected:
	enum Type { NORMAL, FIRE, ICE };
	int attack{25};
	const int BULLET_WIDTH = 20;
	const int BULLET_HEIGHT = 20;
	int bullet_velocity = 10;
	float speed{ 2 };
	int bulletElement{ NORMAL };
	
public:
	Bullet(int x, int y);
	bool hit{false};
	virtual void draw(SDL_Renderer& rend);
	virtual void update(Uint32 delta);
	PositionComponent pos;
	MoveComponent move;
};

//class SlowBullet :public Bullet {
//	void print();
//	void hitInvader(vector<Invader*> invader);
//public:
//	SlowBullet(int attack = 25, int bulletElement = ICE)
//		: Bullet(attack, bulletElement) {}
//	
//};
//
//class FireBullet :public Bullet {
//	void print();
//	void hitInvader(vector<Invader*> invader);
//public:
//	FireBullet(int attack = 25, int bulletElement = FIRE)
//		: Bullet(attack, bulletElement) {}
//
//};