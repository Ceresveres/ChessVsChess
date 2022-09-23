#include "Store.h"
#include "Board.h"
#include <iostream>

using namespace std;
static Store* store_ = nullptr;

void PieceCard::print(SDL_Renderer& rend) {
	SDL_Rect pieceCardRect = { (index-1) * (PIECE_CARD_WIDTH),  SCREEN_HEIGHT - PIECE_CARD_HEIGHT, PIECE_CARD_WIDTH, PIECE_CARD_HEIGHT };
	SDL_SetRenderDrawColor(&rend, (index+4)*20, 0, index * 20, 255);
	SDL_RenderFillRect(&rend, &pieceCardRect);
}

void Store::printStore(SDL_Renderer& rend) {
	for (auto& var : pieces) {
		var->print(rend);
	}
}


//void Store::init() {
//	Goto_XY(2, (GRID_HEIGHT + 1) * GRID_NUM_Y + 1);
//	PrintWithColor("Store");
//	Goto_XY(0, (GRID_HEIGHT + 1) * GRID_NUM_Y + 2);
//	string str(WINDOW_WIDTH, '-');
//	PrintWithColor(str);
//	refreshMoney();
//	Store* GetInstance();
//	//for (auto& var : pieces) {
//	//	var->print();
//	//}
//}
Store *Store::GetInstance(SDL_Renderer& rend) {

	if (store_ == nullptr) {
		store_ = new Store(rend);
	}
	return store_;
}

bool Store::buy(int choice, Board *board) {
	if (money >= pieces[choice - 1]->cost) {
		if (board->setPiece(choice)) {
			money -= pieces[choice - 1]->cost;
			refreshMoney();
			return true;
		}
	}
	return false;
}

void Store::refreshMoney() {
	string str(20, ' ');
	Goto_XY(WINDOW_WIDTH - 10, (GRID_HEIGHT + 1) * GRID_NUM_Y + 1);
	PrintWithColor(str);
	
	Goto_XY(WINDOW_WIDTH - 10, (GRID_HEIGHT + 1) * GRID_NUM_Y + 1);
	PrintWithColor("Bank: $" + to_string(money));
}