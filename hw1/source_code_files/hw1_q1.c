#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
    int num = 0;
    scanf("%d", &num);  // Read an integer input from the user

    if (num == 0) {
        // If input is zero, print that it has no divisors
        printf("%d has no Divisors!", num);
    } else {
        // Print message
        printf("Divisors of %d are: ", num);

        // Loop through all numbers from 1 to num
        for (int i = 1; i <= num; i++) {
            // If i divides num without a remainder, it's a divisor
            if (num % i == 0) {
                printf("%d ", i);  // Print the divisor
            }
        }

        printf("\n");  // Newline for clean output
    }

    return 0;
}
