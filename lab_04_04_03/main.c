#include <stdio.h>
#include <string.h>

#define ERR_OK 0
#define ERR_NO_STRING 1

#define MAX_STRING_LEN 257
#define MAX_STRINGS 2
#define STRINGS_NUMBER 1

#define NULL ((void *)0)

int read_strings(char array_strings[][MAX_STRING_LEN], int strings_number);

char *strip_chars_left(char string[], const char chars_to_remove[]);

char *strip_chars_right(char string[], const char chars_to_remove[]);

char *strip_chars(char string[], const char chars_to_remove[]);

int parce_number(char string[]);

int main(void)
{
    int rc = ERR_OK;

    char array_strings[MAX_STRINGS][MAX_STRING_LEN] = { '\0' };

    const char *spaces_symbols = "\t\n\r ";

    if (read_strings(array_strings, MAX_STRINGS) == STRINGS_NUMBER)
    {
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
    while (strchr(chars_to_remove, *string) != NULL)
    {
        ++string;
    }

    return string; 
}

char *strip_chars_right(char string[], const char chars_to_remove[])
{
    char *string_end = string + strlen(string) - 1;

    while (strchr(chars_to_remove, *string_end) != NULL)
    {
        --string_end;
    }

    *++string_end = '\0';

    return string;
}

char *strip_chars(char string[], const char chars_to_remove[])
{
    char *new_string = strip_chars_left(string, chars_to_remove);
    strip_chars_right(new_string, chars_to_remove);

    return new_string;
}

int parce_number(char string[])
{
    const char *digits = "0123456789";
    int is_mobile_number = 1;

    if (*string == '+')
    {
        ++string;
        int digits_counter = 0;
        if (*string)
        {
            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }

            if (digits_counter < 1)
            {
                is_mobile_number = 0;
            }
        }
        if (*string != '(')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string)
        {
            digits_counter = 0;
            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }
        if (digits_counter != 3)
        {
            is_mobile_number = 0;
        }
        if (*string != ')')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string != '-')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string)
        {
            digits_counter = 0;

            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }

        if (digits_counter != 3)
        {
            is_mobile_number = 0;
        }

        if (*string != '-')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string)
        {
            digits_counter = 0;

            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }

        if (digits_counter != 2)
        {
            is_mobile_number = 0;
        }

        if (*string != '-')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string)
        {
            digits_counter = 0;

            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }

        if (digits_counter != 2)
        {
            is_mobile_number = 0;
        }
        
        if (*string != '\0')
        {
            is_mobile_number = 0;
        }
    }

    else
    {
        int digits_counter = 0;
        if (*string != '(')
        {
            is_mobile_number = 0;
        }
        ++string;
        if(*string)
        {
            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }
        if (digits_counter < 3)
        {
            is_mobile_number = 0;
        }
        if (*string != ')')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string != '-')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string)
        {
            digits_counter = 0;

            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }

        if (digits_counter != 3)
        {
            is_mobile_number = 0;
        }

        if (*string != '-')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string)
        {
            digits_counter = 0;

            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }

        if (digits_counter != 2)
        {
            is_mobile_number = 0;
        }

        if (*string != '-')
        {
            is_mobile_number = 0;
        }
        ++string;
        if (*string)
        {
            digits_counter = 0;

            while ((strchr(digits, *string) != NULL) && *string)
            {
                ++string;
                ++digits_counter;
            }
        }

        if (digits_counter != 2)
        {
            is_mobile_number = 0;
        }
        
        if (*string != '\0')
        {
            is_mobile_number = 0;
        }
    }

    return is_mobile_number;
}
