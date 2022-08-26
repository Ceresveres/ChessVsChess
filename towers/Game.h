#pragma once

#include "Board.h"
#include "ui-tools.h"
#include "Store.h"
#include "Piece.h"
#include "Bullet.h"
#include "Invader.h"
#include <SDL.h>
#include <stdio.h>

#include<list>
using namespace std;

class Game {
	SDL_Window* window { SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	SDL_Renderer* rend { SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) };

	Board* board { Board::GetInstance(*rend) };
	Store* store { Store::GetInstance(*rend) };

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
	void initializeSDL();

	Game(int x = 0, int y = 0, int makeCounter = 0, int makeSpeed = 30)
		: x(x), y(y), makeCounter(makeCounter), makeSpeed(makeSpeed)
		//window{ SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) },
		//rend { SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) },
		//board { Board::GetInstance(*rend) }, store { Store::GetInstance() }
	{
		//initializeSDL();

	}	

public:

	static Game* GetInstance();
	void loop();
	void addBullet(Bullet* p);

	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class Peasant;
};