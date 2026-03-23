/*Write a function that takes a decimal number, num, and replaces its digits 
between odd and even positions. 
For example, if the given number is 23 (00010111), it should be converted to 
43 (00101011). 
The bits of the number are enumerated from the least significant bit at position 
1 (the leftmost bit in the examples given). In the binary representation of 23, 
bit numbers are given as follows. 
position: 87654321 
bit: 00010111 
After the swap has been performed, the output should be the following. 
old position: 87654321 
new position: 78563412 
bit: 00101011*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int swap_bits(int num) {
    int odd_bits = num & 0xAAAAAAAA; // Bits at odd positions
    int even_bits = num & 0x55555555; // Bits at even positions
    odd_bits >>= 1; // Shift odd bits right
    even_bits <<= 1; // Shift even bits left
    return (odd_bits | even_bits);
}

int main()
{
    int num;
    scanf("%d", &num);
    int result = swap_bits(num);
    printf("Output: %d", result);
    return 0;
}