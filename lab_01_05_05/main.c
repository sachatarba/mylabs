#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 100

void print_number(int number);

bool input(int *number);

int main(void)
{
    int exit_code = 0;
    int number = 0;
    if (input(&number) && number != 0)
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

bool input(int *number)
{
    const char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char source[BUFF_SIZE];
    bool is_str_number = true;
    bool is_el_digit = false;
    scanf("%s", source);
    for (size_t i = 0; i < strlen(source); ++i)
    {
        is_el_digit = false;
        for (size_t j = 0; j < sizeof(digits) / sizeof(digits[0]); ++j)
        {
            if (source[i] == digits[j])
            {
                is_el_digit = true;
            }
        }
        if (!is_el_digit)
        {
            is_str_number = false;
        }
    }
    if (is_str_number)
    {
        *number = atoi(source);
    }
    return is_str_number;
}
