#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VERTICAL_LENGTH 25
#define HORIZONTAL_LENGTH 80
#define FINAL_GENERATION 10000
#define DELAY 200000

void init_field(int **field);
void print_field(int **field);
void update_field(int **field);
int count_neighbors(int **field, int x, int y);
int is_alive_function(int **field);

int main() {
    int v = 30000;
    initscr();
    nodelay(stdscr, true);
    noecho();
    int **field = malloc(VERTICAL_LENGTH * sizeof(int *));
    for (int i = 0; i < VERTICAL_LENGTH; i++) field[i] = malloc(HORIZONTAL_LENGTH * sizeof(int));

    init_field(field);
    FILE *f = freopen("/dev/tty", "r", stdin);
    if (f == NULL) {
    }
    int is_alive = 1;
    int play = 1;
    while (is_alive && play) {
        usleep(v);
        char speed = getch();
        if (speed == '+' && v > 5000)
            v -= 5000;
        else if (speed == '-' && v < 150000)
            v += 5000;
        else if (speed == 'q')
            play = 0;
        clear();
        print_field(field);
        update_field(field);
        is_alive = is_alive_function(field);
        refresh();
    }

    for (int i = 0; i < VERTICAL_LENGTH; i++) free(field[i]);
    free(field);
    endwin();
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
    for (int i = 0; i < VERTICAL_LENGTH; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH - 1; j++) {
            if (field[i][j] == 1)
                addch('*');
            else
                addch('.');
        }
        if (field[i][HORIZONTAL_LENGTH - 1] == 1)
            addstr("*\n");
        else
            addstr(".\n");
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

int is_alive_function(int **field) {
    int correct = 0;
    for (int i = 0; i < VERTICAL_LENGTH && !correct; i++) {
        for (int j = 0; j < HORIZONTAL_LENGTH && !correct; j++) {
            if (field[i][j] == 1) correct = 1;
        }
    }
    return correct;
}
