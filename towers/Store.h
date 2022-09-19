#pragma once
#include "ui-tools.h"
#include<string>
#include <SDL_render.h>

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
	void print(SDL_Renderer& rend);
};

class Store {
private:
	SDL_Renderer* m_renderer = NULL;
	PieceCard* pieces[MAXPIECECOUNT];
	int money{100000};
	void refreshMoney();
	Store(SDL_Renderer& rend)
		: m_renderer{ &rend } {
		pieces[0] = new PieceCard(1, "Pawn", 50);
		pieces[1] = new PieceCard(2, "Rook", 100);
		pieces[2] = new PieceCard(3, "Knight", 125);
		pieces[3] = new PieceCard(4, "Bishop", 125);
		pieces[4] = new PieceCard(5, "Peasant", 25);
	}
public:
	static Store* GetInstance(SDL_Renderer& rend);
	void printStore(SDL_Renderer& rend);
	
	virtual void addMoney(int reward) { money += reward; refreshMoney(); }

	bool buy(int choice, int x, int y, Board* board);
};