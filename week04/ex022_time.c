#include <stdio.h>

int main() {
    int seconds;
    printf("Input: ");
    scanf("%d", &seconds);
    //printf(" seconds\n");
    int hours = seconds / 3600;
    int mins = (seconds % 3600) / 60;
    int secs = seconds % 60;

    printf("Output: %d:%02d:%02d", hours, mins, secs);
    
    return 0;
}