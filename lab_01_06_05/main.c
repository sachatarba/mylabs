#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8
#define BUFF_SIZE 100

double vect_mul(double x1, double y1, double x2, double y2, double x3, double y3);

int check_intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

bool input(double *numbers, int *exit_code);

void split(char *source, double *numbers, int *exit_code);

int main(void)
{
    int exit_code = 0;
    double numbers[SIZE];
    if (input(numbers, &exit_code) && exit_code == 0)
    {
        printf("%d", check_intersection(numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], numbers[6], numbers[7]));
    }
    return exit_code;
}

double vect_mul(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);
}

int check_intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    int is_intersection = 0;
    double dir1, dir2, dir3, dir4;
    dir1 = vect_mul(x1, y1, x2, y2, x3, y3);
    dir2 = vect_mul(x1, y1, x2, y2, x4, y4);
    dir3 = vect_mul(x3, y3, x4, y4, x1, y1);
    dir4 = vect_mul(x3, y3, x4, y4, x2, y2);
    if ((dir1 * dir2 < 0) && (dir3 * dir4 < 0))
    {
        is_intersection = 1;
    }
    return is_intersection;
}

void split(char *source, double *numbers, int *exit_code)
{
    char buffer[BUFF_SIZE];
    size_t current_sym_in_source = 0, current_sym_in_buffer = 0, current_number = 0;
    while (current_sym_in_source < strlen(source))
    {
        if ((source[current_sym_in_source] != ' ') && (source[current_sym_in_source] != '\n'))
        {
            buffer[current_sym_in_buffer] = source[current_sym_in_source];
            current_sym_in_buffer += 1;
        }
        else if (source[current_sym_in_source] == ' ')
        {
            buffer[current_sym_in_buffer] = '\0';
            numbers[current_number] = atof(buffer);
            current_sym_in_buffer = 0;
            ++current_number;
        }
        ++current_sym_in_source;
    }
    if (current_number != 8)
    {
        *exit_code = 1;
    }
}

bool input(double *numbers, int *exit_code)
{
    const char digits[12] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '\n' };

    char source[BUFF_SIZE];
    bool is_str_numbers = true;
    bool is_el_digit = false;
    fgets(source, 100, stdin);
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
            is_str_numbers = false;
        }
    }
    if (is_str_numbers)
    {
        split(source, numbers, exit_code);
    }
    return is_str_numbers;
}