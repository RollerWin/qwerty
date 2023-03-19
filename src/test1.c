#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ROWS 25
#define COLS 80

void initialize_board(int board[][COLS]) {
  int row, col;
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      board[row][col] = rand() % 2;
    }
  }
}

void print_board(int board[][COLS]) {
  int row, col;
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      if (board[row][col] == 1)
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
}

int count_neighbors(int board[][COLS], int row, int col) {
  int count = 0;
  // check north
  if (row > 0 && board[row-1][col] == 1) count++;
  // check south
  if (row < ROWS-1 && board[row+1][col] == 1) count++;
  // check west
  if (col > 0 && board[row][col-1] == 1) count++;
  // check east
  if (col < COLS-1 && board[row][col+1] == 1) count++;
  // check northwest
  if (row > 0 && col > 0 && board[row-1][col-1] == 1) count++;
  // check northeast
  if (row > 0 && col < COLS-1 && board[row-1][col+1] == 1) count++;
  // check southwest
  if (row < ROWS-1 && col > 0 && board[row+1][col-1] == 1) count++;
  // check southeast
  if (row < ROWS-1 && col < COLS-1 && board[row+1][col+1] == 1) count++;
  return count;
}

void next_generation(int board[][COLS]) {
  int row, col;
  int new_board[ROWS][COLS];
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      int neighbors = count_neighbors(board, row, col);
      if (board[row][col] == 1 && neighbors < 2) new_board[row][col] = 0;
      else if (board[row][col] == 1 && neighbors > 3) new_board[row][col] = 0;
      else if (board[row][col] == 0 && neighbors == 3) new_board[row][col] = 1;
      else new_board[row][col] = board[row][col];
    }
  }
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      board[row][col] = new_board[row][col];
    }
  }
}

int main() {
  int board[ROWS][COLS];
  srand(time(NULL));
  initialize_board(board);
  while (1) {
    print_board(board);
    next_generation(board);
    sleep(1);
  }
  return 0;
}
