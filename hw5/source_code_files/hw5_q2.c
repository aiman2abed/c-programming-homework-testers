//implement a function that swaps two integers using bitwise operations and without using additional memory
//The function gets two integer values (num1 and num2) and is supposed to swap them.
//The function should replace the values (i.e. num1 should contain the initial value of num2 and num2 should contain the initial value of num1).
//No auxiliary variables are allowed to be used beyond num1 and num2. The solution that uses auxiliary variables will receive 0 points.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void swap(int* num1, int* num2) {
    if (num1 != num2) {
        *num1 = *num1 ^ *num2;
        *num2 = *num1 ^ *num2;
        *num1 = *num1 ^ *num2;
    }
}

int main()
{
	int num1, num2;
    printf("Please enter num1 value: \n");
	scanf("%d", &num1);
	printf("Please enter num2 value: \n");
	scanf("%d", &num2);
    swap(&num1, &num2);
    printf("After swapping: num1=%d, num2=%d", num1, num2);
    return 0;
}
