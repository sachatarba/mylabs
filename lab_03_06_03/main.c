#include <stdio.h>
#include <stdlib.h>

#define ERR_OK 0
#define ERR_INP_MATRIX 1
#define ERR_NO_SQUARE 2

#define MAX_ROWS 10
#define MAX_COLS 10

int fill_ring(int **matrix, int begin, int element_number, int counter);

int fill_matrix(int **matrix, int *rows, int *cols);

void transform_matrix(int **matrix, int *buf, int rows, int cols);

void print_matrix(int **matrix, int rows, int cols);

int main(void)
{
    int rc = ERR_OK;
    int buf[MAX_ROWS][MAX_COLS] = { 0 };
    int *matrix[MAX_ROWS] = { 0 };
    int rows = 0;
    int cols = 0;
    transform_matrix(matrix, buf[0], MAX_ROWS, MAX_COLS);

    if (fill_matrix(matrix, &rows, &cols) && 0 < rows && rows <= MAX_ROWS && 0 < cols && cols <= MAX_COLS)
    {
        if (rows == cols)
        {
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

int fill_ring(int **matrix, int begin, int element_number, int counter)
{
    for (int current_element = 0; current_element < element_number; ++current_element)
    {
        matrix[current_element + begin][begin] = counter++;
    }
    
    for (int current_element = 1; current_element < element_number; ++current_element) 
    {
        matrix[element_number - 1 + begin][current_element + begin] = counter++;
    }

    for (int current_element = element_number - 2; current_element >= 0; --current_element)
    {
        matrix[current_element + begin][element_number - 1 + begin] = counter++;
    }

    for (int current_element = element_number - 2; current_element >= 1; --current_element)
    {
        matrix[begin][current_element + begin] = counter++;
    }
    return counter;
}

int fill_matrix(int **matrix, int *rows, int *cols)
{
    int rc = 1;

    if (scanf("%d %d", rows, cols) == 2)
    {
        int temp = 1;
        int size = *rows;
    
        for (int current_element = 0; size >= 2; ++current_element, size -= 2)
        {
            temp = fill_ring(matrix, current_element, size, temp);
        }
        if (size == 1) 
        {
            matrix[*rows / 2][*rows / 2] = temp;
        }
    }
    else
    {
        rc = 0;
    }

    return rc;
}
