#pragma once
#include "ui-tools.h"
#include "Piece.h"

#include <vector>

using namespace std;

class Game;
class Grid {
	int dx, dy;
	////Piece* piece = {};
	vector<Piece*> pieces = {};
	bool selected;
	bool flag_refresh;
public:
	Grid() { selected = false; flag_refresh = false; }
	void setXY(int x, int y);
	void paint();
	bool setPiece(Piece* piece);
	//void delPiece(Piece* ipiece);
	void setSelected() { selected = true; flag_refresh = true; }
	void setUnSelected() { selected = false; flag_refresh = true; }

	friend class Board;
	friend class Piece;
	friend class Pawn;
};

class Board {
	Grid grid[GRID_NUM_X][GRID_NUM_Y];
public:
	void init();
	void printBoard();
	void refresh();
	bool setPiece(int ix, int iy, char type);

	friend class Game;
	friend class Enemy;
	friend class Piece;
	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class King;
	friend class Queen;
};