#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_INCORRECT_VALUES 2


int main(void)
{
    int exit_code = ERR_OK;
    double x = 0;
    double sum = 0;
    size_t current_iter = 1;
    while (1)
    {
        scanf("%lf", &x);
        if (x < 0)
        {
            break;
        }
        sum += sqrt(x / current_iter);
        ++current_iter;
    }
    printf("%lf", sin(sum));
    return exit_code;
}
