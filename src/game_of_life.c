/*1. Создать функцию, которая будет инициализировать игровое поле. Например:*/
#include <stdio.h>
#define SIZE1 80
#define SIZE2 25

void init_board(int board[80][25]) {
    for(int i=0; i<80; i++) {
        for(int j=0; j<25; j++) {
            board[i][j] = rand() % 2;
        }
    }
}


/*Эта функция заполняет игровое поле случайными значениями (0 или 1).

2. Создать функцию, которая будет отображать игровое поле на экране. Например:*/


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


/*Эта функция выводит на экран содержимое игрового поля.

3. Создать функцию, которая будет обновлять игровое поле. Например:*/


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


/*Эта функция применяет правила игры к текущему состоянию игрового поля и создает новое состояние.

4. Написать главную функцию, которая будет запускать игру. Например:*/

int main() {
    int board[SIZE1][SIZE2];
    init_board(board);
    while(1) {
        system("cls"); // очистка экрана в Windows
        print_board(board);
        update_board(board);
        // здесь может быть пауза или задержка
    }
    return 0;
}
