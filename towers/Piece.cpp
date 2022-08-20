#include "Piece.h"
#include "Board.h"
#include "Game.h"

#include <iostream>

void Piece::printPiece() {
	DrawText(name.c_str(), dx - MeasureText(name.c_str(), 20/2), dy-GRID_HEIGHT/2+10, 20, BLUE);
	DrawTexture(texture,dx - texture.width / 2, dy - texture.height / 2, WHITE);
	//DrawTextureRec(texture, rec, position, WHITE);
	//DrawTexturePro(texture, rec, (Rectangle){0.0 0.0, GRID_WIDTH, GRID_HEIGHT}, position, 0, WHITE);
	//DrawPixel(x * GRID_WIDTH + (GRID_WIDTH / 2), y * GRID_HEIGHT + (GRID_HEIGHT / 2), RED);
	//PrintWithColor(name);
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

//void Knight::printPiece() {
//	PrintWithColor(name, 4);
//}

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

//void Bishop::printPiece() {
//	PrintWithColor(name, 4);
//}

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

//void Peasant::printPiece() {
//	PrintWithColor(name, 4);
//}