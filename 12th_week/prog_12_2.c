/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DOORS 3
#define NUM_OPEN 1 // <= DOORS - 2

//#define DOORS 3
//#define NUM_OPEN 1 // <= DOORS - 2

/* functions */
void doors(int changeDoor, long loops);

/* main */
int main(void) {
  int changeDoor;
    long loops;

    // Seed for random number generation
    srand((unsigned int)time(NULL));

    // Ask the user if they want to change the door
    printf("Will you change the door? <yes...1 / no...0>: ");
    scanf("%d", &changeDoor);

    // Ask the user for the number of loops
    printf("Looping number: ");
    scanf("%ld", &loops);

    // Run the Monty Hall problem simulation
    doors(changeDoor, loops);

    return 0;
}

/* Monty Hall problem */
void doors(int changeDoor, long loops) {
    long wins = 0;
    long losses = 0;

    for (long i = 0; i < loops; i++) {
        int bingo = rand() % DOORS + 1; // Winning door
        int select, open, new_select;

        // The player selects a door
        select = rand() % DOORS + 1;

        // The host opens one of the non-selected doors that is not the winning door
        do {
            open = rand() % DOORS + 1;
        } while (open == select || open == bingo);

        // If the player decides to change the door
        if (changeDoor) {
            // The player changes to the remaining door
            new_select = 6 - select - open; // Since there are only 3 doors, the sum of the door numbers is 6.
            select = new_select;
        }

        // Check if the final selected door is the winning door
        if (select == bingo) {
            wins++;
        } else {
            losses++;
        }
    }

    // Print the results
    printf("Win %ld\n", wins);
    printf("Lose %ld\n", losses);
    printf("Winning rate %f\n", (double)wins / (wins + losses));
}