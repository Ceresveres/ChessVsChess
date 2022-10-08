#pragma once
#include "ui-tools.h"
#include "Piece.h"
#include "Invader.h"
#include "Bullet.h"
#include <SDL_render.h>
#include "InputHandler.h"
#include "Object.h"

#include <vector>
#include <SDL_events.h>

using namespace std;

class Game;
class Piece;
class Invader;
class Bullet;
class Grid : public Object {
	int color[4]{};
	Piece* piece = {nullptr};
	vector<Invader*> invaders = {};
	PositionComponent pos;
	SizeComponent size;
	Board* board;
	bool selected{false};
	bool flag_refresh{true};	
	void setRefresh() { flag_refresh = true; }
public:
	Grid(int x, int y, Board* pboard);
	virtual void draw();
	void judgeAttacking();
	void attackPiece(int attack);
	bool setPiece();
	void delPiece();
	void setColor(int choice);
	void addInvader(Invader* iInvader);
	void damageInvader(Invader* iInvader, int damage);
	void delInvader(Invader* iInvader);
	
	void setSelected() { selected = true; flag_refresh = true; }
	void setUnSelected() { selected = false; flag_refresh = true; }

	friend class Board;
	friend class Bullet;
};


class Board : public Object {	
	SDL_Renderer* m_renderer = NULL;
	bool m_kReleased = false;
	int x {0}, y {0};
	vector<Invader*> invaders = {};
	void handleSelection(const int ix = 0, const int iy = 0);

	PositionComponent pos;

	Board();
public:
	static Board* GetSingleton();
	void SetEventBus(EventBus* eventBus) { this->eventBus = eventBus;  }
	vector<vector<Grid>> grid;
	EventBus* eventBus{};
	bool setPiece(int type);
	void addInvader(int x, int y, Invader* iInvader);

	void handleInput();
	virtual void update();
	virtual void draw();

	void onCollisionEvent(CollisionEvent* collision);
	bool inLineOfSight(int x, int y);
	bool travGrid();
	
	friend class Invader;
	friend class Jumper;
	friend class Bullet;
	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class Peasant;
};