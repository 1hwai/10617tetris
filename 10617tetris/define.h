#pragma once
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

void createBuffer();
void flipBuffer();
void clearBuffer();
void releaseBuffer();
void draw(int x, int y, const char* string);
int random(int from, int to);