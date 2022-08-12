#include "Game.h"
#include <conio.h>

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
			//board.setPiece(x, y, ch);
			break;
		case '3':
			//board.setPiece(x, y, ch);
			break;
		case '4':
			//board.setPiece(x, y, ch);
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


Game::Game()
{
	HideCursor();
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::loop() {
	bool state = true;
	addInvader(5, 2);
	while (state) {
		building();
		board.travGrid(*this);
		if (moveInvader()) break;
		clearInvader();
		board.refresh();
		Sleep(100);
	}
}

void Game::addInvader(int x, int y) {
	Invader* newInvader = nullptr;
	newInvader = new Invader();
	newInvader->setXY(x, y);
	board.grid[x][y].addInvader(newInvader);
	invaders.push_back(newInvader);
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

void Game::init()
{
	board.init();
	x = y = 0;
}
