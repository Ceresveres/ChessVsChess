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
	float speed{ 3.0F };
	int attack{ 10 };
	int reward{ 50 };
	
	int attackSpeed{ 4 };
	int attackCounter{ 0 };
	bool remo{ false };
	int step{ 10 };
	int counter{0};
	Scene* scene = nullptr;
	enum { SHIELD, BURN=1, SLOW=2, MAXEFFECTS };
	vector<Effect*> effects_ {};

public:
	Invader(int x, int y);
	bool attacking = false;
	HealthComponent health{ 100 };

	PositionComponent pos;
	MoveComponent move;
	SizeComponent size;
	virtual void update(Uint32 delta);
	virtual void draw();
	DynamicComponent graphic;
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

template <class Invader> class ObjectFactory
{
public:
	ObjectFactory() : _head(NULL), _tail(NULL) {}

	static ObjectFactory<Invader>& getInstance()
	{
		static ObjectFactory<Invader> instance;
		return instance;
	}

	~ObjectFactory()
	{
		while (_head)
		{
			InvaderNode* next = _head->_next;
			delete _head;
			_head = next;
		}
	}

	Invader* AcquireObject(int x, int y)
	{
		if (_head)
		{
			InvaderNode* oldNode = _head;

			if (_head == _tail) _head = _tail = NULL;
			else
			{
				_head = _head->_next;
				if (_head) _head->_prev = NULL;
			}
			return &oldNode->sInvader;
		}
		else
		{
			// There's nothing in our free-list to re-use!  Hand the user a new object instead.
			InvaderNode* newNode = new InvaderNode;
			return &newNode->sInvader;
		}
	}

	void ReleaseObject(Invader* invader)
	{
		// reset (obj) back to its default-constructed state
		// (this might not be necessary, depending what your Objects represent)
		//(*obj) = Object();

		InvaderNode* node = reinterpret_cast<InvaderNode*>(invader);   // this works only because _object is the first item in the ObjectNode struct
		if (_head)
		{
			// Prepend our node back to the start of our free-nodes-list
			node->_prev = NULL;
			node->_next = _head;
			_head->_prev = node;
			_head = node;
		}
		else
		{
			// We were empty; now will have just this one ObjectNode in the free-list
			_head = _tail = node;
			node->_prev = node->_next = NULL;
		}
	}
//private:
public:
	class InvaderNode
	{
	public:
		Invader sInvader;
		InvaderNode* _prev;
		InvaderNode* _next;
	};

	InvaderNode * _head;  // first item in our free-nodes-list, or NULL if we have no available free nodes
	InvaderNode* _tail;
};