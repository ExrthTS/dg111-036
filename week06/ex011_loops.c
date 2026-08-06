#include <stdio.h>

int main() {
    int sum = 0;

    for (int i = 1; i <= 10; i++) {
        printf("%d", i);
        sum += i;
    }

    int t = 1;
    while (t <= 10) {
        printf("%d", t);
        sum += t;
        t++;
    }

    int j = 1;
    do {
        printf("%d", j);
        sum += j;
        j++;
    } while (j <= 10);

    printf("\nSum = %d\n", sum);
    return 0;
}