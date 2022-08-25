#include "Board.h"
#include <string>
#include <iostream>
#include <algorithm>

#include <vector>
#include <SDL_video.h>
#include <SDL_rect.h>
#include <SDL_render.h>

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
	flag_refresh = true;
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

	if (piece != nullptr && invaders.size() == 0) {
		Goto_XY(dx + (GRID_WIDTH/2) - 1, dy + GRID_HEIGHT / 2 );
		piece->printPiece();
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 1);
		piece->printLife();
	}
	else if (piece != nullptr && invaders.size() == 1) {
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 - 2);
		piece->printLife();
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 - 1);
		piece->printPiece();
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2);
		PrintWithColor("X");
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 1);
		invaders[0]->printName();
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 2);
		invaders[0]->printLife();
	} else if (piece == nullptr && invaders.size() != 0) {
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2);
		invaders[0]->printName();
		Goto_XY(dx + (GRID_WIDTH / 2) - 1, dy + GRID_HEIGHT / 2 + 1);
		invaders[0]->printLife();
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

void Board::printBoard(SDL_Renderer * renderer) {
	//for (int i = 0; i < GRID_NUM_Y; i++) {
	//	string str(WINDOW_WIDTH, '#');
	//	Goto_XY(0, i *(GRID_HEIGHT+1));
	//	PrintWithColor(str);
	//	for (int j = 1; j <= GRID_HEIGHT; j++) {
	//		for (int k = 0; k <= GRID_NUM_X; k++) {
	//			Goto_XY(k * (GRID_WIDTH+1), i*(GRID_HEIGHT+1) + j);
	//			PrintWithColor("#");
	//		}
	//	}
	//}
	//
	//string str(WINDOW_WIDTH, '#');
	//Goto_XY(0, (GRID_HEIGHT + 1) * GRID_NUM_Y);
	//PrintWithColor(str);
	//int countOfRects = (GRID_NUM_X + GRID_NUM_Y) / 2;
	//SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	//SDL_SetRenderDrawColor(&renderer, 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < GRID_NUM_X; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			SDL_Rect gridRect = { i * (BOX_WIDTH),  j* (BOX_HEIGHT), BOX_WIDTH, BOX_HEIGHT };
			if ((i + j) % 2 == 0) {
				SDL_SetRenderDrawColor(renderer, 0, 143, 50, 255);
				SDL_RenderFillRect(renderer, &gridRect);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 86, 201, 50, 255);
				SDL_RenderFillRect(renderer, &gridRect);
			}
			if (grid[i][j].flag_refresh) {
				grid[i][j].paint();
			}
		}
	}
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
	//system("cls");
	//printBoard();
	for(int i = 0; i < GRID_NUM_X; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i][j].setXY(i, j);
		}
	}
}