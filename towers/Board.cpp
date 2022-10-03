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
	for (auto i : grid) {
		i.judgeAttacking();
		if (i.piece != nullptr) i.piece->update();
	}
	//for (int i = 0; i < GRID_NUM_X; i++) {
	//	for (int j = 0; j < GRID_NUM_Y; j++) {
	//		grid[i+j].judgeAttacking();
	//		if (grid[i+j].piece != nullptr) {
	//			grid[i+j].piece->update();
	//		}
	//	}
	//}
	return true;
}

bool Board::setPiece( int type) {
	Piece* newPiece = nullptr;
	switch (type) {
	case 1:
		newPiece = new Pawn(new LoaderParams(x, y, 50, 50));
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
	//newPiece->setXY(x, y);
	if (!grid[x+y].setPiece(newPiece)) {
		delete newPiece;
		return false;
	}
	else {
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

	if (invaders.size() != 0) {
		invaders[0]->draw(pRenderer);
	}
	if (piece != nullptr) {
		piece->draw(pRenderer);
	}
}

void Board::draw(SDL_Renderer& rend) {
	for (auto i : grid) {
		if (i.flag_refresh) i.draw(rend);
	}
	//for (int i = 0; i < GRID_NUM_X; i++) {
	//	for (int j = 0; j < GRID_NUM_Y; j++) {
	//		if (grid[i+j].flag_refresh) {
	//			grid[i+j].draw(rend);
	//		}
	//	}
	//}
}

void Board::update() {
	handleInput();
	travGrid();
}

void Board::addInvader(int x, int y, Invader* iInvader) {
	grid[x * 5 + y].addInvader(iInvader);
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
//void Board::handleInput(SDL_Event &e) {
//	//const Uint8* state = SDL_GetKeyboardState(NULL);
//	switch (e.key.keysym.sym) {
//	case SDLK_UP:
//		handleSelection(0, -1);
//		break;
//	case SDLK_DOWN:
//		handleSelection(0, 1);
//		break;
//	case SDLK_LEFT:
//		handleSelection(-1, 0);
//		break;
//	case SDLK_RIGHT:
//		handleSelection(1, 0);
//		break;
//
//	default:
//		break;
//	}
//	//if (state[SDLK_UP]) handleSelection(0, -1);
//	//if (state[SDLK_DOWN]) handleSelection(0, 1);
//	//if (state[SDLK_LEFT]) handleSelection(-1, 0);
//	//if (state[SDLK_RIGHT]) handleSelection(1, 0);
//}

void Board::handleSelection(const int ix, const int iy) {
	if ((y + iy < 0) || (y > GRID_NUM_Y - 1 - iy)) return;
	if ((x + ix < 0) || (x > GRID_NUM_X - 1 - ix)) return;
	grid[x * 5 + y].setUnSelected();
	this->x += ix;
	this->y += iy;
	grid[x * 5 + y].setSelected();
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

//Grid::Grid(const LoaderParams* pParams) :
//	Object(pParams), pos(pParams->getX(), pParams->getY())
//{
//}

Grid::Grid() : Object(new LoaderParams(0,0,0,0)), pos(0, 0) {};

//grid::grid(const loaderparams* pparams) : object(pparams), pos(pparams->getx(), pparams->gety())
//{};

//Grid::Grid(const LoaderParams* pParams) {};

Grid::Grid(int x, int y) : Object(new LoaderParams(x, y, 100, 100)), pos(x, y) {
	cout << "being made";
	setColor((x + y) % 2);
};

//void Grid::load(const LoaderParams* pParams) {
//	pos.x = pParams->getX();
//	pos.y = pParams->getY();
//	load(pParams);
//}

Board::Board() : Object(new LoaderParams(0,0,0,0)), pos(0, 0) {
	for (int i = 0; i < GRID_NUM_X; i++) {
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid.emplace_back(i, j);
		}
	}
	grid[x+y].setSelected();
}

//Board::Board(const LoaderParams* pParams) :
//	Object(pParams), pos(pParams->getX(), pParams->getY())
//{
//}

//void Board::init() {
//	for(int i = 0; i < GRID_NUM_X; i++) {
//		for (int j = 0; j < GRID_NUM_Y; j++) {
//			grid[i][j].setColor((i + j) % 2);
//			grid[i][j].load(new LoaderParams(i, j, GRID_HEIGHT, GRID_WIDTH));				
//		}
//	}
//	grid[x][y].setSelected();
//}