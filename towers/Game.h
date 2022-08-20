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

	int makeCounter = 0;
	int makeSpeed = 30;

	void openFocus();
	void building();
	void makeInvaders();
	void addInvader(int x, int y, int type);
	bool moveInvader();
	void clearInvader();
	
	void printBullet();
	void moveBullet();
	
	

public:
	Game(int x = 0, int y = 0, int makeCounter = 0, int makeSpeed = 30)
		: x(x), y(y), makeCounter(makeCounter), makeSpeed(makeSpeed) {
		HHideCursor();
		SSetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib [core] example - basic window");

		//InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib [core] example - basic window");
	}
	void init();
	void loop();
	void addBullet(Bullet* p);

	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class Peasant;
};