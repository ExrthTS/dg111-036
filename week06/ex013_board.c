#include <stdio.h>

int main() {

    int rows = 3;
    int cols = 5;

    int count = 1;

    for(int i = 0; i <= rows - 1; i++) {
        printf("+---+---+---+---+---+\n");
        printf("|");
        for(int j = 0; j <= cols - 1; j++) {
            printf("%2d |", count);
            count++;
        }
        printf("\n");
    }
    printf("+---+---+---+---+---+\n");



}