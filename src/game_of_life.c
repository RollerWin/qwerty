#include <stdio.h>

#define LENGTH 80
#define HEIGHT 25

void draw(int**a, const int n, const int m);
void init(int a[][LENGTH]);


int main(void) {

    const int x1 = 0;
    const int y1 = 0;

    int field[HEIGHT][LENGTH];



    return 0;
}


#define SIZE1 80
#define SIZE2 25

void init_board(int board[80][25]) {
    for(int i=0; i<80; i++) {
        for(int j=0; j<25; j++) {
            board[i][j] = rand() % 2;
        }
    }
}

void print_board(int board[SIZE1][SIZE2]) {
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            if(board[i][j] == 1)
                printf("* ");
            else
                printf(". ");
        }
        printf("\n");
    }
}


void update_board(int board[SIZE1][SIZE2]) {
    int tmp[SIZE1][SIZE2];
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            int neighbors = count_neighbors(board, i, j);
            if(board[i][j] == 1 && (neighbors < 2 || neighbors > 3))
                tmp[i][j] = 0;
            else if(board[i][j] == 0 && neighbors == 3)
                tmp[i][j] = 1;
            else
                tmp[i][j] = board[i][j];
        }
    }
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            board[i][j] = tmp[i][j];
        }
    }
}

int count_neighbors(int board[SIZE1][SIZE2], int x, int y) {
    int count = 0;
    for(int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
            if(i == 0 && j == 0)
                continue;
            int row = (x + i + SIZE1) % SIZE1;
            int col = (y + j + SIZE2) % SIZE2;
            count += board[row][col];
        }
    }
    return count;
}

int main() {
    int board[SIZE1][SIZE2];
    init_board(board);
    while(1) {
        print_board(board);
        update_board(board);
    }
    return 0;
}
