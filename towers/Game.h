#pragma once

#include "ui-tools.h"
#include "Timer.h"
#include <SDL.h>
#include <stdio.h>
#include "GameState.h"
#include "GameStateMachine.h"
#include "Object.h"
#include "PlayState.h"

#include<list>

enum State {
	NONE = 0,
	RUNNING = 1,
	END = 2,
	GAMEOVER = 3
};

class Game {
	SDL_Window* window { SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	SDL_Renderer* renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	TextureManager* textureManager{ nullptr };

	LTimer fpsTimer;
	int frameCount = 0;
	float averageFPS = 0;

	GameStateMachine* gameStateMachine{};
	State gameState = NONE;

	SDL_Event e;

	Uint32 fps_counter = 0;

	void update();
	void updateFPS(Uint32 delta);
	void processEvents();
	void onStartUp();
	void render();	
	void loop();
	Game()
	{
		onStartUp();
	}	

public:
	static Game* GetSingleton();
	
	SDL_Renderer* GetRenderer() { return renderer; };

	float getAverageFPS() { return averageFPS; };
};