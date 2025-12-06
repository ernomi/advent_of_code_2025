#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "utils.h"

void process_range(char *str, long *result)
{
    char **range = split(str, '-');
    long start = atol(range[0]);
    long end = atol(range[1]);
    char buf[50];

    while (start <= end)
    {
        char half_1_buf[50], half_2_buf[50];

        snprintf(buf, sizeof(buf), "%ld", start);
        int half = strlen(buf) / 2;

        memcpy(half_1_buf, buf, half);
        half_1_buf[half] = '\0';

        strcpy(half_2_buf, buf + half);

        if (strcmp(half_1_buf, half_2_buf) == 0)
            *result += start;
        
        start++;
    }
    free_arr(range);
}

int main(int argc, char **argv)
{
    FILE *fp;
    char *str = NULL;
    size_t len = 0;
    ssize_t nread;

    if (argc != 2)
    {
        printf("Provide a text file to read.\n");
        return (1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&str, &len, fp)) != -1)
    {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(str, nread, 1, stdout);
    }

    char **list = split(str, ',');
    
    free(str);
    fclose(fp);
    
    int i = 0;
    long result = 0;
    while (list[i])
    {
        process_range(list[i], &result);
        i++;
    }

    free_arr(list);

    printf("\nresult: %ld\n", result);

    return (0);

}