#pragma once
#include "Board.h"
#include "ui-tools.h"
#include "Store.h"
#include "Piece.h"
#include "Invader.h"

#include<list>

class Game {
	Board board;
	Store store;
	list<Invader*> invaders;
	int x, y;

	void building();

	void openFocus();

public:
	Game();
	void init();
	void loop();
	void addInvader();
	//void movePieces();
};