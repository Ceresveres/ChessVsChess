#pragma once
#include "ui-tools.h"
#include <string>

class Game;
class Grid;
class Piece {
protected:
	string name;
	int x{}, y{};
	int dx{}, dy{};
	int counter;
	int speed;
	int HP = 100;
	Image image {};
	Texture2D texture{};
	bool isAttacking = false;
public:
	Piece(const string& name, int speed = 0, string link = "WPawn.png")
		: name{ name }, speed{ speed }, counter{ speed }/*, image{LoadImage(("Textures/" + link).c_str())}*/ {
		Image image{ LoadImage(("Textures/" + link).c_str()) };
		ImageResize(&image, GRID_WIDTH/2, GRID_HEIGHT/2);
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}
	
	void setXY(int ix, int iy) {
		x = ix; y = iy;
		dx = (ix * GRID_WIDTH) + (GRID_WIDTH / 2) ;
		dy = (iy * GRID_HEIGHT) + (GRID_HEIGHT / 2);
	};
	
	virtual void printPiece();
	virtual void printLife();
	virtual void go(Game& nowGame);

	friend class Game;
	friend class Grid;
};

class Pawn :public Piece {
	//Texture2D texture{ LoadTexture("Textures/WPawn.png") };
public:
	Pawn(string name = "PW", int speed = 60, string link = "WPawn.png")
		: Piece{ name, speed, link } {
		this->HP = 200;
	}
	void go(Game& game);
};

class Rook :public Piece {
public:
	Rook(string name = "Ro", int speed = 60, string link = "WRook.png")
		: Piece{ name, speed, link } {}
	void go(Game& game);
};


class Knight :public Piece {
public:
	Knight(string name = "NT", int speed = 1200, string link = "WKnight.png")
		: Piece{ name, speed, link } {}
	//void printPiece();
	void go(Game& game);
}; 

class Bishop :public Piece {
public:
	Bishop(string name = "Bp", int speed = 600, string link = "WBishop.png")
		: Piece{ name, speed, link } {}
	//void printPiece();
	void go(Game& game);
};

class Peasant :public Piece {
public:
	Peasant(string name = "PP", int speed = 30)
		: Piece{ name, speed } {
		this->counter = 0;
	}
	//void printPiece();
	void go(Game& game);
};

/*
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