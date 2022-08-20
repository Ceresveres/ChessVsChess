#include "Board.h"
#include <string>
#include <iostream>
#include <algorithm>

#include <vector>

using namespace std;

void Grid::setXY(int x, int y) {
	dx = x * (GRID_WIDTH);
	dy = y * (GRID_HEIGHT);
 
}

bool Grid::setPiece(Piece* iPiece) {
	if (piece != nullptr) return false;
	else {
		piece = iPiece;
		flag_refresh = true;
		return true;
	}
}

void Grid::delPiece() { 
	delete piece; 
	piece = nullptr; 
	flag_refresh = true;
}

void Grid::addInvader(Invader* iInvader) {
	invaders.push_back(iInvader);
	flag_refresh = true;
}

void Grid::damageInvader(Invader* iInvader, int damage) {
	iInvader->hit(damage);
	flag_refresh = true;
}

void Grid::delInvader(Invader* iInvader) {
	invaders.erase(remove(invaders.begin(), invaders.end(), iInvader), invaders.end());
	flag_refresh = false;
}

void Grid::judgeAttacking()
{
	if (piece != nullptr && invaders.size() != 0) {
		for (auto& var : invaders) {
			var->attacking = true;
		}
	}
	else if (piece == nullptr && invaders.size() != 0) {
		for (auto& var : invaders) {
			var->attacking = false;
		}
	}
}

void Grid::attackPiece(int attack)
{
	if (piece != nullptr) {
		piece->HP -= attack;
		if (piece->HP <= 0) {
			delPiece();
		}
		flag_refresh = true;
	}
}

//void Grid::paint() {
//	flag_refresh = false;
//
//	string str(GRID_WIDTH, ' ');
//	for (int i = 0; i < GRID_HEIGHT; i++) {
//		Goto_XY(dx, dy + i);
//		PrintWithColor(str);
//	}
//
//	if (selected) {
//		string str(GRID_WIDTH - 2, '-');
//		Goto_XY(dx, dy);
//		PrintWithColor("+" + str + "+");
//		for (int i = 1; i < GRID_HEIGHT-1; i++) {
//			Goto_XY(dx, dy + i);
//			PrintWithColor("|");
//			Goto_XY(dx + GRID_WIDTH - 1, dy + i);
//			PrintWithColor("|");
//		}
//		Goto_XY(dx, dy+GRID_HEIGHT-1);
//		PrintWithColor("+" + str + "+");
//	}
//
//	if (piece != nullptr && invaders.size() == 0) {
//		Goto_XY(dx + (GRID_WIDTH/2) - 1, dy + GRID_HEIGHT / 2 );
//		piece->printPiece();
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 1);
//		piece->printLife();
//	}
//	else if (piece != nullptr && invaders.size() == 1) {
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 - 2);
//		piece->printLife();
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 - 1);
//		piece->printPiece();
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2);
//		PrintWithColor("X");
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 1);
//		invaders[0]->printName();
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 2);
//		invaders[0]->printLife();
//	} else if (piece == nullptr && invaders.size() != 0) {
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2);
//		invaders[0]->printName();
//		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 1);
//		invaders[0]->printLife();
//	}
//}

void Grid::paint() {
	if (piece == nullptr && invaders.size() != 0) {
		//DrawRectangle(dx, dy, GRID_WIDTH, GRID_HEIGHT, DARKGREEN);
		invaders[0]->printName();
		invaders[0]->printLife();
	}
	if (piece != nullptr && invaders.size() == 0) {
		//DrawRectangle(dx, dy, GRID_WIDTH, GRID_HEIGHT, DARKGREEN);
		piece->printPiece();
	}
	if (selected) {
		DrawCircleLines(dx + GRID_WIDTH / 2, dy + GRID_HEIGHT / 2, GRID_WIDTH / 3, WHITE);
	}
}

bool Board::travGrid(Game& game)
{
	for (int i = 0; i < GRID_NUM_X; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i][j].judgeAttacking();
			if (grid[i][j].piece != nullptr) {
				grid[i][j].piece->go(game);
			}
		}
	}
	return true;
}

bool Board::setPiece(int ix, int iy, int type) {
	Piece* newPiece = nullptr;
	switch (type) {
	case 1:
		newPiece = new Pawn;
		break;
	case 2:
		newPiece = new Rook;
		break;
	case 3:
		newPiece = new Knight;
		break;
	case 4:
		newPiece = new Bishop;
		break;
	case 5:
		newPiece = new Peasant;
		break;
	case 6:
	//	newPiece = new Queen;
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
	//for (int i = 0; i < GRID_NUM_Y; i++) {
	//	string str(WINDOW_WIDTH, '#');
	//	Goto_XY(0, i *(GRID_HEIGHT+1));
	//	PrintWithColor(str);
	//	for (int j = 1; j <= GRID_HEIGHT; j++) {
	//		for (int k = 0; k <= GRID_NUM_X; k++) {
	//			DrawRectangle(k * (GRID_WIDTH + 1), i * (GRID_HEIGHT + 1) + j, GRID_WIDTH, GRID_HEIGHT, YELLOW);
	//			DrawText("i", k * (GRID_WIDTH + 1), i * (GRID_HEIGHT + 1) + j, 20, LIGHTGRAY);
	//			Goto_XY(k * (GRID_WIDTH+1), i*(GRID_HEIGHT+1) + j);
	//			PrintWithColor("#");
	//		}
	//	}
	//}
	for (int i = 0; i < GRID_NUM_Y; i++) {
		for (int j = 0; j< GRID_NUM_X; j++){

			if ((i + j) % 2 == 0) {
				DrawRectangle(j * GRID_WIDTH, i * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, DARKGREEN);
				DrawText("i", j * GRID_WIDTH + (GRID_WIDTH / 2), i * GRID_HEIGHT + (GRID_HEIGHT / 2), 20, LIGHTGRAY);
			}
			else {
				DrawRectangle(j * GRID_WIDTH, i * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, GREEN);
				DrawText("i", j * GRID_WIDTH + (GRID_WIDTH / 2), i * GRID_HEIGHT + (GRID_HEIGHT / 2), 20, DARKGRAY);
			}
			if (grid[i][j].flag_refresh) {
				grid[i][j].paint();
			}
		}
	}

	//
	//string str(WINDOW_WIDTH, '#');
	//Goto_XY(0, (GRID_HEIGHT + 1) * GRID_NUM_Y);
	//PrintWithColor(str);
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
	//printBoard();
	for(int i = 0; i < GRID_NUM_X; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i][j].setXY(i, j);
		}
	}
}
