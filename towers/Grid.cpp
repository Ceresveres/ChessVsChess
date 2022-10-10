#include "Grid.h"

Grid::Grid(int x, int y, Board* pboard) : pos(x, y), size(100, 100), board(board) {
	setColor((x + y) % 200);
};

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

void Grid::draw() {
	SDL_Rect gridRect = { pos.x,  pos.y, size.mWidth, size.mHeight };
	TextureManager::GetSingletonInstance()->drawTemp(gridRect, color);
	if (selected) {
		int tmpColor[4] = { 16, 10, 10, 255 };
		TextureManager::GetSingletonInstance()->drawTemp(gridRect, tmpColor);

		gridRect = { (pos.x) + 10,  (pos.y) + 10, size.mWidth - 20, size.mHeight - 20 };

	}
	TextureManager::GetSingletonInstance()->drawTemp(gridRect, color);

	if (piece != nullptr) {
		piece->draw();
	}
}

bool Grid::setPiece() {
	if (piece != nullptr) {
		return false;
	}
	else {
		piece = make_unique<Pawn>(pos.x + size.mWidth / 2, pos.y + size.mHeight / 2);
		return true;
	}
}

bool Grid::hasPiece() const {
	return piece != nullptr;
}

void Grid::updatePiece() {
	(*piece).update();
}

void Grid::attackPiece(int attack) {
	if (piece != nullptr) {
		piece->HP -= attack;
		if (piece->HP <= 0) {
			delPiece();
		}
	}
}

void Grid::delPiece() {
	piece.reset();
}

void Grid::addInvader(Invader* iInvader) {
	invaders.push_back(iInvader);
}

bool Grid::hasInvaders() const {
	return invaders.size() != 0;
}

void Grid::damageInvader(Invader* iInvader, int damage) {
	iInvader->hit(damage);
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

void Grid::delInvader(Invader* iInvader) {
	invaders.erase(remove(invaders.begin(), invaders.end(), iInvader), invaders.end());
}













