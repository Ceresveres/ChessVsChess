#pragma once
#include "ui-tools.h"
#include <string>
#include "Scene.h"
#include <SDL_render.h>
#include "Object.h"

class Game;
class Grid;
class Scene;
class Piece : public Object {
protected:
	string name;
	PositionComponent pos;
	DynamicComponent graphic;
	int counter{ 12 * 1000 };
	int indexI, indexJ;
	int speed{ 12 };
	int HP = 100;
	bool isAttacking = false;
public:
	Piece(int x, int y);
	virtual void draw(SDL_Renderer& rend);
	virtual void update() {};

	friend class Game;
	friend class Scene;
	friend class Grid;
};

class Scene;
class Pawn :public Piece {
public:
	Pawn(int x, int y) : Piece(x, y) {};

	void update();
};

class Rook :public Piece {
public:
	//Rook(const LoaderParams* pParams, string name = "Ro", int speed = 6)
	//	: Piece{ pParams } {}

	Rook(int x, int y) : Piece(x, y) {};

};


class Knight :public Piece {
public:
	//Knight(const LoaderParams* pParams, string name = "NT", int speed = 1200 )
	//	: Piece{ pParams } {}
	Knight(int x, int y) : Piece(x, y) {};

	void update();
}; 

class Bishop :public Piece {
public:
	//Bishop(const LoaderParams* pParams, string name = "Bp", int speed = 600)
	//	: Piece{ pParams } {}
	Bishop(int x, int y) : Piece(x, y) {};

	void update();
};

class Peasant :public Piece {
public:
	Peasant(int x, int y) : Piece(x, y) {
		this->counter = 0;
	}
	void update();
};