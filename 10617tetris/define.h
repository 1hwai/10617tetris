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

void createBuffer();
void flipBuffer();
void clearBuffer();
void releaseBuffer();
void draw(int x, int y, const char* string);
int random(int from, int to);
void textColor(int color);
//=====
void rmPiece(struct Board* board, struct Piece* piece);
void copyPiece(struct Piece* p, struct Piece* piece);
void moves(struct Board* board, struct Piece* p, struct Piece* piece);
int valid(struct Board* board, struct Piece* p, int mode);
void moveDown(struct Board* board, struct Piece* p, struct Piece* piece);
void checkHeight(struct Board* board);
void rotate(struct Piece* p);
void spawn(struct Piece* piece, int queue[2]);
void queuePiece(int queue1, int qArr[][4]);

struct Piece {
	int shape[4][4];
	int size; //2, 3, 4
	int x, y;
	int color;
};

struct Board {
	int grid[20][10];
	int height, level, line;
	long long score;
	int queue[2];
	int built, DebugMode;
};
