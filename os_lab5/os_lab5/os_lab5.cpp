#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Создаем анонимный канал
    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        std::cerr << "CreatePipe failed: " << GetLastError() << std::endl;
        return 1;
    }

    // Создаем мьютекс для синхронизации
    HANDLE hMutex = CreateMutex(NULL, FALSE, L"Global\\PrimeNumbersMutex");
    if (hMutex == NULL) {
        std::cerr << "CreateMutex failed: " << GetLastError() << std::endl;
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        return 1;
    }

    // Настраиваем параметры запуска Simple.exe
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    si.hStdInput = hReadPipe;
    si.hStdOutput = hWritePipe;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.dwFlags |= STARTF_USESTDHANDLES;

    // Запускаем процесс Simple.exe
    if (!CreateProcess(
        L".\\Simple.exe",
        NULL, NULL, NULL,
        TRUE,  // Дескрипторы наследуются
        0, NULL, NULL,
        &si, &pi
    )) {
        std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        CloseHandle(hMutex);
        return 1;
    }

    // Закрываем ненужные дескрипторы
    CloseHandle(hReadPipe);
    CloseHandle(pi.hThread);

    // Вводим размер массива
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    // Передаем размер массива процессу Simple
    DWORD bytesWritten;
    
    if (!WriteFile(hWritePipe, &size, sizeof(size), &bytesWritten, NULL)) {
        std::cerr << "WriteFile failed: " << GetLastError() << std::endl;
        ReleaseMutex(hMutex);
        CloseHandle(hWritePipe);
        CloseHandle(pi.hProcess);
        CloseHandle(hMutex);
        return 1;
    }
    

    std::cout << "Sent array size: " << size << std::endl;

    // Получаем простые числа от процесса Simple
    std::vector<__int32> primes;
    __int32 num;
    DWORD bytesRead;

    for (int i = 0; i < size; ++i) {
        WaitForSingleObject(hMutex, INFINITE);
        if (!ReadFile(hReadPipe, &num, sizeof(num), &bytesRead, NULL) || bytesRead != sizeof(num)) {
            std::cerr << "ReadFile failed: " << GetLastError() << std::endl;
            ReleaseMutex(hMutex);
            break;
        }
        ReleaseMutex(hMutex);

        primes.push_back(num);
        std::cout << "Received prime: " << num << std::endl;
    }

    // Закрываем дескрипторы
    CloseHandle(hWritePipe);
    CloseHandle(pi.hProcess);
    CloseHandle(hMutex);

    return 0;
}