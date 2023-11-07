#include <iostream>
#include <string>
#include <limits>
#include "src/student.h"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char const *argv[])
{
    std::string name;
    std::string id;
    std::string courseName;
    int credits;
    std::string grade;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    std::cout << "Enter your ID: ";
    std::getline(std::cin, id);

    Student student(name, id);

    while (true)
    {
        std::cout << "Enter your course name(or 'quit', 'q' to exit) : ";
        std::getline(std::cin, courseName);

        if (toLower(courseName) == "quit" || toLower(courseName) == "q")
            break;

        std::cout << "Enter credits for the course: ";
        if (!(std::cin >> credits))
        {
            std::cin.clear(); // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cerr << "Invalid input. Please enter a number." << std::endl;
            continue; // Restart the loop
        }
        // Clear the newline character from the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter grade for the course: ";
        std::getline(std::cin, grade);

        try
        {
            student.addCourse(courseName, credits, grade);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    std::string writeToFile;
    std::cout << "Do you want to generate a file for your grade report ?('Y' or 'N') ";
    std::getline(std::cin, writeToFile);

    // try
    // {
    //     student.addCourse("Calculus I", 5, "A");
    //     student.addCourse("Linear Algebra I", 5, "A-");
    //     student.addCourse("Programming I", 6, "A+");
    // }
    // catch (const std::invalid_argument &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }

    if (toLower(writeToFile) == "y" || toLower(writeToFile) == "yes")
        student.generateReport(true);
    else
        student.generateReport();

    return 0;
}
