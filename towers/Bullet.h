#pragma once

#include "Invader.h"
#include <vector>

class Board;
class Bullet {
protected:
	int dx{}, dy{};
	int x{}, y{};
	int attack{};
public:
	Bullet(int attack = 25)
		: attack{ attack }, hit{ false } {}
	
	void setXY(int dx, int dy);
	virtual void print();
	bool hit;
	void move(Board* board);
	virtual void hitInvader(vector<Invader*>& invader);
	
	friend class Grid;
};

class SlowBullet :public Bullet {
	void print();
	void hitInvader(vector<Invader*>& invader);
public:
	SlowBullet(int attack = 25)
		: Bullet(attack) {}
	
};

class FireBullet :public Bullet {
	void print();
	void hitInvader(vector<Invader*>& invader);
public:
	FireBullet(int attack = 25)
		: Bullet(attack) {}

};