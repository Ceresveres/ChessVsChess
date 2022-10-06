#include "Piece.h"
#include "Board.h"
#include "Game.h"
#include "Scene.h"


#include <iostream>

Piece::Piece(int x, int y) :pos((x * 100) + 25, (y * 100) + 25), 
							indexI(x), 
							indexJ(y), 
							graphic("Pieces"), 
							size(50, 50) 
							{ cout << "being made";}

void Piece::draw() {
	graphic.draw(pos, size);
}

void Pawn::update() {
	bool isAttacking = false;
	Scene* scene{ Scene::GetSingleton() };
	Board* board{ Board::GetSingleton() };
	isAttacking = board->inLineOfSight(indexI, indexJ);

	if (isAttacking) {
		counter++;
		if (counter >= speed*1000) {
			counter = 0;
			Bullet* p = new Bullet(pos.x+ size.mWidth, pos.y+ size.mHeight/2);
			scene->addBullet(p);
		}
	}
}


void Knight::update() {
	bool isAttacking = false;
	Scene* scene{ Scene::GetSingleton() };
	Board* board{ Board::GetSingleton() };
	isAttacking = board->inLineOfSight(indexI, indexJ);

	if (isAttacking) {
		counter++;
		if (counter >= speed) {
			counter = 0;
			//Bullet* p = new Bullet(new LoaderParams(pos.x * (GRID_WIDTH)+(mWidth + 20), pos.y * (GRID_HEIGHT)+(mHeight), 20, 20), pos.x, pos.y);
			//scene->addBullet(p);
		}
	}
}

void Bishop::update() {
	bool isAttacking = false;
	Scene* scene{ Scene::GetSingleton() };
	Board* board{ Board::GetSingleton() };
	isAttacking = board->inLineOfSight(indexI, indexJ);

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