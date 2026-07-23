#include <stdio.h>

int main() {
    int num;
    char* ans = "NULL";
    scanf("%d", &num);

    switch(num) {
        case 1:
            printf("Monday (Weekday)");
            break;
        case 2:
            printf("Tuesday (Weekday)");
            break;
        case 3:
            printf("Wednesday (Weekday)");
            break;
        case 4:
            printf("Thursday (Weekday)");
            break;
        case 5:
            printf("Friday (Weekday)");
            break;
        case 6:
            printf("Saturday (Weekend! 😚)");
            break;
        case 7:
            printf("Sunday (Weekend! 😚)");
            break;
        default:
            printf("Invalid input");
            break;
    }
}