#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VERTICAL_LENGTH 25
#define HORIZONTAL_LENGTH 80
#define FINAL_GENERATION 100

//--Объявление функций-------------------------------------
void init_field(int **field);
void print_field(int **field);
void update_field(int **field);
int count_neighbors(int **field, int x, int y);

// void init_field(int field[][HORIZONTAL_LENGTH]);
// void print_field(int field[][HORIZONTAL_LENGTH]);
// void update_field(int field[][HORIZONTAL_LENGTH]);
// int count_neighbors(int field[][HORIZONTAL_LENGTH], int x, int y);
int speed();
//int is_equal_function(int **previous_field, int **field);
int is_alive_function(int **field);

//----------------------------------------------------------
int main() {
    int v = speed();
    if (v != 0) {
        int **field = malloc(VERTICAL_LENGTH * sizeof(int *));
        for (int i = 0; i < VERTICAL_LENGTH; i++) field[i] = malloc(HORIZONTAL_LENGTH * sizeof(int));
        
        // int field[VERTICAL_LENGTH][HORIZONTAL_LENGTH];
        init_field(field);
        int current_generation = 1;
        int is_alive = 1;
        while (is_alive && current_generation != FINAL_GENERATION) {
            print_field(field);
            update_field(field);
            usleep(v);
            current_generation++;
            is_alive = is_alive_function(field);
        }

        for (int i = 0; i < VERTICAL_LENGTH; i++) free(field[i]);
        free(field);

    } else
        printf("n/a");
    return 0;
}

//--Инициализация через файл---------------------------------

void init_field(int **field) {
    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
            int initt;
            // char init;
            scanf("%d", &initt);
            field[i][j] = initt;
        }
    }
}

// void init_field(int field[][HORIZONTAL_LENGTH]) {
//     for (int i = 0; i < VERTICAL_LENGTH; i++) {
//         for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
//             int init;
//             scanf("%d", &init);
//             field[i][j] = init;
//         }
//     }
// }

//--Отрисовка данных массива---------------------------------

void print_field(int **field) {
    system("clear");
    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
            if (field[i][j] == 1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

// void print_field(int field[][HORIZONTAL_LENGTH]) {
//     system("clear");
//     for (int i = 0; i < VERTICAL_LENGTH; i++) {
//         for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
//             if (field[i][j] == 1)
//                 printf("*");
//             else
//                 printf(".");
//         }
//         printf("\n");
//     }
// }

//--Обновление данных массива и проверка----------------------

void update_field(int **field) {
    // int update_array[VERTICAL_LENGTH][HORIZONTAL_LENGTH];
    int **update_array = malloc(VERTICAL_LENGTH * sizeof(int *));
    for (int i = 0; i < VERTICAL_LENGTH; i++) update_array[i] = malloc(HORIZONTAL_LENGTH * sizeof(int));

    //Определяем, выживет ли клетка?
    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
            int neighbors = count_neighbors(field, i, j);
            if (field[i][j] == 1 && (neighbors < 2 || neighbors > 3))
                update_array[i][j] = 0;
            else if (field[i][j] == 0 && neighbors == 3)
                update_array[i][j] = 1;
            else
                update_array[i][j] = field[i][j];
        }
    }

    //*is_alive = is_alive_function(field, update_array);

    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
            field[i][j] = update_array[i][j];
        }
    }

    for (int i = 0; i < VERTICAL_LENGTH; i++) free(update_array[i]);
    free(update_array);
}

// void update_field(int field[][HORIZONTAL_LENGTH]) {
//     int update_array[VERTICAL_LENGTH][HORIZONTAL_LENGTH];
//     //Определяем, выживет ли клетка?
//     for (int i = 0; i < VERTICAL_LENGTH; i++) {
//         for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
//             int neighbors = count_neighbors(field, i, j);
//             if (field[i][j] == 1 && (neighbors < 2 || neighbors > 3))
//                 update_array[i][j] = 0;
//             else if (field[i][j] == 0 && neighbors == 3)
//                 update_array[i][j] = 1;
//             else
//                 update_array[i][j] = field[i][j];
//         }
//     }
//     for (int i = 0; i < VERTICAL_LENGTH; i++) {
//         for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
//             field[i][j] = update_array[i][j];
//         }
//     }
// }

//--Подсчёт соседей-------------------------------------------

int count_neighbors(int **field, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int row = (x + i + VERTICAL_LENGTH) % VERTICAL_LENGTH;
            int col = (y + j + HORIZONTAL_LENGTH) % HORIZONTAL_LENGTH;
            count += field[row][col];
        }
    }
    return count;
}

// int count_neighbors(int field[][HORIZONTAL_LENGTH], int x, int y) {
//     int count = 0;
//     for (int i = -1; i <= 1; i++) {
//         for (int j = -1; j <= 1; j++) {
//             if (i == 0 && j == 0) continue;
//             int row = (x + i + VERTICAL_LENGTH) % VERTICAL_LENGTH;
//             int col = (y + j + HORIZONTAL_LENGTH) % HORIZONTAL_LENGTH;
//             count += field[row][col];
//         }
//     }
//     return count;
// }

//--Регулировка скорости--------------------------------------
int speed() {
    int v = 1;
    if (scanf("%d", &v) == 1 && v > 0)
        v = 200000 / v;
    else
        v = 0;
    return v;
}

// int is_equal_function(int **previous_field, int **field) {
//     int correct = 1;
//     for(int i = 0; i < VERTICAL_LENGTH; i++) {
//         for(int j = 0; j < HORIZONTAL_LENGTH; j++) {
//             if(previous_field[i][j] != field[i][j]) correct = 0;
//         }
//     }
//     return correct;
// }

int is_alive_function(int **field) {
    int correct = 0;
    for(int i = 0; i < VERTICAL_LENGTH && !correct; i++) {
        for(int j = 0; j < HORIZONTAL_LENGTH && !correct; j++) {
            if(field[i][j] == 1) correct = 1;
        }
    }
    return correct;
}