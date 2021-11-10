#include "Define.h"
//게임 시작용
void init() {}
//업데이트용
void update() {}
//렌더용
void render() {
	draw(5, 5, "dfsfsf");
}
//게임 종료용
void release() {}

int main() {
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	createBuffer();
	init();

	while (1) {
		clearBuffer();
		update();
		render();
		flipBuffer();
		Sleep(frameDelay);
	}

	render();
	release();
	releaseBuffer();


	return 0;
}
/*#include "Define.h"

	//게임 시작용
	void init() {}
	//업데이트용
	void update() {}
	//렌더용
	void render(int board[][10]) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				board[i][j] = 0;
				printf("%d ", board[i][j]);
			}
			printf("\n");
		}
	}
	//게임 종료용
	void release() {}

	static int dAddress[3];

	int newPiece(int* size) {
		int rn = random(1, 1);
		switch (rn) {
		case 1:
			*size = 4;
			break;
		}
		int** piece = malloc(sizeof(int*) * *size);
		for (int i = 0; i < *size; i++) {
			piece[i] = malloc(sizeof(int) * *size);
		}
		int temp = &piece[0][0];
		for (int i = 0; i < *size; i++) {
			for (int j = 0; j < *size; j++) {
				piece[i][j] = 0;
				printf("%d ", &piece[i][j]);
			}
			printf("\n");
			if (i >= 1) {
				dAddress[i - 1] = &piece[i][0] - &piece[i - 1][0];
				printf("%d - %d\n", &piece[i - 1][0], &piece[i][0]);
			}
		}
		printf("\n========\n");
		for (int i = 0; i < *size - 1; i++) {
			printf("%d ", dAddress[i]);
		}
		printf("\n========\n");

		printf("\n22========\n");
		printf("정답 : &piece[1][0] = %d ", &piece[1][0]);
		printf("&piece[1][0] = %d\n", &piece[0][0] + dAddress[0]);
		printf("정답 : &piece[2][0] = %d ", &piece[2][0]);
		printf("&piece[1][0] = %d\n", &piece[1][0] + dAddress[1]);
		printf("정답 : &piece[3][0] = %d ", &piece[3][0]);
		printf("&piece[1][0] = %d", &piece[2][0] + dAddress[2]);
		printf("\n========\n");

		return &piece[0][0];
	}

	int main() {
		const int fps = 60;
		const int frameDelay = 1000 / fps;
		int board[21][12] = { 0 };
		//I O J L 2 S T;
		//4 2 3 3 3 3 3;
		int size;
		int* piece = newPiece(&size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("%d ", *(piece));
			}
			printf("\n");
		}
		//printf("%d\n", piece);
		/*for (int i = 0; i < 16; i++) {
			printf("%d ", *(piece + i));
			printf("\n");
		}*/

		/*for (int i = 0; ; i++) {
			if (piece + i == 1) {
				printf("%d\n", piece + i);
				break;
			}
		}
	return 0;*/