#pragma once
#include "ui-tools.h"
#include "Piece.h"
#include "Invader.h"
#include "Bullet.h"
#include <SDL_render.h>

#include <vector>
#include <SDL_events.h>

using namespace std;

class Game;
class Invader;
class Bullet;
class Grid {
	int dx{}, dy{};
	int x{}, y{};
	Piece* piece = {};
	vector<Invader*> invaders = {};
	
	bool selected{};
	bool flag_refresh{};

	//SDL_Renderer* m_renderer = NULL;
	
	void setRefresh() { flag_refresh = true; }
public:
	Grid()
		: selected{ false }, flag_refresh{ false } {}
	
	void setXY(int x, int y);
	void paint(SDL_Renderer& rend);
	//void init(SDL_Renderer& rend);
	
	void judgeAttacking();
	void attackPiece(int attack);
	
	bool setPiece(Piece* piece);
	void delPiece();
	
	void addInvader(Invader* iInvader);
	void damageInvader(Invader* iInvader, int damage);
	void delInvader(Invader* iInvader);
	
	void setSelected() { selected = true; flag_refresh = true; }
	void setUnSelected() { selected = false; flag_refresh = true; }

	friend class Board;
	friend class Bullet;
	friend class Piece;
	friend class Pawn;
	friend class Knight;
	friend class Rook;
	friend class Bishop;
	friend class Peasant;
};

class Board {
	
	SDL_Renderer* m_renderer = NULL;
	void init();
	int x {0}, y {0};
	Board(SDL_Renderer& rend)
		: m_renderer{ &rend } {init(); }
public:
	//void printBoard();
	Grid grid[GRID_NUM_X][GRID_NUM_Y];
	void printBoard(SDL_Renderer& rend);
	void refresh(SDL_Renderer& rend);
	bool setPiece(int type);
	bool travGrid(Game& game);
	static Board* GetInstance(SDL_Renderer& renderer);
	void update();
	void handleInput(SDL_Event& e);
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