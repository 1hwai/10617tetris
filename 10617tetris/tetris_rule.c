#include "Define.h"

short colmove = 0;
const int POSITION[2] = { COL + 15, ROW + 19 };

void rmPiece(Board* board, Piece* piece) {
	for (int i = 0; i < piece->size; i++)
		for (int j = 0; j < piece->size; j++)
			if (piece->shape[i][j] == 2)
				board->grid[piece->y + i][piece->x + j] = 0;
}

void copyPiece(Piece* p, Piece* piece) {
	//copying piece members to p
	p->x = piece->x;
	p->y = piece->y;
	p->size = piece->size;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			p->shape[i][j] = piece->shape[i][j];
}

void moves(Board* board, Piece* p, Piece* piece) {
	char c;
	static int cnt = 0;
	//x�� ������ ���� �� 1, �ƴϸ� 0
	//���� �ٴ� �� ������
	if (_kbhit()) {
		rmPiece(board, piece);
		copyPiece(p, piece);
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
			case LEFT:
				draw(POSITION[0], POSITION[1], "LEFT");
				p->x--;
				if (valid(board, p, 0)) {
					piece->x--;
				}
				colmove = 1;
				break;
			case RIGHT:
				draw(POSITION[0], POSITION[1], "RIGHT");
				p->x++;
				if (valid(board, p, 0)) {
					piece->x++;
				}
				colmove = 1;
				break;
			case UP:
				draw(POSITION[0], POSITION[1], "UP");
				rotate(p);
				if (valid(board, p, 0)) {
					for (int i = 0; i < piece->size; i++) {
						for (int j = 0; j < piece->size; j++) {
							piece->shape[i][j] = p->shape[i][j];
						}
					}
				}
				colmove = 1;
				cnt = 0;
				break;
			case DOWN:
				draw(POSITION[0], POSITION[1], "DOWN");
				p->y++;
				if (valid(board, p, 0)) {
					piece->y++;
					board->score++;
				}
				board->score += (long long)board->level * 2;
				break;
			}
		}
		else if (c == SPACE) {
			draw(POSITION[0], POSITION[1], "SPACE");
			while (valid(board, p, 0)) {
				piece->y++;
				p->y++;
				board->score += 2;
			}
			board->score += (long long)board->level * 2;
			piece->y--;
			cnt = 40; //�ϵ������� �ٷ� ����
		}
		if (c == ESC) {
			while (1) {
				PlaySound(NULL, 0, 0);
				if (_kbhit()) {
					c = _getch();
					if (c == ENTER) {
						PlaySound(TEXT(TETRIS_BGM), NULL, SND_ASYNC | SND_LOOP);
						break; //return to the game
					}
				}
			}
		}
		if (!colmove && cnt >= 40) {
			p->y++;
			if (!(valid(board, p, 1))) { //�� �̻� �����̴� �� �Ұ����ϴٸ�
				for (int i = 0; i < piece->size; i++) {
					for (int j = 0; j < piece->size; j++) {
						if (piece->shape[i][j] == 2) {
							board->grid[piece->y + i][piece->x + j] = 1;
						}
					}
				}
				board->built = 1;
			}
			cnt = 0;
		}
		else {
			colmove = 0;
			cnt++;
		}
	}
}

void moveDown(Board* board, Piece* p, Piece* piece) {
	static int dt = 0; //delta time;
	static int limit = 48;
	if (board->level <= 8) {
		limit = 48 - board->level * 5;
	}
	else {
		switch (board->level) {
		case 9:
		case 10:
			limit = 15 - board->level;
			break;
		case 13:
			limit = 4;
			break;
		case 16:
			limit = 3;
			break;
		case 19:
			limit = 2;
			break;
		case 29:
			limit = 1;
		}
	}

	//9�ܰ�+�δ� ������ �ƴ� switch case �̹Ƿ�
	//�׽�Ʈ �� 9, 10, 13, 16, 19, 29 �ܰ�� ���� ���� ����.
	//�ܰ� ���� �� board->line�� (level - 1) * 10���� ���� ���� ����.
	if (board->DebugMode) {
		char time[20];
		sprintf_s(time, sizeof(time), "dt: %I32d  limit: %I32d", dt, limit);
		draw(25, 30, time);
	}
	rmPiece(board, piece);
	copyPiece(p, piece);
	if (dt >= limit) {
		p->y++;
		if (valid(board, p, 0)) {
			piece->y++;
		}
		dt = 0;
	}
	else {
		dt++;
	}
	static int cnt = 0;
	if (colmove) {
		cnt = 30;
	}
	if (!colmove && cnt == 50) {
		p->y++;
		if (!(valid(board, p, 1))) { //�� �̻� �����̴� �� �Ұ����ϴٸ�
			for (int i = 0; i < piece->size; i++) {
				for (int j = 0; j < piece->size; j++) {
					if (piece->shape[i][j] == 2) {
						board->grid[piece->y + i][piece->x + j] = 1;
					}
				}
			}
			board->built = 1;
		}
		cnt = 0;
	}
	else {
		colmove = 0;
		cnt++;
	}

	board->level = (board->line + 10) / 10;
}

int valid(Board* board, Piece* p, int mode) {
	int count = 0;
	for (int i = 0; i < p->size; i++) {
		for (int j = 0; j < p->size; j++) {
			int x = p->x + j;
			int y = p->y + i;
			if (p->shape[i][j] == 2) {
				if (board->grid[y][x] == 1) {
					return 0;
				}
				if (!mode) {
					if (x >= 0 && x < 10 && y >= 0 && y < 20) { //border check
						count++;
					}
					else {
						return 0;
					}
				}
				else {
					if (y >= 0 && y < 20) { //border check
						count++;
					}
					else {
						return 0;
					}
				}
			}
		}
	}
	if (count == 4)
		return 1;

	return 0;
}


void checkHeight(Board* board) {
	int countOne = 0;
	for (int i = 19; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (board->grid[i][j] == 1) {
				countOne++;
			}
		}
		if (countOne > 0) {
			board->height = 20 - i;
			if (countOne == 10) {
				for (; i >= 1; i--) {
					for (int j = 0; j < 10; j++) {
						board->grid[i][j] = board->grid[i - 1][j];
					}
				}
				board->line++;
				board->score += 120 + ((long long)board->level - 1) * 10;
			}
		}
		countOne = 0;
	}
}

void rotate(Piece* p) {
	int temp;
	for (int i = 0; i < p->size; i++) {
		for (int j = i; j < p->size; j++) {
			temp = p->shape[i][j]; //p->shape[j][i];
			p->shape[i][j] = p->shape[j][i];
			p->shape[j][i] = temp;
		}
	}
	int tArr[4];
	for (int i = 0, j; i < p->size; i++) {
		for (j = 0; j < p->size; j++)
			tArr[p->size - j - 1] = p->shape[i][j];
		for (j = 0; j < p->size; j++)
			p->shape[i][j] = tArr[j];
	}
}

void spawn(Piece* piece, int queue[2]) {
	queue[0] = queue[1];
	piece->x = 3;
	piece->y = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			piece->shape[i][j] = 0;
		}
	}
	switch (queue[0]) {
	case 1: //I    row col
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->shape[1][3] = 2;
		piece->size = 4;
		piece->color = SKYBLUE;
		break;
	case 2: //O
		piece->x = 4;
		piece->shape[0][0] = 2;
		piece->shape[0][1] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->size = 2;
		piece->color = YELLOW;
		break;
	case 3: //J
		piece->shape[0][0] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		piece->color = BLUE;
		break;
	case 4: //L
		piece->shape[0][2] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		piece->color = ORANGE;
		break;
	case 5: //S
		piece->shape[0][1] = 2;
		piece->shape[0][2] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->size = 3;
		piece->color = GREEN;
		break;
	case 6: //2
		piece->shape[0][0] = 2;
		piece->shape[0][1] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		piece->color = RED;
		break;
	case 7: //T
		piece->shape[0][1] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		piece->color = PURPLE;
		break;
	}
	queue[1] = random(1, 7);
	if (queue[1] == queue[0]) {
		if (random(1, 5) != 3) {
			do {
				queue[1] = random(1, 7);
			} while (queue[1] == queue[0]);
		}
	}
}

void queuePiece(int queue1, int qArr[][4]) {
	switch (queue1) {
	case 1: //I    row col
		qArr[1][0] = 2;
		qArr[1][1] = 2;
		qArr[1][2] = 2;
		qArr[1][3] = 2;
	case 2:
		qArr[0][0] = 2;
		qArr[0][1] = 2;
		qArr[1][0] = 2;
		qArr[1][1] = 2;
		break;
	case 3: //J
		qArr[0][0] = 2;
		qArr[1][0] = 2;
		qArr[1][1] = 2;
		qArr[1][2] = 2;
		break;
	case 4: //L
		qArr[0][2] = 2;
		qArr[1][0] = 2;
		qArr[1][1] = 2;
		qArr[1][2] = 2;
		break;
	case 5: //S
		qArr[0][1] = 2;
		qArr[0][2] = 2;
		qArr[1][0] = 2;
		qArr[1][1] = 2;
		break;
	case 6: //2
		qArr[0][0] = 2;
		qArr[0][1] = 2;
		qArr[1][1] = 2;
		qArr[1][2] = 2;
		break;
	case 7: //T
		qArr[0][1] = 2;
		qArr[1][0] = 2;
		qArr[1][1] = 2;
		qArr[1][2] = 2;
		break;
	}
}