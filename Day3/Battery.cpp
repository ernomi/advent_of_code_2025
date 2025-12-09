#include "Battery.h"
#include <iostream>

int Battery::processInput(std::string &line)
{
    int len = line.length();
    int bat1 = 0;
    int bat2 = 0;
    int num = 0;
    int bat1Index = 0;
    int total = 0;

    for (int i = 0; i < len; i++)
    {
        num = line[i] - '0';
        if (num > bat1)
        {
            bat1 = num;
            bat1Index = i;
        }
        bat2 = 0;
        for (int j = bat1Index + 1; j < len; j++)
        {
            num = line[j] - '0';
            if (num > bat2)
                bat2 = num;
            if (total < bat1 * 10 + bat2)
                total = bat1 * 10 + bat2;
        }
    }

    return total;
}