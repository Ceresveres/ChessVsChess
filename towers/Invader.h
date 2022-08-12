#pragma once
#include "ui-tools.h"
#include <string>

using namespace std;

class Game;
class Board;
class Invader {
protected:
	string name;
	int x, y;
	int counter = 0;
	int speed = 10;
	bool attacking;
	int attack = 10;
	int HP = 100;
public:
	void setXY(int ix, int iy) { x = ix; y = iy; }
	virtual bool move(Board& board);
	virtual void hit(int attack) { HP -= attack; }
	friend class Game;
	friend class Grid;
};