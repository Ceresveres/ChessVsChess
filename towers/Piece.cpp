#include "Piece.h"
#include "Board.h"
#include "Game.h"

#include <iostream>

void Piece::printPiece() {
	PrintWithColor(name);
}

void Piece::printLife() {
	PrintWithColor(to_string(HP));
}

void Piece::go(Game& curgam) {
	cout << "You can't go there!" << endl;
}

void Pawn::go(Game & curgame) {
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

void Knight::printPiece() {
	PrintWithColor(name, FOREGROUND_BLUE);
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

void Bishop::printPiece() {
	PrintWithColor(name, FOREGROUND_RED | FOREGROUND_BLUE);
}

void Bishop::go(Game& curgame) {
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
			Bullet* p = new FireBullet;
			p->setXY(x, y);
			curgame.addBullet(p);
		}
	}
}

void Peasant::go(Game& curgame) {
	counter++;
	if (counter >= speed) {
		counter = 0;
		curgame.store.addMoney(25);
	}
}

void Peasant::printPiece() {
	PrintWithColor(name, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
}