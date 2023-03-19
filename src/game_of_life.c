#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define VERTICAL_LENGTH 25
#define HORIZONTAL_LENGTH 81

//--Объявление функций-------------------------------------
void init_field(int field[][HORIZONTAL_LENGTH]);
void print_field(int field[][HORIZONTAL_LENGTH]);
void update_field(int field[][HORIZONTAL_LENGTH]);
int count_neighbors(int field[][HORIZONTAL_LENGTH], int x, int y);
int speed();

//----------------------------------------------------------
int main() {
    int v = speed();
    if (v !=0) {
    int field[VERTICAL_LENGTH][HORIZONTAL_LENGTH];
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
void init_field(int field[][HORIZONTAL_LENGTH]) 
{
    FILE *file = NULL;
    if(! (file = fopen("txt1.txt","r")))
    {
       printf("open %s failed\n", "txt"); exit(1);
    }

    for(int i=0; i<VERTICAL_LENGTH; i++) {
        for(int j=0; j<HORIZONTAL_LENGTH; j++) {
            
            field[i][j] = fgetc(file)-48;
           
        }
    }
    fclose(file);
}

//--Отрисовка данных массива---------------------------------
void print_field(int field[][HORIZONTAL_LENGTH]) {
    system("clear");
    for(int i=0; i<VERTICAL_LENGTH; i++) {
        for(int j=0; j<HORIZONTAL_LENGTH; j++) {
            if(field[i][j] == 1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

//--Обновление данных массива и проверка---------------------- 
void update_field(int field[][HORIZONTAL_LENGTH]) {
 int update_array[VERTICAL_LENGTH][HORIZONTAL_LENGTH];
    //Определяем, выживет ли клетка?
    for(int i=0; i<VERTICAL_LENGTH; i++) {
        for(int j=0; j<HORIZONTAL_LENGTH; j++) {
            int neighbors = count_neighbors(field, i, j);
            if(field[i][j] == 1 && (neighbors < 2 || neighbors > 3))
                update_array[i][j] = 0;
            else if(field[i][j] == 0 && neighbors == 3)
                update_array[i][j] = 1;
            else
                update_array[i][j] = field[i][j];
        }
    }
    for(int i=0; i<VERTICAL_LENGTH; i++) {
        for(int j=0; j<HORIZONTAL_LENGTH; j++) {
            field[i][j] = update_array[i][j];
        }
    }
   
    // for(int i=0; i<VERTICAL_LENGTH; i++) {
    //     int top_neigh = field[(i-1+VERTICAL_LENGTH)%VERTICAL_LENGTH][HORIZONTAL_LENGTH-1];
    //     int bot_neigh = field[(i+1)%VERTICAL_LENGTH][HORIZONTAL_LENGTH-1];
    //     if(field[i][HORIZONTAL_LENGTH-1] == 1 && top_neigh+bot_neigh < 2)
    //         update_array[i][HORIZONTAL_LENGTH-1] = 0;
    //     else if(field[i][HORIZONTAL_LENGTH-1] == 0 && top_neigh+bot_neigh == 3)
    //         update_array[i][HORIZONTAL_LENGTH-1] = 1;
        
    //     top_neigh = field[(i-1+VERTICAL_LENGTH)%VERTICAL_LENGTH][0];
    //     bot_neigh = field[(i+1)%VERTICAL_LENGTH][0];
    //     if(field[i][0] == 1 && top_neigh+bot_neigh < 2)
    //         update_array[i][0] = 0;
    //     else if(field[i][0] == 0 && top_neigh+bot_neigh == 3)
    //         update_array[i][0] = 1;
    // }
    // for(int j=0; j<HORIZONTAL_LENGTH; j++) {
    //     int left_neigh = field[VERTICAL_LENGTH-1][(j-1+HORIZONTAL_LENGTH)%HORIZONTAL_LENGTH];
    //     int right_neigh = field[VERTICAL_LENGTH-1][(j+1)%HORIZONTAL_LENGTH];
    //     if(field[VERTICAL_LENGTH-1][j] == 1 && left_neigh+right_neigh < 2)
    //         update_array[VERTICAL_LENGTH-1][j] = 0;
    //     else if(field[VERTICAL_LENGTH-1][j] == 0 && left_neigh+right_neigh == 3)
    //         update_array[VERTICAL_LENGTH-1][j] = 1;
        
    //     left_neigh = field[0][(j-1+HORIZONTAL_LENGTH)%HORIZONTAL_LENGTH];
    //     right_neigh = field[0][(j+1)%HORIZONTAL_LENGTH];
    //     if(field[0][j] == 1 && left_neigh+right_neigh < 2)
    //         update_array[0][j] = 0;
    //     else if(field[0][j] == 0 && left_neigh+right_neigh == 3)
    //         update_array[0][j] = 1;
    // }
   
    // for(int i=0; i<VERTICAL_LENGTH; i++) {
    //     for(int j=0; j<HORIZONTAL_LENGTH; j++) {
    //         field[i][j] = update_array[i][j];
    //     }
    // }
}

//--Подсчёт соседей-------------------------------------------
int count_neighbors(int field[][HORIZONTAL_LENGTH], int x, int y) {
      int count = 0;
    for(int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
            if(i == 0 && j == 0)
                continue;
            int row = (x + i + VERTICAL_LENGTH) % VERTICAL_LENGTH;
            int col = (y + j + HORIZONTAL_LENGTH) % HORIZONTAL_LENGTH;
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

