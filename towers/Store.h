#pragma once
#include "ui-tools.h"
#include<string>

class Game;
class Store;
class Board;

class PieceCard {
	int index;
	string name;
	bool flag;
public:
	void init(int i, const string& iname) {
		index = i;
		name = iname;
		flag = false;
	}
	void setSelect() { flag = true; }

};

class Store {
	PieceCard pieces[6];
public:
	Store() {
		pieces[0].init(0, "Pawn");
		pieces[1].init(1, "Rook");
		pieces[2].init(2, "Knight");
		pieces[3].init(3, "Bishop");
		pieces[4].init(4, "King");
		pieces[5].init(5, "Queen");
	}
	void init();

	friend class Game;
};