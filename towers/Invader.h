#pragma once

#include <string>
#include <vector>
#include <SDL_render.h>
#include "Object.h"
#include "Scene.h"

using namespace std;

class Invader;
class Modifier;
class Effect {
	void initEffect(int type);
	int damage{ 0 };
	int duration{ 30 };
	int type;
	int tick{ 1 };
public:
	Modifier* modifier = nullptr;
	enum { BURN = 1, SLOW = 2, MAXEFFECTS };
	Effect(int i)
		: type{ i } {initEffect(i); };
	int triggerEffect(Invader& invader);
};

class Invader;
class Modifier {
	enum { SPEED, HP, ATTACK };
public:
	int type{};
	int val{};
	Modifier(int i, int increment)
		: type{ i }, val{ increment } { };
};

class Game;
class Scene;
class Board;
class Invader : public Object {
protected:
	string name{};
	float speed{ .01F };
	int HP{ 100 };
	int attack{ 10 };
	int reward{ 50 };
	
	int attackSpeed{ 4 };
	int attackCounter{ 0 };
	bool remo{ false };
	int step{ 10 };
	int counter{0};

	enum { SHIELD, BURN=1, SLOW=2, MAXEFFECTS };
	vector<Effect*> effects_ {};

public:
	Invader(int x, int y);
	bool attacking = false;
	PositionComponent pos;
	MoveComponent move;
	virtual void update(Uint32 delta);
	virtual void draw(SDL_Renderer& pRenderer);
	virtual void load(const LoaderParams* pParams);

	virtual int getHP() { return HP; };
	virtual int getReward() { return reward; };
	virtual void hit(int damage);


	virtual void removeEffect(Effect* effect);
	virtual void applyEffect(int type) { effects_.push_back(new Effect(type)); };
	virtual void applyModifier(int type) { };
};
//
//class Jumper :public Invader {
//	bool hasJump{ true };
//public:
//	Jumper(string name = "Jump", int speed = 10, int HP = 80, int attack = 20, int reward = 10)
//		: Invader{ name, speed, HP, attack, reward } {
//	}
//	bool move(Board* board);
//};
//
//class Heavy :public Invader {
//public:
//	Heavy(string name = "Hevy", int speed = 50, int HP = 300, int attack = 50, int reward = 60)
//		: Invader{ name, speed, HP, attack, reward } {}
//};
//
//class Shield :public Invader {
//	int shield;
//	bool hasShield{ true };
//	void boostAttributes() { this->speed /= 2; this->attackSpeed /= 2; this->hasShield = false; }
//public:
//	Shield(string name = "Shld", int speed = 20, int HP = 250, int attack = 10, int reward = 70, int shield = 150)
//		: Invader{ name, speed, HP, attack, reward }, shield { shield } {		
//	}
//	void hit(int damage);
//};
