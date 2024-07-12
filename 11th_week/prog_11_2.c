/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* define */
#define MAX 100
#define DICE 6
#define UNIT 1000

#if 0
#define DICE_1 0.5 // 0.0 ~ 0.5
#define DICE_2 0.6 // ~ 0.6
#define DICE_3 0.7 // ~ 0.7
#define DICE_4 0.8 // ~ 0.8
#define DICE_5 0.9 // ~ 0.9
//      DICE_6     // 0.9 ~ 1.0
#endif
//// normal dice
#define DICE_1 0.1666667
#define DICE_2 0.3333333
#define DICE_3 0.5
#define DICE_4 0.6666667
#define DICE_5 0.8333333
//      DICE_6     // 0.9 ~ 1.0

int dice() {
    double d = ((double)rand())/RAND_MAX;
    if (d <= DICE_1) {
        return 1;
    } else if (d <= DICE_2) {
        return 2;
    } else if (d <= DICE_3) {
        return 3;
    } else if (d <= DICE_4) {
        return 4;
    } else if (d <= DICE_5) {
        return 5;
    }
    return 6;
}

void print_hist(long count[], int num, int unit, int cast)
{
  long cnt;
  for(int i = 0; i < num; i++) {
    cnt = count[i]/unit;
    printf("%02d:", i + cast);
    for(int j = 0; j < cnt; j++) {
      printf("*");
    }
    printf("\n");
  }
}

/* main */
int main(void) {
    long cast, repeat;
    puts("The central limit theorem.");
    printf("The number of dice cast: ");
    scanf("%ld", &cast);
    printf("The repeat number: ");
    scanf("%ld", &repeat);
    printf("\n");
    srand((unsigned int)time(NULL));

    long *count = (long *)calloc(cast * 6 - cast + 1, sizeof(long));
    if (count == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (long i = 0; i < repeat; i++) {
        int sum = 0;
        for (long j = 0; j < cast; j++) {
            sum += dice();
        }
        count[sum - cast]++;
    }

    print_hist(count, cast * 6 - cast + 1, 1000, cast);

    // Free the allocated memory
    free(count);

    return 0;
}