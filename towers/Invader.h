#pragma once
#include "ui-tools.h"
#include <string>

using namespace std;

class Game;
class Board;
class Invader {
protected:
	string name{};
	int x{}, y{};
	
	int counter{0};

	int attackCounter{ 0 };
	
	int speed{};
	
	bool slow = false;
	int slowCounter{ 0 };
	int slowTime{ 20 };

	bool burn = false;
	int burnDamage{ 11 };
	int burnCounter{ 0 };
	int burnTick{ 3 };
	int burnTime{ 30 };
	
	bool attacking = false;
	int attack = 10;
	int attackSpeed{};
	int HP = 100;
	virtual void printName();
	virtual void printLife();
public:
	Invader(const string& name = "Basic", int speed = 10, int HP = 100, int attackSpeed = 3)
		: name{ name }, speed{ speed }, HP{ HP }, attackSpeed{ attackSpeed } {}
	
	void setXY(int ix, int iy) { x = ix; y = iy; }
	
	virtual void hit(int damage);
	virtual bool move(Board& board);	
	
	virtual void setSlow() { slow = true; slowCounter = 0; };

	virtual void setBurn() { burn = true; burnCounter = 0; };

	
	friend class Game;
	friend class Grid;
};

class Jumper :public Invader {
	bool hasJump{ true };
public:
	Jumper(string name = "Jump", int speed = 10, int HP = 80)
		: Invader{ name, speed, HP } {
		this->attack = 20;
	}
	bool move(Board& board);
};

class Heavy :public Invader {
public:
	Heavy(string name = "Hevy", int speed = 50, int HP = 300, int attackSpeed = 6)
		: Invader{ name, speed, HP } {
		this->attack = 50;
	}
};

class Shield :public Invader {
	int shield{};
	bool hasShield{ true };
	void boostAttributes() { this->speed = this->speed / 2; this->attackSpeed = this->attackSpeed / 2; this->hasShield = false; }
public:
	Shield(string name = "Shld", int speed = 20, int HP = 250, int attackSpeed = 10)
		: Invader{ name, speed, HP } {
		this->shield = 150;
	}
	void setSlow();
	void setBurn();
	void hit(int damage);
	void printName();
};