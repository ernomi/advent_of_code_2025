#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include "utils.h"

int count_digits(long n)
{
    int c = 0;
    n = labs(n);
    do
    {
        n /= 10;
        c++;
    } while (n > 0);
    return c;
}

void pattern(long start, long *result)
{
    int digits = count_digits(start);
    if (digits < 2) return;
    char buf[20];
    snprintf(buf, sizeof(buf), "%ld", start);

    for (int pat = 1; pat <= digits / 2; pat++)
    {
        if (digits % pat != 0) continue;
        bool match = true;
        for (int i = pat; i < digits; i++)
        {
            if (buf[i] != buf[i % pat])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            *result += start;
            return;
        }
    }
}

void halve(long start, long *result)
{
    char buf[20];
    char half_1_buf[10], half_2_buf[10];

    snprintf(buf, sizeof(buf), "%ld", start);
    int half = strlen(buf) / 2;

    memcpy(half_1_buf, buf, half);
    half_1_buf[half] = '\0';

    strcpy(half_2_buf, buf + half);

    if (strcmp(half_1_buf, half_2_buf) == 0)
        *result += start;
}

int process_range(char *str, long *result, int searching)
{
    char **range = split(str, '-');
    long start = atol(range[0]);
    long end = atol(range[1]);

    if (errno == ERANGE)
    {
        printf("\nLong int %s value out of range.\n", range[1]);
        free_arr(range);
        return (-1);
    }

    while (start <= end)
    {
        if (!searching)
            halve(start, result);
        else
            pattern(start, result);
        start++;
    }
    free_arr(range);
    return (0);
}

int main(int argc, char **argv)
{
    FILE *fp;
    char *str = NULL;
    size_t len = 0;
    ssize_t nread;
    int searching = 0;

    if (argc != 2 && argc != 3)
    {
        printf("Provide a text file to read.\n");
        return (1);
    }
    if (argc == 3)
    {
        searching = atoi(argv[2]);
        if (searching != 0 && searching != 1)
        {
            printf("Use '0' for first part or '1' for second part.\n");
            return (1);
        }
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&str, &len, fp)) != -1)
    {
        fwrite(str, nread, 1, stdout);
    }

    str[strcspn(str, "\n")] = '\0';

    size_t L = strlen(str);
    if (L > 0 && str[L-1] == ',')
        str[L-1] = '\0';

    char **list = split(str, ',');
    
    free(str);
    fclose(fp);
    
    int i = 0;
    long result = 0;
    while (list[i])
    {
        if (process_range(list[i], &result, searching) < 0)
        {
            free_arr(list);
            return (1);
        }
        i++;
    }

    free_arr(list);

    printf("\nresult: %ld\n", result);

    return (0);

}