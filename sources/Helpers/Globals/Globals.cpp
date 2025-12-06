#include "Globals.h"

#include <sstream>
#include <iostream>

void StringHelper::ParseIntoArray(std::vector<std::string>& OutArray, const std::string& InStr, char Delimiter)
{
    std::istringstream Stream(InStr);

    std::string Token;

    while (std::getline(Stream, Token, Delimiter)) {
        OutArray.push_back(Token);
    }
}