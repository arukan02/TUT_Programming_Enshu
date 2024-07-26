/* header files */
#include <stdio.h>
#include <stdlib.h>

/* define */
#define HEIGHT 40
#define WIDTH 80
#define BIN 1

/* functions */
void lifegame(void);
void display_and_count(int life[BIN][HEIGHT + BIN][WIDTH + BIN]);
void update(int life[BIN][HEIGHT + BIN][WIDTH + BIN]);
void load(int life[BIN][HEIGHT + BIN][WIDTH + BIN], const char *filename);

/* main */
int main(void) {
    lifegame();
    return 0;
}

/* life game */
void lifegame(void) {
    int life[BIN][HEIGHT + BIN][WIDTH + BIN] = {{{0}}};
    load(life, "diehard.txt");
    int generations = 131;

    for (int gen = 0; gen < generations; gen++) {
        printf("Generation: %d\n", gen);
        display_and_count(life);
        update(life);
    }
}

/* load initial conditions from file */
void load(int life[BIN][HEIGHT + BIN][WIDTH + BIN], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int x, y;
    while (fscanf(file, "%d %d", &x, &y) != EOF) {
        life[0][x][y] = 1;
    }

    fclose(file);
}

/* display the grid and count life */
void display_and_count(int life[BIN][HEIGHT + BIN][WIDTH + BIN]) {
    int life_count = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (life[0][i][j]) {
                life_count++;
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    if (life_count == 0) {
        printf("Life has gone extinct.\n");
        exit(EXIT_SUCCESS);
    }
}

/* update the grid based on the rules */
void update(int life[BIN][HEIGHT + BIN][WIDTH + BIN]) {
    int next_life[BIN][HEIGHT + BIN][WIDTH + BIN] = {{{0}}};

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di != 0 || dj != 0) {
                        count += life[0][i + di][j + dj];
                    }
                }
            }

            if (life[0][i][j]) {
                if (count == 2 || count == 3) {
                    next_life[0][i][j] = 1;
                }
            } else {
                if (count == 3) {
                    next_life[0][i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            life[0][i][j] = next_life[0][i][j];
        }
    }
}
