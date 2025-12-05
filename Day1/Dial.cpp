#include "Dial.h"

Dial::Dial(int startPos) : m_number(startPos), m_result(0)
{
}

void Dial::processInput(std::string instruction)
{
    if (instruction[0] == 'R')
    {
        instruction.erase(instruction.begin());
        dialRight(std::stoi(instruction));
    }
    else if (instruction[0] == 'L')
    {
        instruction.erase(instruction.begin());
        dialLeft(std::stoi(instruction));
    }
}

void Dial::dialRight(int amount)
{
    while (amount)
    {
        m_number++;
        if (m_number > 99)
            m_number = 0;
        amount--;
    }
    if (m_number == 0)
        m_result += 1;
}

void Dial::dialLeft(int amount)
{
    while (amount)
    {
        m_number--;
        if (m_number < 0)
            m_number = 99;
        amount--;
    }
    if (m_number == 0)
        m_result += 1;
}