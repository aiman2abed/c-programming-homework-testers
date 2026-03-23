//prompt the user to input bin_num binary sequence of 0's  and 1's (the maximal number of bits is 32)
/*and outputs the following: A) Decimal representation of bin_num B) Hexadecimal representation of bin_num (base 16)*/
//If the input is invalid (that is, if bin_num contains digits different from 0 and 1), the user should receive an error message (detailed below).
/*In order to solve the problem correctly, you will not be able to read the binary numbers as integers, since it might cause an overflow. (Think of what happens when the input has 30 binary digits).
On the other hand, the answer (in decimal) will always fit the standard integer size */

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LEN 32
#include <stdio.h>
int main()
{
    char str[MAX_LEN];
    while (1)
    {
        if (!fgets(str, sizeof(str), stdin)) break;
        // Remove trailing newline if present
        int len = 0;
        while (str[len] != '\0' && str[len] != '\n') len++;
        str[len] = '\0';
        if (str[0] == '0' && str[1] == '\0') break;
        int valid = 1;
        for (int i = 0; i < len; i++) {
            if (str[i] != '0' && str[i] != '1') {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("invalid input, please try again.");
            continue;
        }
        int decimal = 0;
        for (int i = 0; i < len; i++) {
            decimal = (decimal << 1) | (str[i] - '0');
        }
        printf("%s to decimal is: %d\n", str, decimal);
        printf("%s to hexadecimal is: %X\n", str, decimal);
    }
    return 0;
}