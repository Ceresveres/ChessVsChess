#include "Game.h"
#include <conio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include <iostream>
#include "InputHandler.h"


static Game* game_ = nullptr;

Game* Game::GetSingleton() {
	if (game_ == nullptr) {
		game_ = new Game();
	}
	return game_;
}

void Game::onStartUp() {
	fpsTimer.start();
	gameState = RUNNING;
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new PlayState(m_pRenderer));
	loop();
}

// Fps helper counter
void Game::updateFPS(Uint32 delta) {
	if (frameCount < 10) {
		fps_counter += delta;
	} else {
		this->mAverageFPS = (float)fps_counter / ((float)frameCount * 1000.0f);
		fps_counter = 0;
		frameCount = 0;
	}
	frameCount++;
}

// Core game loop
void Game::loop() {
	//addInvader(7, 2, BASIC);
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
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(window);
	_CrtDumpMemoryLeaks();
	SDL_Quit();

}

// Handles the rendering and graphic updates
void Game::render() {
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
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
	m_pGameStateMachine->update(delta);
	updateFPS(delta);
}
