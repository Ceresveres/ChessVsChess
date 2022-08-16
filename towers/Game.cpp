#include "Game.h"
#include <conio.h>

void Game::init()
{
	board.init();
	openFocus();
}

void Game::loop() {
	bool state = true;
	addInvader(7, 2, JUMPER);
	while (state) {
		building();
		board.travGrid(*this);
		if (moveInvader()) break;
		//makeInvaders();
		clearInvader();
		moveBullet();
		board.refresh();
		printBullet();
		Sleep(SLEEP_TIME);
	}
}

void Game::openFocus() {
	board.grid[x][y].setSelected();
}

void Game::building() {
	char ch;
	if (_kbhit()) {
		ch = _getch();
		switch (ch) {
		case -32:
			board.grid[x][y].setUnSelected();
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
			board.grid[x][y].setSelected();
			break;
		case '1':
			board.setPiece(x, y, ch);
			break;
		case '2':
			board.setPiece(x, y, ch);
			break;
		case '3':
			board.setPiece(x, y, ch);
			break;
		case '4':
			board.setPiece(x, y, ch);
			break;
		case '5':
			//board.setPiece(x, y, ch);
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
		;
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
		board.grid[x][y].addInvader(newInvader);
		invaders.push_back(newInvader);
	}
}

bool Game::moveInvader()
{
	for (auto& var : invaders) {
		if (var->move(board))
			return true;
	}
	return false;
}

void Game::clearInvader() {
	for (auto list = invaders.begin(); list != invaders.end();) {
		if ((*list)->HP <= 0) {
			board.grid[(*list)->x][(*list)->y].delInvader(*list);
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
		var->print();
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
