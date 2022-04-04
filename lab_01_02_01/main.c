#include <stdio.h>
#include <math.h>
#define PI 3.1415926

double calc_area(double a, double b, double fi);

int main(void)
{
    int exit_code = 0;
    double a = 0, b = 0, fi = 0;

    if (scanf("%lf%lf%lf", &a, &b, &fi) == 3)
    {
        double answer = calc_area(a, b, fi);
        printf("%lf", answer);
    }
    else
    {
        exit_code = 1;
    }
    return exit_code;
}

double calc_area(double a, double b, double fi)
{
    double fi_rad = fi * PI / 180;
    double area = (b + a) * fabs((b - a)) * tan(fi_rad) / 4;
    return area;
}
