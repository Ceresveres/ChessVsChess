#pragma once
//#include <Windows.h>
#include <string>
#include "raylib.h"

using namespace std;

const int GRID_NUM_Y = 5;
const int GRID_HEIGHT = 100;

const int GRID_NUM_X = 8;
const int GRID_WIDTH = 100;

const int FPS = 30;

const int WINDOW_WIDTH = GRID_NUM_X * (GRID_WIDTH) ;
const int WINDOW_HEIGHT = GRID_NUM_Y * (GRID_HEIGHT);

const int PIECE_CARD_WIDTH = WINDOW_WIDTH / 4;

const int SLEEP_TIME = 100;

void SSetWindowSize(int cols, int lines);
void HHideCursor();
void Goto_XY(const int x, const int y);
void PrintWithColor(const string& str, int colorID= 4);
inline int RANDOM(int x) { return rand() % x; }

enum EnemyType {BASIC, JUMPER, HEAVY, SHIELD};
enum PieceType {PAWN, ROOK, KNIGHT, BISHOP, PEASANT, MAX};