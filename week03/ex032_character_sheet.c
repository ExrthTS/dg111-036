#include <stdio.h>

int main() {

    char name[50];
    int maxHp;
    int currentHp;
    int attackPower;
    int defense;
    int level;
    int powerScore;
    //char hpBar = "█";
    int hpPercent;
    int i = 0;
    //char hpBars = hpBar * (hpPercent / 10);
    



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

    currentHp = maxHp;
    printf("\n=== Character Summary ===\n");
    printf("╔═══════════════════════════════╗\n");
    printf("║ %-10s                    ║\n", name);
    printf("╠═══════════════════════════════╣\n");
    printf("║ Level : %-10d            ║\n", level);
    printf("║ HP    : %d / %-9d       ║\n", maxHp, currentHp);
    printf("║ ATK   : %-10d            ║\n", attackPower);
    printf("║ DEF   : %-10d            ║\n", defense);
    printf("╠═══════════════════════════════╣\n");
    printf("║ HP Bar: [");
    
    hpPercent = (currentHp * 100) / maxHp;
    while(i <= (hpPercent / 10)) {
        i++;
        printf("█");
    }
    printf("] %d%%    ║\n", hpPercent);
    powerScore = (attackPower * 2 + defense + maxHp / 10);
    printf("║ Power Score: %-10d       ║\n");
    printf("╚═══════════════════════════════╝");


    return 0;
}