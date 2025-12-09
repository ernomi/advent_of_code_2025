#include <fstream>
#include <iostream>
#include "Battery.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Provide a text file to read.\n";
        return (1);
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cout << "Failed to open file.\n";
        return (1);
    }

    std::string line;
    int total = 0;

    while (std::getline(file, line))
    {
        total += Battery::processInput(line);
    }

    std::cout << "Total joltage: " << total << std::endl;

    return (0);
}