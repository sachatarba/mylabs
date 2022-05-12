#include <stdio.h>
#include <string.h>

#define ERR_OK 0
#define ERR_NO_STRING 1

#define MAX_STRING_LEN 257
#define MAX_STRINGS 2
#define STRINGS_NUMBER 1

#define MIN_DIGITS_CNTRY_CODE 1
#define DIGITS_OPERATOR_CODE 3
#define DIGITS_FIRST_BLOCK 3
#define DIGITS_SECOND_BLOCK 2
#define DIGITS_THIRD_BLOCK 2

#define NULL ((void *)0)

int read_strings(char array_strings[][MAX_STRING_LEN], int strings_number);

char *strip_chars_left(char string[], const char chars_to_remove[]);

char *strip_chars_right(char string[], const char chars_to_remove[]);

char *strip_chars(char string[], const char chars_to_remove[]);

int parce_number(char string[]);

void set_phone_status_by_min_digits(char **string, int required_min_number_of_digits, int *is_mobile_number_status);

void set_phone_status_by_digits(char **string, int required_number_of_digits, int *is_mobile_number_status);

void set_phone_status_by_char(char **string, char required_char, int *is_mobile_number_status);

int parce_number_withno_cntry_code(char **string, int *is_mobile_number_status);

int main(void)
{
    int rc = ERR_OK;

    char array_strings[MAX_STRINGS][MAX_STRING_LEN] = { '\0' };


    if (read_strings(array_strings, MAX_STRINGS) == STRINGS_NUMBER)
    {
        const char *spaces_symbols = "\t\n\r ";
        char *new_string = strip_chars(array_strings[0], spaces_symbols);

        if (parce_number(new_string))
        {
            printf("YES");
        }
        else
        {
            printf("NO");
        }
    }
    else
    {
        rc = ERR_NO_STRING;
    }

    return rc;
}

int read_strings(char array_strings[][MAX_STRING_LEN], int strings_number)
{
    int current_string = 0;
    int strings = 0;

    while (current_string < strings_number)
    {
        if (fgets(array_strings[current_string], MAX_STRING_LEN - 1, stdin) != NULL)
        {
            ++strings;
        }

        ++current_string;
    }

    return strings;
}

char *strip_chars_left(char string[], const char chars_to_remove[])
{
    while (*string && strchr(chars_to_remove, *string) != NULL)
    {
        ++string;
    }

    return string; 
}

char *strip_chars_right(char string[], const char chars_to_remove[])
{
    if (*string)
    {
        char *string_end = string + strlen(string) - 1;

        while (strchr(chars_to_remove, *string_end) != NULL)
        {
            --string_end;
        }

        *++string_end = '\0';
    }

    return string;
}

char *strip_chars(char string[], const char chars_to_remove[])
{
    char *new_string = strip_chars_left(string, chars_to_remove);
    strip_chars_right(new_string, chars_to_remove);

    return new_string;
}

int read_digits(char **string)
{
    const char *digits = "0123456789";
    int digits_counter = 0;

    while (**string && (strchr(digits, **string) != NULL))
    {
        ++*string;
        ++digits_counter;
    }

    return digits_counter;
}

void set_phone_status_by_min_digits(char **string, int required_min_number_of_digits, int *is_mobile_number_status)
{
    int digits_counter = read_digits(string);

    if (digits_counter < required_min_number_of_digits)
    {
        *is_mobile_number_status = 0;
    }
}

void set_phone_status_by_digits(char **string, int required_number_of_digits, int *is_mobile_number_status)
{
    int digits_counter = read_digits(string);

    if (digits_counter != required_number_of_digits)
    {
        *is_mobile_number_status = 0;
    }
}

void set_phone_status_by_char(char **string, char required_char, int *is_mobile_number_status)
{
    if (**string != required_char)
    {
        *is_mobile_number_status = 0;
    }

    ++*string;
}

int parce_number_withno_cntry_code(char **string, int *is_mobile_number_status)
{
    set_phone_status_by_char(string, '(', is_mobile_number_status);

    set_phone_status_by_digits(string, DIGITS_OPERATOR_CODE, is_mobile_number_status);

    set_phone_status_by_char(string, ')', is_mobile_number_status);

    set_phone_status_by_char(string, '-', is_mobile_number_status);

    set_phone_status_by_digits(string, DIGITS_FIRST_BLOCK, is_mobile_number_status);

    set_phone_status_by_char(string, '-', is_mobile_number_status);

    set_phone_status_by_digits(string, DIGITS_SECOND_BLOCK, is_mobile_number_status);

    set_phone_status_by_char(string, '-', is_mobile_number_status);
        
    set_phone_status_by_digits(string, DIGITS_THIRD_BLOCK, is_mobile_number_status);

    set_phone_status_by_char(string, '\0', is_mobile_number_status);

    return *is_mobile_number_status;
}

int parce_number(char string[])
{
    int is_mobile_number = 1;

    if (*string == '+')
    {
        ++string;

        set_phone_status_by_min_digits(&string, MIN_DIGITS_CNTRY_CODE, &is_mobile_number);

        parce_number_withno_cntry_code(&string, &is_mobile_number);
    }
    else
    {
        parce_number_withno_cntry_code(&string, &is_mobile_number);
    }

    return is_mobile_number;
}
