#include <stdio.h>
#include <math.h>

int main() {
    int player_attack;
    int enemy_defense;
    int hit_number;

    printf("=== COMBAT SIMULATOR ===\n");
    printf("Enemy HP 500\n");
    printf("Player Attack   : ");
    scanf("%d", &player_attack);
    printf("Enemy Defense   : ");
    scanf("%d", &enemy_defense);
    printf("Hit Number      : ");
    scanf("%d", &hit_number);

    int base_atk = player_attack - enemy_defense;
    if(hit_number % 5 == 0) {
       base_atk = (int)ceil((float)base_atk * 1.5f);
        printf("Damage = %d *** CRITICAL HIT! x1.5 ***", base_atk);
    } else {
        printf("Damage = %d", base_atk);
    
    }
    int enemy_hp = 500 - base_atk;
    if(enemy_hp > 0) {
        printf("\nEnemy have %d HP left.", enemy_hp);
    } else {
        printf("\nEnemy is dead.");
    }
    
    
    

    return 0;
}