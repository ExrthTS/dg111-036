#include <stdio.h> 

int main() {
  
    int input = 0;
    int isPrime = 1;
    printf("Enter positive integer: ");
    scanf("%d", &input);

    for(int i = 2; i < input - 1; i++) {
        if(input % i == 0) {
            isPrime = 0;
            break;
        }
    }

    if(isPrime == 1) {
        printf("%d is a Prime Number", input);
    } else if(isPrime == 0) {
        printf("%d is NOT a Prime Number (divisible by 2)", input);
    }


}