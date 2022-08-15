#pragma once

#include "Board.h"
#include "ui-tools.h"
#include "Store.h"
#include "Piece.h"
#include "Bullet.h"
#include "Invader.h"

#include<list>
using namespace std;

class Game {
	Board board;
	Store store;

	list<Invader*> invaders = {};

	list<Bullet*> bullets = {};

	int x, y;

	void building();
	void openFocus();
	bool moveInvader();
	void printBullet();
	void moveBullet();
	void addInvader(int x, int y);
	void clearInvader();

public:
	Game();
	void init();
	void loop();
	void addBullet(Bullet* p);

	//void movePieces();

	friend class Pawn;
	friend class Rook;
	friend class Knight;
};