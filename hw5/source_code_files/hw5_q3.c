//A function that for a given input num, outputs the smallest power of 2 greater or equal to num.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int smallest_power_of_2(int num) {
    int power = 1;
    while (power < num) {
        power <<= 1;  // Multiply by 2
    }
    return power;
}

int main()
{
    int num;
    scanf("%d", &num);
    int result = smallest_power_of_2(num);
    printf("Output: %d", result);
    return 0;
}