#define LEFT 75
#define UP 72
#define RIGHT 77
#define DOWN 80
#define SPACE 32
#define ENTER 13
#define ALT 18
#define ESC 27
#define ROW 8
#define COL 15
#define final const

//==== Tetris Piece color setting
#define BLUE 1
#define GREEN 2
#define SKYBLUE 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define ORANGE 14

//BGM
#define TETRIS_BGM "../audio/Tetris.wav"

#pragma once
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

struct Piece {
	int shape[4][4];
	int size; //2, 3, 4 (a.k.a. hit box)
	int x, y;
	int color;
} typedef Piece;

struct Board {
	int grid[20][10];
	int height, level, line;
	long long score;
	int queue[2];
	short built, DebugMode;
} typedef Board;

void createBuffer();
void flipBuffer();
void clearBuffer();
void releaseBuffer();
void draw(int x, int y, const char* string);
int random(int from, int to);
void textColor(int color);

void rmPiece(Board* board, Piece* piece);
void copyPiece(Piece* p, Piece* piece);
void moves(Board* board, Piece* p, Piece* piece);
int valid(Board* board, Piece* p, int mode);
void moveDown(Board* board, Piece* p, Piece* piece);
void checkHeight(Board* board);
void rotate(Piece* p);
void spawn(Piece* piece, int queue[2]);
void queuePiece(int queue1, int qArr[][4]);