#include "Piece.h"
#include "Board.h"

void Piece::printPiece() {
	PrintWithColor(name);
}

/*
bool Piece::move(Board& board) {
	counter += 10;
	if (counter >= 10) {
		//board.grid[x][y].delPiece(this);
		x++;
		if (x > GRID_NUM_X)
			return true;
		board.grid[x][y].setPiece(this);
		counter = 0;
	}
}
*/