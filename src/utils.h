#pragma once
#include <string>
#include <algorithm>
#include <sstream>
#include <ctime>

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

std::string getTimeNow()
{
    const auto currentTime = std::time(nullptr);
    if (currentTime == -1)
        throw std::runtime_error("Failed to get current time.");
    const auto localtime = *std::localtime(&currentTime);
    std::ostringstream osstream;
    osstream << std::put_time(&localtime, "%d-%m-%Y %H-%M-%S");
    return osstream.str();
}

std::string getFileName(const std::string &name, const std::string &timestamp)
{
    return name + "-" + timestamp + "-grade-report.txt";
}