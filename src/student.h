#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <fstream>
#include "course.h"
#include "point.h"
#include "utils.h"

class Student
{
private:
    std::string name;
    std::string id;
    std::vector<Course> courses;
    const std::map<std::string, float> gradePoints = {
        {"A+", 4.0}, {"A", 4.0}, {"A-", 3.75}, {"B+", 3.5}, {"B", 3.0}, {"B-", 2.75}, {"C+", 2.5}, {"C", 2.0}, {"C-", 1.75}, {"D+", 1.5}, {"D", 1.0}, {"F", 0.0}};

    bool isValidGrade(std::string& grade)
    {
        if (grade.empty())
            return false;

        // grade[0] = std::toupper(grade[0]);
        return gradePoints.find(toUpper(grade)) != gradePoints.end();
    }

    float gradeToPoints(std::string grade)
    {
        if (grade.empty() || !isValidGrade(grade))
            throw std::invalid_argument("Invalid grade, Grade should be A-F");

        // grade[0] = std::toupper(grade[0]);
        if (gradePoints.find(toUpper(grade)) != gradePoints.end())
            return gradePoints.at(grade);
        else
            throw std::invalid_argument("Invalid grade. Grade should be A-F.");
    }

    void generateReportInFile(Point& point)
    {
        std::string filename = name + " - grade report.txt";
        try
        {
            std::ofstream outputFile(filename);

            if (!outputFile.is_open())
            {
                std::cerr << "Error: unable to open a file for writing." << std::endl;
                return;
            }

            outputFile << "Student Name: " << name << std::endl;
            outputFile << "Student ID: " << id << std::endl;
            outputFile << "----------------------------------------------------------------" << std::endl;
            outputFile << std::setw(30) << std::left << "Course Name"
                       << std::setw(20) << std::left << "Credits"
                       << std::setw(5) << std::left << "Grade" << std::endl;
            outputFile << "----------------------------------------------------------------" << std::endl;

            for (const Course &course : courses)
            {
                outputFile << std::setw(32) << std::left << course.name
                           << std::setw(22) << std::left << course.credits
                           << std::setw(5) << std::left << course.grade << std::endl;
            }

            outputFile << "----------------------------------------------------------------" << std::endl;
            outputFile << "SGP : " << point.totalGradePoints << std::setw(25) << std::right << "GPA : " << std::fixed << std::setprecision(2) << point.gpa() << std::endl;

            outputFile.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error : " << e.what() << std::endl;
        }

        std::cout << std::endl
                  << "Report written to '" << filename + "." << std::endl;
    }

public:
    Student(std::string& name, std::string& id) : name(name), id(id) {}

    void addCourse(std::string& name, int& credits, std::string& grade)
    {
        if (name.empty() || !isValidGrade(grade))
        {
            throw std::invalid_argument("Invalid course or grade.");
        }
        Course course = {name, credits, toUpper(grade)};
        courses.push_back(course);
    }

    Point calculateGPA()
    {
        Point point = {0, 0.0};

        for (const Course &course : courses)
        {
            point.totalCredits += course.credits;
            point.totalGradePoints += course.credits * gradeToPoints(course.grade);
        }

        return point;
    }

    void generateReport(bool writeToFile = false)
    {
        Point point = calculateGPA();
        std::cout << "Student Name: " << name << std::endl;
        std::cout << "Student ID: " << id << std::endl;
        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << std::setw(30) << std::left << "Course Name"
                  << std::setw(20) << std::left << "Credits"
                  << std::setw(5) << std::left << "Grade" << std::endl;
        std::cout << "----------------------------------------------------------------" << std::endl;

        for (const Course &course : courses)
        {
            std::cout << std::setw(32) << std::left << course.name
                      << std::setw(22) << std::left << course.credits
                      << std::setw(5) << std::left << course.grade << std::endl;
        }

        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << "SGP : " << point.totalGradePoints << std::setw(25) << std::right << "GPA : " << std::fixed << std::setprecision(2) << point.gpa() << std::endl;
        if (writeToFile)
            generateReportInFile(point);
    }
};