#pragma once
#include <Windows.h>
#include <string>

using namespace std;

const int GRID_NUM_Y = 5;
const int GRID_HEIGHT = 5;

const int GRID_NUM_X = 9;
const int GRID_WIDTH = 10;

const int WINDOW_WIDTH = GRID_NUM_X * (GRID_WIDTH + 1) + 1;
const int WINDOW_HEIGHT = GRID_NUM_Y * (GRID_HEIGHT + 1) + 20;

const int BOX_WIDTH = 100;
const int BOX_HEIGHT = 100;

const int SCREEN_WIDTH = BOX_WIDTH * GRID_NUM_X;
const int SCREEN_HEIGHT = BOX_HEIGHT * GRID_NUM_Y;

const int PIECE_CARD_WIDTH = WINDOW_WIDTH / 4;

const int SLEEP_TIME = 100;

void SetWindowSize(int cols, int lines);
void HideCursor();
void Goto_XY(const int x, const int y);
void PrintWithColor(const string& str, int colorID= FOREGROUND_INTENSITY);
inline int RANDOM(int x) { return rand() % x; }

enum EnemyType {BASIC, JUMPER, HEAVY, SHIELD};
enum PieceType {PAWN, ROOK, KNIGHT, BISHOP, PEASANT, MAX};