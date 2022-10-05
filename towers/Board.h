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
	Piece* piece = {};
	vector<Invader*> invaders = {};
	PositionComponent pos;

	bool selected{false};
	bool flag_refresh{true};	
	void setRefresh() { flag_refresh = true; }
public:
	Grid(int x, int y);
	
	virtual void draw(SDL_Renderer& pRenderer);

	void judgeAttacking();
	void attackPiece(int attack);
	bool setPiece(Piece* piece);
	void delPiece();
	//virtual void load(const LoaderParams* pParams);
	void setColor(int choice);
	void addInvader(Invader* iInvader);
	void damageInvader(Invader* iInvader, int damage);
	void delInvader(Invader* iInvader);
	
	void setSelected() { selected = true; flag_refresh = true; }
	void setUnSelected() { selected = false; flag_refresh = true; }

	friend class Board;
	friend class Bullet;
	//friend class Piece;
	//friend class Pawn;
	//friend class Knight;
	//friend class Rook;
	friend class Bishop;
	friend class Peasant;
};

class Board : public Object {	
	SDL_Renderer* m_renderer = NULL;
	//void init();
	bool m_kReleased = false;
	int x {0}, y {0};
	vector<Invader*> invaders = {};
	//Board() {init(); }
	Board();
	Board(const LoaderParams* pParams);
public:
	static Board* GetSingleton();
	Scene* scene {nullptr};
	virtual void update();
	void addInvader(int x, int y, Invader* iInvader);
	virtual void draw(SDL_Renderer& pRenderer);
	bool inLineOfSight(int x, int y);
	bool setPiece(int type);
	bool travGrid();
	vector<vector<Grid>> grid;

	PositionComponent pos;

	void handleInput();
	void handleSelection(const int ix = 0, const int iy = 0);
	friend class Invader;
	friend class Jumper;
	friend class Bullet;
	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class Peasant;
};