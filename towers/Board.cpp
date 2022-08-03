#include "Board.h"
#include <string>
#include <iostream>

#include <vector>

using namespace std;

void Grid::setXY(int x, int y) {
	dx = x * (GRID_WIDTH + 1) + 1;
	dy = y * (GRID_HEIGHT + 1) + 1;
 
}


bool Grid::setPiece(Piece* iPiece) {
	if (piece != nullptr) return false;
	else {
		piece = iPiece;
		flag_refresh = true;
		return true;
	}
}

void Grid::addInvader(Invader* iInvader) {
	invaders.push_back(iInvader);
	flag_refresh = true;
}

void Grid::delPiece(Piece* ipiece) {
	delete ipiece;
	piece = nullptr;
	flag_refresh = true;
}


void Grid::paint() {
	flag_refresh = false;

	string str(GRID_WIDTH, ' ');
	for (int i = 0; i < GRID_HEIGHT; i++) {
		Goto_XY(dx, dy + i);
		PrintWithColor(str);
	}

	if (selected) {
		string str(GRID_WIDTH - 2, '-');
		Goto_XY(dx, dy);
		PrintWithColor("+" + str + "+");
		for (int i = 1; i < GRID_HEIGHT-1; i++) {
			Goto_XY(dx, dy + i);
			PrintWithColor("|");
			Goto_XY(dx + GRID_WIDTH - 1, dy + i);
			PrintWithColor("|");
		}
		Goto_XY(dx, dy+GRID_HEIGHT-1);
		PrintWithColor("+" + str + "+");
	}

	if (piece != nullptr) {
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 - 1);
		piece->printPiece();
	}

	if (invaders.size() != 0) {
		Goto_XY(dx + 1, dy + GRID_HEIGHT / 2 - 2);
		cout << "sup";
	}
}

bool Board::setPiece(int ix, int iy, char type) {
	Piece* newPiece = nullptr;
	switch (type) {
	case '1':
		newPiece = new Pawn;
		break;
	case '2':
		newPiece = new Rook;
		break;
	case '3':
		newPiece = new Knight;
		break;
	case '4':
		newPiece = new Bishop;
		break;
	case '5':
		newPiece = new King;
		break;
	case '6':
		newPiece = new Queen;
		break;
	}
	newPiece->setXY(ix, iy);
	if (!grid[ix][iy].setPiece(newPiece)) {
		delete newPiece;
		return false;
	}
	else {
		return true;
	}
}

void Board::printBoard() {
	for (int i = 0; i < GRID_NUM_Y; i++) {
		string str(WINDOW_WIDTH, '#');
		Goto_XY(0, i *(GRID_HEIGHT+1));
		PrintWithColor(str);
		for (int j = 1; j <= GRID_HEIGHT; j++) {
			for (int k = 0; k <= GRID_NUM_X; k++) {
				Goto_XY(k * (GRID_WIDTH+1), i*(GRID_HEIGHT+1) + j);
				PrintWithColor("#");
			}
		}
	}
	
	string str(WINDOW_WIDTH, '#');
	Goto_XY(0, (GRID_HEIGHT + 1) * GRID_NUM_Y);
	PrintWithColor(str);
	
	
}

void Board::refresh() {
	for (int i = 0; i < GRID_NUM_X; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			if (grid[i][j].flag_refresh) {
				grid[i][j].paint();
			}
		}
	}
}

void Board::init() {
	system("cls");
	printBoard();
	for(int i = 0; i < GRID_NUM_X; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i][j].setXY(i, j);
		}
	}
}