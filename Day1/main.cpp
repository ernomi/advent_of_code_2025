#include "Dial.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Provide a text file to read\n";
        return (1);
    }

    Dial passCodeDial(50);

    std::ifstream file(argv[1]);
    std::string line;

    while (std::getline(file, line))
    {
        passCodeDial.processInput(line);
    }

    std::cout << passCodeDial.getResult() << std::endl;


    return (0);
}