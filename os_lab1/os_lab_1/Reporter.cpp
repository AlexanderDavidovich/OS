#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[])
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <binary_file> <report_file> <hourly_rate>\n";
        return 1;
    }

    const char* binaryFilename = argv[1];
    const char* reportFilename = argv[2];
    double rate = std::atof(argv[3]);

    std::ifstream in(binaryFilename, std::ios::binary);
    if (!in)
    {
        std::cerr << "Error opening file " << binaryFilename << " for reading.\n";
        return 1;
    }

    std::vector<employee> employees;
    employee emp;
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(emp)))
    {
        
        std::cout << "DEBUG: Read from file - ID: " << emp.num
            << ", Name: " << emp.name
            << ", Hours: " << emp.hours << std::endl;

        employees.push_back(emp);
    }
    in.close();

    std::sort(employees.begin(), employees.end(), [](const employee& a, const employee& b) {
        return a.num < b.num;
        });

    std::ofstream out(reportFilename);
    if (!out)
    {
        std::cerr << "Error opening file " << reportFilename << " for writing.\n";
        return 1;
    }

    out << "Report for file \"" << binaryFilename << "\"\n";
    out << "ID\t\tName\t\tHours\tSalary\n";

    for (const auto& e : employees)
    {
        double salary = e.hours * rate;
        out << e.num << "\t\t" << e.name << "\t\t" << e.hours << "\t" << salary << "\n";
    }

    out.close();
    std::cout << "Report successfully created in \"" << reportFilename << "\".\n";
    return 0;
}
