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

	int speed;
	int HP;
	int attack;
	int reward;
	
	int attackSpeed{ 4 };
	int attackCounter{ 0 };

	int counter{0};
	
	bool slow = false;
	int slowCounter{ 0 };
	int slowTime{ 20 };

	bool burn = false;
	int burnDamage{ 11 };
	int burnCounter{ 0 };
	int burnTick{ 3 };
	int burnTime{ 30 };
	
	bool attacking = false;

	virtual void printName();
	virtual void printLife();
public:
	Invader(const string& name = "Basic", int speed = 10, int HP = 100, int attack = 10, int reward = 50)
		: name{ name }, speed{ speed }, HP{ HP }, attack{ attack }, reward{ reward } {}
	
	void setXY(int ix, int iy) { x = ix; y = iy; }
	
	virtual void hit(int damage);
	virtual bool move(Board* board);	
		
	virtual void setSlow() { slow = true; slowCounter = 0; };

	virtual void setBurn() { burn = true; burnCounter = 0; };

	
	friend class Game;
	friend class Grid;
};

class Jumper :public Invader {
	bool hasJump{ true };
public:
	Jumper(string name = "Jump", int speed = 10, int HP = 80, int attack = 20, int reward = 10)
		: Invader{ name, speed, HP, attack, reward } {
	}
	bool move(Board* board);
};

class Heavy :public Invader {
public:
	Heavy(string name = "Hevy", int speed = 50, int HP = 300, int attack = 50, int reward = 60)
		: Invader{ name, speed, HP, attack, reward } {
		this->attackSpeed = 6;
	}
};

class Shield :public Invader {
	int shield;
	bool hasShield{ true };
	void boostAttributes() { this->speed /= 2; this->attackSpeed /= 2; this->hasShield = false; }
public:
	Shield(string name = "Shld", int speed = 20, int HP = 250, int attack = 10, int reward = 70, int shield = 150)
		: Invader{ name, speed, HP, attack, reward }, shield { shield } {		
	}
	void setSlow();
	void setBurn();
	void hit(int damage);
	void printName();
};
