#include <stdio.h>
#include <string.h>

#define ERR_OK 0

#define MAX_LEN 256

#define NULL ((void *)0) 

#define STR_TESTS 6
#define CHAR_TESTS 7

char *my_strchr(const char *str, int symbol);

char *my_strrchr(const char *str, int symbol);

char *my_strpbrk(const char *str1, const char *str2);

int test_strchr(char *source_str, int source_symbol);

int test_strrchr(char *source_str, int source_symbol);

int test_strpbrk(char *source_str1, char *source_str2);

int test_all(char tests_source_str[][MAX_LEN], int str_number, char tests_source_chars[], int chars_number);

int main(void)
{
    char source_str[][MAX_LEN] = { "hello, my friend", "\0", "k", "we live in a society", "o,im", "hell\0 no" };
    char source_chars[] = { 'h', 'd', 'y', ' ', 'm', 'k', '\0' };

    int failed_tests = test_all(source_str, STR_TESTS, source_chars, CHAR_TESTS);

    printf("%d", failed_tests);

    return ERR_OK;   
}

char *my_strchr(const char *str, int symbol)
{
    char *ptr = NULL;

    while (*str && !ptr)
    {
        if (*str == symbol)
        {
            ptr = (char *) str;
        }

        ++str;
    }

    if (symbol == '\0')
    {
        ptr = (char *) str;
    }

    return ptr;
}

char *my_strrchr(const char *str, int symbol)
{
    char *ptr = NULL;

    while (*str)
    {
        if (*str == symbol)
        {
            ptr = (char *) str;
        }

        ++str;
    }

    if (symbol == '\0')
    {
        ptr = (char *) str;
    }

    return ptr;
}

char *my_strpbrk(const char *str1, const char *str2)
{
    char *ptr_ret = NULL;
    char *str2_copy = (char *) str2;

    while (*str1 && !ptr_ret)
    {
        str2 = str2_copy;

        while (*str2)
        {
            if (*str1 == *str2)
            {
                ptr_ret = (char *) str1;
            }

            ++str2;
        }

        ++str1;
    }

    return ptr_ret;
}

int test_strchr(char *source_str, int source_symbol)
{
    return (strchr(source_str, source_symbol) == my_strchr(source_str, source_symbol));
}

int test_strrchr(char *source_str, int source_symbol)
{
    return strrchr(source_str, source_symbol) == my_strrchr(source_str, source_symbol);
}

int test_strpbrk(char *source_str1, char *source_str2)
{
    return strpbrk(source_str1, source_str2) == my_strpbrk(source_str1, source_str2);
}

int test_all(char tests_source_str[][MAX_LEN], int str_number, char tests_source_chars[], int chars_number)
{
    int failed_tests = 0;
    int is_test_passed = 0;

    for (int current_test_str = 0; current_test_str < str_number; ++current_test_str)
    {
        for (int current_test_char = 0; current_test_char < chars_number; ++current_test_char)
        {
            is_test_passed = test_strchr(tests_source_str[current_test_str], tests_source_chars[current_test_char]);
            
            if (!is_test_passed)
            {
                ++failed_tests;
            }
        }
    }

    for (int current_test_str = 0; current_test_str < str_number; ++current_test_str)
    {
        for (int current_test_char = 0; current_test_char < chars_number; ++current_test_char)
        {
            is_test_passed = test_strrchr(tests_source_str[current_test_str], tests_source_chars[current_test_char]);
            
            if (!is_test_passed)
            {
                ++failed_tests;
            }
        }
    }

    for (int current_test_str = 0; current_test_str < str_number; ++current_test_str)
    {
        for (int next_test_str = 0; next_test_str < str_number; ++next_test_str)
        {
            is_test_passed = test_strpbrk(tests_source_str[current_test_str], tests_source_str[next_test_str]);
            
            if (!is_test_passed)
            {
                ++failed_tests;
            }
        }
    }

    return failed_tests;
}