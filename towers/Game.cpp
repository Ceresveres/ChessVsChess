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

//void Game::loop() {
//	bool state = true;
//	addInvader(7, 2, JUMPER);
//	while (state) {
//		building();
//		board.travGrid(*this);
//		if (moveInvader()) break;
//		//makeInvaders();
//		clearInvader();
//		moveBullet();
//		board.refresh();
//		printBullet();
//		Sleep(SLEEP_TIME);
//	}
//}

void Game::initializeSDL() {
	window = SDL_CreateWindow("Tower Defense", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::onStartUp() {
	//fpsTimer.start();
}
	
float Game::getAverageFPS() {
	return mAverageFPS;
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

void keyboard(bool KEYS[]) {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		// check for messages
		switch (e.type) {
			// exit if the window is closed
		case SDL_QUIT:
			break;
			// check for keypresses
		case SDL_KEYDOWN:
			KEYS[e.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			KEYS[e.key.keysym.sym] = false;
			break;
		default:
			break;
		}
	}
}

void Game::loop() {
	string path = "v0he8g2kvsn91.jpg";
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	SDL_Event e;
	bool end = false;

	addInvader(7, 2, BASIC);

	LTimer timer;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL] = {};
	SDL_Surface* gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
	board->printBoard(*rend);
	fpsTimer.start();
	while (!end) 
	{
		Uint32 delta = fpsTimer.restart();
		updateFPS(delta);
		board->grid[x][y].setUnSelected();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				end = true;
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
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					if (y > 0) y--;
					break;

				case SDLK_DOWN:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					if (y < GRID_NUM_Y - 1) y++;
					break;

				case SDLK_LEFT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					if (x > 0) x--;
					break;

				case SDLK_RIGHT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					if (x < GRID_NUM_X - 1) x++;
					break;

				default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}
		}
		
		
		//if ((currentKeyStates[SDL_SCANCODE_UP]) && (y > 0))
		//{
		//	y--;
		//}
		//else if ((currentKeyStates[SDL_SCANCODE_DOWN]) && (y < GRID_NUM_Y - 1))
		//{
		//	y++;
		//}
		//else if ((currentKeyStates[SDL_SCANCODE_LEFT]) && (x > 0))
		//{
		//	x--;
		//}
		//if ((currentKeyStates[SDL_SCANCODE_RIGHT]) && (x < GRID_NUM_X - 1))	x++;

		if ((currentKeyStates[SDL_SCANCODE_1])) store->buy(1, x, y, board);
		board->grid[x][y].setSelected();
		
		update(delta);
		/*moveBullet();
		clearInvader();
		board->refresh(*rend);
		printBullet();
		if (moveInvader()) break;
		board->refresh(*rend);

		SDL_RenderPresent(rend);*/
	}

	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);

	_CrtDumpMemoryLeaks();
	SDL_Quit();

}

void Game::update(Uint32 timestep) {
	store->printStore(*rend);
	board->travGrid(*this);
	moveBullet();
	clearInvader();
	board->refresh(*rend);
	printBullet();
	moveInvader();
	board->refresh(*rend);
	SDL_RenderPresent(rend);
}

void Game::openFocus() {
	board->grid[x][y].setSelected();
}

void Game::building() {
	char ch;
	if (_kbhit()) {
		ch = _getch();
		switch (ch) {
		case -32:
			board->grid[x][y].setUnSelected();
			ch = _getch();
			switch (ch) {
			case 72:
				if (y > 0)
					y--;
				break;
			case 75:
				if (x > 0)
					x--;
				break;
			case 77:
				if (x < GRID_NUM_X - 1)
					x++;
				break;
			case 80:
				if (y < GRID_NUM_Y - 1)
					y++;
				break;
			default:
				break;
			}
			board->grid[x][y].setSelected();
			break;
		case '1':
			//board.setPiece(x, y, ch);
			store->buy(1, x, y, board);
			break;
		case '2':
			//board.setPiece(x, y, ch);
			store->buy(2, x, y, board);
			break;
		case '3':
			//board.setPiece(x, y, ch);
			store->buy(3, x, y, board);
			break;
		case '4':
			//board.setPiece(x, y, ch);
			store->buy(4, x, y, board);
			break;
		case '5':
			//board.setPiece(x, y, ch);
			store->buy(5, x, y, board);
			break;
		case '6':
			//board.setPiece(x, y, ch);
			break;
		default:
			break;
		}
	}
}

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
