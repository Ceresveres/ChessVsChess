#include "Store.h"
#include "Board.h"
#include <iostream>

using namespace std;
static Store* store_ = nullptr;

Store* Store::GetSingleton() {

	if (store_ == nullptr) {
		store_ = new Store(new LoaderParams(0, 0, 0, 0));
	}
	return store_;
}

void PieceCard::draw(SDL_Renderer& rend) {
	SDL_Rect pieceCardRect = { (index-1) * (PIECE_CARD_WIDTH),  SCREEN_HEIGHT - PIECE_CARD_HEIGHT, PIECE_CARD_WIDTH, PIECE_CARD_HEIGHT };
	SDL_SetRenderDrawColor(&rend, (index+4)*20, 0, index * 20, 255);
	SDL_RenderFillRect(&rend, &pieceCardRect);
}

void Store::init() {
	pieces[0] = new PieceCard(1, "Pawn", 50);
	pieces[1] = new PieceCard(2, "Rook", 100);
	pieces[2] = new PieceCard(3, "Knight", 125);
	pieces[3] = new PieceCard(4, "Bishop", 125);
	pieces[4] = new PieceCard(5, "Peasant", 25);
}

void Store::draw(SDL_Renderer& rend) {
	for (auto& var : pieces) {
		var->draw(rend);
	}
}

Store::Store(const LoaderParams* pParams) : Object(pParams) {
	init();
}

bool Store::buy(int choice, Board *board) {
	if (money >= pieces[choice - 1]->cost) {
		if (board->setPiece(choice)) {
			money -= pieces[choice - 1]->cost;
			return true;
		}
	}
	return false;
}
