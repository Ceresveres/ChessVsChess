#include "Board.h"

static Board* board_ = nullptr;

Board* Board::GetSingleton() {
	if (board_ == nullptr) {
		board_ = new Board();
	}
	return board_;
}

Board::Board() {
	for (int i = 0; i < GRID_NUM_X; i++) {
		grid.push_back(std::vector<Grid>());
		for (int j = 0; j < GRID_NUM_Y; j++) {
			grid[i].emplace_back(i * 100, j * 100, this);
		}
	}
	grid[x][y].setSelected();
}

void Board::update() {
	handleInput();
	travGrid();
}

void Board::draw() {
	for (auto& row : grid) {
		for (auto& i : row) {
			i.draw();
		}
	}
}

bool Board::setPiece(int type) {
	switch (type) {
	case 1:
		if (!grid[x][y].setPiece()) {
			return false;
		}
	default:
		return false;
	}
}

void Board::addInvader(int x, int y, Invader* iInvader) {
	grid[x][y].addInvader(iInvader);
}

bool Board::travGrid() {
	int rowIndex = 0;
	for (auto& row : grid) {
		int index = 0;
		for (auto& box : row) {
			if (box.hasPiece()) {
				for (int i = rowIndex; i < grid.size(); i++) {
					if (grid[i][index].hasInvaders()) {
						box.updatePiece();
						break;
					}
				}
			}
			index++;
		}
		rowIndex++;
	}
	return true;
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



