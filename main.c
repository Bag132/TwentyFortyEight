#define BOARD_LENGTH 4
#define ARROW_KEY_CODE 224
#define UP_CODE 72
#define DOWN_CODE 80
#define LEFT_CODE 75
#define RIGHT_CODE 77
#define R_LOWER_CODE 114
#define R_UPPER_CODE 82

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// TODO: Re-write entire console. (TUI) Upload compiled exe to git releases. exe should open command window
enum Command {
	LEFT = LEFT_CODE, RIGHT = RIGHT_CODE, UP = UP_CODE, DOWN = DOWN_CODE, RESET
};

int board_length = BOARD_LENGTH;

int board[4][4];

void fill_board(int fill_value);

void display_board();

int spawn_tile();

void shift_left();

void shift_right();

void shift_up();

void shift_down();

enum Command get_command();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main(int argc, char *argv[]) {
	srand(time(NULL) * time(NULL) * time(NULL));
	fill_board(0);

	spawn_tile();
	spawn_tile();

	while (1) {
		display_board();
		enum Command command = get_command();
		if (command == LEFT) {
			shift_left();
			spawn_tile();
		} else if (command == RIGHT) {
			shift_right();
			spawn_tile();
		} else if (command == UP) {
			shift_up();
			spawn_tile();
		} else if (command == DOWN) {
			shift_down();
			spawn_tile();
		} else if (command == RESET) {
			fill_board(0);
			spawn_tile();
			spawn_tile();
		}
	}

	return 0;
}

enum Command get_command() {
	get_key:
	{
		while (!_kbhit());
		int key = _getch();

		if (key == ARROW_KEY_CODE) {
			int direction = _getch();
			if (direction == LEFT) {
				return LEFT;
			} else if (direction == RIGHT) {
				return RIGHT;
			} else if (direction == UP) {
				return UP;
			} else if (direction == DOWN) {
				return DOWN;
			}
		} else if (key == R_LOWER_CODE || key == R_UPPER_CODE) {
			return RESET;
		}
	}
	goto get_key;
}


void shift_left() {
	int newBoard[board_length][board_length];
	int newRowIdx = 0;
	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			newBoard[i][j] = 0;
		}
	}

	for (int row = 0; row < board_length; row++) {
		for (int col = 0; col < board_length; col++) {
			int current = board[row][col];
			int hasNext = col + 1 != board_length;
			int next = 0, nextNumIdx;
			for (int i = col + 1; i < board_length && hasNext; i++) {
				if (board[row][i] != 0) {
					next = board[row][i];
					nextNumIdx = i;
					break; // Spent hours before I realized I needed a break here to make this work
				}
			}

			if (next == 0) {
				newBoard[row][newRowIdx] = current;
				break;
			}

			if (current != 0 && current == next) {
				newBoard[row][newRowIdx++] = current + current;
				board[row][nextNumIdx] = 0;
			} else if (current != 0) {
				newBoard[row][newRowIdx++] = current;
			}
		}
		newRowIdx = 0;
	}

	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			board[i][j] = newBoard[i][j];
		}
	}
}

void shift_right() {
	int newBoard[board_length][board_length];
	int newRowIdx = board_length - 1;

	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			newBoard[i][j] = 0;
		}
	}

	for (int row = 0; row < board_length; row++) {
		for (int col = board_length - 1; col >= 0; col--) {
			int current = board[row][col];
			int hasNext = col - 1 >= 0;
			int next = 0, nextNumIdx = 0;
			for (int i = col - 1; i >= 0 && hasNext; i--) {
				if (board[row][i] != 0) {
					next = board[row][i];
					nextNumIdx = i;
					break;
				}
			}

			if (next == 0) {
				newBoard[row][newRowIdx] = current;
				break;
			}

			if (current != 0 && current == next) {
				newBoard[row][newRowIdx--] = current + current;
				board[row][nextNumIdx] = 0;
			} else if (current != 0) {
				newBoard[row][newRowIdx--] = current;
			}
		}
		newRowIdx = board_length - 1;
	}

	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			board[i][j] = newBoard[i][j];
		}
	}
}

void shift_up() {
	int newBoard[board_length][board_length];
	int newColIdx = 0;

	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			newBoard[i][j] = 0;
		}
	}

	for (int col = 0; col < board_length; col++) {
		for (int row = 0; row < board_length; row++) {
			int current = board[row][col];
			int hasNext = row + 1 != board_length;
			int next = 0, nextIdx = 0;
			for (int i = row + 1; i < board_length && hasNext; i++) {
				if (board[i][col] != 0) {
					next = board[i][col];
					nextIdx = i;
					break;
				}
			}

			if (next == 0) {
				newBoard[newColIdx][col] = current;
				break;
			}

			if (current != 0 && current == next) {
				newBoard[newColIdx++][col] = current + current;
				board[nextIdx][col] = 0;
			} else if (current != 0) {
				newBoard[newColIdx++][col] = current;
			}
		}
		newColIdx = 0;
	}

	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			board[i][j] = newBoard[i][j];
		}
	}
}

void shift_down() {
	int newBoard[board_length][board_length];
	int newColIdx = board_length - 1;

	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			newBoard[i][j] = 0;
		}
	}

	for (int col = 0; col < board_length; col++) {
		for (int row = board_length - 1; row >= 0; row--) {
			int current = board[row][col];
			int hasNext = row - 1 >= 0;
			int next = 0, nextIdx = 0;
			for (int i = row - 1; i >= 0 && hasNext; i--) {
				if (board[i][col] != 0) {
					next = board[i][col];
					nextIdx = i;
					break;
				}
			}

			if (next == 0) {
				newBoard[newColIdx][col] = current;
				break;
			}

			if (current != 0 && current == next) {
				newBoard[newColIdx--][col] = current + current;
				board[nextIdx][col] = 0;
			} else if (current != 0) {
				newBoard[newColIdx--][col] = current;
			}
		}
		newColIdx = board_length - 1;
	}

	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			board[i][j] = newBoard[i][j];
		}
	}
}

int get_random_number(int bound) { // Make better?
	return rand() % bound;
}

int tile_free() {
	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			if (board[i][j] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int spawn_tile() {
	if (!tile_free()) {
		return -1;
	}

	int x, y;
	do {
		x = get_random_number(4), y = get_random_number(4);
	} while (board[y][x] != 0);

	board[y][x] = get_random_number(2) ? 2 : 4;
	return 0;
}

void display_board() {
	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void fill_board(int fill_value) {
	for (int i = 0; i < board_length; i++) {
		for (int j = 0; j < board_length; j++) {
			board[i][j] = fill_value;
		}
	}
}
