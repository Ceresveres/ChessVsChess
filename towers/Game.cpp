#include "Game.h"
#include <conio.h>
#include <SDL.h>
#include <SDL_render.h>

static Game* game_ = nullptr;

Game* Game::GetInstance() {
	if (game_ == nullptr) {
		game_ = new Game();
	}
	return game_;
}

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

void Game::loop() {
	SDL_Event e;
	bool end = false;
	addInvader(7, 2, BASIC);
	board->printBoard(*rend);
	while (!end) 
	{
		store->printStore(*rend);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				end = true;
				break;
			}
		}
		board->grid[x][y].setUnSelected();
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if ((currentKeyStates[SDL_SCANCODE_UP]) && (y > 0))
		{
			y--;
		}
		else if ((currentKeyStates[SDL_SCANCODE_DOWN]) && (y < GRID_NUM_Y - 1))
		{
			y++;
		}
		else if ((currentKeyStates[SDL_SCANCODE_LEFT]) && (x > 0))
		{
			x--;
		}
		if ((currentKeyStates[SDL_SCANCODE_RIGHT]) && (x < GRID_NUM_X - 1))	x++;

		if ((currentKeyStates[SDL_SCANCODE_1])) store->buy(1, x, y, board);
		board->grid[x][y].setSelected();
		Sleep(100);
		board->travGrid(*this);
		
		moveBullet();
		clearInvader();
		printBullet();
		if (moveInvader()) break;
		board->refresh(*rend);

		SDL_RenderPresent(rend);
	}

	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);

	_CrtDumpMemoryLeaks();
	SDL_Quit();

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
