#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SIZE1 25
#define SIZE2 80

//--Объявление функций-------------------------------------
void init_field(int field[][SIZE2]);
void print_field(int field[][SIZE2]);
void update_field(int field[][SIZE2]);
int count_neighbors(int field[][SIZE2], int x, int y);
int speed();

//----------------------------------------------------------
int main() {
    int v = speed();
    if (v !=0) {
    int field[SIZE1][SIZE2];
    init_field(field);
    while(1) {
        
        print_field(field);
        update_field(field);
        usleep (v);
       
    }
    }
    else printf("нормально вводи блядь!!!");
    return 0;
}

//--Инициализация через файл---------------------------------
void init_field(int field[][SIZE2]) 
{
    FILE *file = NULL;
    if(! (file = fopen("txt1.txt","r")))
    {
       printf("open %s failed\n", "txt"); exit(1);
    }

    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            
            field[i][j] = fgetc(file)-48;
           
        }
    }
    fclose(file);
}

//--Отрисовка данных массива---------------------------------
void print_field(int field[][SIZE2]) {
    system("clear");
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            if(field[i][j] == 1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

//--Обновление данных массива и проверка---------------------- 
void update_field(int field[][SIZE2]) {
 int tmp[SIZE1][SIZE2];
    //Определяем, выживет ли клетка?
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            int neighbors = count_neighbors(field, i, j);
            if(field[i][j] == 1 && (neighbors < 2 || neighbors > 3))
                tmp[i][j] = 0;
            else if(field[i][j] == 0 && neighbors == 3)
                tmp[i][j] = 1;
            else
                tmp[i][j] = field[i][j];
        }
    }
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            field[i][j] = tmp[i][j];
        }
    }
   
    for(int i=0; i<SIZE1; i++) {
        int top_neigh = field[(i-1+SIZE1)%SIZE1][SIZE2-1];
        int bot_neigh = field[(i+1)%SIZE1][SIZE2-1];
        if(field[i][SIZE2-1] == 1 && top_neigh+bot_neigh < 2)
            tmp[i][SIZE2-1] = 0;
        else if(field[i][SIZE2-1] == 0 && top_neigh+bot_neigh == 3)
            tmp[i][SIZE2-1] = 1;
        
        top_neigh = field[(i-1+SIZE1)%SIZE1][0];
        bot_neigh = field[(i+1)%SIZE1][0];
        if(field[i][0] == 1 && top_neigh+bot_neigh < 2)
            tmp[i][0] = 0;
        else if(field[i][0] == 0 && top_neigh+bot_neigh == 3)
            tmp[i][0] = 1;
    }
    for(int j=0; j<SIZE2; j++) {
        int left_neigh = field[SIZE1-1][(j-1+SIZE2)%SIZE2];
        int right_neigh = field[SIZE1-1][(j+1)%SIZE2];
        if(field[SIZE1-1][j] == 1 && left_neigh+right_neigh < 2)
            tmp[SIZE1-1][j] = 0;
        else if(field[SIZE1-1][j] == 0 && left_neigh+right_neigh == 3)
            tmp[SIZE1-1][j] = 1;
        
        left_neigh = field[0][(j-1+SIZE2)%SIZE2];
        right_neigh = field[0][(j+1)%SIZE2];
        if(field[0][j] == 1 && left_neigh+right_neigh < 2)
            tmp[0][j] = 0;
        else if(field[0][j] == 0 && left_neigh+right_neigh == 3)
            tmp[0][j] = 1;
    }
   
    for(int i=0; i<SIZE1; i++) {
        for(int j=0; j<SIZE2; j++) {
            field[i][j] = tmp[i][j];
        }
    }
}

//--Подсчёт соседей-------------------------------------------
int count_neighbors(int field[][SIZE2], int x, int y) {
      int count = 0;
    for(int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
            if(i == 0 && j == 0)
                continue;
            int row = (x + i + SIZE1) % SIZE1;
            int col = (y + j + SIZE2) % SIZE2;
            count += field[row][col];
        }
    }
    return count;
}

//--Регулировка скорости--------------------------------------
int speed() {
int v=1;
if (scanf("%d", &v)==1 && v>0)
    v = 200000/v;
else v = 0;
return v;
}

