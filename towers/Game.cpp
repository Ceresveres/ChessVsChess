#include "Game.h"
#include <conio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include <iostream>
#include "InputHandler.h"


static Game* game = nullptr;

Game* Game::GetSingleton() {
	if (game == nullptr) {
		game = new Game();
	}
	return game;
}

void Game::onStartUp() {
	fpsTimer.start();
	gameState = RUNNING;
	textureManager = TextureManager::GetSingleton(renderer);
	gameStateMachine = new GameStateMachine();
	gameStateMachine->changeState(new PlayState(textureManager));
	loop();
}

// Fps helper counter
void Game::updateFPS(Uint32 delta) {
	if (frameCount < 10) {
		fps_counter += delta;
	} else {
		this->averageFPS = (float)fps_counter / ((float)frameCount * 1000.0f);
		fps_counter = 0;
		frameCount = 0;
	}
	frameCount++;
}

// Core game loop
void Game::loop() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	while (gameState == RUNNING)
	{
		// handle input
		processEvents();

		// update physics logic
		update();

		// display
		render();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	_CrtDumpMemoryLeaks();
	SDL_Quit();

}

// Handles the rendering and graphic updates
void Game::render() {
	SDL_RenderClear(renderer);
	gameStateMachine->render();
	SDL_RenderPresent(renderer);
}

// handles the input
void Game::processEvents() {
	InputHandler::GetSingleton()->update();
	if (InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		//m_pGameStateMachine->changeState(new PlayState());
	}
	//board->update();
	//while (SDL_PollEvent(&e) != 0)
	//{
	//	if (e.type == SDL_QUIT)
	//	{
	//		gameState = END;
	//		break;
	//	}
	//	else if (e.type == SDL_KEYDOWN)
	//	{
	//		//Start/stop
	//		if (e.key.keysym.sym == SDLK_s)
	//		{
	//			if (timer.isStarted())
	//			{
	//				getAverageFPS();
	//				timer.stop();
	//			}
	//			else
	//			{
	//				timer.start();
	//			}
	//		}
	//		//Pause/unpause
	//		else if (e.key.keysym.sym == SDLK_p)
	//		{
	//			if (timer.isPaused())
	//			{
	//				timer.unpause();
	//			}
	//			else
	//			{
	//				timer.pause();
	//			}
	//		}
	//	}
	//	if (e.type == SDL_KEYDOWN) {
	//		board->handleInput(e);
	//		if (e.key.keysym.sym == SDLK_1) store->buy(1, board);
	//	}
	//}
}

// Physics update loop
void Game::update() {
	Uint32 delta = fpsTimer.restart();
	gameStateMachine->update(delta);
	updateFPS(delta);
}
