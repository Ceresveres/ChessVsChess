#pragma once
#include "ui-tools.h"
#include <string>

class Game;
class Grid;
class Piece {
protected:
	string name{};
	int x{}, y{};
	int counter;
	int speed;
	int HP = 100;
	bool isAttacking = false;
	//void init(const string& iname) {
	//	name = iname;
	//}
	
public:
	Piece(const string& name, int speed = 0)
		: name{ name }, speed{ speed }, counter{ speed } {}
	
	void setXY(int ix, int iy) { x = ix; y = iy; }
	
	virtual void printPiece();
	virtual void printLife();
	virtual void go(Game& nowGame) {}

	friend class Game;
	friend class Grid;
};

class Pawn :public Piece {
public:
	Pawn(string name = "PW", int speed = 12)
		: Piece{ name, speed } {
		this->HP = 200;
	}
	void go(Game& game);
};

class Rook :public Piece {
public:
	Rook(string name = "Ro", int speed = 6)
		: Piece{ name, speed } {}
	void go(Game& game);
};


class Knight :public Piece {
public:
	Knight(string name = "NT", int speed = 1200 )
		: Piece{ name, speed } {}
	void printPiece();
	void go(Game& game);
}; 

class Bishop :public Piece {
public:
	Bishop(string name = "Bp", int speed = 600)
		: Piece{ name, speed } {}
	void printPiece();
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