#pragma once

#include <string>

class Dial
{
private:
    int m_number;
    int m_result;
public:
    Dial(int startPos);
    ~Dial() = default;

    void processInput(std::string instruction);
    void dialRight(int amount);
    void dialLeft(int amount);

    int getResult() { return m_result; }

};

