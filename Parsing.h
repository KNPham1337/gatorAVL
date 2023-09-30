#pragma once
#include <string>
#include <queue>
#include <iostream>

class parsing{
    public:
        static void parseCommand(std::string& instructions, std::queue<std::string>& q);
        static std::string parseFunction(std::string& instructions);
        static std::string parseName(std::string& instructions);
        static std::string parseID(std::string& instructions);

    private:
        parsing(){}
        ~parsing(){}
};