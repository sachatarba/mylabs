#include <stdio.h>

#define ERR_OK 0
#define ERR_INP_MATRIX 1
#define ERR_NO_SQUARE 2

#define MAX_ROWS 10
#define MAX_COLS 10

int input_matrix(int **matrix, int *rows, int *cols);

void transform_matrix(int **matrix, int *buf, int rows, int cols);

void print_matrix(int **matrix, int rows, int cols);

int min(int number_1, int number_2);

void swap(int *number_1, int *number_2);

void change_cols(int **matrix, int rows, int cols);

int main(void)
{
    int rc = ERR_OK;
    int buf[MAX_ROWS][MAX_COLS] = { 0 };
    int *matrix[MAX_ROWS] = { 0 };
    int rows = 0;
    int cols = 0;
    transform_matrix(matrix, buf[0], MAX_ROWS, MAX_COLS);

    if (input_matrix(matrix, &rows, &cols) && 0 < rows && rows <= MAX_ROWS && 0 < cols && cols < MAX_COLS)
    {
        if (rows == cols)
        {
            change_cols(matrix, rows, cols);
            print_matrix(matrix, rows, cols);
        }
        else
        {
            rc = ERR_NO_SQUARE;
        }
    }
    else
    {
        rc = ERR_INP_MATRIX;
    }

    return rc;
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

void print_matrix(int **matrix, int rows, int cols)
{
    for (int current_row = 0; current_row < rows; ++current_row)
    {
        for (int current_col = 0; current_col < cols; ++current_col)
        {
            printf("%d ", matrix[current_row][current_col]);
        }

        printf("\n");
    }
}

int min(int number_1, int number_2)
{
    return (number_1 < number_2) ? number_1 : number_2;
}

void swap(int *number_1, int *number_2)
{
    int temp = *number_1;
    *number_1 = *number_2;
    *number_2 = temp; 
}

void change_cols(int **matrix, int rows, int cols)
{
    for (int current_row = 0; current_row < rows; ++current_row)
    {
        for (int current_element = 0; current_element <= min(current_row, rows - current_row - 1); ++current_element)
        {
            swap(matrix[current_row] + current_element, matrix[current_row] + cols - current_element - 1);
        }
    }
}
