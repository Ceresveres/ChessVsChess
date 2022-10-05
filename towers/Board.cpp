#include "Board.h"
#include <string>
#include <iostream>
#include <algorithm>

#include <vector>
#include <SDL_video.h>
#include <SDL_rect.h>
#include <SDL_render.h>

using namespace std;
static Board* board_ = nullptr;

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
	//iInvader->applyEffect(1);
	//iInvader->applyEffect(2);
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

void Grid::judgeAttacking() {
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


bool Board::travGrid() {
	for (auto& row : grid) {
		for (auto& i : row) {
			i.judgeAttacking();
			if (i.piece != nullptr) i.piece->update();
		}
	}
	return true;
}

bool Board::setPiece( int type) {
	Piece* newPiece = nullptr;
	switch (type) {
	case 1:
		newPiece = new Pawn(x, y);
		break;
	case 2:
		//newPiece = new Rook;
		break;
	case 3:
		//newPiece = new Knight;
		break;
	case 4:
		//newPiece = new Bishop;
		break;
	case 5:
		//newPiece = new Peasant;
		break;
	case 6:
	//	newPiece = new Queen;
		break;
	}
	if (!grid[x][y].setPiece(newPiece)) {
		delete newPiece;
		return false;
	}
	else {
		Scene* pScene = Scene::GetSingleton();
		return true;
	}
}

void Grid::draw(SDL_Renderer& pRenderer) {
	SDL_Rect gridRect = { pos.x * mWidth,  pos.y * mHeight, mWidth, mHeight };
	if (selected) {
		SDL_SetRenderDrawColor(&pRenderer, 16, 10, 10, 255);
		SDL_RenderFillRect(&pRenderer, &gridRect);
		gridRect = { (pos.x * mWidth) + 10,  (pos.y * (mHeight)) + 10, mWidth - 20, mHeight -20 };

	}
	SDL_SetRenderDrawColor(&pRenderer, color[0], color[1], color[2], color[3]);
	SDL_RenderFillRect(&pRenderer, &gridRect);

	//if (invaders.size() != 0) {
	//	invaders[0]->draw(pRenderer);
	//}
	if (piece != nullptr) {
		piece->draw(pRenderer);
	}
}

void Board::draw(SDL_Renderer& rend) {
	for (auto& row : grid) {
		for (auto& i : row) {
			if (i.flag_refresh) i.draw(rend);
		}
	}
}

void Board::update() {
	handleInput();
	travGrid();
}

void Board::addInvader(int x, int y, Invader* iInvader) {
	grid[x][y].addInvader(iInvader);
}

void Board::handleInput() {
	SDL_GetKeyboardState(0);

	if (InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_RIGHT) && m_kReleased)
	{
		m_kReleased = false;
		handleSelection(1, 0);
	}
	if (InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_LEFT) && m_kReleased)
	{
		m_kReleased = false;
		handleSelection(-1, 0);
	}
	if (InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_UP) && m_kReleased)
	{
		m_kReleased = false;
		handleSelection(0, -1);
	}
	if (InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_DOWN) && m_kReleased)
	{
		m_kReleased = false;
		handleSelection(0, 1);
	}
	if (InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_1) && m_kReleased)
	{
		m_kReleased = false;
		setPiece(1);
	}

	if (!InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_DOWN) && !InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_UP) && !InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_LEFT) && !InputHandler::GetSingleton()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		m_kReleased = true;
	}
}

void Board::handleSelection(const int ix, const int iy) {
	if ((y + iy < 0) || (y > GRID_NUM_Y - 1 - iy)) return;
	if ((x + ix < 0) || (x > GRID_NUM_X - 1 - ix)) return;
	grid[x][y].setUnSelected();
	this->x += ix;
	this->y += iy;
	grid[x][y].setSelected();

}

Board* Board::GetSingleton() {
	if (board_ == nullptr) {
		board_ = new Board();
	}
	return board_;
}

void Grid::setColor(int choice) {
	if (choice == 0) {
		color[0] = 0;
		color[1] = 143;
		color[2] = 50;
		color[3] = 255;
	}
	else {
		color[0] = 86;
		color[1] = 201;
		color[2] = 50;
		color[3] = 255;
	}
}

Grid::Grid(int x, int y) : Object(new LoaderParams( 100, 100)), pos(x, y) {
	cout << "being made";
	setColor((x + y) % 2);
};

bool Board::inLineOfSight(int x, int y) {
	for (int i = x; i < GRID_NUM_X; i++) {
		if (grid[i][y].invaders.size() != 0) {
			return true;
		}
	}
	return false;
}

Board::Board() : Object(new LoaderParams(0,0)), pos(0, 0) {
	for (int i = 0; i < GRID_NUM_X; i++) {
		grid.push_back(std::vector<Grid>());
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i].emplace_back(i, j);
		}
	}
	grid[x][y].setSelected();

}
