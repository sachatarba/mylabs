#include <stdio.h>
#include <stdlib.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_INCORRECT_VALUES 2
#define IN_BYTE 8
#define GET_BIT(value, pos) ((value >> pos) & 1)

void pack(int x1, size_t *b);

void unpack(size_t b);

size_t to_bin(int x);

void print_ans(int x1, int x2, int x3, int x4);

int main(void)
{
    int exit_code = ERR_OK;
    int x1, x2, x3, x4 = 0;
    if (scanf("%d%d%d%d", &x1, &x2, &x3, &x4) == 4)
    {
        if ((x1 >= 0) && (x1 < 256) && (x2 >= 0) && (x2 < 256) && (x3 >= 0) && (x3 < 256) && (x4 >= 0) && (x4 < 256))
        {
            printf("Result: ");
            print_ans(x1, x2, x3, x4);
        }
        else
        {
            exit_code = ERR_INCORRECT_VALUES;
        }
    }
    else
    {
        exit_code = ERR_IO;
    }
    if (exit_code)
    {
        printf("Error: ");
        printf("INVALID VALUES");
    }
    return exit_code;
}

size_t to_bin(int x)
{
    size_t ans = 0;
    int mul = 1;
    while (x)
    {
        ans += (x % 2) * mul;
        x = x / 2;
        mul *= 10;
    }
    return ans;
}

void unpack(size_t b)
{
    int ans = 0;
    int current_mul = 1;
    for (int current_bit = 0; current_bit < 8; ++current_bit)
    {
        ans = ans + b % 10 * current_mul;
        b /= 10;
        current_mul *= 2;
    }
    printf("%d ", ans);
}

void pack(int x, size_t *b)
{
    for (int current_bit = 1; current_bit <= IN_BYTE; ++current_bit)
    {
        printf("%d", GET_BIT(x, (IN_BYTE - current_bit)));
    }
    *b = to_bin(x);
}

void print_ans(int x1, int x2, int x3, int x4)
{
    size_t b1 = 0;
    size_t b2 = 0;
    size_t b3 = 0;
    size_t b4 = 0;
    pack(x1, &b1);
    pack(x2, &b2);
    pack(x3, &b3);
    pack(x4, &b4);
    putc(' ', stdout);
    unpack(b1);
    unpack(b2);
    unpack(b3);
    unpack(b4);
}
