#pragma once
#include "ui-tools.h"
#include <string>

class Game;
class Board;
class Piece {
protected:
	string name;
	int x, y;
	int counter = 0;
	void init(const string& iname) {
		name = iname;
	}

	//friend class Grid;

public:
	void setXY(int ix, int iy) { x = ix; y = iy; }
	void printPiece();
	bool move(Board& board);

	friend class Game;
	friend class Grid;
};

class Pawn :public Piece {
public:
	Pawn() {
		init("PW");
	}

};

class Knight :public Piece {
public:
	Knight() {
		init("NT");
	}

}; 

class Rook :public Piece {
public:
	Rook() {
		init("Ro");
	}

};

class Bishop :public Piece {
public:
	Bishop() {
		init("Bp");
	}

};

class King :public Piece {
public:
	King() {
		init("Kn");
	}

};

class Queen :public Piece {
public:
	Queen() {
		init("Qu");
	}

};