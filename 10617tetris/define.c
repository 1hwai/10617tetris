#include "Define.h"

static int nBufferIndex;
static HANDLE hBuffer[2];

void createBuffer()
{
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	ConsoleCursor.dwSize = 1;
	ConsoleCursor.bVisible = 0;
	SetConsoleCursorInfo(hBuffer[0], &ConsoleCursor);
	SetConsoleCursorInfo(hBuffer[1], &ConsoleCursor);
}

void draw(int x, int y, const char* string)
{
	DWORD dw;
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(hBuffer[nBufferIndex], pos);
	WriteFile(hBuffer[nBufferIndex], string, strlen(string), &dw, NULL);
}

void flipBuffer()
{
	SetConsoleActiveScreenBuffer(hBuffer[nBufferIndex]);
	nBufferIndex = !nBufferIndex;
}

void clearBuffer()
{
	COORD start = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nBufferIndex], ' ', 60 * 60, start, &dw);
}

void releaseBuffer()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

int random(int from, int to)
{
	srand(time(NULL));
	return rand() % (to + 1 - from) + from;
}
