#include <stdio.h>

double calc_volume(double v1, double v2);
double calc_temp(double v1, double t1, double v2, double t2);

int main(void)
{
    int exit_code = 0;
    double v1 = 0, t1 = 0, v2 = 0, t2 = 0;

    if (scanf("%lf%lf%lf%lf", &v1, &t1, &v2, &t2) == 4)
    {
        double v = calc_volume(v1, v2);
        double t = calc_temp(v1, t1, v2, t2);
        printf("%lf %lf", v, t);
    }
    else
    {
        exit_code = 1;
    }

    return exit_code;
}

double calc_volume(double v1, double v2)
{
    return v1 + v2;
}

double calc_temp(double v1, double t1, double v2, double t2)
{
    double v = calc_volume(v1, v2);
    return (v1 * t1 + v2 * t2) / v;
}
