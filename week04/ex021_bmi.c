#include <stdio.h>

int main() {
    float kg;
    float cm;
    printf("Input Weight (kg): ");
    scanf("%f", &kg);
    printf("Input Height (cm): ");
    scanf("%f", &cm);
    float m = cm / 100.0;
    float bmi = kg / (m * m);
    char *status;
    if(bmi < 18.5) {
        status = "Underweight";
    } else if (bmi < 24.9 && bmi > 18.5) {
        status = "Normal";
    } else if (bmi < 29.9 && bmi > 25.0) {
        status = "Overweight";
    } else {
        status = "Obese";
    }

    printf("Output BMI: %.2f -> %s\n", bmi, status);
    
    return 0;
}