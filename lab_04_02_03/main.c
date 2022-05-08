#include <stdio.h>
#include <string.h>

#define ERR_OK 0
#define ERR_NO_STRINGS 1
#define ERR_NO_WORDS 2

#define MAX_STRING_LEN 257
#define MAX_WORD_LEN 17
#define MAX_STRINGS 2
#define MAX_WORDS 257
#define STRINGS_NUMBER 2
#define ALL_WORDS 1024

#define NULL ((void *)0)

int read_strings(char array_strings[][MAX_STRING_LEN], int strings_number);

void split_string(char *string, char array_words[][MAX_WORD_LEN], int max_words, const char *delim, int *words_in_string);

int word_count(char array_words[][MAX_WORD_LEN], int words_number, char *word);

void make_unique_from_words1(char words1[][MAX_WORD_LEN], int words_number1, char words2[][MAX_WORD_LEN], int words_number2, char words_unique[][MAX_WORD_LEN], int *unique_words);

void make_unique_words(char words1[][MAX_WORD_LEN], int words_number1, char words2[][MAX_WORD_LEN], int words_number2, char words_unique[][MAX_WORD_LEN], int *unique_words);

void print_words(char array_words[][MAX_WORD_LEN], int words_number);

int main(void)
{
    int rc = ERR_OK;

    char array_strings[MAX_STRINGS][MAX_STRING_LEN] = { '\0' };

    const char *delim = "\t\n\r .,:;!?-";

    if (read_strings(array_strings, MAX_STRINGS) == STRINGS_NUMBER)
    {
        char words1[MAX_WORDS][MAX_WORD_LEN] = { '\0' };
        char words2[MAX_WORDS][MAX_WORD_LEN] = { '\0' };
        char words_unique[ALL_WORDS][MAX_WORD_LEN] = { '\0' };

        int number_of_words1 = 0;
        int number_of_words2 = 0;
        int number_of_unique_words = 0;

        split_string(array_strings[0], words1, MAX_WORDS, delim, &number_of_words1);
        split_string(array_strings[1], words2, MAX_WORDS, delim, &number_of_words2);

        make_unique_words(words1, number_of_words1, words2, number_of_words2, words_unique, &number_of_unique_words);

        if (number_of_unique_words)
        {
            printf("Result: ");
            print_words(words_unique, number_of_unique_words);
        }
        else
        {
            rc = ERR_NO_WORDS;
        }       
    }
    else
    {
        rc = ERR_NO_STRINGS;
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

int word_count(char array_words[][MAX_WORD_LEN], int words_number, char *word)
{
    int word_counter = 0;

    for (int current_word = 0; current_word < words_number; ++current_word)
    {
        if (!strcmp(array_words[current_word], word))
        {
            ++word_counter;
        }
    }

    return word_counter;
}

void make_unique_from_words1(char words1[][MAX_WORD_LEN], int words_number1, char words2[][MAX_WORD_LEN], int words_number2, char words_unique[][MAX_WORD_LEN], int *unique_words)
{
    int counter_word_in_arrays = 0;
    
    for (int current_word = 0; current_word < words_number1; ++current_word)
    {
        counter_word_in_arrays = word_count(words1, words_number1, words1[current_word]);
        counter_word_in_arrays += word_count(words2, words_number2, words1[current_word]);

        if (counter_word_in_arrays == 1)
        {
            strcpy(words_unique[*unique_words], words1[current_word]);
            ++*unique_words;
        }        
    }
}

void make_unique_words(char words1[][MAX_WORD_LEN], int words_number1, char words2[][MAX_WORD_LEN], int words_number2, char words_unique[][MAX_WORD_LEN], int *unique_words)
{
    make_unique_from_words1(words1, words_number1, words2, words_number2, words_unique, unique_words);
    make_unique_from_words1(words2, words_number2, words1, words_number1, words_unique, unique_words);
}

void print_words(char words[][MAX_WORD_LEN], int words_number)
{
    for (int current_word = 0; current_word < words_number; ++current_word)
    {
        printf("%s ", words[current_word]);
    }
}
