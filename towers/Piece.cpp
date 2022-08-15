#include "Piece.h"
#include "Board.h"
#include "Game.h"

#include <iostream>

void Piece::printPiece() {
	PrintWithColor(name);
}


void Pawn::go(Game & curgame) {
	bool isAttacking = false;
	
	for (int i = x; i < GRID_NUM_X; i++) {
		if (curgame.board.grid[i][y].invaders.size() != 0) {
			isAttacking = true; break;
		}
	}
	
	/*
	for (int i = x; i < x+1; i++) {
		if (curgame.board.grid[i][y].invaders.size() != 0) {
//			std::cout << "attack";
			isAttacking = true; break;
		}
	}
	*/

	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			Bullet* p = new Bullet();
			p->setXY(x, y);
			curgame.addBullet(p);
		}

	}
/*
	if (isAttacking) {
		for (int i = x; i < GRID_NUM_X; i++) {
			for (auto var : curgame.board.grid[i][y].invaders) {
				var->hit(10);
			}
		}
	}
*/
}

void Rook::go(Game& curgame) {
	bool isAttacking = false;
	for (int i = x; i < GRID_NUM_X; i++) {
		if (curgame.board.grid[i][y].invaders.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			Bullet* p = new Bullet();
			p->setXY(x, y);
			curgame.addBullet(p);
		}
	}
}

void Knight::go(Game& curgame) {
	bool isAttacking = false;
	for (int i = x; i < GRID_NUM_X; i++) {
		if (curgame.board.grid[i][y].invaders.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			Bullet* p = new SlowBullet;
			p->setXY(x, y);
			curgame.addBullet(p);
		}
	}
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