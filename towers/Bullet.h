#pragma once

#include "Invader.h"
#include <vector>
#include <SDL_render.h>

class Board;
class Bullet {
protected:
	enum Type { NORMAL, FIRE, ICE };
	int dx{}, dy{};
	int x{}, y{};
	int attack{};
	const int BULLET_WIDTH = 20;
	const int BULLET_HEIGHT = 20;
	int bullet_velocity = 10;

	int bulletElement{ NORMAL };
	
public:
	Bullet(int attack = 25, int bulletElement = NORMAL)
		: attack{ attack }, hit{ false }, bulletElement{ bulletElement } {}
	
	void setXY(int dx, int dy);
	void updateXY();
	virtual void print(SDL_Renderer& rend);
	bool hit;
	void render();
	void move(Board* board);
	virtual void hitInvader(vector<Invader*>& invader);
	
	friend class Grid;
};

class SlowBullet :public Bullet {
	void print();
	void hitInvader(vector<Invader*>& invader);
public:
	SlowBullet(int attack = 25, int bulletElement = ICE)
		: Bullet(attack, bulletElement) {}
	
};

class FireBullet :public Bullet {
	void print();
	void hitInvader(vector<Invader*>& invader);
public:
	FireBullet(int attack = 25, int bulletElement = FIRE)
		: Bullet(attack, bulletElement) {}

};