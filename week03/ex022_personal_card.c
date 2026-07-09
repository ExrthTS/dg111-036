#include <stdio.h>

int main() {

    char name[50];
    int age;
    float gpa;
    char major[50];

    printf("=== Enter Data ===\n");
    printf("Name: ");
    scanf("%s", &name);

    printf("Age: ");
    scanf("%d", &age);

    printf("GPA: ");
    scanf("%f", &gpa);

    printf("Major: ");
    scanf("%s", &major);

    printf("\n=== PERSONAL INFO ===\n");
    printf("┌─────────────────────────────┐\n");
    printf("│ Name  : %-20s│\n", name);
    printf("│ Age   : %-20d│\n", age);
    printf("│ GPA   : %-20.2f│\n", gpa);
    printf("│ Major : %-20s│\n", major);
    printf("└─────────────────────────────┘");

    return 0;
}