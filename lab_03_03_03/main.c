#include <stdio.h>

#define ERR_OK 0
#define ERR_INP_MATRIX 1

#define MAX_ROWS 10
#define MAX_COLS 10

int input_matrix(int **matrix, int *rows, int *cols);

void transform_matrix(int **matrix, int *buf, int rows, int cols);

void print_matrix(int **matrix, int rows, int cols);

void swap(int **row_1, int **row_2);

int min_in_array(int *array, int elements_number);

void sort_rows_by_min_elements(int **matrix, int rows, int cols);

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
        sort_rows_by_min_elements(matrix, rows, cols);
        print_matrix(matrix, rows, cols);
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

int min_in_array(int *array, int elements_number)
{
    int min = array[0];

    for (int current_element = 1; current_element < elements_number; ++current_element)
    {
        if (array[current_element] < min)
        {
            min = array[current_element];
        }
    }

    return min;
}

void swap(int **row_1, int **row_2)
{
    int *temp_ptr = *row_1;
    *row_1 = *row_2;
    *row_2 = temp_ptr;
}

void sort_rows_by_min_elements(int **matrix, int rows, int cols)
{
    for (int current_step = 0; current_step < rows - 1; ++current_step)
    {
        for (int current_row = 0; current_row < rows - current_step - 1; ++current_row)
        {
            if (min_in_array(matrix[current_row], cols) < min_in_array(matrix[current_row + 1], cols))
            {
                swap(matrix + current_row, matrix + current_row + 1); 
            }
        }
    }
}
