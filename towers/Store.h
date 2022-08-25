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

	friend class Store;
public:
	PieceCard(int index = 0, const string& name = "blank", int cost=0)
		: index{ index }, name{ name }, cost{ cost }, flag{ false } {}

	void setSelect() { flag = true; }
	void print();
};

class Store {
private:
	PieceCard* pieces[MAX];
	int money{100};
	void refreshMoney();
	Store() {
		pieces[0] = new PieceCard(1, "Pawn", 50);
		pieces[1] = new PieceCard(2, "Rook", 100);
		pieces[2] = new PieceCard(3, "Knight", 125);
		pieces[3] = new PieceCard(4, "Bishop", 125);
		pieces[4] = new PieceCard(5, "Peasant", 25);
	}
	void init();
public:
	static Store* GetInstance();
	
	virtual void addMoney(int reward) { money += reward; refreshMoney(); }

	bool buy(int choice, int x, int y, Board* board);
};