#pragma once

#include "Invader.h"
#include <vector>

class Board;
class Bullet {
protected:
	int dx, dy;
	int x, y;
	int attack = 1;
public:
	Bullet();
	void setXY(int dx, int dy);
	virtual void print();
	bool hit = false;
	virtual void hitInvader(vector<Invader*>& invader);
	void move(Board& board);
	
	friend class Grid;
};

class SlowBullet :public Bullet {
	void print();
	void hitInvader(vector<Invader*>& invader);
};