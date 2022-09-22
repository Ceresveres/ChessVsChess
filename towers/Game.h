#pragma once

#include "Board.h"
#include "ui-tools.h"
#include "Store.h"
#include "Piece.h"
#include "Bullet.h"
#include "Invader.h"
#include "Timer.h"
#include <SDL.h>
#include <stdio.h>

#include<list>
using namespace std;

class Game {
	SDL_Window* window { SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	SDL_Renderer* rend { SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };

	Board* board { Board::GetInstance(*rend) };
	Store* store { Store::GetInstance(*rend) };
	LTimer fpsTimer;

	list<Invader*> invaders = {};

	list<Bullet*> bullets = {};

	int x, y;

	int makeCounter = 0;
	int makeSpeed = 30;

	int frameCount = 0;
	float mAverageFPS = 0;
	Uint32 fps_counter = 0;

	void openFocus();
	void building();
	void makeInvaders();
	void addInvader(int x, int y, int type);
	bool moveInvader();
	void clearInvader();
	void update(Uint32 timestep);
	void printBullet();
	void updateFPS(Uint32 delta);
	void moveBullet();
	void initializeSDL();

	void onStartUp();

	//float getAverageFPS();
	

	Game(int x = 0, int y = 0, int makeCounter = 0, int makeSpeed = 30)
		: x(x), y(y), makeCounter(makeCounter), makeSpeed(makeSpeed)
		//window{ SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) },
		//rend { SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) },
		//board { Board::GetInstance(*rend) }, store { Store::GetInstance() }
	{
		//initializeSDL();
		onStartUp();
	}	

public:

	static Game* GetInstance();
	void loop();
	void addBullet(Bullet* p);
	float getAverageFPS() { return mAverageFPS; };
	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class Peasant;
};