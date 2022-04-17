#include <stdio.h>

#define ERR_OK 0
#define ERR_INP 1
#define MAX_ROWS 10
#define MAX_COLS 10

int input_matrix(int **matrix, int *rows, int *cols);

void transform_matrix(int **matrix, int *buf, int rows, int cols);

void print_array(int *array, int elements_number);

int is_monotone(int *array, int elements_number);

void make_array_from_matrix(int **matrix, int rows, int cols, int *array, int *elements_number);

int main(void)
{
    int buf[MAX_ROWS][MAX_COLS] = { 0 };
    int *matrix[MAX_COLS] = { 0 };
    transform_matrix(matrix, buf[0], MAX_ROWS, MAX_COLS);
    int rows = 0;
    int cols = 0;
    int exit_code = ERR_INP;

    if (input_matrix(matrix, &rows, &cols))
    {
        if (rows <= MAX_ROWS && rows > 0 && cols <= MAX_COLS && cols > 0)
        {
            int array[MAX_ROWS] = { 0 };
            int elements_number = 0;
            
            make_array_from_matrix(matrix, rows, cols, array, &elements_number);
            print_array(array, elements_number);
            exit_code = ERR_OK;
        }
    }

    return exit_code;
}

int input_matrix(int **matrix, int *rows, int *cols)
{
    int is_correct = 1;

    if (scanf("%d %d", rows, cols) != 2)
    {
        is_correct = 0;
    }

    for (int current_row = 0; current_row < *rows; ++current_row)
    {
        for (int current_col = 0; current_col < *cols; ++current_col)
        {
            if (scanf("%d", (matrix[current_row] + current_col)) != 1)
            {
                is_correct = 0;
            }
        }    
    }

    return is_correct;
}

void transform_matrix(int **matrix, int *buf, int rows, int cols)
{
    for (int current_row = 0; current_row < rows; ++current_row)
    {
        matrix[current_row] = buf + current_row * cols;
    }
}

void print_array(int *array, int elements_number)
{
    for (int current_element = 0; current_element < elements_number; ++current_element)
    {
        printf("%d ", array[current_element]);
    }
}

int is_monotone(int *array, int elements_number)
{
    int flag = array[0] <= array[elements_number - 1];
    int is_monotone = 1;

    for (int current_element = 0; current_element < elements_number - 1; ++current_element)
    {
        if ((array[current_element] < array[current_element + 1]) != flag && array[current_element] != array[current_element + 1])
        {
            is_monotone = 0;
        } 
    }

    if (elements_number == 1)
    {
        is_monotone = 0;
    }

    return is_monotone;
}

void make_array_from_matrix(int **matrix, int rows, int cols, int *array, int *elements_number)
{
    for (int current_row = 0; current_row < rows; ++current_row)
    {
        array[current_row] = is_monotone(matrix[current_row], cols);
    }

    *elements_number = rows;
}
