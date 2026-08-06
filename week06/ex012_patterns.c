#include <stdio.h>

int main() {

    for(int i = 1; i <= 5; i++) {
        printf("\n");
        for(int j = 1; j <= i; j++) {
            printf("*");
        }
    }

    printf("\n");

    int n = 4;
    for(int t = 1; t <= n; t++) {
        printf("\n");
        for(int j = 1; j <= n; j++) {
            printf("*");
        }
    }

    printf("\n");

    n = 3;
    for(int r = 1; r <= 5; r++) {
        printf("\n");
        for(int j = 1; j <= 5; j++) {
            if(r <= 3) {
                if(j < ((n+1)-r) || j > (5-(n-r))) {
                    printf(" ");
                } else {
                    printf("*");
                }
            } else {
                int rr = r-3;
                if(j < (4-3+rr) || j > (5-rr)) {
                    printf(" ");
                } else {
                    printf("*");
                }
            }
            
            
            
        }
    }
}