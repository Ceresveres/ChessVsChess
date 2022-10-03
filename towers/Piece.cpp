#include "Piece.h"
#include "Board.h"
#include "Game.h"
#include "Scene.h"


#include <iostream>

void Piece::draw(SDL_Renderer& rend) {
	SDL_Rect gridRect = { pos.x * (GRID_WIDTH)+(mWidth / 2),  pos.y * (GRID_HEIGHT)+(mHeight / 2), mWidth, mHeight };
	SDL_SetRenderDrawColor(&rend, 3, 252, 98, 255);
	SDL_RenderFillRect(&rend, &gridRect);
}

void Pawn::update() {
	bool isAttacking = false;
	Scene* scene{ Scene::GetSingleton() };
	Board* board{ Board::GetSingleton() };

	for (int i = pos.x; i < GRID_NUM_X; i++) {
		if (board->grid[i+pos.y].invaders.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed*1000) {
			counter = 0;
			Bullet* p = new Bullet(new LoaderParams(pos.x * (GRID_WIDTH)+(mWidth+20), pos.y * (GRID_HEIGHT)+(mHeight), 20, 20), pos.x, pos.y);
			scene->addBullet(p);
		}
	}
}


void Knight::update() {
	bool isAttacking = false;
	Scene* scene{ Scene::GetSingleton() };
	Board* board{ Board::GetSingleton() };
	for (int i = pos.x; i < GRID_NUM_X; i++) {
		if (board->grid[i+pos.y].invaders.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			Bullet* p = new Bullet(new LoaderParams(pos.x * (GRID_WIDTH)+(mWidth + 20), pos.y * (GRID_HEIGHT)+(mHeight), 20, 20), pos.x, pos.y);
			scene->addBullet(p);
		}
	}
}

void Bishop::update() {
	bool isAttacking = false;
	Scene* scene{ Scene::GetSingleton() };
	Board* board{ Board::GetSingleton() };
	for (int i = pos.x; i < GRID_NUM_X; i++) {
		if (board->grid[i+pos.y].invaders.size() != 0) {
			isAttacking = true; break;
		}
	}
	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			//Bullet* p = new FireBullet;
			//p->setXY(mX, mY);
			//curGame->addBullet(p);
		}
	}
}

void Peasant::update() {
	counter++;
	Store* store{ Store::GetSingleton() };
	Board* board{ Board::GetSingleton() };
	if (counter >= speed) {
		counter = 0;
		store->addMoney(25);
	}
}