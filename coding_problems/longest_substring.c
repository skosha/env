/*
 * Problem:
 * Given a string, find the length of the longest substring without repeating characters.
 *
 * Example 1:
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 *              Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */
#include "common.h"

#define MAX_CHAR                128
#define LEN_SUBSTRING(s, e)     (e - s + 1)
#define MAX(a, b)               ((a) > (b) ? (a) : (b))

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("pass a string\n");
        return -1;
    }

    char *input_string = argv[1];
    uint32_t pos[MAX_CHAR] = {0};
    uint32_t start_index = 0;
    uint32_t max_length = 0;

    for (uint32_t i = 0; i < strlen(input_string); i++)
    {
        uint32_t new_length = 0;
        uint8_t c = (uint8_t)input_string[i];

        if (pos[c] != 0)
        {
            uint32_t last_pos = pos[c] - 1;
            printf("1: i %d, pos[c] %d, start_index %d, max_length %d\n", i, last_pos, start_index, max_length);
            new_length = MAX(LEN_SUBSTRING(start_index, last_pos), LEN_SUBSTRING(last_pos, i));
            start_index = last_pos + 1;
        }
        else
        {
            new_length = LEN_SUBSTRING(start_index, i);
        }

        max_length = MAX(max_length, new_length);
        pos[c] = i + 1;

        printf("2: i %d, pos[c] %d, start_index %d, max_length %d\n", i, pos[c] - 1, start_index, max_length);
    }

    printf("Max length of unique substring: %d\n", max_length);

    return 0;
}
