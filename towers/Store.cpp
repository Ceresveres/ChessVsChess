//#include "Store.h"
//#include "Board.h"
//#include <iostream>
//
//using namespace std;
//static Store* store_ = nullptr;
//
//Store* Store::GetSingleton() {
//
//	if (store_ == nullptr) {
//		store_ = new Store();
//	}
//	return store_;
//}
//
//void PieceCard::draw() {
//	SDL_Rect pieceCardRect = { (index-1) * (PIECE_CARD_WIDTH),  SCREEN_HEIGHT - PIECE_CARD_HEIGHT, PIECE_CARD_WIDTH, PIECE_CARD_HEIGHT };
//	int tmpColor[4] = { (index + 4) * 20, 0,  index * 20, 255 };
//	TextureManager::GetSingletonInstance()->drawTemp(pieceCardRect, tmpColor);
//}
//
//void Store::init() {
//	pieces[0] = new PieceCard(1, "Pawn", 50);
//	pieces[1] = new PieceCard(2, "Rook", 100);
//	pieces[2] = new PieceCard(3, "Knight", 125);
//	pieces[3] = new PieceCard(4, "Bishop", 125);
//	pieces[4] = new PieceCard(5, "Peasant", 25);
//}
//
//void Store::draw() {
//	for (auto& var : pieces) {
//		var->draw();
//	}
//}
//
//Store::Store() {
//	init();
//}
//
//bool Store::buy(int choice, Board *board) {
//	if (money >= pieces[choice - 1]->cost) {
//		if (board->setPiece(choice)) {
//			money -= pieces[choice - 1]->cost;
//			return true;
//		}
//	}
//	return false;
//}
