#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define REPEAT 1000000 // 大規模な試行回数

double probabilities[6] = {0.1, 0.2, 0.3, 0.2, 0.1, 0.1};

int weighted_dice() {
    double r = (double)rand() / RAND_MAX;
    double cumulative_probability = 0.0;
    for (int i = 0; i < 6; i++) {
        cumulative_probability += probabilities[i];
        if (r < cumulative_probability) {
            return i + 1;
        }
    }
    return 6; // 最後のケース
}

int main(void) {
    srand((unsigned int)time(NULL));

    int cast = 6; // サイコロの回数
    long repeat = REPEAT;

    // 理論的な母平均と母分散
    //手動で計算した
    double theoretical_mean = 3.3 * cast;
    double theoretical_variance = 2.01 * cast;

    // サンプリングによる統計値
    double sum = 0;
    double sum_of_squares = 0;

    for (long i = 0; i < repeat; i++) {
        int sum_cast = 0;
        for (int j = 0; j < cast; j++) {
            sum_cast += weighted_dice();
        }
        sum += sum_cast;
        sum_of_squares += sum_cast * sum_cast;
    }

    double sample_mean = sum / repeat;
    double sample_variance = (sum_of_squares / repeat) - (sample_mean * sample_mean);

    printf("理論的な母平均: %f\n", theoretical_mean);
    printf("サンプリングによる平均: %f\n", sample_mean);
    printf("理論的な母分散: %f\n", theoretical_variance);
    printf("サンプリングによる分散: %f\n", sample_variance);

    return 0;
}
