#include <stdio.h>

void print_number(int number);

int main(void)
{
    int exit_code = 0;
    int number = 0;

    if (scanf("%d", &number) == 1)
    {
        print_number(number);
    }
    else
    {
        exit_code = 1;
    }
    return exit_code;
}

void print_number(int number)
{
    if (number > 9)
    {
        print_number(number / 10);
    }
    printf("%d", number % 10);
}
