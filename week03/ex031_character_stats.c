#include <stdio.h>

int main() {

    char name[50];
    int maxHp;
    int attackPower;
    int defense;
    int level;


    printf("=== Create Character ===\n");
    printf("Character Name: ");
    scanf("%s", &name);
    printf("Max HP        : ");
    scanf("%d", &maxHp);
    printf("Attack Power  : ");
    scanf("%d", &attackPower);
    printf("Defense       : ");
    scanf("%d", &defense);
    printf("Level         : ");
    scanf("%d", &level);

    printf("\n=== Character Summary ===\n");
    printf("Name  : %s\n", name);
    printf("Level : %d\n", level);
    printf("HP    : %d\n", maxHp);
    printf("ATK   : %d\n", attackPower);
    printf("DEF   : %d\n", defense);

    return 0;
}