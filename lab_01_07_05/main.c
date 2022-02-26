#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_INCORRECT_VALUES 2
#define EPS 0.000001

double calculate_value(double x, double eps);

int main(void)
{
    int exit_code = ERR_OK;
    double x, eps = 0;
    if (scanf("%lf%lf", &x, &eps) == 2)
    {
        if ((fabs(x - 1) < EPS) && (fabs(eps - 1) < EPS))
        {
            exit_code = ERR_INCORRECT_VALUES;
        }
        else
        {
            double calc_value = calculate_value(x, eps);
            double real_value = 1 / sqrt(1 - x * x);
            double abs_error = fabs(real_value - calc_value);
            double relative_error = abs_error / real_value;
            printf("%lf %lf %lf %lf", calc_value, real_value, abs_error, relative_error);
        }
    }
    else
    {
        exit_code = ERR_IO;
    }
    return exit_code;
}

double calculate_value(double x, double eps)
{
    double value = 0;
    double iter_value = 1;
    size_t current_mul = 1;
    while (iter_value > eps)
    {
        value += iter_value;
        iter_value = iter_value * x * x * current_mul / (current_mul + 1);
        current_mul += 2;
    }
    return value;
}
