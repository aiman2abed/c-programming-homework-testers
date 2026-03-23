//Given an integer num, write a function that returns 1 if the binary representation of num is palindrome else returns 0. 
//Notice that here, the output of a function is a value 0 or 1 and you are supposed to print the corresponding output to the user.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int is_palindrome(int num) {
    int reversed = 0;
    int original = num;

    while (num > 0) {
        reversed = (reversed << 1) | (num & 1);
        num >>= 1;
    }

    return original == reversed;
}

int main()
{
    int num;
    scanf("%d", &num);

    if (is_palindrome(num)) {
        printf("%d is a palindrome in binary.", num);
    } else {
        printf("%d is not a palindrome in binary.", num);
    }

    return 0;
}
