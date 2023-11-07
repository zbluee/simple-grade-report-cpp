#pragma once
#include <string>
#include <algorithm>

std::string toUpper(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

std::string toLower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}