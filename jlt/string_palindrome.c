#include "common.h"

char *string_splice(char *input_str, int len)
{
    char *output_str = malloc(len);
    if (output_str)
    {
        char *start = input_str;
        strncpy(output_str, input_str, len);
        strncpy(input_str, input_str + len, strlen(input_str) - len);
    }

    return output_str;
}

bool is_palindrome(char *string, int len)
{
    if (len > 1)
    {
        char *start = string;
        char *end = string + len - 1;

        for (; start < end; start++, end--)
        {
            if (*start != *end)
            {
                return false;
            }
        }
    }

    return true;
}

void print_palindromes(char *string)
{
    printf("input_str: %s\n", string);

    int num_palindromes = 0;
    char *p = string;
    while (p < (string + strlen(string)))
    {
        int len;
        for (len = strlen(p); len >= 1; len--)
        {
            printf("%s %d\n", p, len);
            if (is_palindrome(p, len))
            {
                char *palindrome = malloc(len);
                strncpy(palindrome, p, len);
                printf("palindrome found: %s\n", palindrome);
                free(palindrome);
                num_palindromes++;
                break;
            }
        }
        p += len;
    }
    printf("num palindromes: %d\n", num_palindromes);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Pass a string to the program\n");
        return 1;
    }

    char *input_str = argv[1];

    /* Validate the input string */
    for (int i = 0; i < strlen(input_str); i++)
    {
        if (input_str[i] != 'a' && input_str[i] != 'b')
        {
            printf("Pass a string containing only 'a' and 'b'\n");
            return 1;
        }
    }

    print_palindromes(input_str);

    return 0;
}
