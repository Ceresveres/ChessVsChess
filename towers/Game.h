#pragma once
#include "Board.h"
#include "ui-tools.h"
#include "Store.h"
#include "Piece.h"

class Game {
	Board board;
	Store store;

	int x, y;

	void building();

	void openFocus();

public:
	Game();
	void init();
	void loop();
};