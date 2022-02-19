#include <stdio.h>
#define NUM_OF_APARTS 4
#define NUM_OF_FLOORS 9

void calc_answer(int number_of_apart, int *entrance, int *floor);

int main(void)
{
    int exit_code = 0;
    int number_of_apart = 0;
    int entrance = 0;
    int floor = 0;

    if (scanf("%d", &number_of_apart) == 1)
    {
        calc_answer(number_of_apart, &entrance, &floor);
        printf("%d %d", entrance, floor);
    }
    else
    {
        exit_code = 1;
    }
    return exit_code;
}

void calc_answer(int number_of_apart, int *entrance, int *floor)
{
    *entrance = (number_of_apart - 1) / (NUM_OF_APARTS * NUM_OF_FLOORS) + 1;
    *floor = (((number_of_apart - 1) / NUM_OF_APARTS + 1) - 1) % NUM_OF_FLOORS + 1;
}
