#include <stdio.h>
#include <stdlib.h>

#define ERR_OK 0
#define ERR_INP_MATRIX 1
#define ERR_NO_ARRAY 2

#define MAX_ROWS 10
#define MAX_COLS 10

#define TEN_DIV 10

#define SHIFT 3

#define MIN_DIGIT_SUM 11

int input_matrix(int **matrix, int *rows, int *cols);

void transform_matrix(int **matrix, int *buf, int rows, int cols);

void print_matrix(int **matrix, int rows, int cols);

int is_digits_sum_more_or_eq_than(int number, int min_digits_sum);

void copy_number_from_matrix(int **matrix, int rows, int cols, int *array, int *elements_number);

void insert_numbers(int **matrix, int rows, int cols, int *array);

void shift_left(int *array, int element_number);

void shift_left_on_size(int *array, int element_number, int size);

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
        int array[MAX_ROWS * MAX_COLS] = { 0 };
        int elements_number = 0;

        copy_number_from_matrix(matrix, rows, cols, array, &elements_number);

        if (elements_number != 0)
        {
            shift_left_on_size(array, elements_number, SHIFT);
            insert_numbers(matrix, rows, cols, array);
            print_matrix(matrix, rows, cols);
        }
        else
        {
            rc = ERR_NO_ARRAY;
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

int is_digits_sum_more_or_eq_than(int number, int min_digits_sum)
{
    int is_sum_more_or_eq = 0;
    int current_digit = 0;
    int digits_sum = 0;
    number = abs(number);

    while ((number != 0) && digits_sum < min_digits_sum)
    {
        current_digit = number % TEN_DIV;
        number /= TEN_DIV;
        digits_sum += current_digit;
    }
    is_sum_more_or_eq = digits_sum >= min_digits_sum;

    return is_sum_more_or_eq;
}

void copy_number_from_matrix(int **matrix, int rows, int cols, int *array, int *elements_number)
{
    *elements_number = 0;
    for (int current_row = 0; current_row < rows; ++current_row)
    {
        for (int current_col = 0; current_col < cols; ++current_col)
        {
            if (is_digits_sum_more_or_eq_than(matrix[current_row][current_col], MIN_DIGIT_SUM))
            {
                array[*elements_number] = matrix[current_row][current_col]; 
                ++*elements_number;
            }
        }
    }  
}

void shift_left(int *array, int element_number)
{
    int first = array[0];

    for (int current_element = 1; current_element < element_number; ++current_element)
    {
        array[current_element - 1] = array[current_element];
    }

    array[element_number - 1] = first;
}

void shift_left_on_size(int *array, int element_number, int size)
{
    for (int counter = 0; counter < size; ++counter)
    {
        shift_left(array, element_number);
    }
}

void insert_numbers(int **matrix, int rows, int cols, int *array)
{
    int current_element = 0;

    for (int current_row = 0; current_row < rows; ++current_row)
    {
        for (int current_col = 0; current_col < cols; ++current_col)
        {
            if (is_digits_sum_more_or_eq_than(matrix[current_row][current_col], MIN_DIGIT_SUM))
            {
                matrix[current_row][current_col] = array[current_element];
                ++current_element;
            }
        }
    }
}
