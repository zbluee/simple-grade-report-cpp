#pragma once
#include <string>

struct Course
{
    /* data */
    std::string name;
    int credits;
    std::string grade;
    Course(const std::string &name, const int &credits, const std::string &grade) : name(name), credits(credits), grade(grade) {}
};
