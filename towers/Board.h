#pragma once
#include "ui-tools.h"
#include "Piece.h"
#include "Invader.h"
#include "Bullet.h"

#include <vector>

using namespace std;

class Game;
class Invader;
class Bullet;
class Grid {
	int dx{}, dy{};
	
	Piece* piece = {};
	vector<Invader*> invaders = {};
	
	bool selected{};
	bool flag_refresh{};
	
	void setRefresh() { flag_refresh = true; }
public:
	Grid()
		: selected{ false }, flag_refresh{ false } {}
	
	void setXY(int x, int y);
	void paint();
	
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
	Grid grid[GRID_NUM_X][GRID_NUM_Y];
public:
	void init();
	void printBoard();
	void refresh();
	bool setPiece(int ix, int iy, int type);
	bool travGrid(Game& game);

	friend class Game;
	friend class Invader;
	friend class Jumper;
	friend class Bullet;
	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class Peasant;
};
