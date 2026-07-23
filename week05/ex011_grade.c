#include <stdio.h>
#include <stdbool.h>

int main() {
    
    int sc;
    char *gr = "ZERO";
    bool p = false;
    //printf("Score: ");
    printf("Score: ");
    scanf("%d", &sc);

    if(sc >= 80 && sc <= 100) { gr = "A (4.0)"; }
    else if(sc >= 75 && sc <= 79) { gr = "B+ (3.5)"; }
    else if(sc >= 70 && sc <= 74) { gr = "B (3.0)"; }
    else if(sc >= 65 && sc <= 69) { gr = "C+ (2.5)"; }
    else if(sc >= 60 && sc <= 64) { gr = "C (2.0)"; }
    else if(sc >= 55 && sc <= 59) { gr = "D+ (1.5)"; }
    else if(sc >= 50 && sc <= 54) { gr = "D (1.0)"; }
    else { gr = "F (0.0)"; }

    if(sc >= 50) { p = true; }

    printf("Grade: %s", gr);
    if(p == true) {
        printf(" -- PASS");
    } else {
        printf(" -- FAIL");
    }

}

/*80–100 = A (4.0)
75–79 = B+ (3.5)
70–74 = B (3.0)
65–69 = C+ (2.5)
60–64 = C (2.0)
55–59 = D+ (1.5)
50–54 = D (1.0)
0–49 = F (0.0)*/