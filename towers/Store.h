#pragma once
#include "ui-tools.h"
#include<string>

class Game;
class Store;
class Board;

class PieceCard {
	int index{};
	int cost{};
	string name{};
	bool flag;
public:
	PieceCard(int index = 0, const string& name = "blank", int cost=0)
		: index{ index }, name{ name }, cost{ cost }, flag{ false } {}

	void setSelect() { flag = true; }
	void print();
};

class Store {
	PieceCard* pieces[SHIELD+1];
public:
	Store() {
		pieces[0] = new PieceCard(0, "Pawn", 50);
		pieces[1] = new PieceCard(1, "Rook", 100);
		pieces[2] = new PieceCard(2, "Knight", 125);
		pieces[3] = new PieceCard(3, "Bishop", 125);
	}
	void init();

	friend class Game;
};