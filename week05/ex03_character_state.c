#include <stdio.h>

int main() {
    int max_hp, damage, poiNum, ac;
    _Bool is_poisoned;
    printf("Max HP: ");
    scanf("%d", &max_hp);
    printf("Damage Taken: ");
    scanf("%d", &damage);
    printf("Poisoned (0/1): ");
    scanf("%d", &poiNum);
    is_poisoned = poiNum;
    printf("Attack Count : ");
    scanf("%d", &ac);

    printf("\n======= CHARACTER STATUS =======\n");



    int hp = max_hp - damage;
    if (hp < 0) hp = 0;


    if(hp == 0) { 
        printf("State: DEAD"); 
        return 1;
    }

    printf("HP : %d/%d\n", hp, max_hp);
    if(is_poisoned) {
        printf("State: POISONED");
    } else if(hp * 100 / max_hp <= 25) {
        printf("State: CRITICAL");
    } else if(ac % 5 == 0) {
        printf("State: NORMAL + ULTIMATE");
    }

}