#pragma once

struct Point
{
    int totalCredits;
    double totalGradePoints;
    double gpa() { return totalGradePoints / totalCredits; };
};