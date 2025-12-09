#pragma once

#include <string>

class Battery
{
private:

public:
    Battery() = delete;
    ~Battery() = default;

    static int processInput(std::string &line);
};

