#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

int q_1(int num);
int q_2(int num);
int q_3(int num);


int main()
{
    int q_num = 0, n = 0, res = 0;

    printf("Which question would you like to check?: \n");
    scanf("%d", &q_num);
    printf("Please enter a number: \n");
    scanf("%d", &n);
    switch (q_num)
    {
    case 1:
        res = q_1(n);
        printf("Result = %d \n", res);
        break;
    case 2:
        res = q_2(n);
        printf("Result = %d \n", res);
        break;
    case 3:
        res = q_3(n);
        printf("Result = %d \n", res);
        break;
    default:
        printf("%d is an invalid input \n", q_num);
    }
    return 0;
}

// Recursively count how many bits are needed to represent n (n>0).
static int countBits(int n) {
    if (n == 0) return 0;
    return 1 + countBits(n / 2);
}

// Recursively build a decimal‑digit integer whose digits are the
static int buildBinaryFromVal(unsigned int val, int bits) {
    if (bits == 0) return 0;
    return buildBinaryFromVal(val >> 1, bits - 1) * 10 + (val & 1);
}

//dec to bin 
int q_1(int num)
{
    if (num >= 0) {
        // for 0 we still want one digit "0"
        int bits = (num == 0 ? 1 : countBits(num));
        return buildBinaryFromVal((unsigned int)num, bits);
    } else {
        // compute binary of the magnitude…
        unsigned int absn = (unsigned int)(-num);
        int bits = absn == 0 ? 1 : countBits(absn);
        int binMag = buildBinaryFromVal(absn, bits);
        // then just negate that integer:
        return -binMag;
    }
}



//digital root
static int sumDigits(int num) {
    if (num == 0) return 0;
    return (num % 10) + sumDigits(num / 10);
}

int q_2(int num)
{
    if (num < 10)
        return num;
    int s = sumDigits(num);
    return q_2(s);
}

//sequence sum
int q_3(int num)
{
    if (num == 0)
        return 0;
    // S(n) = n^2 - S(n-1)
    return num * num - q_3(num - 1);
}