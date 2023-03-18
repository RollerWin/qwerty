#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SIZE1 25
#define SIZE2 80

void init_board(int board[SIZE1][SIZE2]);
void print_board(int board[SIZE1][SIZE2]);
void update_board(int board[SIZE1][SIZE2]);
int count_neighbors(int board[SIZE1][SIZE2], int x, int y);


int main() {
    int board[SIZE1][SIZE2];
    init_board(board);
    while(1) {
        
        print_board(board);
        update_board(board);
        usleep (700000);
       
    }
    return 0;
}


void init_board(int board[SIZE1][SIZE2]) 
{
    FILE *file = NULL;
    if(! (file = fopen("txt1.txt","r")))
    {
       printf("open %s failed\n", "txt"); exit(1);
    }

    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            
            board[i][j] = fgetc(file)-48;
           
        }
    }
    fclose(file);
}





void print_board(int board[SIZE1][SIZE2]) {
    for (int p=0;p<40;p++)
        printf("\n");
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            if(board[i][j] == 1)
                printf("*");
            else
                printf(".");
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
   
    for(int i=0; i<SIZE1; i++) {
        int top_neigh = board[(i-1+SIZE1)%SIZE1][SIZE2-1];
        int bot_neigh = board[(i+1)%SIZE1][SIZE2-1];
        if(board[i][SIZE2-1] == 1 && top_neigh+bot_neigh < 2)
            tmp[i][SIZE2-1] = 0;
        else if(board[i][SIZE2-1] == 0 && top_neigh+bot_neigh == 3)
            tmp[i][SIZE2-1] = 1;
        
        top_neigh = board[(i-1+SIZE1)%SIZE1][0];
        bot_neigh = board[(i+1)%SIZE1][0];
        if(board[i][0] == 1 && top_neigh+bot_neigh < 2)
            tmp[i][0] = 0;
        else if(board[i][0] == 0 && top_neigh+bot_neigh == 3)
            tmp[i][0] = 1;
    }
    for(int j=0; j<SIZE2; j++) {
        int left_neigh = board[SIZE1-1][(j-1+SIZE2)%SIZE2];
        int right_neigh = board[SIZE1-1][(j+1)%SIZE2];
        if(board[SIZE1-1][j] == 1 && left_neigh+right_neigh < 2)
            tmp[SIZE1-1][j] = 0;
        else if(board[SIZE1-1][j] == 0 && left_neigh+right_neigh == 3)
            tmp[SIZE1-1][j] = 1;
        
        left_neigh = board[0][(j-1+SIZE2)%SIZE2];
        right_neigh = board[0][(j+1)%SIZE2];
        if(board[0][j] == 1 && left_neigh+right_neigh < 2)
            tmp[0][j] = 0;
        else if(board[0][j] == 0 && left_neigh+right_neigh == 3)
            tmp[0][j] = 1;
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



