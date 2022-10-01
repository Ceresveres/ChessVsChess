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
#include "GameState.h"
#include "GameStateMachine.h"
#include "Object.h"
#include "PlayState.h"

#include<list>
using namespace std;

enum State {
	NONE = 0,
	RUNNING = 1,
	END = 2,
	GAMEOVER = 3
};

class Game {
	SDL_Window* window { SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	SDL_Renderer* m_pRenderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };

	Board* board { Board::GetSingleton() };
	Store* store { Store::GetSingleton() };

	LTimer fpsTimer;
	int frameCount = 0;
	float mAverageFPS = 0;

	GameStateMachine* m_pGameStateMachine{};
	State gameState = NONE;

	SDL_Event e;

	Uint32 fps_counter = 0;

	void update();
	void updateFPS(Uint32 delta);
	void processEvents();
	void onStartUp();
	void render();	
	void loop();
	Game(int x = 0, int y = 0, int makeCounter = 0, int makeSpeed = 30)
	{
		onStartUp();
	}	

public:
	static Game* GetSingleton();
	
	SDL_Renderer* GetRenderer() { return m_pRenderer; };

	float getAverageFPS() { return mAverageFPS; };
};