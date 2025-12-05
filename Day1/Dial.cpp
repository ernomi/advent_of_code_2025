#include "Dial.h"
#include <iostream>

Dial::Dial(int startPos) : m_number(startPos), m_result(0), m_version(1)
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
    int zeroCount = 0;

    while (amount)
    {
        m_number++;
        if (m_number > 99)
        {
            m_number = 0;
            if (m_version == 2)
                zeroCount += 1;
        }
        amount--;
    }
    if (m_number == 0)
        m_version == 2 ? m_result += zeroCount : m_result += 1;
    else
        m_result += zeroCount;
}

void Dial::dialLeft(int amount)
{
    int zeroCount = 0;

    while (amount)
    {
        m_number--;
        if (m_version == 2 && m_number == 0)
            zeroCount += 1;
        if (m_number < 0)
        {
            m_number = 99;
        }
        amount--;
    }
    if (m_number == 0)
        m_version == 2 ? m_result += zeroCount : m_result += 1;
    else
        m_result += zeroCount;
}

void Dial::setVersion(int version)
{
    m_version = version;
}