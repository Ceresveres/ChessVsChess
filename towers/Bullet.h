#pragma once

#include "Invader.h"
#include <vector>
#include "Object.h"
#include <SDL_render.h>

class Board;
class Bullet : public Object {
protected:
	enum Type { NORMAL, FIRE, ICE };
	int dx{}, dy{};
	int attack{25};
	const int BULLET_WIDTH = 20;
	const int BULLET_HEIGHT = 20;
	int bullet_velocity = 10;

	int bulletElement{ NORMAL };
	
public:
	Bullet(const LoaderParams* pParams, int x, int y);

	
	void setXY(int dx, int dy);
	bool hit{false};
	virtual void draw(SDL_Renderer& rend);
	virtual void update();
	PositionComponent pos;

	//virtual void hitInvader(vector<Invader*> invaders);
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