#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_OK 0
#define ERR_IO 1
#define ERR_NOT_LINE 2
#define EPS 0.000001


double vect_mul(double x1, double y1, double x2, double y2, double x3, double y3);

int check_intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

int main(void)
{
    int exit_code = 0;
    double xp, yp, xq, yq, xr, yr, xs, ys = 0;
    if (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &xp, &yp, &xq, &yq, &xr, &yr, &xs, &ys) == 8)
    {
        if (((fabs(xp - xq) < EPS) && (fabs(yp - yq) < EPS)) || ((fabs(xr - xs) < EPS) && (fabs(yr - ys) < EPS)))
        {
            exit_code = ERR_NOT_LINE;
        }
        else
        {
            printf("%d", check_intersection(xp, yp, xq, yq, xr, yr, xs, ys));
        }
    }
    else
    {
        exit_code = 1;
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
