#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_OK 0
#define ERR_IO 1

double calc_sum(size_t *current_iter);

int main(void)
{
    int exit_code = ERR_OK;
    size_t current_iter = 1;
    double sum = calc_sum(&current_iter);
    if (current_iter == 1)
    {
        exit_code = ERR_IO;
    }
    if (!exit_code)
    {
        printf("%lf", sin(sum));
    }
    return exit_code;
}

double calc_sum(size_t *current_iter)
{
    double x = 0;
    double sum = 0;
    while (1)
    {
        scanf("%lf", &x);
        if (x < 0)
        {
            break;
        }
        sum += sqrt(x / *current_iter);
        ++(*current_iter);
    }
    return sum;
}