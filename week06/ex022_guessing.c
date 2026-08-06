#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));

    int target = rand() % 100 + 1;

    int guess;
    int attempts = 0;

    printf("=== Number Guessing Game (1-100) ===\n");
    do
    {
        printf("Now GUESS!! : ");
        scanf("%d", &guess);

        if(guess > target) {
            printf("TOO HIGH!!!!");
        } else if(guess < target) {
            printf("too low.........");
        } else if(guess == target) {
            printf("YIPPIE YIPPA YOU GUESSED IT IN %d ATTEMPTS", attempts);
            guess = 888;
        }
        attempts += 1;
        if(attempts >= 10) {
            printf("How can you be this bad? You lost...");
            guess = 888;
        }
        printf("\n\n");
    } while (guess != 888);

    return 0;
    

}