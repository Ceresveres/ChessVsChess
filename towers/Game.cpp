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
			board.setPiece(x, y, ch);
			break;
		case '3':
			board.setPiece(x, y, ch);
			break;
		case '4':
			board.setPiece(x, y, ch);
			break;
		case '5':
			board.setPiece(x, y, ch);
			break;
		case '6':
			board.setPiece(x, y, ch);
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
	while (state) {
		building();
		board.refresh();
		Sleep(100);
	}
}

void Game::init()
{
	board.init();
	x = y = 0;
}
