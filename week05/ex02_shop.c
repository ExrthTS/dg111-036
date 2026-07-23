#include <stdio.h>

int main() {
    int gold = 1000;
    int action;

    char* items[] = {"Health Potion", "Mana Potion", "Iron Sword", "Leather Armor"};
    int prices[] = {50, 80, 500, 300};
    int cart[10] = {0};
    int cart_count = 0;
    int total_price = 0;

    printf("=== ITEM SHOP ===\n");
    printf("Gold: %d\n\n", gold);

    printf("1. %s - %d Gold (+50 HP)\n", items[0], prices[0]);
    printf("2. %s - %d Gold (+30 MP)\n", items[1], prices[1]);
    printf("3. %s - %d Gold (+20 ATK)\n", items[2], prices[2]);
    printf("4. %s - %d Gold (+15 DEF)\n", items[3], prices[3]);
    printf("5. CONFIRM\n");
    printf("6. EXIT\n\n");

    while (1) {
        printf("Select item: ");
        scanf("%d", &action);

        if(action == 6) {
            break;
        }

        if(action >= 1 && action <= 4) {
            int con = gold - prices[action - 1];
            if(con <= 0) {
                printf("Not enough gold!\n");
                continue;
            }
        }

        if(action == 5) {
            printf("\n=== YOUR CART ===\n");
            for (int i = 0; i < cart_count; ++i) {
                int idx = cart[i];
                printf("%d. %s - %d Gold\n", i + 1, items[idx], prices[idx]);
            }
            printf("Total spent: %d Gold\n", total_price);
            printf("Remaining gold: %d\n\n", gold);
            printf("Item purchased successfully! \u2713\n");
            break;
        }

        if(action < 1 || action > 4) {
            printf("Invalid selection.\n");
            continue;
        }

        if(cart_count >= 10) {
            printf("Cart is full.\n");
            continue;
        }

        cart[cart_count++] = action - 1;
        gold -= prices[action - 1];
        total_price += prices[action - 1];

        printf("\n=== YOUR CART ===\n");
        for(int i = 0; i < cart_count; ++i) {
            int idx = cart[i];
            printf("%d. %s - %d Gold\n", i + 1, items[idx], prices[idx]);
        }
        printf("Remaining gold on purchase: %d\n\n", gold);
    }

    return 0;
}
