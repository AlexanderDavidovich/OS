
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

struct employee {
    int num;        
    char name[10];  
    double hours;   
};

int main(int argc, char* argv[])
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <binary_file> <number_of_records>\n";
        return 1;
    }

    const char* filename = argv[1];
    int numRecords = std::atoi(argv[2]);

    std::ofstream out(filename, std::ios::binary);
    if (!out)
    {
        std::cerr << "Error opening file " << filename << " for writing.\n";
        return 1;
    }

    for (int i = 0; i < numRecords; i++)
    {
        employee emp;
        std::cout << "\nEnter data for employee " << (i + 1) << ":\n";
        std::cout << "Employee ID: ";
        std::cin >> emp.num;
        std::cout << "Employee name (max 9 chars): ";
        std::cin >> emp.name;
        std::cout << "Hours worked: ";
        std::cin >> emp.hours;


        emp.name[9] = '\0';


        std::cout << "DEBUG: Writing to file - ID: " << emp.num
            << ", Name: " << emp.name
            << ", Hours: " << emp.hours << std::endl;

        out.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    out.close();
    std::cout << "\nFile \"" << filename << "\" created successfully.\n";
    return 0;
}
