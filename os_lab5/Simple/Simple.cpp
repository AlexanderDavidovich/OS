#include <windows.h>
#include <iostream>
#include <vector>

bool isPrime(__int32 n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (__int32 i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    // Получаем дескрипторы канала
    HANDLE hReadPipe = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hWritePipe = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hReadPipe == INVALID_HANDLE_VALUE || hWritePipe == INVALID_HANDLE_VALUE) {
        std::cerr << "GetStdHandle failed: " << GetLastError() << std::endl;
        return 1;
    }

    // Открываем мьютекс для синхронизации
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"Global\\PrimeNumbersMutex");
    if (hMutex == NULL) {
        std::cerr << "OpenMutex failed: " << GetLastError() << std::endl;
        return 1;
    }

    // Получаем размер массива от процесса Server
    int size;
    DWORD bytesRead;
    WaitForSingleObject(hMutex, INFINITE);
    if (!ReadFile(hReadPipe, &size, sizeof(size), &bytesRead, NULL) || bytesRead != sizeof(size)) {
        std::cerr << "ReadFile failed: " << GetLastError() << std::endl;
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        return 1;
    }
    ReleaseMutex(hMutex);

    std::cout << "Received array size: " << size << std::endl;

    // Генерируем простые числа и передаем их процессу Server
    __int32 current = 2;
    DWORD bytesWritten;

    for (int i = 0; i < size; ) {
        if (isPrime(current)) {
            WaitForSingleObject(hMutex, INFINITE);
            if (!WriteFile(hWritePipe, &current, sizeof(current), &bytesWritten, NULL)) {
                std::cerr << "WriteFile failed: " << GetLastError() << std::endl;
                ReleaseMutex(hMutex);
                break;
            }
            ReleaseMutex(hMutex);

            std::cout << "Sent prime: " << current << std::endl;
            i++;
        }
        current++;
    }

    CloseHandle(hMutex);
    return 0;
}