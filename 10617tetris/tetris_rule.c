#include "Define.h"

void rmPiece(struct Board* board, struct Piece* piece) {
	for (int i = 0; i < piece->size; i++) {
		for (int j = 0; j < piece->size; j++) {
			if (piece->shape[i][j] == 2) {
				board->grid[piece->y + i][piece->x + j] = 0;
			}
		}
	}
}

void copyPiece(struct Piece* p, struct Piece* piece) {
	//copying piece members to p
	p->x = piece->x;
	p->y = piece->y;
	p->size = piece->size;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			p->shape[i][j] = piece->shape[i][j];
		}
	}
}

void moves(struct Board* board, struct Piece* p, struct Piece* piece, int* built) {
	char c;
	const int keyMessage[2] = { 15, 20 + LINE - 1 };
	int colmove = 0;
	if (_kbhit()) {
		rmPiece(board, piece);
		copyPiece(p, piece);
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
			case LEFT:
				draw(keyMessage[0], keyMessage[1], "LEFT");
				p->x--;
				if (valid(board, p, 0)) {
					piece->x--;
				}
				colmove = 1;
				break;
			case RIGHT:
				draw(keyMessage[0], keyMessage[1], "RIGHT");
				p->x++;
				if (valid(board, p, 0)) {
					piece->x++;
				}
				colmove = 1;
				break;
			case UP:
				draw(keyMessage[0], keyMessage[1], "UP");
				rotate(p);
				if (valid(board, p, 0)) {
					for (int i = 0; i < piece->size; i++) {
						for (int j = 0; j < piece->size; j++) {
							piece->shape[i][j] = p->shape[i][j];
						}
					}
				}
				break;
			case DOWN:
				draw(keyMessage[0], keyMessage[1], "DOWN");
				p->y++;
				if (valid(board, p, 0)) {
					piece->y++;
					board->score++;
				}
				break;
			}
		}
		else if (c == 32) {
			draw(keyMessage[0], keyMessage[1], "SPACE");
			while (valid(board, p, 0)) {
				piece->y++;
				p->y++;
				board->score++;
			}
			piece->y--;
			p->y--;
		}
		else if (c == 27) {
			while (1) {
				if (_kbhit()) {
					c = _getch();
					if (c == 27) {
						break;
					}
				}
			}
		}

		p->y++;
		if (!(valid(board, p, 1))) {
			if (colmove == 0) {
				for (int i = 0; i < piece->size; i++) {
					for (int j = 0; j < piece->size; j++) {
						if (piece->shape[i][j] == 2) {
							board->grid[piece->y + i][piece->x + j] = 1;
						}
					}
				}
				*built = 1;
			}
			else {
				colmove = 0;
			}
		}
	}
}

void moveDown(struct Board* board, struct Piece* p, struct Piece* piece, int* built) {
	static int dt = 0; //delta time;
	dt++;
	rmPiece(board, piece);
	copyPiece(p, piece);
	if (dt == 5 - board->level) {
		p->y++;
		if (valid(board, p, 0)) {
			piece->y++;
		}
		dt = 0;
	}
	p->y++;
	if (!(valid(board, p, 1))) {

		for (int i = 0; i < piece->size; i++) {
			for (int j = 0; j < piece->size; j++) {
				if (piece->shape[i][j] == 2) {
					board->grid[piece->y + i][piece->x + j] = 1;
				}
			}
		}
		*built = 1;
	}
	board->level = (board->line + 10) / 10;
}

int valid(struct Board* board, struct Piece* p, int mode) {
	int count = 0;
	char str1[20];
	draw(40, LINE, "Debug");
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			sprintf_s(str1, sizeof(str1), "%d ", board->grid[i][j]);
			draw(j + 40, i + LINE + 1, str1);
		}
	}
	for (int i = 0; i < p->size; i++) {
		for (int j = 0; j < p->size; j++) {
			int x = p->x + j;
			int y = p->y + i;
			if (p->shape[i][j] == 2) {
				if (board->grid[y][x] == 1) {
					//draw(25, 20, "111");
					return 0;
				}
				if (mode == 0) {
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
	if (count == 4) {
		return 1;
	}
}


void checkHeight(struct Board* board) {
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
			}
		}
		countOne = 0;
	}
	
}

int rotate(struct Piece* p) {
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
		for (j = 0; j < p->size; j++) {
			tArr[p->size - j - 1] = p->shape[i][j];
		}
		for (j = 0; j < p->size; j++) {
			p->shape[i][j] = tArr[j];
		}
	}
}

void spawn(struct Piece* piece, int queue[2]) {
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
		break;
		//0 1 2 3 4
		//ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ
		//     ㅁㅁㅁㅁ
		//       ㅁ
		//       ㅁ
		//       ㅁ
		//       ㅁ
	case 2: //O
		piece->x = 4;
		piece->shape[0][0] = 2;
		piece->shape[0][1] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->size = 2;
		break;
		//0 1 2 3 4
		//ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ
		//       ㅁㅁㅁㅁ
		//       ㅁㅁ
		//       ㅁㅁ
	case 3: //J
		piece->shape[0][0] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		break;
	case 4: //L
		piece->shape[0][2] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		break;
	case 5: //S
		piece->shape[0][1] = 2;
		piece->shape[0][2] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->size = 3;
		break;
	case 6: //2
		piece->shape[0][0] = 2;
		piece->shape[0][1] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		break;
	case 7: //T
		piece->shape[0][1] = 2;
		piece->shape[1][0] = 2;
		piece->shape[1][1] = 2;
		piece->shape[1][2] = 2;
		piece->size = 3;
		break;
	}
	queue[1] = random(1, 7);
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
