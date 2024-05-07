/* header files */
#include <stdio.h>

/* functions */
int euclid_loop(int m, int n); // 関数宣言
int euclid_recf(int m, int n); // 関数宣言

/* main */
int main(void) {
int m,n;
printf("The calculation of the greatest common factor of positive integers m and n.\n");
printf("m: ");
scanf("%d", &m);
printf("n: ");
scanf("%d", &n);
printf("LOOP GCD %d & %d = %d\n", m, n, euclid_loop(m, n));
printf("RECF GCD %d & %d = %d\n", m, n, euclid_recf(m, n));
return 0;
}

/*Euclidean function using for loop*/
int euclid_loop(int m, int n) {
    int temp;
    while (n != 0) { //repeat until n equals to zero (m mod n = 0)
        temp = n; //put n in temp variable
        n = m % n; //put the result of m mod n in n
        m = temp; //put temp as the new m
    }
    return m;
}

/*Euclidean function using recursive*/
int euclid_recf(int m, int n) {
    if(n==0){
        return m;
    } else {
        return euclid_recf(n , m % n); //when n is not zero, run the euclid_recf function again
    }
}
