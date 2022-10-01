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
	int counter{12*1000};
	int speed{12};
	int HP = 100;
	bool isAttacking = false;
public:
	Piece(const LoaderParams* pParams) :
		Object(pParams) {
	}
	
	void setXY(int ix, int iy) { mX = ix; mY = iy; }
	
	virtual void draw(SDL_Renderer& rend);
	virtual void update() {};

	friend class Game;
	friend class Scene;
	friend class Grid;
};

class Scene;
class Pawn :public Piece {
public:
	Pawn(const LoaderParams* pParams, string name = "PW", int speed = 12)
		: Piece{ pParams } {
		this->HP = 200;
	}
	void update();
};

class Rook :public Piece {
public:
	Rook(const LoaderParams* pParams, string name = "Ro", int speed = 6)
		: Piece{ pParams } {}
};


class Knight :public Piece {
public:
	Knight(const LoaderParams* pParams, string name = "NT", int speed = 1200 )
		: Piece{ pParams } {}
	void update();
}; 

class Bishop :public Piece {
public:
	Bishop(const LoaderParams* pParams, string name = "Bp", int speed = 600)
		: Piece{ pParams } {}
	void update();
};

class Peasant :public Piece {
public:
	Peasant(const LoaderParams* pParams, string name = "PP", int speed = 30)
		: Piece{ pParams } {
		this->counter = 0;
	}
	void update();
};