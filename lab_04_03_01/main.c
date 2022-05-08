#include <stdio.h>
#include <string.h>

#define ERR_OK 0
#define ERR_NO_STRING 1
#define ERR_NO_WORDS 2

#define MAX_STRING_LEN 257
#define MAX_WORD_LEN 17
#define MAX_STRINGS 2
#define MAX_WORDS 257
#define STRINGS_NUMBER 1
#define ALL_WORDS 1024

#define NULL ((void *)0)

int read_strings(char array_strings[][MAX_STRING_LEN], int strings_number);

void split_string(char *string, char array_words[][MAX_WORD_LEN], int max_words, const char *delim, int *words_in_string);

char *modify_word(char word[]);

void make_string_from_words(char string[MAX_STRING_LEN], char words[][MAX_WORD_LEN], int words_number);

void del_symbol(char string[], int del_index);

int main(void)
{
    int rc = ERR_OK;

    char array_strings[MAX_STRINGS][MAX_STRING_LEN] = { '\0' };

    const char *delim = "\t\n\r .,:;!?-";

    if (read_strings(array_strings, MAX_STRINGS) == STRINGS_NUMBER)
    {
        char words[MAX_WORDS][MAX_WORD_LEN] = { '\0' };
        char ans_string[MAX_STRING_LEN] = { '\0' };

        int number_of_words = 0;

        split_string(array_strings[0], words, MAX_WORDS, delim, &number_of_words);
        make_string_from_words(ans_string, words, number_of_words);

        if (strlen(ans_string))
        {
            printf("Result: ");
            printf("%s", ans_string);
        }
        else
        {
            rc = ERR_NO_WORDS;
        }       
    }
    else
    {
        rc = ERR_NO_STRING;
    }

    return rc;
}

void split_string(char *string, char array_words[][MAX_WORD_LEN], int max_words, const char *delim, int *words_in_string)
{
    int current_word = 0;

    while (*string && current_word < max_words)
    {
        int current_symbol = 0;

        if (strchr(delim, (int) *string) == NULL)
        {
            while (strchr(delim, (int) *string) == NULL && current_symbol < MAX_WORD_LEN)
            {
                array_words[current_word][current_symbol] = *string;
                ++current_symbol;
                ++string;
            }
            
            array_words[current_word][current_symbol] = '\0';
            ++current_word;
        }
        
        ++string;
    }

    *words_in_string = current_word;
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

void del_symbol(char string[], int del_index)
{
    while (string[del_index])
    {
        string[del_index] = string[del_index + 1];
        ++del_index;
    }
}

char *modify_word(char word[])
{
    char set_of_symbols[MAX_WORD_LEN] = { '\0' };
    int different_symbols = 0;

    for (int current_symbol = 0; word[current_symbol] != '\0'; ++current_symbol)
    {
        if (strchr(set_of_symbols, word[current_symbol]) == NULL)
        {
            set_of_symbols[different_symbols] = word[current_symbol];
            ++different_symbols;
        }
        else
        {
            del_symbol(word, current_symbol);
            --current_symbol;
        }
    }  

    return word;
}

void make_string_from_words(char string[MAX_STRING_LEN], char words[][MAX_WORD_LEN], int words_number)
{
    int len = 0;

    for (int current_word = words_number - 1; current_word >= 0; --current_word)
    {
        if (strcmp(words[current_word], words[words_number - 1]))
        {
            strcat(string, modify_word(words[current_word]));
            len = strlen(string);
            string[len] = ' ';
            string[len + 1] = '\0';
        }
    }

    string[strlen(string) - 1] = '\0';
}
