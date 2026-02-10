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

#if 1
//// normal dice
#define DICE_1 0.1666667
#define DICE_2 0.3333333
#define DICE_3 0.5
#define DICE_4 0.6666667
#define DICE_5 0.8333333
//      DICE_6     // 0.9 ~ 1.0
#endif

int dice()
{
  double d = ((double)rand())/RAND_MAX;
  if (d <= DICE_1) {
    return 0;
  } else if (d <= DICE_2) {
    return 1;
  } else if (d <= DICE_3) {
    return 2;
  } else if (d <= DICE_4) {
    return 3;
  } else if (d <= DICE_5) {
    return 4;
  }
  return 5;
}

/* functions */
void cent_limit(long cast, long rep);
void welford_update(double value, double* mean, double* m2, long count);

/* main */
int main(void) {
  long cast, rep;
  puts("The central limit theorem.");
  printf("The number of dice cast: ");
  scanf("%ld", &cast);
  printf("The repeat number: ");
  scanf("%ld", &rep);
  printf("\n");
  cent_limit(cast, rep);

  return 0;
}

/* central limit theorem */
void cent_limit(long cast, long rep) {

  long i, j, sum;
  long array[MAX] = {};
  srand((unsigned int)time(NULL) );

  double mean = 0.0;
  double m2 = 0.0;

  for (i = 0; i < rep; i++) {
    sum = 0;
    for (j = 0; j < cast; j++) {
      sum += dice() + 1;
    }
    array[sum - cast]++;
    welford_update(sum, &mean, &m2, i + 1);
  }

  long total = 0;
  for (i = cast; i <= DICE * cast; i++) {
    long num = array[i - cast];
    total += i * num;
    printf("%03ld [%7ld] :", i, num);
    for (j = 0; j < num / UNIT; j++) {
      putchar('*');
    }
    putchar('\n');
  }

  double ave = ((double)total)/rep;
  long total_2 = 0;
  for (i = cast; i <= DICE * cast; i++) {
    long num = array[i - cast];
    total_2 += i * i * num; //
  }
  double var = ((double)total_2)/rep - ave * ave;

  printf("average = %lf, variance = %lf\n", ave, var); 
  printf("Welford's method: mean = %lf, unbiased variance = %lf\n", mean, m2 / (rep - 1));
}

/* Welford's method */
void welford_update(double value, double* mean, double* m2, long count) {
  double delta = value - *mean;
  *mean += delta / count;
  double delta2 = value - *mean;
  *m2 += delta * delta2;
}
