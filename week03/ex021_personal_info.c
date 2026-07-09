#include <stdio.h>

int main() {

    char name[50];
    int age;
    float gpa;
    char favorite_subject[50];

    printf("=== Enter Data ===\n");
    printf("Name: ");
    scanf("%s", &name);

    printf("Age: ");
    scanf("%d", &age);

    printf("GPA: ");
    scanf("%f", &gpa);

    printf("Favorite Subject: ");
    scanf("%s", &favorite_subject);

    printf("\n=== Personal Info ===\n");
    printf("Name               : %s\n", name);
    printf("Age                : %d\n", age);
    printf("GPA                : %.2f\n", gpa);
    printf("Favorite Subject   : %s\n", favorite_subject);

    return 0;
}