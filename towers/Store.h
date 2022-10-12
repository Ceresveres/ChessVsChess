//#pragma once
//#include "ui-tools.h"
//#include<string>
//#include <SDL_render.h>
//#include "Object.h"
//
//class Game;
//class Sccene;
//class Store;
//class Board;
//class PieceCard {
//	int index{};
//	int cost{};
//	string name{};
//	bool flag;
//
//	friend class Store;
//public:
//	PieceCard(int index = 0, const string& name = "blank", int cost=0)
//		: index{ index }, name{ name }, cost{ cost }, flag{ false } {}
//
//	void setSelect() { flag = true; }
//
//	void draw();
//};
//
//class Store : public Object {
//private:
//	PieceCard* pieces[MAXPIECECOUNT];
//	int money{100000};
//	Store();
//public:
//	static Store* GetSingleton();
//	void init();
//	void draw();
//
//
//	virtual void addMoney(int reward) { money += reward; }
//	bool buy(int choice, Board* board);
//};