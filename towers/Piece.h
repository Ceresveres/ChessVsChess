#pragma once
#include "ui-tools.h"
#include <string>

class Game;
class Grid;
class Piece {
protected:
	string name;
	int x, y;
	int HP = 100;
	int speed = 12;
	bool isAttacking;
	void init(const string& iname) {
		name = iname;
	}

	//friend class Grid;

public:
	void setXY(int ix, int iy) { x = ix; y = iy; }
	void printPiece();
	//void go(Game& game);
	//bool move(Board& board);
	virtual void go(Game& nowGame) {}

	friend class Game;
	friend class Grid;
};

class Pawn :public Piece {
	int counter = 0;
	int speed = 12;
	int attack = 20;
public:
	Pawn() {
		init("PW");
	}
	void go(Game& game);
};

class Rook :public Piece {
	int counter = 0;
	int speed = 6;
	int attack = 12;
public:
	Rook() {
		init("Ro");
	}
	void go(Game& game);
};


class Knight :public Piece {
	int counter = 0;
	int attack = 50;
	int speed;
public:
	Knight() {
		init("NT");
		//counter = 0;
		speed = 6;
	}
	void go(Game& game);
}; 



/*
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
*/