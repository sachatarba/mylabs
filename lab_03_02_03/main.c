#include <stdio.h>

#define ERR_OK 0
#define ERR_INP_MATRIX 1
#define ERR_INP_DIGIT 2
#define ERR_NO_MATRIX 3

#define MAX_ROWS 10
#define MAX_COLS 10

#define TEN_DIV 10

int input_matrix(int **matrix, int *rows, int *cols);

void transform_matrix(int **matrix, int *buf, int rows, int cols);

void print_matrix(int **matrix, int rows, int cols);

int int_abs(int number);

int has_number_digit(int number, int digit);

int has_col_digit(int **matrix, int rows, int col, int digit);

void del_col(int **matrix, int rows, int *cols, int del_col);

void del_cols_with_digit(int **matrix, int rows, int *cols, int digit);

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
        int digit = 0;

        if (scanf("%d", &digit) == 1 && digit >= 0 && digit < 10)
        {
            del_cols_with_digit(matrix, rows, &cols, digit);

            if (cols > 0)
            {
                print_matrix(matrix, rows, cols);
            }
            else
            {
                rc = ERR_NO_MATRIX;
            }
        }
        else
        {
            rc = ERR_INP_DIGIT;
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

int int_abs(int number)
{
    if (number < 0)
    {
        number *= -1;
    }
    
    return number;
}

int has_number_digit(int number, int digit)
{
    int has_digit = 0;
    int current_digit = 0;

    if (number == digit)
    {
        has_digit = 1;
    }
    else
    {
        while ((number != 0) && !has_digit)
        {
            current_digit = number % TEN_DIV;
            number /= TEN_DIV;
            has_digit = digit == current_digit;
        }
    }

    return has_digit;
}

int has_col_digit(int **matrix, int rows, int col, int digit)
{
    int has_digit = 0;

    for (int current_row = 0; current_row < rows && !has_digit; ++current_row)
    {
        has_digit = has_number_digit(int_abs(matrix[current_row][col]), digit);
    }

    return has_digit;
}

void del_col(int **matrix, int rows, int *cols, int del_col)
{
    for (int current_row = 0; current_row < rows; ++current_row)
    {
        for (int current_col = del_col; current_col < *cols - 1; ++current_col)
        {
            matrix[current_row][current_col] = matrix[current_row][current_col + 1];
        }
    }

    --*cols;
}

void del_cols_with_digit(int **matrix, int rows, int *cols, int digit)
{
    for (int current_col = 0; current_col < *cols; ++current_col)
    {
        if (has_col_digit(matrix, rows, current_col, digit))
        {
            del_col(matrix, rows, cols, current_col);
            --current_col;
        }
    }
}
