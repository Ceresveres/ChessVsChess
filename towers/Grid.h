//#pragma once
//#include "Object.h"
//#include "Board.h"
//
//class Piece;
//class Invader;
//class Grid : public Object {
//public:
//	Grid(int x, int y, Board* board);
//
//	virtual ~Grid() = default;				 // destructor (virtual if X is meant to be a base class)
//	Grid(const Grid&) = default;             // copy constructor
//	Grid& operator=(const Grid&) = default;  // copy assignment
//	Grid(Grid&&) = default;                  // move constructor
//	Grid& operator=(Grid&&) = default;       // move assignment
//
//	void setColor(int choice);
//
//	virtual void draw();
//
//	bool setPiece();
//	bool hasPiece() const;
//	void updatePiece();
//	void attackPiece(int attack);
//	void delPiece();
//
//	void addInvader(Invader* iInvader);
//	bool hasInvaders() const;
//	void damageInvader(Invader* iInvader, int damage);
//	void judgeAttacking();
//	void delInvader(Invader* iInvader);
//
//	void setSelected() { selected = true; }
//	void setUnSelected() { selected = false; }
//
//private:
//	int color[4]{};
//	std::unique_ptr<Piece> piece;
//	vector<Invader*> invaders {};
//	PositionComponent pos;
//	SizeComponent size;
//	Board* board;
//	bool selected{ false };
//};