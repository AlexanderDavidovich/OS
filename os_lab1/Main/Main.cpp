#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct employee {
    int num;
    char name[10];
    double hours;
};

std::wstring ConvertToWideString(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
    return wstr;
}

void PrintBinaryFile(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        std::cerr << "Error opening file " << filename << " for reading.\n";
        return;
    }

    std::cout << "\nBinary file contents:\n";
    employee emp;
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(emp)))
    {
        std::cout << "ID: " << emp.num
            << ", Name: " << emp.name
            << ", Hours: " << emp.hours << "\n";
    }
    in.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string binaryFilename;
    int numRecords;

    std::cout << "Enter the name of the binary file: ";
    std::getline(std::cin, binaryFilename);

    std::cout << "Enter the number of records: ";
    std::cin >> numRecords;
    std::cin.ignore();

    //запуск креатор
    std::stringstream cmdCreator;
    cmdCreator << "Creator.exe " << binaryFilename << " " << numRecords;
    std::wstring wCmdCreator = ConvertToWideString(cmdCreator.str());

    STARTUPINFO siCreator = { sizeof(siCreator) };
    PROCESS_INFORMATION piCreator;
    ZeroMemory(&piCreator, sizeof(piCreator));

    if (!CreateProcess(NULL, &wCmdCreator[0], NULL, NULL, FALSE, 0, NULL, NULL, &siCreator, &piCreator))
    {
        std::cerr << "Error launching Creator.\n";
        return 1;
    }

   
    WaitForSingleObject(piCreator.hProcess, INFINITE);
    CloseHandle(piCreator.hProcess);
    CloseHandle(piCreator.hThread);

    
    PrintBinaryFile(binaryFilename);

    std::string reportFilename;
    double hourlyRate;
    std::cout << "\nEnter the name of the report file: ";
    std::getline(std::cin, reportFilename);
    std::cout << "Enter the hourly rate: ";
    std::cin >> hourlyRate;

    //запуск репортер
    std::stringstream cmdReporter;
    cmdReporter << "Reporter.exe " << binaryFilename << " " << reportFilename << " " << hourlyRate;
    std::wstring wCmdReporter = ConvertToWideString(cmdReporter.str());

    STARTUPINFO siReporter = { sizeof(siReporter) };
    PROCESS_INFORMATION piReporter;
    ZeroMemory(&piReporter, sizeof(piReporter));

    if (!CreateProcess(NULL, &wCmdReporter[0], NULL, NULL, FALSE, 0, NULL, NULL, &siReporter, &piReporter))
    {
        std::cerr << "Error launching Reporter.\n";
        return 1;
    }

    
    WaitForSingleObject(piReporter.hProcess, INFINITE);
    CloseHandle(piReporter.hProcess);
    CloseHandle(piReporter.hThread);

   
    std::ifstream reportFile(reportFilename);
    if (!reportFile)
    {
        std::cerr << "Error opening report file " << reportFilename << " for reading.\n";
    }
    else
    {
        std::cout << "\nReport file contents:\n";
        std::string line;
        while (std::getline(reportFile, line))
        {
            std::cout << line << "\n";
        }
        reportFile.close();
    }

    return 0;
}
