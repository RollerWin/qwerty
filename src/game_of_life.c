#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VERTICAL_LENGTH 25
#define HORIZONTAL_LENGTH 80
#define FINAL_GENERATION 10000

void init_field(int **field);
void print_field(int **field);
void update_field(int **field);
int count_neighbors(int **field, int x, int y);

int speed();
int is_equal_function(int **previous_field, int **field);
int is_alive_function(int **field);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }
    int v;
    if (argv[1][0] == '1') {
        v = 1;
    } else if (argv[1][0] == '2') {
        v = 2;
    } else if (argv[1][0] == '3') {
        v = 3;
    } else if (argv[1][0] == '4') {
        v = 4;
    }
    v = 200000 / v;

    if (v != 0) {
        int **field = malloc(VERTICAL_LENGTH * sizeof(int *));
        for (int i = 0; i < VERTICAL_LENGTH; i++) field[i] = malloc(HORIZONTAL_LENGTH * sizeof(int));

        init_field(field);
        int is_alive = 1;
        int is_equal = 0;
        while (is_alive && !is_equal) {
            print_field(field);
            update_field(field);
            usleep(v);
            is_alive = is_alive_function(field);
        }

        for (int i = 0; i < VERTICAL_LENGTH; i++) free(field[i]);
        free(field);

    } else
        printf("n/a");
    return 0;
}

void init_field(int **field) {
    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
            int init;
            scanf("%d", &init);
            field[i][j] = init;
        }
    }
}

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

void update_field(int **field) {
    int **update_array = malloc(VERTICAL_LENGTH * sizeof(int *));
    for (int i = 0; i < VERTICAL_LENGTH; i++) update_array[i] = malloc(HORIZONTAL_LENGTH * sizeof(int));

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

    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
            field[i][j] = update_array[i][j];
        }
    }

    for (int i = 0; i < VERTICAL_LENGTH; i++) free(update_array[i]);
    free(update_array);
}

int count_neighbors(int **field, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                int row = (x + i + VERTICAL_LENGTH) % VERTICAL_LENGTH;
                int col = (y + j + HORIZONTAL_LENGTH) % HORIZONTAL_LENGTH;
                count += field[row][col];
            }
        }
    }
    return count;
}

int is_equal_function(int **previous_field, int **field) {
    int correct = 1;
    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH; j++) {
            if (previous_field[i][j] != field[i][j]) correct = 0;
        }
    }
    return correct;
}

int is_alive_function(int **field) {
    int correct = 0;
    for (int i = 0; i < VERTICAL_LENGTH && !correct; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH && !correct; j++) {
            if (field[i][j] == 1) correct = 1;
        }
    }
    return correct;
}