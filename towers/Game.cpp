#include "Game.h"
#include <conio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include <iostream>

static Game* game_ = nullptr;

Game* Game::GetInstance() {
	if (game_ == nullptr) {
		game_ = new Game();
	}
	return game_;
}

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

void Game::initializeSDL() {
	window = SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::onStartUp() {
	fpsTimer.start();
	gameState = RUNNING;
}

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

void Game::loop() {
	addInvader(7, 2, BASIC);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	board->printBoard(*rend);
	while (gameState == RUNNING)
	{
		Uint32 delta = fpsTimer.restart();
		updateFPS(delta);
		processEvents();		
		update(delta);
	}
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	_CrtDumpMemoryLeaks();
	SDL_Quit();

}

void Game::processEvents() {
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			gameState = END;
			break;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			//Start/stop
			if (e.key.keysym.sym == SDLK_s)
			{
				if (timer.isStarted())
				{
					getAverageFPS();
					timer.stop();
				}
				else
				{
					timer.start();
				}
			}
			//Pause/unpause
			else if (e.key.keysym.sym == SDLK_p)
			{
				if (timer.isPaused())
				{
					timer.unpause();
				}
				else
				{
					timer.pause();
				}
			}
		}
		if (e.type == SDL_KEYDOWN) {
			board->handleInput(e);
			if (e.key.keysym.sym == SDLK_1) store->buy(1, board);
		}
	}
}

void Game::update(Uint32 timestep) {
	store->printStore(*rend);
	board->travGrid(*this);
	moveBullet();
	clearInvader();
	board->refresh(*rend);
	printBullet();
	if (moveInvader()) gameState = GAMEOVER;
	board->refresh(*rend);
	SDL_RenderPresent(rend);
}

//void Game::building() {
//	char ch;
//	if (_kbhit()) {
//		ch = _getch();
//		switch (ch) {
//		case -32:
//			board->grid[x][y].setUnSelected();
//			ch = _getch();
//			switch (ch) {
//			case 72:
//				if (y > 0)
//					y--;
//				break;
//			case 75:
//				if (x > 0)
//					x--;
//				break;
//			case 77:
//				if (x < GRID_NUM_X - 1)
//					x++;
//				break;
//			case 80:
//				if (y < GRID_NUM_Y - 1)
//					y++;
//				break;
//			default:
//				break;
//			}
//			board->grid[x][y].setSelected();
//			break;
//		case '1':
//			//board.setPiece(x, y, ch);
//			//store->buy(1, x, y, board);
//			break;
//		case '2':
//			//board.setPiece(x, y, ch);
//			//store->buy(2, x, y, board);
//			break;
//		case '3':
//			//board.setPiece(x, y, ch);
//			//store->buy(3, x, y, board);
//			break;
//		case '4':
//			//board.setPiece(x, y, ch);
//			//store->buy(4, x, y, board);
//			break;
//		case '5':
//			//board.setPiece(x, y, ch);
//			//store->buy(5, x, y, board);
//			break;
//		case '6':
//			//board.setPiece(x, y, ch);
//			break;
//		default:
//			break;
//		}
//	}
//}

void Game::makeInvaders() {
	makeCounter++;
	if (makeCounter >= makeSpeed) {
		addInvader(GRID_NUM_X - 1, RANDOM(GRID_NUM_Y), RANDOM(SHIELD+1));
		makeCounter = 0;
	}
}

void Game::addInvader(int x, int y, int type) {
	if (x < 0 || x >= GRID_NUM_X || y < 0 || y >= GRID_NUM_Y) return;
	Invader* newInvader = nullptr;
	switch (type) {
	case BASIC:
		newInvader = new Invader();
		break;
	case JUMPER:
		newInvader = new Jumper();
		break;
	case HEAVY:
		newInvader = new Heavy();
		break;
	case SHIELD:
		newInvader = new Shield();
		break;
	default:
		break;
	}
	if (newInvader != nullptr) {
		newInvader->setXY(x, y);
		board->grid[x][y].addInvader(newInvader);
		invaders.push_back(newInvader);
	}
}

bool Game::moveInvader()
{
	for (auto& var : invaders) {
		//var->go(board);
		if (var->go(board))
			return true;
	}
	return false;
}

void Game::clearInvader() {
	for (auto list = invaders.begin(); list != invaders.end();) {
		if ((*list)->HP <= 0) {
			board->grid[(*list)->x][(*list)->y].delInvader(*list);
			store->addMoney((*list)->reward);
			delete (*list);
			list = invaders.erase(list);
		}
		else {
			list++;
		}
	}
}

void Game::addBullet(Bullet* p) {
	bullets.push_back(p);
}

void Game::printBullet() {
	for (auto const& var: bullets) {
		var->print(*rend);
	}
}

void Game::moveBullet() {
	for (auto const& var : bullets) {
		var->move(board);
	}
	
	for (auto list = bullets.begin(); list != bullets.end(); ) {
		if ((*list)->hit) {
			delete *list;
			list = bullets.erase(list);
		}
		else {
			list++;
		}
	}
}
